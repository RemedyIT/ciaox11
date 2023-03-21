#--------------------------------------------------------------------
# @file    component.rb
# @author  Marijke Hengstmengel
#
# @brief   Component recipes
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------
require 'set'

module AxciomaPC
  class ComponentRecipe < Recipe
    class Base_Projects
      attr_reader :plus , :min, :default
      # min contains the projects that has to be removed from the final list
      # plus contains the projects that has to be added to the final list
      # default contains the projects that will replace the default projects

      def initialize(defbases = nil)
        @plus = Util::UniqueStringList.new(:ws)
        @min = Util::UniqueStringList.new(:ws)
        @default = Util::UniqueStringList.new(:ws, defbases)
      end

      def dup
        bp_new = self.class.new
        bp_new.plus.assign(plus)
        bp_new.min.assign(min)
        bp_new.default.assign(default)
        bp_new
      end

      def -(val)
        bp_new = dup
        bp_new.min << val
        bp_new
      end

      def +(val)
        bp_new = dup
        bp_new.plus << val
        bp_new
      end

      def assign(bp)
        min.assign(bp.min)
        plus.assign(bp.plus)
        default.assign(bp.default)
      end
    end # Base_Projects

    class << self
      def interaction_handlers
        @interaction_handlers ||= {}
      end
      private :interaction_handlers

      def interaction_patterns
        interaction_handlers.keys
      end

      def register_interaction_handler(pattern, handler)
        interaction_handlers[pattern.to_s.to_sym] = handler
      end

      def handle_interaction_setup(recipe, interaction_type)
        interaction_handlers[interaction_type].setup_component(recipe) if interaction_handlers.has_key?(interaction_type)
      end

      def handle_interaction_dependencies(recipe, interaction_type, project_dependencies)
        interaction_handlers[interaction_type].process_component_dependencies(recipe, project_dependencies) if interaction_handlers.has_key?(interaction_type)
      end
    end

    class ComponentConfigurator < Recipe::Configurator
      def initialize(recipe)
        super
      end

      def generate_exec(generate_exec)
        @recipe.generate_exec(generate_exec)
      end

      def combined_lib(flag)
        @recipe.combined_lib = (flag == true)
      end

      def includes(*dirs)
        # Solve event. used environment variables
        solved_dirs = dirs.flatten.collect { |dir| Util::path_without_env(dir) }
        @recipe.include_dirs << solved_dirs.flatten.collect { |dir| File.expand_path(dir, @recipe.recipe_file.path) }
        @recipe.include_dirs
      end

      def libpaths(*paths)
        # Solve event. used environment variables
        solved_paths = paths.flatten.collect { |path| Util::path_without_env(path) }
        @recipe.lib_paths << solved_paths.flatten.collect { |p| File.expand_path(p, @recipe.recipe_file.path) }
      end

      def libs(*libs)
        @recipe.libs << libs.flatten
      end

      def lit_libs(*libs)
        @recipe.lit_libs << libs.flatten
      end

      # when called in case of += or  -= in the recipe 'val' is empty
      # and the recipes Base_Projects instance is returned
      # when called with a(n) (list of) argument(s) the arguments
      # are used to initialize a new Base_Projects instance with the
      # arguments as defaults
      def base_projects(*val)
        if !val.empty?
          @recipe.base_projects.assign(Base_Projects.new(val.flatten))
        else
          @recipe.base_projects
        end
      end

      # This is called in case of += or -= with a single Base_Project instance as argument
      # or in case of = with a(n) (list of) argument(s) used to initialize a new Base_Projects
      # instance with the arguments as new defaults
      def base_projects=(*val)
        if val.size == 1 && Base_Projects === val.first
          @recipe.base_projects.assign(*val)
        else
          @recipe.base_projects.assign(Base_Projects.new(val.flatten))
        end
      end

      def define(comp_def, &_block)
        if block_given?
          @recipe.define(comp_def, &_block)
        else
          @recipe.define(comp_def)
        end
      end
    end

    CONFIGURATOR = ComponentConfigurator

    attr_reader :comp_name

    def initialize(rcpfile, name, *features, &block)
      super(rcpfile, name)
      @type = :component
      @include_dirs = Util::UniqueStringList.new(:ws)
      @lib_paths = Util::UniqueStringList.new(:ws)
      @libs = Util::UniqueStringList.new(:ws)
      @lit_libs = Util::UniqueStringList.new(:ws)
      @compdef = nil
      # only configure if required features match
      configure(&block) if check_features(*features)
    end

    def define(comp_def, &_block)
      @comp_name = comp_def
      if block_given?
        @compdef = ComponentDefinition.new(self, &_block)
      else
        @compdef = ComponentDefinition.new(self)
      end
    end

    def verify
      if @compdef
        @compdef.verify
      else
        idl_files.each_value do |fidl|
          fidl.recipes << self unless fidl.recipes.include?(self)
        end
      end
    end

    def generate_exec(generate_exec)
      @gen_exec = generate_exec
    end

    def generate_exec?
      @gen_exec
    end

    def combined_lib=(f)
      @combined_lib = f
    end

    def combined_lib?
      @combined_lib == true
    end

    def include_dirs(paths = nil)
      @include_dirs.assign(paths) if paths
      @include_dirs
    end

    def lib_paths(paths = nil)
      @lib_paths.assign(paths) if paths
      @lib_paths
    end

    def libs(libs = nil)
      @libs.assign(libs) if libs
      @libs
    end

    def lit_libs(libs = nil)
      @lit_libs.assign(libs) if libs
      @lit_libs
    end

    def base_projects
      @base_projects ||= Base_Projects.new
    end

    # add IDLFile, override for component
    def add_idl_file(idl_file, name = nil)
       # IDLFiles listed by component recipes are not managed
       # so we do not register the recipe with the IDLFile,
       # unless it is the component idl file self.
       # this is done later in recipe #verify
       @idl_files[name || idl_file.full_path] = idl_file
    end

    def to_s
      "APC::ComponentRecipe{#{recipe_id}}"
    end

    def dump(indent = 0, out = STDERR)
      super(indent, out, "shared_name: [#{@shared_name}] export_name: [#{@export_name}]")
    end

    def handle_interaction_setup(interaction_type)
      self.class.handle_interaction_setup(self, interaction_type)
    end
    protected :handle_interaction_setup

    def handle_interaction_dependencies(interaction_type, project_dependencies)
      self.class.handle_interaction_dependencies(self, interaction_type, project_dependencies)
    end
    protected :handle_interaction_dependencies

    #================================================================
    # Project preparation setup phase specialization

    # setup the MPC projects for this recipe and collect and process
    # all required interaction types for the component
    def setup_projects
      BRIX11.log(3, "[%s] setup projects", self)

      # collect all interaction types recorded for all included IDL files
      # setup their corresponding recipes for the interaction types
      interaction_types = Set.new
      # idl file for component
      @idl_files.each_value do |fidl|
        BRIX11.log(4, '[%s] %s', self, fidl)
        fidl.includes.each do |ifidl|
          # only of interest if a member of this project (and thus part of a recipe)
          if ifidl.is_member?
            BRIX11.log(4, '[%s] %s specifies %s interactions', self, ifidl, ifidl.interaction_types.to_a)
            # an empty interaction types set means non-specific port which must be SRR
            ifidl.interaction_types << :srr if ifidl.interaction_types.empty?

            # collect the interaction types for this include
            interaction_types.merge(ifidl.interaction_types)

            # setup the recipe of this IDL include for the recorded interaction types
            rcp = ifidl.recipes.first
            rcp.setup_project_interaction(ifidl, *ifidl.interaction_types.to_a)
          end
        end
      end

      # create the MPC projects for this recipe itself
      mpc_obj = create_comp_gen
      mpc_file.add_mpc_project(mpc_obj)

      unless self.combined_lib?
        if self.needs_stub?
          mpc_obj = create_stub_comp
          mpc_file.add_mpc_project(mpc_obj)
        end

        mpc_obj = create_lem_comp
        mpc_file.add_mpc_project(mpc_obj)

        mpc_obj = create_svnt_comp
        mpc_file.add_mpc_project(mpc_obj)
      end

      mpc_obj = create_exec_lib
      mpc_file.add_mpc_project(mpc_obj)

      # Until now all components have the above mentioned mpc projects
      # Maybe in the future this must move to interaction specific component handling

      @compdef.setup_projects if @compdef

      # handle interaction specific project setup for each (unique)
      # collected transaction type
      interaction_types.each do |int_type|
        handle_interaction_setup(int_type)
      end
    end

    #================================================================
    # Project preparation dependency processing phase

    # collect and process project dependencies for referenced
    # project files
    def process_project_dependencies
      BRIX11.log(3, '[%s] process project dependencies', self)
      # collect all interaction types and the project dependencies
      interaction_types = Set.new
      project_dependencies = MPC::Dependencies.new
      @idl_files.each_value do |fidl|
        BRIX11.log(4, "[#{self}] #{fidl}")
        fidl.includes.each do |ifidl|
          if ifidl.is_member?
            BRIX11.log(4, "[#{self}] #{ifidl}")
            interaction_types.merge(ifidl.interaction_types)
            rcp = ifidl.recipes.first
            rcp.get_dependencies(ifidl, ifidl.interaction_types, project_dependencies)
          end
        end
      end

      # process dependencies for MPC projects for this recipe
      setup_comp_gen(project_dependencies)

      if self.needs_stub?
        setup_stub_comp(project_dependencies)
      end

      setup_lem_comp(project_dependencies)
      setup_svnt_comp(project_dependencies)
      setup_exec_lib(project_dependencies)

      # process interaction specific project dependencies for
      # each (unique) collected transaction type
      interaction_types.each do |int_type|
        handle_interaction_dependencies(int_type, project_dependencies)
      end
    end

    #================================================================
    # MPC project creation methods

    def create_comp_gen
      MPC::IDLProject.new(:comp_gen, self)
    end
    protected :create_comp_gen

    def create_stub_comp
      MPC::CompStubProject.new(self)
    end
    protected :create_stub_comp

    def create_lem_comp
      MPC::CompLemStubProject.new(self)
    end
    protected :create_lem_comp

    def create_svnt_comp
      MPC::SvntProject.new(self)
    end
    protected :create_svnt_comp

    def create_exec_lib
      MPC::ExecProject.new(self, self.combined_lib?)
    end
    protected :create_exec_lib

    def setup_comp_gen(project_dependencies)
      BRIX11.log(4, '[%s] setup_comp_gen: project_dependencies = %s', self, project_dependencies)
      mpc_obj = mpc_file[:comp_gen]
      @idl_files.collect { |n, f| mpc_obj.add_project_file(f.full_path) }

      # idl_includes: idl in recipe self, concat with includes given in project root aprc file
      mpc_obj.includes << idl_includes << project.idl_includes
      mpc_obj.add_dependencies(project_dependencies, :lem_gen)

      mpc_obj.base_projects << 'taox11_anytypecode' if self.needs_anytype?

      if self.needs_stub? && self.creates_stubcode?
        mpc_obj.set_stub_flags
      end
      if self.has_ttc?
        mpc_obj.base_projects << %w(ciaox11_tt4ccm)
      end
      mpc_obj
    end
    protected :setup_comp_gen

    def setup_stub_comp(project_dependencies)
      mpc_obj = mpc_file[self.combined_lib? ? :exec : :comp_stub]
      mpc_obj.add_dependencies(project_dependencies, :stub)
      if self.has_ttc?
        mpc_obj.base_projects << %w(ciaox11_tt4ccm_stub)
      end
      mpc_obj
    end
    protected :setup_stub_comp

    def setup_lem_comp(project_dependencies)
      mpc_obj = mpc_file[self.combined_lib? ? :exec : :comp_lem]
      mpc_obj.add_dependencies(project_dependencies, :lem_stub)
      if (!self.combined_lib?) && self.needs_stub? && self.creates_stubcode?
        mpc_obj.set_stub
      end
      if self.has_ttc?
        mpc_obj.base_projects << %w(ciaox11_tt4ccm_stub)
      end
      mpc_obj
    end
    protected :setup_lem_comp

    def setup_exec_lib(project_dependencies)
      mpc_obj = mpc_file[:exec]
      mpc_obj.add_dependencies(project_dependencies, :lem_stub, false)
      # include paths, lib_paths and libs given in recipe:
      mpc_obj.includes << include_dirs << project.include_dirs
      mpc_obj.lib_paths << lib_paths << project.lib_paths
      mpc_obj.link_libs << libs + project.libs
      mpc_obj.link_lit_libs << lit_libs + project.lit_libs

      if (!self.combined_lib?) && self.needs_stub? && self.creates_stubcode?
        mpc_obj.set_stub
      end
      if self.has_ttc?
        mpc_obj.base_projects << %w(ciaox11_tt4ccm_stub)
      end
      mpc_obj
    end
    protected :setup_exec_lib

    def setup_svnt_comp(project_dependencies)
      return if self.combined_lib?

      mpc_obj = mpc_file[:comp_svnt]
      mpc_obj.add_dependencies(project_dependencies, :lem_stub, false)

      if (!self.combined_lib?) && self.needs_stub? && self.creates_stubcode?
        mpc_obj.set_stub
      end
      if self.has_ttc?
        mpc_obj.base_projects << %w(ciaox11_tt4ccm_stub)
      end
      mpc_obj
    end
    protected :setup_svnt_comp

    # IDL scanner hook for component IDL
    def check_idl_node(idl_scanner, node, delegator)
      case node
      when IDL::AST::Component
        node.ports.each do |p|
          if p.porttype == :facet
            # find IDL file chain providing port interface type
            enc = p.idltype.node.enclosure
            while enc
              if IDL::AST::Include === enc
                # register IDL file if not yet done
                ifidl = project.add_idl_file(enc.fullpath)
                BRIX11.log(4, '[%s] IDL scan found port %s from %s', self, p.scoped_name, ifidl)
                if ifidl.is_member?
                  # found an included project IDL file needing LEM generation
                  # mark for LEM generation
                  ifidl.properties[:needs_lem] = true
                end
              end
              enc = enc.enclosure
            end
          end
        end
        # check any attributes on this IDL Component
        check_attributes_for_anytypecode(idl_scanner, node)
      when IDL::AST::Module,
           IDL::AST::ComponentBase,
           IDL::AST::Porttype,
           IDL::AST::TemplateModule
        # nothing
      else
        idl_scanner.properties[:needs_stub] = true
        ### MUST generate stubs from component IDL
      end
    end

    def find_include_for_node(n)
      enc = n.enclosure
      while enc
        return enc if IDL::AST::Include === enc

        enc = enc.enclosure
      end
      nil
    end
    private :find_include_for_node

    def check_attributes_for_anytypecode(idl_scanner, node)
      # Attributes from components and attributes from mirror ports are needed,
      # so we can't use node.attributes, but we have to walk the members self.
      attrs = []
      node.walk_members do |m|
        if m.is_a?(IDL::AST::Attribute)
          attrs << m
        elsif
          m.is_a?(IDL::AST::Port) && m.porttype == :mirrorport
          attrs.concat m.attributes
        end
      end

      # find all attributes with types requiring AnyTypeCode support
      attrs.each do |a|
        BRIX11.log(5, '[%s] IDL scan checking attribute %s %s for component %s', self, a.idltype.typename, a.cxxname, node.cxxname)

        look_for_members = false # remember if need to recurse type members as well
        anytypecode_needed = false

        case a.idltype.resolved_type
          when IDL::Type::Struct,
               IDL::Type::Union,
               IDL::Type::Valuetype,
               IDL::Type::Enum
            look_for_members = true unless a.idltype.resolved_type.is_a?(IDL::Type::Enum)
            anytypecode_needed = true
          when IDL::Type::Sequence,
               IDL::Type::Array
            # in case of complex sequence or array anytypecode is needed
            case a.idltype.resolved_type.basetype.resolved_type
              when IDL::Type::Struct,
                   IDL::Type::Union,
                   IDL::Type::Valuetype,
                   IDL::Type::Enum,
                   IDL::Type::Sequence,
                   IDL::Type::Array
                 look_for_members = true
                 anytypecode_needed = true
            end
        end

        if anytypecode_needed
          # look up idl file of attribute (if any)
          inc = find_include_for_node(a.idltype.node)
          if !inc
            # data for attribute in component idl file self
            idl_scanner.properties[:needs_anytype] = true
            ### MUST also generate stubs from component IDL, but this property is set above
          else
            process_anytypecode_include(inc)
          end
        end

        # Now look for members of complex types, because they can be located in other idl files,
        # and this idl file should then also use anytypecode.
        if look_for_members
          type = a.idltype.resolved_type
          check_for_anytypecode_include(type)
        end
      end # each attribute
    end
    private :check_attributes_for_anytypecode

    # check complex data members for anytypecode includes
    def check_for_anytypecode_include(type)
      case type
        when IDL::Type::Struct, IDL::Type::Union, IDL::Type::Valuetype
          type.node.members.each do |m|
            inc = nil
            unless m.idltype.is_standard_type?
              inc = find_include_for_node(m.idltype.node)
              # check include if found
              process_anytypecode_include(inc) if inc
              # recurse for members of complex member type
              mtype = m.idltype.resolved_type
              check_for_anytypecode_include(mtype)
            end
          end
        when IDL::Type::Sequence, IDL::Type::Array
          inc = nil
          mtype = type.basetype.resolved_type
          unless mtype.is_standard_type?
            case mtype
              when IDL::Type::Struct, IDL::Type::Union, IDL::Type::Valuetype
                inc = find_include_for_node(type.basetype.resolved_type.node)
                # check include if found
                process_anytypecode_include(inc) if inc
            end
            check_for_anytypecode_include(mtype)
          end
        else
          # no further checks needed
      end
    end
    private :check_for_anytypecode_include

    def process_anytypecode_include(inc)
      # add to IDL registry if not yet done
      fidl = project.add_idl_file(inc.fullpath)
      # no need to register anything else if include is not a project member
      if fidl.is_member?
        # found an included project IDL file needing anytypecode
        # mark for anytypecode generation
        fidl.properties[:needs_anytype] = true
      end
    end
    private :process_anytypecode_include

    def needs_anytype?
      @idl_files.each_value.any? { |val|val.needs_anytype? }
    end

    def has_ttc?
      @idl_files.each_value.any? { |val|val.has_ttc? }
    end

    def needs_stub?
      @idl_files.each_value.any? { |val|val.needs_stub? }
    end

    def creates_stubcode?
      @idl_files.each_value.any? { |val| val.creates_stubcode? || val.needs_anytype? }
    end
  end

  Recipe.register_recipe(:component, ComponentRecipe)
end

# load specializations and extensions
Dir.glob(File.join(File.dirname(__FILE__), 'component', '*.rb')).each do |fnm|
  require fnm
end
