#--------------------------------------------------------------------
# @file    config.rb
# @author  Marijke Hengstmengel
#
# @brief   RIDL backend facet configuration for ExF for AMI4CCM
#
# @copyright Copyright (c) Remedy IT Expertise BV
# Chamber of commerce Rotterdam nr.276339, The Netherlands
#--------------------------------------------------------------------


module IDL

  module CCMX11

    module ExF4AMI
      COPYRIGHT = "Copyright (c) 2007-#{Time.now.year} Remedy IT Expertise BV, The Netherlands".freeze
      TITLE = 'RIDL AXCIOMA ExF for AMI4CCM Facet'.freeze

      ## Configure facet
      #
      Backend::Facet.configure('exf4ami', File.dirname(__FILE__), TITLE, COPYRIGHT, {major: 0, minor: 1, release: 1}) do |fctcfg|

        # optionally define dependencies on other facets
        #   specify dependencies either as:
        #   - a facet id (assumed to be loaded by current backend)
        #   - a hash where key(s) specifies(y) backend id(s) and value(s) facet id(s)
        #   - any combination thereof
        #
        fctcfg.depends_on :exfbase, :ami4ccm

        fctcfg.setup_after :exfbase, :ami4ccm

        def self.add_extended_options(ol)

        end # add_extended_options

        # setup backend option handling
        #
        fctcfg.on_setup do |optlist, ridl_params|
          ExF4AMI.add_extended_options(optlist)

          # setup extension here now we know AMI4CCM is loaded as result of this facet's dependencies
          AMI4CCMExt.setup_extension
        end

        # process input / generate code
        # arguments:
        #   in parser - parser object with full AST from parsed source
        #   in options - initialized option hash
        #
        fctcfg.on_process_input do |parser, options|
          if options.gen_exf_support
            if options[:gen_component_servant]
              IDL.log(2, 'Extending ami4ccm connector executor generation for ExF')

              IDL.production(:ami4ccm_conn_header).extend(IDL::CCMX11::ExF::AmiExFConnectorHeaderWriter)
              IDL.production(:ami4ccm_conn_source).extend(IDL::CCMX11::ExF::AmiExFConnectorSourceWriter)

              IDL.log(2, 'Extending ami4ccm connector servant generation for ExF')
              # extend standard generators for AMIA4CCM
              IDL.production(:comp_svnt_source).extend(IDL::CCMX11::ExF::AmiExFSvntConnectorSourceExt)
            end
          end
        end # fctcfg.on_process_input
      end # configure facet

      # extend the AMIA4CCM facet with some specific ExF settings/handling
      module AMI4CCMExt

        def self.included(base)
          base.class_eval do

            # extend gen_ami_connector_complete
            def gen_ami_connector_complete_ami_conn_idl_with_exf4ami(options, idl_ext)

                run_opts = gen_ami_connector_complete_ami_conn_idl_without_exf4ami(options, idl_ext)

                # make sure the -GExF is passed on
                run_opts.gen_exf_support = true if options.gen_exf_support && options.gen_ami_connector_idl

            end

            alias_method_chain :gen_ami_connector_complete_ami_conn_idl, :exf4ami

          end
        end

        def self.setup_extension
          AMI4CCM.singleton_class.__send__(:include, AMI4CCMExt)
        end

      end # AMI4CCMExt

    end  #ExF4AMI

  end # CCMX11

end # IDL
