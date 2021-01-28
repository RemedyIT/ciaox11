#--------------------------------------------------------------------
# @file    ddsidl_extensions.rb
# @author  Johnny Willemsen
#
# @brief   DDS4OPENDDS extensions for dds idl traits generation
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------

module IDL

  module CCMX11

    module DDSX11

      module OPENDDS

        module DDSIDLWriterExt
          def self.configure_extension(writer)
            IDL.log(3, 'Configuring DDS4OPENDDS DDSIDLWriterExt extension')
            # make writer look for templates in opendds folder first
            writer.template_root = File.join(writer.template_root, 'opendds')
          end
        end

      end # OPENDDS

    end # DDSX11

  end # CCMX11

end # IDL
