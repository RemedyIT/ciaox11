#--------------------------------------------------------------------
# @file    scanidlfile.rb
# @author  Marijke Hengstmengel
#
# @brief   Scan  for idl files
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------

module AxciomaPC
  class IDLFileScanner
    class IDLScanner

      def initialize(recipe, fidl)
        @recipe = recipe
        @fidl = fidl
        @ports = {}
        @ports_facet = {}
      end

      def recipe
        @recipe
      end

      def idl_file
        @fidl
      end

      def properties
        @fidl.properties
      end

      def project
        @recipe.project
      end

      def idl_includes
        @fidl.includes
      end

      def visit_nodes(delegator)
        check_node(delegator.root, delegator)
      end

      def check_node(node, delegator)
        if IDL::AST::Include === node
          if node.filename != 'orb.idl'
            if node.filename == 'ccm_timed_trigger.idl'
              # register the use of timed-trigger-connectors by a component, so
              # extra mpc base projects can be added later on.
              # No deed to register this include with the idl_includes.
              properties[:has_ttc] = true;
            else
              # register IDL file if not yet done
              ifidl = project.add_idl_file(node.fullpath)
              # add to include list for current IDL file
              idl_includes << ifidl
            end
          end
        elsif IDL::AST::Module === node
          # recurse into IDL Module
          node.walk_members do |n|
            check_node(n, delegator)
          end
        else
          # check for special IDL generation properties of data nodes
          case node
          when IDL::AST::Interface,
               IDL::AST::Struct,
               IDL::AST::Union,
               IDL::AST::Valuetype,
               IDL::AST::Valuebox,
               IDL::AST::Enum
            # generation for these nodes *always* creates stubcode (not inline)
            properties[:creates_stubcode] = true
            # only interfaces and valuetypes needs skel, so set flag if node is one of these
            if IDL::AST::Interface === node
              properties[:needs_skel] = true
              # register the presence of an interface because only then we need lem generation later on
              properties[:has_interface] = true
            elsif IDL::AST::Valuetype === node
              properties[:needs_skel] = true
            end
          when IDL::AST::Typedef
            aliased_type = node.idltype.resolved_type
            case aliased_type
            when IDL::Type::String,
                 IDL::Type::WString
              # generation for bounded strings also always creates stubcode (not inline)
              properties[:creates_stubcode] = !aliased_type.size.nil?
            end
          end
        end
        # call recipe specific checks
        @recipe.check_idl_node(self, node, delegator)
      end

    end # IDLScanner

    def initialize(recipe)
      @recipe = recipe
      @ridl_opts = {
          client_stubs: false,
          svnt_skeletons: false,
          xincludepaths: [],  # quoted includes
          includepaths: []    # all includes ("" and <>)
      }

      # include system paths
      taox11_root = BRIX11::Exec.get_run_environment('TAOX11_ROOT')
      ciaox11_root = BRIX11::Exec.get_run_environment('CIAOX11_ROOT')
      # make sure include paths always end with '/'
      @ridl_opts[:includepaths] << (taox11_root.end_with?('/', '\\') ? taox11_root : taox11_root + '/')
      @ridl_opts[:includepaths] << (ciaox11_root.end_with?('/', '\\') ? ciaox11_root : ciaox11_root + '/')
      @ridl_opts[:includepaths] << (File.join(ciaox11_root, 'ccm') + '/')
      @ridl_opts[:includepaths] << (File.join(ciaox11_root, 'connectors/tt4ccm/idl') + '/')

      # # recipe specific includes
      # @ridl_opts[:xincludepaths].concat(@recipe.recipe_idl_includes.collect {|inc| inc.end_with?('/', '\\') ? inc : inc+'/' })

      # user defined project includes
      @ridl_opts[:xincludepaths].concat(@recipe.project.idl_includes.collect { |inc| inc.end_with?('/', '\\') ? inc : inc + '/' })

      # user defined recipe includes
      @ridl_opts[:xincludepaths].concat(@recipe.idl_includes.collect { |inc| inc.end_with?('/', '\\') ? inc : inc + '/' })
    end

    def scan_idl_file(idl_file)
      @is = IDLScanner.new(@recipe, idl_file)
      scan_idl_file_i(idl_file)
    end

    def scan_idl_file_i(idl_file)
      BRIX11.log(4, "[%s] Start scanning idl file %s", self.class.name, idl_file)

      # setup scan options for this idl file
      scan_opts = @ridl_opts.dup
      scan_opts[:includepaths] = @ridl_opts[:includepaths].dup.concat(idl_file.properties[:includepaths]) if idl_file.properties[:includepaths]
      scan_opts[:macros] = idl_file.properties[:macros].dup if idl_file.properties[:macros]

      begin
        # store current project for JIT IDL support
        Thread.current[:apc_project] = @recipe.project
        parser = BRIX11::ERIDL.parse('ccmx11', idl_file.full_path, scan_opts)
        raise "ERROR in  idl file #{idl_file.full_path}" unless parser
        parser.visit_nodes(@is)
      ensure
        # reset current project reference
        Thread.current[:apc_project] = nil
      end

      BRIX11.log(4, '[%s] Found idl includes : [%s]', self.class.name, idl_file.includes.join(','))

      # mark IDL file object as scanned
      idl_file.set_scanned
      idl_file
    end
    protected :scan_idl_file_i
  end # IDLFileScanner

  class IDLFileScannerType < IDLFileScanner
    class IDLScannerType < IDLFileScanner::IDLScanner

      def initialize(recipe, fidl, type_name, &type_check)
        super(recipe, fidl)
        @scoped_type_name = type_name
        @type_check = block_given? ? type_check : nil
        @type_checked = false
        @type_found = false
        @inclvl = 0
      end

      def type_name
        @scoped_type_name
      end

      def type_check
        @type_check
      end

      def type_found
        @type_found
      end

      def check_node(node, delegator)
        # check for type if not yet found
        unless @type_checked || (IDL::AST::Module === node) || (type_name != node.scoped_name)
          @type_checked = true
          @type_found = type_check.call(node)
        end
        # only do full scan if not yet scanned yet
        if idl_file.has_been_scanned? || @inclvl > 0
          # otherwise recurse to check for type if not found yet
          if (!@type_checked) && IDL::AST::Module === node
            # recurse into IDL Module
            node.walk_members do |n|
              check_node(n, delegator)
              break if @type_checked
            end
          end
        else
          super
          # base scanner does not recurse includes so handle that here
          if (!@type_checked) && IDL::AST::Include === node
            @inclvl += 1
            check_node(node, delegator)
            @inclvl -= 1
          end
        end
      end

    end

    def idl_has_type?(idl_file, type_name, &type_check)
      @is = IDLScannerType.new(@recipe, idl_file, type_name, &type_check)
      scan_idl_file_i(idl_file)
      BRIX11.log(4, "[%s] Type %s %sfound", self.class.name, type_name, @is.type_found ? '' : 'NOT ')
      return @is.type_found
    end

  end

  class IDLFileScannerAttr < IDLFileScanner

    class IDLScannerAttr < IDLFileScanner::IDLScanner

      def initialize(recipe, fidl, type_name)
        super(recipe, fidl)
        @type_name = type_name
        @type_checked = false
        @type_found = false
        @inclvl = 0
      end

      def type_name
        @type_name
      end

      def type_found
        @type_found
      end

      def check_node(node, delegator)
        # check for type if not yet found
        unless @type_checked || (IDL::AST::Module === node) || (type_name != node.scoped_name)
          @type_checked = true
          @type_found = check_type(node.idltype.resolved_type)
        end
        # only do full scan if not yet scanned yet
        if idl_file.has_been_scanned?
          # otherwise recurse to check for type if not found yet
          if (!@type_checked) && IDL::AST::Module === node
            # recurse into IDL Module
            node.walk_members do |n|
              check_node(n, delegator)
              break if @type_checked
            end
          end
        else
          super
          # base scanner does not recurse includes so handle that here
          if (!@type_checked) && IDL::AST::Include === node
            @inclvl += 1
            check_node(node, delegator)
            @inclvl -= 1
          end
        end
      end

      def check_type(t)
        case t
          when IDL::Type::Struct,
               IDL::Type::Union,
               IDL::Type::Valuetype,
               IDL::Type::Enum
            true
        when IDL::Type::Sequence,
             IDL::Type::Array
            bt = t.basetype.resolved_type
            bt.is_pod? || check_type(bt)
        end
      end

    end

    def idl_has_attrib_def?(idl_file, type_name)
      @is = IDLScannerAttr.new(@recipe, idl_file, type_name)
      scan_idl_file_i(idl_file)
      BRIX11.log(4, "[%s] Type %s %sfound", self.class.name, type_name, @is.type_found ? '' : 'NOT ')
      return @is.type_found
    end

  end
