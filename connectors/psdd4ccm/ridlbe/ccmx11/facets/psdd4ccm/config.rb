#--------------------------------------------------------------------
# @file    config.rb
# @author  Martin Corino
#
# @brief   CCMX11 PSDD4CCM facet configuration
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------

module IDL

  module CCMX11

    module PSDD4CCM

      COPYRIGHT = "Copyright (c) 2016-#{Time.now.year} Remedy IT Expertise BV, The Netherlands".freeze
      TITLE = 'RIDL CCMX11 PSDD4CCM Facet'.freeze

      def self.add_extended_options(ol)

        ol.for_switch '-G{generation options}', :type => String, :separator => true do |swcfg|
          swcfg.for_group :psdd4ccm_group do |grpcfg|
            grpcfg.on_prepare do |arg, params|
              if /^psdd4ccm\,(.*)/ =~ arg
                return [$1]
              end
              nil
            end
            # IMPORTANT When these flags are updated also update the PSDD4CCM docs/src/ridlc.adoc
            # which is used for our user documentation
            grpcfg.for_params :strings,
            :params => {
              'conn' => {
                  :option_name => :gen_psddconn_complete,
                  :description => "-Gpsdd4ccm,conn\t\tGenerate all files needed for an PSDD4CCM connector"
                },
              'conn_only' => {
                  :option_name => :gen_psddconn_only,
                  :description => "-Gpsdd4ccm,conn_only\tGenerate connector files needed for an PSDD4CCM connector"
                },
              'lem' => {
                  :option_name => :gen_psdd4ccm_lem,
                  :description => "-Gpsdd4ccm,lem\t\tGenerate lem IDL needed for PSDD4CCM interaction"
                },
              'lemgen' => {
                  :option_name => :gen_psdd4ccm_lemgen,
                  :description => "-Gpsdd4ccm,lemgen\t\tGenerate lem IDL + derived code needed for PSDD4CCM interaction"
                },
              'traits' => {
                  :option_name => :gen_psdd_traits,
                  :description => "-Gpsdd4ccm,traits\t\tGenerate PSDD type traits (not generated by default)"
                }
            }
          end
        end

        ol.for_switch '-W<extended option>=OPT', :type => String, :separator => true do |swcfg|
          swcfg.modify_group :b_extopt do |grpcfg|
            grpcfg.modify_params :strings,
                                 :params => {
                                     'psdd_topic' => {:description => "-Wb,psdd_topic=SCOPED_TOPIC\tSpecifies scoped topic name for PSDD4CCM lem generation"},
                                     'psdd_topic_namespace' => {:description => "-Wb,psdd_topic_namespace=SCOPED_NAME\tSpecifies scoped namespace name for PSDD4CCM lem generation (default is topic type namespace)"},
                                     'psdd_topic_seq_suffix' => {:description => "-Wb,psdd_topic_seq_suffix=SUFFIX\tSpecifies suffix for topic sequence name for PSDD4CCM lem generation"},
                                     'psdd_topic_if_suffix' => {:description => "-Wb,psdd_topic_if_suffix=SUFFIX\tSpecifies suffix topic interface name for PSDD4CCM lem generation"},
                                     'psdd_topic_seq' => {:description => "-Wb,psdd_topic_seq=NAME\t\tSpecifies topic sequence name for PSDD4CCM lem generation. Only effective in combination with -Wb,psdd_topic"},
                                     'psdd_topic_if' => {:description => "-Wb,psdd_topic_if=NAME\t\tSpecifies topic interface name for PSDD4CCM lem generation. Only effective in combination with -Wb,psdd_topic"}
                                 }
          end
        end

      end # add_extended_options

      # Configure facet
      #
      Backend::Facet.configure('psdd4ccm', File.dirname(__FILE__), TITLE, COPYRIGHT, {major: 1, minor: 0, release: 0}) do |fctcfg|

        # setup facet option handling
        #
        fctcfg.on_setup do |optlist, ridl_params|
          ridl_params[:gen_psddconn_complete] = false
          ridl_params[:gen_psddconn_only] = false
          ridl_params[:psdd_traits_pfx] = '_psdd_traits'

          IDL::CCMX11::PSDD4CCM.add_extended_options(optlist)
        end

        # process input / generate code
        # arguments:
        #   in parser - parser object with full AST from parsed source
        #   in options - initialized option hash
        #
        fctcfg.on_process_input do |parser, options|

          idl_ext = (options[:idlext] ||= File.extname(options[:idlfile]))

          if options[:gen_psddconn_complete]
            IDL::CCMX11::PSDD4CCM.gen_psdd4ccm_conn_complete(options, idl_ext)
          end

          if options[:gen_psddconn_only]
            IDL::CCMX11::PSDD4CCM.gen_psdd4ccm_conn_only(options, idl_ext)
          end

          if options[:gen_psdd4ccm_lem]
            IDL::CCMX11::PSDD4CCM.gen_psdd4ccm_lem(options, idl_ext)
          end

          if options[:gen_psdd4ccm_lemgen]
            IDL::CCMX11::PSDD4CCM.gen_psdd4ccm_lemgen(options, idl_ext)
          end

          if options[:gen_psdd_traits]
            IDL::CCMX11::PSDD4CCM.gen_psdd_traits(options, idl_ext)
          end

        end # process_input

      end # configure

      #########################################################################
      ## PSDD4CCM connector generation
      ##

      # This method drives 2 input processing passes:
      # 1. the current (main) pass processing the base IDL file passed on the command line
      #    - during this pass the following generators (productions) are scheduled:
      #       I) xxxE.idl generation (PSDD4CCM pubsub LEM IDL)
      #      II) xxx_conn.* generation (PSDD4CCM templated connector executor implementation)
      #     III) xxx_svnt.* generation (PSDD4CCM connector context&executor locator)
      # 2. processing the xxxE.idl file generated in the first pass
      #    - during this pass the following generators (productions) are scheduled:
      #       I) xxxEC.* generation (PSDD4CCM connector lem stubs)
      #      II) export header for xxxEC code (if specified)
      #
      # generate ALL files for a PSDD4CCM connector (incl. state/event LEM)
      def self.gen_psdd4ccm_conn_complete(options, idl_ext)
        options[:gen_ddsconn_complete] = false

        options[:no_servant_code] = true

        # generate lem stub exports if -Gxhlst or -Gxhcn or -Gxhsv are specified
        options.gen_export_lem_stub ||= options.gen_export_conn || options.gen_export_svnt

        # schedule parser pass on lem IDL unless already done (when -Glem was specified)
        IDL::CCMX11.compile_lem_idl(options, idl_ext)

        options[:gen_psdd4ccm_lemidl] = true # mark the LEM IDL generation in this pass for PSDD4CCM
        # schedule lem IDL generation unless already done (when -Glem[,gen] was specified)
        IDL::CCMX11.gen_lem_idl(options, idl_ext)

        # now schedule PSDD4CCM connector implementation code generation
        gen_psdd4ccm_conn_only(options, idl_ext)
      end

      # This method drives a single input processing pass:
      # 1. the current (main) pass processing the base IDL file passed on the command line
      #    - during this pass the following generators (productions) are scheduled:
      #       I) xxx_conn.* generation (PSDD4CCM templated connector executor implementation)
      #      II) xxx_svnt.* generation (PSDD4CCM connector context&executor locator)
      #
      # generate only files specific for a PSDD4CCM connector
      def self.gen_psdd4ccm_conn_only(options, idl_ext)
        options[:gen_ddsconn_only] = false

        options[:no_servant_code] = true
        options[:no_cdr_streaming] = true
        options[:no_client_proxy] = true

        # mark this pass for PSDD4CCM connector implementation generation
        options[:gen_exec_for_psdd_connector] = true
        options[:gen_svnt_for_psdd_connector] = true

        # schedule templated connector implementation generation if not yet done
        IDL::CCMX11.gen_templated_connector_impl(options, idl_ext)
        # extend standard generators for PSDD4CCM
        IDL.production(:templated_conn_impl_source).extend(IDL::CCMX11::PSDD4CCM::TemplatedConnectorImplSourceExt)

        # schedule connector servant generation if not yet done
        IDL::CCMX11.gen_component_servant(options, idl_ext)
      end

      #########################################################################
      ## PSDD4CCM pubsub interface generation
      ##

      def self.gen_psdd4ccm_lem(options, idl_ext)
        options[:gen_psdd4ccm_lem] = false

        idl_base = File.basename(options[:idlfile], idl_ext)
        options[:psdd4ccm_lem_idl_file] = File.join(options.outputdir, idl_base+'PS'+idl_ext)
        psdd4ccm_lem_idl_file = GenFile.new(options[:psdd4ccm_lem_idl_file])

        # schedule psdd4ccm lem IDL generation
        IDL.push_production(:psdd4ccm_lem_idl,
                            ::IDL::CCMX11::PSDD4CCM::PSDDIDLWriter.new(
                                    psdd4ccm_lem_idl_file,
                                    options.merge({ :output => options[:psdd4ccm_lem_idl_file] })))
      end

      # This method drives 3 input processing passes:
      # 1. the current (main) pass processing the base IDL file passed on the command line
      #    - during this pass the following generator (production) is scheduled:
      #       I) xxxPS.idl (declaring the PSDD4CCM pubsub interfaces)
      # 2. processing the xxxPS.idl file generated in the first pass
      #    - during this pass the following generators (productions) are scheduled:
      #       I) xxxPSC.* generation (pubsub stubs)
      #      II) xxxPSE.idl generation (pubsub LEM IDL)
      # 3. processing the xxxPSE.idl file generated in the second pass
      #    - during this pass the following generators (productions) are scheduled:
      #       I) xxxPSEC.* generation (pubsub lem stubs)
      #      II) export header for xxxPSEC code (if specified)
      #
      # generate all files for the PSDD4CCM state/event pattern interface
      def self.gen_psdd4ccm_lemgen(options, idl_ext)
        options[:gen_psdd4ccm_lemgen] = false

        # first take care of generating PSDD4CCM PS idl
        gen_psdd4ccm_lem(options, idl_ext)

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

        lemgen_opts[:idlfile] = options[:psdd4ccm_lem_idl_file]
        # if not set explicitly but -Gxhst is than assume -Gxhlst is as well
        lemgen_opts.gen_export_lem_stub ||= options.gen_export_st
        lemgen_opts[:gen_lem_gen] = true # -Glem,gen
        lemgen_opts[:no_client_proxy] = true
        lemgen_opts[:no_cdr_streaming] = true
        lemgen_opts[:svnt_skeletons] = false # suppress all skeleton code generation
        lemgen_opts[:gen_psdd4ccm_lemidl] = true # mark the LEM IDL generation in the scheduled pass for PSDD4CCM
        IDL.push_input(lemgen_opts[:idlfile], lemgen_opts)
        lemgen_opts
      end

      def self.gen_psdd_traits(options, idl_ext)
        psdd_traits_file = GenFile.new(File.join(options.outputdir,
            File.basename(options[:idlfile], idl_ext)+options[:psdd_traits_pfx]+options.hdr_ext))

        # schedule psdd traits generation
        IDL.push_production(:psdd_traits,
                            ::IDL::CCMX11::PSDD4CCM::PSDDTraitsWriter.new(psdd_traits_file, options))
      end

    end # PSDD4CCM

  end # CCMX11

end # IDL