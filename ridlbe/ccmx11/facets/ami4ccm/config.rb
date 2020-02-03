#--------------------------------------------------------------------
# @file    config.rb
# @author  Marijke Hengstmengel
#
# @brief   IDL language mapping configuration for AMI4CCM
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------

module IDL

  module CCMX11

    module AMI4CCM
      COPYRIGHT = "Copyright (c) 2007-#{Time.now.year} Remedy IT Expertise BV, The Netherlands".freeze
      TITLE = 'RIDL CCMX11 AMI4CCM Facet'.freeze

      ## Configure facet
      #
      Backend::Facet.configure('ami4ccm', File.dirname(__FILE__), TITLE, COPYRIGHT, {major: 1, minor: 0, release: 0}) do |fctcfg|

        def self.add_extended_options(ol)
          ol.for_switch '-G{generation options}', :type => String, :separator => true do |swcfg|
            swcfg.for_group :ami4ccm_group do |grpcfg|
              grpcfg.on_prepare do |arg, params|
                if /^ami4ccm\,(.*)/ =~ arg
                  return [$1]
                end
                nil
              end
              # IMPORTANT When these flags are updated also update the AMI4CCM docs/src/ridlc.adoc
              # which is used for our user documentation
              grpcfg.for_params :strings,
                :params => {
                  'Aidl' => {:description => "-Gami4ccm,Aidl\t\tGenerate the AMI4CCM IDL and stubs",
                           :option_name => :gen_ami_idl},
                  'Aidl-only' => {:description => "-Gami4ccm,Aidl\t\tGenerate the AMI4CCM IDL only",
                           :option_name => :gen_ami_idl_only},
                  'idl' => {:description => "-Gami4ccm,idl\t\tGenerate all AMI4CCM connector IDL",
                           :option_name => :gen_ami_connector_idl},
                  'impl' => {:description => "-Gami4ccm,impl\t\tGenerate the AMI4CCM connector implementation",
                            :option_name => :gen_ami_connector_impl },
                  'lem' => {:description => "-Gami4ccm,lem\t\tGenerate the local executor mapping (lem) for AMI4CCM",
                           :option_name => :gen_lem_with_ami},
                  'svnt' => {:description => "-Gami4ccm,svnt\t\tGenerate the servant for AMI4CCM",
                            :option_name => :gen_component_servant_with_ami },
                  'conn' => {:description => "-Gami4ccm,conn\t\tGenerate all files needed for an AMI4CCM connector",
                            :option_name => :gen_amiconn_complete },
                  'conn_only' => {:description => "-Gami4ccm,conn_only\tGenerate all AMI4CCM dependent files needed for an AMI4CCM connector",
                              :option_name => :gen_amiconn_only_ami4ccm_complete },
                  'comp' => { :description => "-Gami4ccm,comp\t\tGeneration of all files/support needed for an AMI4CCM component",
                             :option_name => :gen_amicomp_complete},
                  'ex' => { :description => "-Gami4ccm,ex\t\tGeneration of AMI4CCM component executor support",
                            :option_name => :gen_component_executor_with_ami},
                }
            end # ami4ccm_group
          end
        end # add_extended_options

        # setup backend option handling
        #
        fctcfg.on_setup do |optlist, ridl_params|
          # defaults
          ridl_params[:gen_ami_connector_idl] = false
          ridl_params[:gen_ami_idl] = false
          ridl_params[:gen_ami_connector_impl] = false
          ridl_params[:gen_lem_with_ami] = false
          ridl_params[:gen_amiconn_complete] = false
          ridl_params[:gen_amiconn_only_ami4ccm_complete] = false
          ridl_params[:gen_amicomp_complete] = false
          ridl_params[:gen_component_servant_with_ami] = false
          ridl_params[:ami_idl_pfx] = 'A'
          ridl_params[:ami_idl_conn_pfx] = 'A_conn'
          ridl_params[:ami4ccm_pfx] = '_ami4ccm'

          IDL::CCMX11::AMI4CCM.add_extended_options(optlist)

        end

        # process input / generate code
        # arguments:
        #   in parser - parser object with full AST from parsed source
        #   in options - initialized option hash
        #
        fctcfg.on_process_input do |parser, options|
          # determine IDL file extension if not yet done
          idl_ext = (options[:idlext] ||= File.extname(options[:idlfile]))

          ##---------------------------------------------------------
          ## AMI4CCM toplevel, combination switches. These have to
          ## come first as they may trigger one or more of the
          ## following steps.

          # generate all files for a component using ami4ccm
          if options[:gen_amicomp_complete]
            IDL::CCMX11::AMI4CCM.gen_ami_component_complete(options, idl_ext)
          end

          # generate all files for an ami4ccm connector
          if options[:gen_amiconn_complete]
            IDL::CCMX11::AMI4CCM.gen_ami_connector_complete(options, idl_ext)
          end

          # generate only the ami4ccm facet dependent files for an ami4ccm connector
          if options[:gen_amiconn_only_ami4ccm_complete]
            IDL::CCMX11::AMI4CCM.gen_ami_connector_only_ami4ccm_complete(options, idl_ext)
          end

          ##---------------------------------------------------------
          ## AMI4CCM Interface related handling

          if options[:gen_ami_idl]
            IDL::CCMX11::AMI4CCM.gen_ami_idl(options, idl_ext)
          end

          if options[:gen_ami_idl_only]
            IDL::CCMX11::AMI4CCM.gen_ami_idl_only(options, idl_ext)
          end

          ##---------------------------------------------------------
          ## AMI4CCM Component related handling

          # Generate lem implementation ami4ccm component
          if (options[:gen_lem_with_ami])
            IDL::CCMX11::AMI4CCM.gen_ami_lem_idl(options, idl_ext)
          end

          # svnt generation ami component
          if (options[:gen_component_servant_with_ami])
            IDL::CCMX11::AMI4CCM.gen_ami_component_servant(options, idl_ext)
          end

          # executor generation ami component
          if (options[:gen_component_executor_with_ami])
            IDL::CCMX11::AMI4CCM.gen_ami_component_executor(options, idl_ext)
          end

          ##---------------------------------------------------------
          ## AMI4CCM Connector related handling

          if options[:gen_ami_connector_idl]
            IDL::CCMX11::AMI4CCM.gen_ami_connector_idl(options, idl_ext)
          end

          if options[:gen_ami_connector_impl]
            IDL::CCMX11::AMI4CCM.gen_ami_connector_impl(options, idl_ext)
          end

        end # fctcfg.on_process_input
      end # fctcfg

      #########################################################################
      ## AMI4CCM export macros/include handling
      ##

      def self.check_ami_lem_stub_export_params(options)
        options[:ami_lem_stub_export_macro] = options[:base_export_macro]+"_AMI4CCM_LEM_STUB" + options[:export_macro_pfx] unless options[:ami_lem_stub_export_macro] || options[:base_export_macro].nil?
        options[:ami_lem_stub_export_include] = options[:base_export_include]+"_ami4ccm_lem_stub" + options[:export_header_pfx] unless options[:ami_lem_stub_export_include] || options[:base_export_include].nil?
      end

      def self.check_conn_lem_stub_export_params(options)
        options[:conn_lem_stub_export_macro] = options[:base_export_macro]+"_LEM_STUB_AMI_CONN" + options[:export_macro_pfx] unless options[:conn_lem_stub_export_macro] || options[:base_export_macro].nil?
        options[:conn_lem_stub_export_include] = options[:base_export_include]+"_lem_stub_ami_conn" + options[:export_header_pfx] unless options[:conn_lem_stub_export_include] || options[:base_export_include].nil?
      end

      def self.check_ami_stub_export_params(options)
        options[:ami_stub_export_macro] = options[:base_export_macro]+"_AMI4CCM_STUB" + options[:export_macro_pfx] unless options[:ami_stub_export_macro] || options[:base_export_macro].nil?
        options[:ami_stub_export_include] = options[:base_export_include]+"_ami4ccm_stub" + options[:export_header_pfx] unless options[:ami_stub_export_include] || options[:base_export_include].nil?
      end

      #########################################################################
      ## AMI4CCM CONNECTOR handling
      ##

      # This method drives 3 input processing passes:
      # 1. the current (main) pass processing the base IDL file passed on the command line
      #    - during this pass the following generators (productions) are scheduled:
      #       I) xxxA_conn.idl (declaring the AMI4CCM templated connector instantiation)
      # 2. processing the xxxA_conn.idl file generated in the first pass
      #    - during this pass the following generators (productions) are scheduled:
      #       I) xxxA_connC.h generation (AMI4CCM connector stub header)
      #      II) xxxA_conn_exec.* generation (AMI4CCM connector executor implementation)
      #     III) export header for xxxA_conn_exec code
      #      IV) xxxA_conn_svnt.* generation (AMI4CCM connector context&executor locator)
      #       V) export header for xxxA_conn_svnt code
      #      VI) xxxA_connE.idl (AMI4CCM connector LEM)
      # 3. processing the xxxA_connE.idl file generated in the second pass
      #    - during this pass the following generators (productions) are scheduled:
      #       I) xxxA_connEC.* generation (AMI4CCM connector lem stubs)
      #      II) export header for xxxA_connEC code
      #
      # Only ami4ccm dependent files are generated in this operation, ami4ccm independent files
      # necessary for compiling the ami4ccm dependent files must already be present .
      def self.gen_ami_connector_only_ami4ccm_complete(options, idl_ext)
        # do this once
        options[:gen_amiconn_only_ami4ccm_complete]=false

        # check export directive parameters for derived generations
        IDL::CCMX11.check_lem_stub_export_params(options)
        check_ami_lem_stub_export_params(options)
        check_ami_stub_export_params(options)
        check_conn_lem_stub_export_params(options)

        #first pass , generate files from base idl
        IDL::CCMX11::AMI4CCM.gen_ami_connector_only_ami4ccm_base(options, idl_ext)

        # second pass, with as input the options from the first pass , with idlname *.idl
        # force new loop for generating files from the A_conn.idl file of the ami4ccm connector
        IDL::CCMX11::AMI4CCM.gen_ami_connector_complete_ami_conn_idl(options, idl_ext)

        # third pass, with as input the options from the fourth pass , with idlname *A_conn.idl
        # force new loop for generating files from the A_connE.idl file of the ami4ccm connector
        IDL::CCMX11::AMI4CCM.gen_ami_connector_complete_ami_conn_lem(options, idl_ext)
      end

      # setup the options for the first pass of #gen_ami_connector_only_ami4ccm_complete
      # this will only specify to schedule xxxA_conn.idl generation later in this pass
      def self.gen_ami_connector_only_ami4ccm_base(options, idl_ext)
        # first pass gen_ami_connector_complete for the base idl file

        # ami callback is taox11 functionality, no ami4ccm, so generate this elsewhere
        options[:gen_ami_callback] = false
        # we'll do this in later passes
        options[:gen_lem] = false
        options[:gen_component_servant] = false
        options[:gen_ami_connector_impl] = false

        # signal to schedule *A_conn.idl generation later in this pass
        options[:gen_ami_connector_idl] = true
      end

      ##=======================================================================

      # This method drives 3 input processing passes:
      # 1. the current (main) pass processing the base IDL file passed on the command line
      #    - during this pass the following generators (productions) are scheduled:
      #       I) xxxAmiC.* generation (CORBA AMI stubs/reply handlers)
      #      II) export header for AmiC code
      #     III) xxxA_conn.idl (declaring the AMI4CCM templated connector instantiation)
      # 2. processing the xxxA_conn.idl file generated in the first pass
      #    - during this pass the following generators (productions) are scheduled:
      #       I) xxxA_connC.h generation (AMI4CCM connector stub header)
      #      II) xxxA_conn_exec.* generation (AMI4CCM connector executor implementation)
      #     III) export header for xxxA_conn_exec code
      #      IV) xxxA_conn_svnt.* generation (AMI4CCM connector context&executor locator)
      #       V) export header for xxxA_conn_svnt code
      #      VI) xxxA_connE.idl (AMI4CCM connector LEM)
      # 3. processing the xxxA_connE.idl file generated in the second pass
      #    - during this pass the following generators (productions) are scheduled:
      #       I) xxxA_connEC.* generation (AMI4CCM connector lem stubs)
      #      II) export header for xxxA_connEC code
      #
      # All ami4ccm dependent files and ami4ccm independent files are generated in this operation
      # Except the A.idl file and it's derivatives
      def self.gen_ami_connector_complete(options, idl_ext)
        # do this once
        options[:gen_amiconn_complete]=false

        # check export directive parameters for derived generations
        IDL::CCMX11.check_lem_stub_export_params(options)
        check_ami_lem_stub_export_params(options)
        check_ami_stub_export_params(options)
        check_conn_lem_stub_export_params(options)

        # first pass , generate files from base idl
        IDL::CCMX11::AMI4CCM.gen_ami_connector_complete_base(options, idl_ext)

        # second pass, with as input the options from the first pass , with idlname *.idl
        # force new loop for generating files from the A_conn.idl file of the ami4ccm connector
        IDL::CCMX11::AMI4CCM.gen_ami_connector_complete_ami_conn_idl(options, idl_ext)

        # third pass, with as input the options from the previous pass , with idlname *A_conn.idl
        # force new loop for generating files from the A_connE.idl file of the ami4ccm connector
        IDL::CCMX11::AMI4CCM.gen_ami_connector_complete_ami_conn_lem(options, idl_ext)
      end

      # setup the options for the first pass of #gen_ami_connector_complete
      # this will:
      # - schedule xxxAmiC.* generation (CORBA AMI stubs/reply handlers)
      # - schedule export header generation for AmiC code
      # - specify to schedule xxxA_conn.idl generation later in this pass
      # the first two steps may be skipped in case explicit switches were specified and the
      # base backend processing handled this already (not usual)
      def self.gen_ami_connector_complete_base(options, idl_ext)
        # setup the current (first) pass of gen_ami_connector_complete for the base idl file

        # schedule AMI callback and export header generation as this is implicit here
        # unless explicit switches were specified and the base backend did this already (not usual)
        unless IDL.has_production?(:ami_stub_header)
          options[:gen_ami_callback] = true
          # generate ami stub exports if generating exports for connector
          options[:gen_export_sta] ||= (options.gen_export_svnt || options.gen_export_conn)
          IDL::Cxx11.check_ami_export_params(options)
          # schedule xxxAmiC.* generation
          IDL::Cxx11.generate_ami_support(options)
          # schedule AmiC export header generation
          IDL::Cxx11.gen_amic_export(options)
        end

        options[:gen_lem] = false
        options[:gen_component_servant] = false
        options[:gen_ami_connector_impl] = false

        # signal to schedule *A_conn.idl generation later in this pass
        options[:gen_ami_connector_idl] = true
      end


      ##=======================================================================

      # schedule an additional input processing pass from the xxxA_conn.idl
      # file to generate the connector implementation and it's LEM IDL
      # this will:
      # - process the xxxA_conn.idl file generated in the first pass and
      #   during this pass the following generators (productions) are scheduled:
      #       I) xxxA_connC.h generation (AMI4CCM connector stub header)
      #      II) xxxA_conn_exec.* generation (AMI4CCM connector executor implementation)
      #     III) export header for xxxA_conn_exec code
      #      IV) xxxA_conn_svnt.* generation (AMI4CCM connector context&executor locator)
      #       V) export header for xxxA_conn_svnt code
      #      VI) xxxA_connE.idl (AMI4CCM connector LEM)
      def self.gen_ami_connector_complete_ami_conn_idl(options, idl_ext)
        # setup and schedule the second pass of gen_ami_connector_complete for
        # generating files out of the A_conn.idl file of the ami4ccm connector

        # restore new (clean) options set for new input processing pass
        impl_opts = options.restore
        # keep core option values (like include paths, macros and such)
        impl_opts.copy!(options, IDL::CORE_OPTIONS)

        # copy needed export settings
        impl_opts.copy!(options,
                        :base_export_include, :base_export_macro,
                        :svnt_export_include, :svnt_export_macro, :svnt_export_file,
                        :conn_export_include, :conn_export_macro, :conn_export_file,
                        :gen_any_ops, :gen_typecodes, :gen_localintf_any_ops,
                        :gen_ostream_operators, :no_cdr_streaming)

        # get the *A_conn.idl name with the *.idl as input
        impl_opts[:idlfile] = IDL::CCMX11::AMI4CCM.acon_conn_idl(options, idl_ext)

        # Generate lem IDL
        impl_opts[:gen_lem] = true
        # generate connector servant and export header
        impl_opts[:gen_component_servant] = true
        # generate Ami connector impl and export header
        impl_opts[:gen_ami_connector_impl] = true
        # suppress skeleton generation
        impl_opts[:svnt_skeletons] = false
        # generate only stub header
        impl_opts[:no_client_source] = true
        impl_opts[:no_client_proxy] = true

        # schedule new input processor for *A_conn.idl
        IDL.push_input(impl_opts[:idlfile], impl_opts)
        impl_opts
      end

      # schedule an additional input processing pass from the xxxA_connE.idl
      # file to generate the connector LEM stubs
      # this will:
      # - process the xxxA_connE.idl file generated in the second pass and
      #   during this pass the following generators (productions) are scheduled:
      #       I) xxxA_connEC.* generation (AMI4CCM connector lem stubs)
      #      II) export header for xxxA_connEC code
      def self.gen_ami_connector_complete_ami_conn_lem(options, idl_ext)
        # setup and schedule the third pass of gen_ami_connector_complete,
        # for generating files out of the A_connE.idl file of the ami4ccm connector

        # restore new (clean) options set for new input processing pass
        impl_opts = options.restore
        # keep core option values (like include paths, macros and such)
        impl_opts.copy!(options, IDL::CORE_OPTIONS)

        # copy needed export settings
        impl_opts.copy!(options,
                        :base_export_include, :base_export_macro,
                        :stub_export_include, :stub_export_macro, :stub_export_file,
                        :lem_stub_export_include, :lem_stub_export_macro, :lem_stub_export_file,
                        :conn_lem_stub_export_include, :conn_lem_stub_export_macro,
                        :gen_any_ops, :gen_typecodes, :gen_localintf_any_ops,
                        :gen_ostream_operators, :no_cdr_streaming)

        # get the *A_connE.idl name with the *A_conn.idl as input
        impl_opts[:idlfile] = IDL::CCMX11.lem_output_file(options[:acon_conn_idl], options, idl_ext)

        # Only (lem) stub and conn_lem_stub_export file have to be generated from lem idl file
        impl_opts[:no_client_proxy] = true
        impl_opts[:svnt_skeletons] = false

        # generate the composite lem_stub_export if generating exports for connector
        impl_opts[:gen_export_st] ||= (options.gen_export_svnt || options.gen_export_conn)
        if impl_opts[:gen_export_st]
          impl_opts.copy!(options,
                          :stub_export_include, :stub_export_macro, :stub_export_file)
          # use composite lem_stub_export for stub generated of *A_connE.idl lem file
          if impl_opts[:conn_lem_stub_export_macro]
            impl_opts[:stub_export_macro] = impl_opts[:conn_lem_stub_export_macro]
          else
            if impl_opts[:lem_stub_export_macro]
              impl_opts[:stub_export_macro] = 'AMI_CONN_' + impl_opts[:lem_stub_export_macro]
            end
          end
          if impl_opts[:conn_lem_stub_export_include]
            impl_opts[:stub_export_include] = impl_opts[:conn_lem_stub_export_include]
            # we have a lem_stub_export_include, so don't use old value  of stub_export_file
            impl_opts.delete(:stub_export_file) if impl_opts.has_key?(:stub_export_file)
          else
            if impl_opts[:lem_stub_export_include]
              impl_opts[:stub_export_include] = 'ami_conn_' + impl_opts[:lem_stub_export_include]
              # we have a lem_stub_export_include, so don't use old value  of stub_export_file
              impl_opts.delete(:stub_export_file) if impl_opts.has_key?(:stub_export_file)
            end
            if impl_opts[:lem_stub_export_file]
              impl_opts[:stub_export_file]= 'ami_conn_' + impl_opts[:lem_stub_export_file]
            end
          end
        end
        IDL.push_input(impl_opts[:idlfile], impl_opts)
      end

      # determine xxxA_conn.idl filename for templated connector instantiation declaration
      def self.acon_conn_idl(options, idl_ext)
        options[:acon_conn_idl] = File.join(options.outputdir, File.basename(options[:idlfile], idl_ext)+options[:ami_idl_conn_pfx]+idl_ext)
      end

      # generate  xxxA_conn.idl and ami connector
      def self.gen_ami_connector_idl(options, idl_ext)
        AMI4CCM.load_ami4ccm_config

        IDL::CCMX11::AMI4CCM.acon_conn_idl(options, idl_ext)
        a_conn_idl_file = GenFile.new(options[:acon_conn_idl])

        # schedule Writer for *A_conn.idl
        IDL.push_production(
            :ami4ccm_conn_idl,
            ::IDL::CCMX11::AMI4CCM::AmiConnectorConnIDLWriter.new(a_conn_idl_file, options))
      end

      # generate  xxxA_conn_exec files from xxxA_conn.idl
      def self.gen_ami_connector_impl(options, idl_ext)
        AMI4CCM.load_ami4ccm_config

        options[:ami4ccm] = true
        options[:conn_exec_outputdir] = options.outputdir unless options[:conn_exec_outputdir]
        options[:conn_exec_output_hdr] = File.join(options[:conn_exec_outputdir], File.basename(options[:idlfile], idl_ext)+options[:comp_exec_pfx])
        options[:conn_exec_output_src] = options[:conn_exec_output_hdr]+options.src_ext
        options[:conn_exec_output_hdr] += options.hdr_ext

        conn_exec_h = GenFile.new(options[:conn_exec_output_hdr])
        conn_exec_src = GenFile.new(options[:conn_exec_output_src])

        # schedule AmiConnectorExecutor writers
        IDL.push_production(
            :ami4ccm_conn_header,
            ::IDL::CCMX11::AMI4CCM::AmiConnectorHeaderWriter.new(conn_exec_h, options))
        IDL.push_production(
            :ami4ccm_conn_source,
            ::IDL::CCMX11::AMI4CCM::AmiConnectorSourceWriter.new(conn_exec_src, options))

        if options[:gen_component_servant]
          # extend generic servant generators for AMI4CCM
          IDL.production(:comp_svnt_header).extend(IDL::CCMX11::Ami4ccmSvntConnectorHeaderExt)
          IDL.production(:comp_svnt_source).extend(IDL::CCMX11::Ami4ccmSvntConnectorSourceExt)
        end
      end

      #########################################################################
      ## AMI4CCM COMPONENT handling
      ##

      # This method drives 1-2 input processing passes:
      # 1. the current (main) pass processing the base IDL file passed on the command line
      #    - during this pass the following generators (productions) are scheduled
      #      (if not yet scheduled) and/or adapted for AMI4CCM:
      #       I) xxx_svnt.* generation (component context&executor locator)
      #      II) xxx_exec.* generation (component executor)
      #     III) xxxE.idl (component LEM)
      # 2. processing the xxxE.idl file generated in the first pass
      #    - during this pass the following generators (productions) are scheduled:
      #       I) xxxEC.* generation (component lem stubs)
      #      II) export header for xxxEC code
      #
      def self.gen_ami_component_complete(options, idl_ext)
        # generate lem stub exports if -Gxhlst or -Gxhex or -Gxhsv are specified
        options.gen_export_lem_stub ||= options.gen_export_ex || options.gen_export_svnt

        # schedule generation of lem idl&stubs if not yet done
        # (when -GComp or -Glem was specified since this should than be handled by
        #  the base backend)
        IDL::CCMX11.compile_lem_idl(options, idl_ext)

        # signal to generate component lem ,servant and executor with AMI4CCM extensions
        # later this pass
        # (need to extend the generic functionality in all these cases)
        # export directives/header generation is controlled by base backend based on
        # the specification of specific xxx_export_macro/_include switches and/or
        # base_export_macro/_include switches in combination with -GxhXX switches
        options[:gen_lem_with_ami] = true
        options[:gen_component_servant_with_ami] = true
        # only generate AMI executor specifics if -Gex is specified
        options[:gen_component_executor_with_ami] = (options[:gen_component_executor])
      end

      def self.gen_ami_lem_idl(options, idl_ext)
        AMI4CCM.load_ami4ccm_config

        # schedule lem IDL generation if not yet done in base backend
        IDL::CCMX11.gen_lem_idl(options, idl_ext)
        # extend generic lem IDL generation for AMI4CCM
        IDL.production(:lem_idl).extend(Ami4ccmLemExecutorIDLExt)
      end

      # extend the scheduled component servant generation for Async Request/Reply pattern
      def self.gen_ami_component_servant(options, idl_ext)
        AMI4CCM.load_ami4ccm_config

        # schedule component servant generation if not done yet
        IDL::CCMX11.gen_component_servant(options, idl_ext)
        # extend generic component servant generation for AMI4CCM
        IDL.production(:comp_svnt_header).extend(Ami4ccmSvntComponentHeaderExt)
        IDL.production(:comp_svnt_source).extend(Ami4ccmSvntComponentSourceExt)
      end

      # extend the scheduled component executor generation for Async Request/Reply pattern
      def self.gen_ami_component_executor(options, idl_ext)
        # explicit -Gex required
        unless options.gen_component_executor
          IDL.fatal("ERROR: it isn't allowed to use -Gami4ccm,ex without specifying -Gex")
        end

        AMI4CCM.load_ami4ccm_config

        # extend generic component executor generation for AMI4CCM
        IDL.production(:comp_exec_header).extend(AmiComponentExecutorHeaderEx)
        IDL.production(:comp_exec_source).extend(AmiComponentExecutorSourceEx)
      end

      #########################################################################
      ## AMI4CCM interface generation
      ##

      # determine xxxAidl filename for Async Request/Reply pattern interfaces
      def self.acon_idl(options, idl_ext)
        options[:acon_idl] = File.join(options.outputdir, File.basename(options[:idlfile], idl_ext)+options[:ami_idl_pfx]+idl_ext)
      end

      # generate xxxA.idl with Async Request/Reply pattern interfaces
      def self.gen_ami_idl_only(options, idl_ext)
        AMI4CCM.load_ami4ccm_config

        IDL::CCMX11::AMI4CCM.acon_idl(options, idl_ext)

        a_idl_file = GenFile.new(options[:acon_idl])

        # schedule Writer for *A.idl, situated in AmiConnectorIDLWriter
        IDL.push_production(
            :ami4ccm_ami_idl,
            ::IDL::CCMX11::AMI4CCM::AmiConnectorIDLWriter.new(a_idl_file, options))
      end

      def self.gen_ami_idl(options, idl_ext)
        gen_ami_idl_only(options, idl_ext)

        # restore new (clean) options set for new input processing pass
        a_opts = options.restore
        # keep core option values (like include paths, macros and such)
        a_opts.copy!(options, IDL::CORE_OPTIONS)

        # copy needed export settings and other important switches
        a_opts.copy!(options,
                     :stub_export_include, :stub_export_macro,
                     :gen_any_ops, :gen_typecodes, :gen_localintf_any_ops,
                     :gen_ostream_operators, :no_cdr_streaming)

        # schedule next input processing for generated *A.idl to generate *AC.* files
        a_opts[:idlfile] = options[:acon_idl]
        # suppress skeleton generation
        a_opts[:svnt_skeletons] = false
        # generate full stubs
        a_opts[:no_client_source] = false
        a_opts[:no_client_header] = false
        a_opts[:no_client_proxy] = false
        IDL.push_input(a_opts[:idlfile], a_opts)
      end


      #########################################################################
      ## AMI4CCM configuration
      ##

      # configuration methods
      def self.load_ami4ccm_config
        require "#{AMI4CCM::ROOT}/config/parser"
      end

      # extend the base backend with some specific AMI4CCM settings/handling
      module BaseExt

        def self.included(base)
          base.class_eval do

            # extend CCMX11#setup_compile_lem_idl
            # make sure to reset some switches to prevent unwanted actions
            # in new input passes
            def setup_compile_lem_idl_with_ami4ccm(options, idl_ext)
              opts = setup_compile_lem_idl_without_ami4ccm(options, idl_ext)
              opts[:gen_amicomp_complete] = false
              opts[:gen_amiconn_complete] = false
              opts
            end

            alias_method_chain :setup_compile_lem_idl, :ami4ccm

            # extend CCMX11#check_servant_export_params
            # use ami4ccm prefix for servant export names when generating ami4ccm connector
            def check_servant_export_params_with_ami4ccm(options, prefix = nil, force = false)
              if options.gen_amiconn_only_ami4ccm_complete || options.gen_amiconn_complete
                prefix ||= options[:ami4ccm_pfx]
              end
              check_servant_export_params_without_ami4ccm(options, prefix, force)
            end

            alias_method_chain :check_servant_export_params, :ami4ccm

            # extend CCMX11#check_conn_export_params
            # use ami4ccm prefix for connector executor export names when generating ami4ccm connector
            def check_conn_export_params_with_ami4ccm(options, prefix = nil, force = false)
              if options.gen_amiconn_only_ami4ccm_complete || options.gen_amiconn_complete
                prefix ||= options[:ami4ccm_pfx]
              end
              check_conn_export_params_without_ami4ccm(options, prefix, force)
            end

            alias_method_chain :check_conn_export_params, :ami4ccm

          end
        end

      end

      module Cxx11Ext

        def self.included(base)
          base.class_eval do

            def check_stub_export_params_with_ami4ccm(options)
              if options.gen_ami_idl && options.gen_export_st
                # use composite _stub_export for stub generated of *A.idl file unless specified explicitly
                options.stub_export_macro = options.base_export_macro+'_AMI4CCM_STUB' + options.export_macro_pfx unless options.stub_export_macro || options.base_export_macro.nil?
                options.stub_export_include = options.base_export_include+'_ami4ccm_stub' + options.export_header_pfx unless options.stub_export_include || options.base_export_include.nil?
              end
              check_stub_export_params_without_ami4ccm(options)
            end

            alias_method_chain :check_stub_export_params, :ami4ccm

          end
        end
      end

    end  #AMI4CCM

    self.singleton_class.__send__(:include, AMI4CCM::BaseExt)

    IDL::Cxx11.singleton_class.__send__(:include, AMI4CCM::Cxx11Ext)

  end # CCMX11

end # IDL

# config modules
Dir.glob(File.join(File.dirname(__FILE__), 'config', '*.rb')).each do |f|
  require File.join(IDL::CCMX11::AMI4CCM::ROOT, 'config', File.basename(f, '.*'))
end
