#--------------------------------------------------------------------
# @file    config.rb
# @author  Martin Corino
#
# @brief   RIDL backend facet configuration for ExF for DDS4CCM
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------


module IDL
  module CCMX11
    module ExF4DDS
      COPYRIGHT = "Copyright (c) 2007-#{Time.now.year} Remedy IT Expertise BV, The Netherlands".freeze
      TITLE = 'RIDL AXCIOMA ExF for DDS4CCM Facet'.freeze

      ## Configure facet
      #
      Backend::Facet.configure('exf4dds', File.dirname(__FILE__), TITLE, COPYRIGHT, {major: 0, minor: 1, release: 1}) do |fctcfg|
        # optionally define dependencies on other facets
        #   specify dependencies either as:
        #   - a facet id (assumed to be loaded by current backend)
        #   - a hash where key(s) specifies(y) backend id(s) and value(s) facet id(s)
        #   - any combination thereof
        #
        fctcfg.depends_on :exfbase, :dds4ccm

        fctcfg.setup_after :exfbase, :dds4ccm

        def self.add_extended_options(ol)
          # nothing
        end # add_extended_options

        # setup backend option handling
        #
        fctcfg.on_setup do |optlist, ridl_params|
          ExF4DDS.add_extended_options(optlist)

          # extend DDS4CCM facet
          IDL::CCMX11::DDS4CCM.singleton_class.__send__(:include, DDS4CCMExt)
        end

        # process input / generate code
        # arguments:
        #   in parser - parser object with full AST from parsed source
        #   in options - initialized option hash
        #
        fctcfg.on_process_input do |parser, options|
          if options.gen_exf_support

            if options.gen_exec_for_dds_connector
              IDL.log(2, 'Extending connector executor generation for ExF4DDS')
              # extend standard generators for ExF for DDS4CCM
              IDL.production(:templated_conn_impl_source).extend(IDL::CCMX11::ExF4DDS::TemplatedConnectorImplSourceExt)
            end

            if options.gen_svnt_for_dds_connector
              IDL.log(2, 'Extending connector servant generation for ExF4DDS')
              # extend standard generators for ExF for DDS4CCM
              IDL.production(:comp_svnt_header).extend(IDL::CCMX11::ExF4DDS::CompSvntHeaderExt)
              IDL.production(:comp_svnt_source).extend(IDL::CCMX11::ExF4DDS::CompSvntSourceExt)
            end

          end
        end # fctcfg.on_process_input
      end # configure facet

      # extend the DDS4CCM facet with some specific ExF settings/handling
      module DDS4CCMExt
        def self.included(base)
          base.class_eval do
            # extend CCMX11::DDS4CCM#gen_dds4ccm_lemgen
            def gen_dds4ccm_lemgen_with_exf(options, idl_ext)
              # make sure the -GExF is passed on
              lemgen_opts = gen_dds4ccm_lemgen_without_exf(options, idl_ext)
              lemgen_opts.gen_exf_support = true if options.gen_exf_support
            end

            alias_method_chain :gen_dds4ccm_lemgen, :exf
          end
        end
      end
    end  # ExF4DDS
  end # CCMX11
end # IDL
