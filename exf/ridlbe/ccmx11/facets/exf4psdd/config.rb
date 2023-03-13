#--------------------------------------------------------------------
# @file    config.rb
# @author  Martin Corino
#
# @brief   RIDL backend facet configuration for ExF for PSDD4CCM
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------

module IDL
  module CCMX11
    module ExF4PSDD
      COPYRIGHT = "Copyright (c) 2007-#{Time.now.year} Remedy IT Expertise BV, The Netherlands".freeze
      TITLE = 'RIDL AXCIOMA ExF for PSDD4CCM Facet'.freeze

      ## Configure facet
      #
      Backend::Facet.configure('exf4psdd', File.dirname(__FILE__), TITLE, COPYRIGHT, { major: 0, minor: 1, release: 1 }) do |fctcfg|
        # optionally define dependencies on other facets
        #   specify dependencies either as:
        #   - a facet id (assumed to be loaded by current backend)
        #   - a hash where key(s) specifies(y) backend id(s) and value(s) facet id(s)
        #   - any combination thereof
        #
        fctcfg.depends_on :exfbase, :psdd4ccm

        fctcfg.ignore_on_missing :exfbase

        fctcfg.setup_after :exfbase, :psdd4ccm

        def self.add_extended_options(ol)
          # nothing
        end # add_extended_options

        # setup backend option handling
        #
        fctcfg.on_setup do |optlist, _ridl_params|
          ExF4PSDD.add_extended_options(optlist)

          # extend PSDD4CCM facet
          IDL::CCMX11::PSDD4CCM.singleton_class.__send__(:include, PSDD4CCMExt)
        end

        # process input / generate code
        # arguments:
        #   in parser - parser object with full AST from parsed source
        #   in options - initialized option hash
        #
        fctcfg.on_process_input do |_parser, options|
          if options.gen_exf_support

            if options.gen_exec_for_psdd_connector
              IDL.log(2, 'Extending connector executor generation for ExF4PSDD')
              # extend standard generators for ExF for DDS4CCM
              IDL.production(:templated_conn_impl_source).extend(IDL::CCMX11::ExF4PSDD::TemplatedConnectorImplSourceExt)
            end

            if options.gen_svnt_for_psdd_connector
              IDL.log(2, 'Extending connector servant generation for ExF4PSDD')
              # extend standard generators for ExF for PSDD4CCM
              IDL.production(:comp_svnt_header).extend(IDL::CCMX11::ExF4PSDD::CompSvntHeaderExt)
              IDL.production(:comp_svnt_source).extend(IDL::CCMX11::ExF4PSDD::CompSvntSourceExt)
            end

          end
        end # fctcfg.on_process_input
      end # configure facet

      # extend the PSDD4CCM facet with some specific ExF settings/handling
      module PSDD4CCMExt
        def self.included(base)
          base.class_eval do
            # extend CCMX11::PSDD4CCM#gen_psdd4ccm_lemgen
            def gen_psdd4ccm_lemgen_with_exf(options, idl_ext)
              # make sure the -GExF is passed on
              lemgen_opts = gen_psdd4ccm_lemgen_without_exf(options, idl_ext)
              lemgen_opts.gen_exf_support = true if options.gen_exf_support
            end

            alias_method_chain :gen_psdd4ccm_lemgen, :exf
          end
        end
      end
    end # ExF4PSDD
  end # CCMX11
end # IDL
