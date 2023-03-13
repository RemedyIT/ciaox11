#--------------------------------------------------------------------
# @file    compsvnt_extensions.rb
# @author  Martin Corino
#
# @brief   ExF extensions for PSDD4CCM connector servant generation
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------
require 'ridlbe/c++11/writerbase'

module IDL
  module CCMX11
    module ExF4PSDD
      module CompSvntHeaderExt
        def self.configure_extension(writer)
          IDL.log(3, 'Configuring ExF4PSDD CompExecHeader extension')
          # make writer look for templates in ExF folder first
          # (requires PSDD4CCM extension to be loaded first)
          writer.template_root = File.join(writer.template_root, 'exf', 'psdd')
        end
      end

      module CompSvntSourceExt
        def self.configure_extension(writer)
          IDL.log(3, 'Configuring ExF4PSDD CompExecSource extension')
          # make writer look for templates in ExF folder first
          # (requires PSDD4CCM extension to be loaded first)
          writer.template_root = File.join(writer.template_root, 'exf', 'psdd')
          writer.overload_template(:pre_extra_include, 'exf/psdd/pre_extra_include')
        end
      end
    end # ExF4PSDD
  end # CCMX11
end # IDL
