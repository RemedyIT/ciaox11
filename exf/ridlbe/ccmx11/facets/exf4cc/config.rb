#--------------------------------------------------------------------
# @file    config.rb
# @author  Martin Corino
#
# @brief   RIDL backend facet configuration for ExF for CORBA4CCM
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------

module IDL
  module CCMX11
    module ExF4CORBA
      COPYRIGHT = "Copyright (c) 2007-#{Time.now.year} Remedy IT Expertise BV, The Netherlands".freeze
      TITLE = 'RIDL AXCIOMA ExF for CORBA4CCM Facet'.freeze

      ## Configure facet
      #
      Backend::Facet.configure('exf4cc', File.dirname(__FILE__), TITLE, COPYRIGHT, { major: 2, minor: 6, release: 0 }) do |fctcfg|
        # optionally define dependencies on other facets
        #   specify dependencies either as:
        #   - a facet id (assumed to be loaded by current backend)
        #   - a hash where key(s) specifies(y) backend id(s) and value(s) facet id(s)
        #   - any combination thereof
        #
        fctcfg.depends_on :exfbase, :corba4ccm

        fctcfg.setup_after :exfbase, :corba4ccm

        def self.add_extended_options(ol)
        end # add_extended_options

        # setup backend option handling
        #
        fctcfg.on_setup do |optlist, _ridl_params|
          ExF4CORBA.add_extended_options(optlist)

          # extend CORBA4CCM facet
          IDL::CCMX11::CORBA.singleton_class.__send__(:include, Corba4CCMExt)
        end

        # process input / generate code
        # arguments:
        #   in parser - parser object with full AST from parsed source
        #   in options - initialized option hash
        #
        fctcfg.on_process_input do |_parser, options|
          if options.gen_exf_support

            if options.svnt_skeletons && !(options.no_servant_header || options.no_servant_code)
              IDL.log(2, 'Extending skeleton generation for ExF4CORBA')
              # extend standard skeleton generators for CORBA
              IDL.production(:skel_header).extend(IDL::CCMX11::ExF::CorbaServantHeaderExt)
              IDL.production(:skel_source).extend(IDL::CCMX11::ExF::CorbaServantSourceExt)
            end

            if options.gen_exec_for_corba_connector
              IDL.log(2, 'Extending connector executor generation for ExF4CORBA')
              # extend standard generators for CORBA4CCM
              IDL.production(:comp_exec_header).extend(IDL::CCMX11::ExF::CorbaCompExecHeaderExt)
              IDL.production(:comp_exec_source).extend(IDL::CCMX11::ExF::CorbaCompExecSourceExt)
            end

            if options.gen_svnt_for_corba_connector
              IDL.log(2, 'Extending connector servant generation for ExF4CORBA')
              # extend standard generators for CORBA4CCM
              IDL.production(:comp_svnt_header).extend(IDL::CCMX11::ExF::CorbaCompSvntHeaderExt)
              IDL.production(:comp_svnt_source).extend(IDL::CCMX11::ExF::CorbaCompSvntSourceExt)
            end

          end
        end # fctcfg.on_process_input
      end # configure facet

      # extend the CORBA4CCM facet with some specific ExF settings/handling
      module Corba4CCMExt
        def self.included(base)
          base.class_eval do
            # extend CCMX11::CORBA#schedule_corba4ccm_idl_input
            def schedule_corba4ccm_idl_input_with_exf(options, cc_opts)
              # make sure the -GExF is passed on
              if options.gen_exf_support
                cc_opts.gen_exf_support = true
              end
              schedule_corba4ccm_idl_input_without_exf(options, cc_opts)
            end

            alias_method_chain :schedule_corba4ccm_idl_input, :exf
          end
        end
      end
    end # ExF4CORBA
  end # CCMX11
end # IDL
