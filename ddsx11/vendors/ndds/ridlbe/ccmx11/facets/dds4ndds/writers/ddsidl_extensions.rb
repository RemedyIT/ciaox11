#--------------------------------------------------------------------
# @file    ddsidl_extensions.rb
# @author  Johnny Willemsen
#
# @brief   DDS4NDDS extensions for dds idl traits generation
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------

module IDL

  module CCMX11

    module DDSX11

      module NDDS

        module DDSIDLWriterExt
          def self.configure_extension(writer)
            IDL.log(3, 'Configuring DDS4NDDS DDSIDLWriterExt extension')
            # make writer look for templates in ndds folder first
            writer.template_root = File.join(writer.template_root, 'ndds')
          end
        end

      end # NDDS

    end # DDSX11

  end # CCMX11

end # IDL
