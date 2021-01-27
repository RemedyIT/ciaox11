#--------------------------------------------------------------------
# @file    config.rb
# @author  Johnny Willemsen
#
# @brief   DDS OpenDDS facet configuration
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------

module IDL

  module CCMX11

    module DDS

      module OPENDDS
        COPYRIGHT = "Copyright (c) 2007-#{Time.now.year} Remedy IT Expertise BV, The Netherlands".freeze
        TITLE = 'RIDL OpenDDS DDS Facet'.freeze

        ## Configure facet
        #
        Backend::Facet.configure('dds4opendds', File.dirname(__FILE__), TITLE, COPYRIGHT, {major: 1, minor: 0, release: 0}) do |fctcfg|

          # optionally define dependencies on other facets
          #   specify dependencies either as:
          #   - a facet id (assumed to be loaded by current backend)
          #   - a hash where key(s) specifies(y) backend id(s) and value(s) facet id(s)
          #   - any combination thereof
          #
          fctcfg.depends_on :dds
          fctcfg.setup_after :dds

          # setup facet option handling
          #
          fctcfg.on_setup do |optlist, ridl_params|
            ridl_params[:opendds_typesupportimpl_pfx] = '_ddsTypeSupportImpl'
          end

          # process input / generate code
          # arguments:
          #   in parser - parser object with full AST from parsed source
          #   in options - initialized option hash
          #
          fctcfg.on_process_input do |parser, options|
            if options.gen_user_defined_type_traits_for_dds
              IDL::CCMX11::DDS::OPENDDS.gen_user_defined_type_traits_for_opendds(options)
            end
            if options.gen_impl_for_type_support
              IDL::CCMX11::DDS::OPENDDS.gen_impl_for_type_support_for_opendds(options)
            end
            if options.gen_idl_for_dds
              IDL::CCMX11::DDS::OPENDDS.gen_idl_for_dds_for_opendds(options)
            end
          end
        end # configure

        #
        # modify generation of the type traits for OpenDDS
        #
        def self.gen_user_defined_type_traits_for_opendds(options)
          # schedule opendds type traits generation
          IDL.production(:dds_type_traits).extend(IDL::CCMX11::DDSX11::OPENDDS::UserDefinedTypeTraitsWriterExt)
        end
        def self.gen_impl_for_type_support_for_opendds(options)
          # schedule opendds type support source generation
          IDL.production(:dds_typesupport_source_file).extend(IDL::CCMX11::DDSX11::OPENDDS::DDSTypeSupportSourceWriterExt)
        end
        def self.gen_idl_for_dds_for_opendds(options)
          # schedule opendds idl file generation
          IDL.production(:dds_idl).extend(IDL::CCMX11::DDSX11::OPENDDS::DDSIDLWriterExt)
        end
      end # OPENDDS
    end # DDSX11
  end # CCMX11
end # IDL
