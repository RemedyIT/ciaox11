#--------------------------------------------------------------------
# @file    config.rb
# @author  Martin Corino
#
# @brief   DDSX11 facet configuration
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------

module IDL
  module CCMX11
    module DDSX11
      module NDDS
        COPYRIGHT = "Copyright (c) 2007-#{Time.now.year} Remedy IT Expertise BV, The Netherlands".freeze
        TITLE = 'RIDL NDDS DDS Facet'.freeze

        ## Configure facet
        #
        Backend::Facet.configure('dds4ndds', File.dirname(__FILE__), TITLE, COPYRIGHT, IDL::CCMX11.ciaox11_version) do |fctcfg|
          # optionally define dependencies on other facets
          #   specify dependencies either as:
          #   - a facet id (assumed to be loaded by current backend)
          #   - a hash where key(s) specifies(y) backend id(s) and value(s) facet id(s)
          #   - any combination thereof
          #
          fctcfg.depends_on :dds
          fctcfg.setup_after :dds

          # process input / generate code
          # arguments:
          #   in parser - parser object with full AST from parsed source
          #   in options - initialized option hash
          #
          fctcfg.on_process_input do |parser, options|
            if options.gen_user_defined_type_traits_for_dds
              IDL::CCMX11::DDSX11::NDDS.gen_user_defined_type_traits_for_ndds(options)
            end
            if options.gen_impl_for_type_support
              IDL::CCMX11::DDSX11::NDDS.gen_impl_for_type_support_for_ndds(options)
            end
            if options.gen_idl_for_dds
              IDL::CCMX11::DDSX11::NDDS.gen_idl_for_dds_for_ndds(options)
            end
          end
        end # configure

        #
        # modify generation of the type traits for NDDS
        #
        def self.gen_user_defined_type_traits_for_ndds(options)
          # schedule ndds type traits generation
          IDL.production(:dds_type_traits).extend(IDL::CCMX11::DDSX11::NDDS::UserDefinedTypeTraitsWriterExt)
        end

        def self.gen_impl_for_type_support_for_ndds(options)
          # schedule ndds type support source generation
          IDL.production(:dds_typesupport_source_file).extend(IDL::CCMX11::DDSX11::NDDS::DDSTypeSupportSourceWriterExt)
        end

        def self.gen_idl_for_dds_for_ndds(options)
          # schedule ndds idl file generation
          IDL.production(:dds_idl).extend(IDL::CCMX11::DDSX11::NDDS::DDSIDLWriterExt)
        end
      end # NDDS
    end # DDSX11
  end # CCMX11
end # IDL
