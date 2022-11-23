#--------------------------------------------------------------------
# @file    compsvnt_extensions.rb
# @author  Martin Corino
#
# @brief   ExF extensions for DDS4CCM connector servant generation
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------
require 'ridlbe/c++11/writerbase'

module IDL

  module CCMX11

    module ExF4DDS

      module CompSvntHeaderExt

        def self.configure_extension(writer)
          IDL.log(3, 'Configuring ExF4DDS CompExecHeader extension')
          # make writer look for templates in ExF folder first
          # (requires DDS4CCM extension to be loaded first)
          writer.template_root = File.join(writer.template_root, 'exf', 'dds')
        end

      end

      module CompSvntSourceExt

        def self.configure_extension(writer)
          IDL.log(3, 'Configuring ExF4DDS CompExecSource extension')
          # make writer look for templates in ExF folder first
          # (requires DDS4CCM extension to be loaded first)
          writer.template_root = File.join(writer.template_root, 'exf', 'dds')
          writer.overload_template(:pre_extra_include, 'exf/dds/pre_extra_include')
        end
      end

    end # ExF4DDS

  end # CCMX11

end # IDL