end # AxciomaPC

# IDL::Scanner patch to provide support for including auto-generated IDL files
#
module IDL
  class Scanner

    def find_include_with_apcautogen(fname, all = true)
      # first check if IDL include already exists
      if fpinc = find_include_without_apcautogen(fname, all)
        # if found check for additionally required include paths and/or macros

        # get current APC project
        project = Thread.current[:apc_project]
        if project
          # get registered IDLFile
          idlfile = project.idl_files[fpinc]
          if idlfile
            @includepaths.concat(idlfile.properties[:includepaths]) if idlfile.properties[:includepaths]
            idlfile.properties[:macros].each { |k, v| @defined[k] = v } if idlfile.properties[:macros]
          end
        end
      else
        # if no IDL file found check if this is an APC autogenerated IDL file

        # get current APC project
        project = Thread.current[:apc_project]

        if project
          # find first registered matching autogen IDLFile
          if idlfile = project.match_idl_files(fname).find { |fidl| fidl.is_generated? }
            fpinc = idlfile.full_path
            # check for additionally required include paths and/or macros
            @includepaths.concat(idlfile.properties[:includepaths]) if idlfile.properties[:includepaths]
            idlfile.properties[:macros].each { |k, v| @defined[k] = v } if idlfile.properties[:macros]
          end
        end
      end
      fpinc
    end

    # create patched method chain
    alias_method_chain :find_include, :apcautogen

  end
end
