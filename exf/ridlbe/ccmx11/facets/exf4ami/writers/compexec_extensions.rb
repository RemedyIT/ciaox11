#--------------------------------------------------------------------
# @file    compexec_extensions.rb
# @author  Marijke Hengstmengel
#
# @brief   ExF extensions for AMI4CCM connector executor generation
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------
require 'ridlbe/c++11/writerbase'

module IDL
  module CCMX11
    module ExF
      module AmiExFConnectorHeaderWriter
        def self.configure_extension(writer)
          IDL.log(3, 'Configuring ExF AmiExFConnectorHeaderWriter extension')
          # make writer look for templates in ExF folder first
          # (requires AMI4CCM extension to be loaded first)
          writer.template_root = File.join(writer.template_root, 'exf')
          writer.overload_template(:reply_handler, 'exf/reply_handler')
          writer.overload_template(:facet_exec, 'exf/facet_exec')
        end
      end

      module AmiExFConnectorSourceWriter
        def self.configure_extension(writer)
          IDL.log(3, 'Configuring ExF AmiExFConnectorSourceWriter extension')
          # make writer look for templates in ExF folder first
          # (requires AMI4CCMextension to be loaded first)
          writer.template_root = File.join(writer.template_root, 'exf')
          # append ExF template after regular template
          writer.append_template(:pre, :pre_exf)
        end
      end
    end # ExF
  end # CCMX11
end # IDL
