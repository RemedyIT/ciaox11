#--------------------------------------------------------------------
# @file    udttraits_extensions.rb
# @author  Martin Corino
#
# @brief   DDS4OPENDDS extensions for udt traits generation
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------

module IDL
  module CCMX11
    module DDSX11
      module OPENDDS
        module UserDefinedTypeTraitsWriterExt
          def self.configure_extension(writer)
            IDL.log(3, 'Configuring DDS4OPENDDS UserDefinedTypeTraitsWriterExt extension')
            # make writer look for templates in opendds folder first
            writer.template_root = File.join(writer.template_root, 'opendds')
          end
        end
      end # OPENDDS
    end # DDSX11
  end # CCMX11
end # IDL
