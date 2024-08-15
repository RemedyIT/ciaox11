#--------------------------------------------------------------------
# @file    config.rb
# @author  Marcel Smit
#
# @brief   CCMX11 DDS4CCM facet configuration
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------

module IDL
  module CCMX11
    module DDS4CCM
      COPYRIGHT = "Copyright (c) 2007-#{Time.now.year} Remedy IT Expertise BV, The Netherlands".freeze
      TITLE = 'RIDL CCMX11 DDS4CCM Facet'.freeze

      # Configure facet
      #
      Backend::Facet.configure('dds4ccm', File.dirname(__FILE__), TITLE, COPYRIGHT, IDL::CCMX11.ciaox11_version) do |fctcfg|
        # optionally define dependencies on other facets
        #   specify dependencies either as:
        #   - a facet id (assumed to be loaded by current backend)
        #   - a hash where key(s) specifies(y) backend id(s) and value(s) facet id(s)
        #   - any combination thereof
        #
        fctcfg.depends_on :dds
        fctcfg.setup_after :dds

        def self.add_extended_options(ol)
          ol.for_switch '-G{generation options}', type: String, separator: true do |swcfg|
            swcfg.for_group :dds4ccm_group do |grpcfg|
              grpcfg.on_prepare do |arg, params|
                if /^dds4ccm\,(.*)/ =~ arg
                  return [::Regexp.last_match(1)]
                end

                nil
              end
              # IMPORTANT When these flags are updated also update the DDS4CCM docs/src/ridlc.adoc
              # which is used for our user documentation
              grpcfg.for_params :strings,
              params: {
                'conn' => {
                    option_name: :gen_ddsconn_complete,
                    description: "-Gdds4ccm,conn\t\tGenerate all files needed for an DDS4CCM connector"
                  },
                'conn_only' => {
                    option_name: :gen_ddsconn_only,
                    description: "-Gdds4ccm,conn_only\tGenerate connector files needed for an DDS4CCM connector"
                  },
                'lem' => {
                    option_name: :gen_dds4ccm_lem,
                    description: "-Gdds4ccm,lem\t\tGenerate lem IDL needed for DDS4CCM interaction"
                  },
                'lemgen' => {
                    option_name: :gen_dds4ccm_lemgen,
                    description: "-Gdds4ccm,lemgen\t\tGenerate lem IDL + derived code needed for DDS4CCM interaction"
                }
              }
            end
          end

          ol.for_switch '-W<extended option>=OPT', type: String, separator: true do |swcfg|
            swcfg.modify_group :b_extopt do |grpcfg|
              grpcfg.modify_params :strings,
                                   params: {
                                       'dds_topic' => { description: "-Wb,dds_topic=SCOPED_TOPIC\tspecifies scoped topic name for DDS4CCM lem generation" },
                                       'dds_topic_namespace' => { description: "-Wb,dds_topic_namespace=SCOPED_NAME\tspecifies scoped namespace name for DDS4CCM lem generation (default is topic type namespace)" },
                                       'dds_topic_seq_suffix' => { description: "-Wb,dds_topic_seq_suffix=SUFFIX\tspecifies suffix for topic sequence name for DDS4CCM lem generation" },
                                       'dds_topic_if_suffix' => { description: "-Wb,dds_topic_if_suffix=SUFFIX\tspecifies suffix topic interface name for DDS4CCM lem generation" },
                                       'dds_topic_seq' => { description: "-Wb,dds_topic_seq=NAME\t\tspecifies topic sequence name for DDS4CCM lem generation. Only effective in combination with -Wb,dds_topic" },
                                       'dds_topic_if' => { description: "-Wb,dds_topic_if=NAME\t\tspecifies topic interface name for DDS4CCM lem generation. Only effective in combination with -Wb,dds_topic" }
                                   }
            end
          end
        end # add_extended_options

        # setup facet option handling
        #
        fctcfg.on_setup do |optlist, ridl_params|
          ridl_params[:gen_ddsconn_complete] = false
          ridl_params[:gen_ddsconn_only] = false
          ridl_params[:gen_all_dds_related_files] = false

          DDS4CCM.add_extended_options(optlist)
        end

        # process input / generate code
        # arguments:
        #   in parser - parser object with full AST from parsed source
        #   in options - initialized option hash
        #
        fctcfg.on_process_input do |parser, options|
          idl_ext = (options.idlext ||= File.extname(options.idlfile))

          if options.gen_ddsconn_complete
            IDL::CCMX11::DDS4CCM.gen_dds4ccm_conn_complete(options, idl_ext)
          end

          if options.gen_ddsconn_only
            IDL::CCMX11::DDS4CCM.gen_dds4ccm_conn_only(options, idl_ext)
          end

          if options.gen_dds4ccm_lem
            IDL::CCMX11::DDS4CCM.gen_dds4ccm_lem(options, idl_ext)
          end

          if options.gen_dds4ccm_lemgen
            IDL::CCMX11::DDS4CCM.gen_dds4ccm_lemgen(options, idl_ext)
          end
        end # process_input
      end # configure

      #########################################################################
      ## DDS4CCM connector generation
      ##

      # This method drives 2 input processing passes:
      # 1. the current (main) pass processing the base IDL file passed on the command line
      #    - during this pass the following generators (productions) are scheduled:
      #       I) xxxE.idl generation (DDS4CCM state/event LEM IDL)
      #      II) xxx_conn.* generation (DDS4CCM templated connector executor implementation)
      #     III) xxx_svnt.* generation (DDS4CCM connector context&executor locator)
      # 2. processing the xxxE.idl file generated in the first pass
      #    - during this pass the following generators (productions) are scheduled:
      #       I) xxxEC.* generation (DDS4CCM connector lem stubs)
      #      II) export header for xxxEC code (if specified)
      #
      # generate ALL files for a DDS4CCM connector (incl. state/event LEM)
      def self.gen_dds4ccm_conn_complete(options, idl_ext)
        options[:gen_ddsconn_complete] = false

        options[:no_servant_code] = true

        # generate lem stub exports if -Gxhlst or -Gxhcn or -Gxhsv are specified
        options.gen_export_lem_stub ||= options.gen_export_conn || options.gen_export_svnt

        # schedule parser pass on lem IDL unless already done (when -Glem was specified)
        IDL::CCMX11.compile_lem_idl(options, idl_ext)

        options[:gen_dds4ccm_lemidl] = true # mark the LEM IDL generation in this pass for DDS4CCM
        # schedule lem IDL generation unless already done (when -Glem[,gen] was specified)
        IDL::CCMX11.gen_lem_idl(options, idl_ext)

        # now schedule DDS4CCM connector implementation code generation
        gen_dds4ccm_conn_only(options, idl_ext)
      end

      # This method drives a single input processing pass:
      # 1. the current (main) pass processing the base IDL file passed on the command line
      #    - during this pass the following generators (productions) are scheduled:
      #       I) xxx_conn.* generation (DDS4CCM templated connector executor implementation)
      #      II) xxx_svnt.* generation (DDS4CCM connector context&executor locator)
      #
      # generate only files specific for a DDS4CCM connector
      def self.gen_dds4ccm_conn_only(options, idl_ext)
        options[:gen_ddsconn_only] = false

        options[:no_servant_code] = true
        options[:no_cdr_streaming] = true
        options[:no_stub_proxy_hdr] = true

        # mark this pass for DDS4CCM connector implementation generation
        options[:gen_exec_for_dds_connector] = true
        options[:gen_svnt_for_dds_connector] = true

        # schedule templated connector implementation generation if not yet done
        IDL::CCMX11.gen_templated_connector_impl(options, idl_ext)
        # extend standard generators for DDS4CCM
        IDL.production(:templated_conn_impl_source).extend(IDL::CCMX11::DDS4CCM::TemplatedConnectorImplSourceExt)

        # schedule connector servant generation if not yet done
        IDL::CCMX11.gen_component_servant(options, idl_ext)
      end

      #########################################################################
      ## DDS4CCM state/event interface generation
      ##

      def self.gen_dds4ccm_lem(options, idl_ext)
        options[:gen_dds4ccm_lem] = false

        idl_base = File.basename(options[:idlfile], idl_ext)
        options[:dds4ccm_lem_idl_file] = File.join(options.outputdir, idl_base + 'SE' + idl_ext)
        dds4ccm_lem_idl_file = GenFile.new(options[:dds4ccm_lem_idl_file])

        # schedule dds4ccm lem IDL generation
        IDL.push_production(:dds4ccm_lem_idl,
                            ::IDL::CCMX11::DDS4CCM::SEVIDLWriter.new(dds4ccm_lem_idl_file,
                                                                     options.merge({ output: options[:dds4ccm_lem_idl_file] })))
      end

      # This method drives 3 input processing passes:
      # 1. the current (main) pass processing the base IDL file passed on the command line
      #    - during this pass the following generator (production) is scheduled:
      #       I) xxxSE.idl (declaring the DDS4CCM state/event interfaces)
      # 2. processing the xxxSE.idl file generated in the first pass
      #    - during this pass the following generators (productions) are scheduled:
      #       I) xxxSEC.* generation (state/event stubs)
      #      II) xxxSEE.idl generation (state/event LEM IDL)
      # 3. processing the xxxSEE.idl file generated in the second pass
      #    - during this pass the following generators (productions) are scheduled:
      #       I) xxxSEEC.* generation (state/event lem stubs)
      #      II) export header for xxxSEEC code (if specified)
      #
      # generate all files for the DDS4CCM state/event pattern interface
      def self.gen_dds4ccm_lemgen(options, idl_ext)
        options[:gen_dds4ccm_lemgen] = false

        # first take care of generating DDS4CCM SEV idl
        gen_dds4ccm_lem(options, idl_ext)

        # next schedule processing of generated LEM idl
        # generating stubs and LEM IDL stubs

        # restore new (clean) options set for new input processing pass
        lemgen_opts = options.restore
        # keep core option values (like include paths, macros and such)
        lemgen_opts.copy!(options, IDL::CORE_OPTIONS)

        # copy needed export settings
        lemgen_opts.copy!(options,
                      :base_export_include, :base_export_macro,
                      :stub_export_include, :stub_export_macro, :stub_export_file,
                      :lem_stub_export_include, :lem_stub_export_macro, :lem_stub_export_file,
                      :gen_any_ops, :gen_typecodes, :gen_localintf_any_ops,
                      :gen_ostream_operators, :no_cdr_streaming)

        lemgen_opts[:idlfile] = options[:dds4ccm_lem_idl_file]
        # if not set explicitly but -Gxhst is than assume -Gxhlst is as well
        lemgen_opts.gen_export_lem_stub ||= options.gen_export_st
        lemgen_opts[:gen_lem_gen] = true # -Glem,gen
        lemgen_opts[:no_stub_proxy_hdr] = true
        lemgen_opts[:no_cdr_streaming] = true
        lemgen_opts[:svnt_skeletons] = false # suppress all skeleton code generation
        lemgen_opts[:gen_dds4ccm_lemidl] = true # mark the LEM IDL generation in the scheduled pass for DDS4CCM
        IDL.push_input(lemgen_opts[:idlfile], lemgen_opts)
        lemgen_opts
      end
    end # DDS4CCM
  end # CCMX11
end # IDL
