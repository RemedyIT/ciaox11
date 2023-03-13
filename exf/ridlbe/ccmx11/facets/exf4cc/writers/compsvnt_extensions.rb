#--------------------------------------------------------------------
# @file    compsvnt_extensions.rb
# @author  Martin Corino
#
# @brief   ExF extensions for CORBA4CCM connector servant generation
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------
require 'ridlbe/c++11/writerbase'

module IDL
  module CCMX11
    module ExF
      module CorbaCompSvntHeaderExt
        def self.configure_extension(writer)
          IDL.log(3, 'Configuring ExF CorbaCompExecHeader extension')
          # make writer look for templates in ExF folder first
          # (requires CORBA4CCM extension to be loaded first)
          writer.template_root = File.join(writer.template_root, 'corba', 'exf')
        end
      end

      module CorbaCompSvntSourceExt
        def self.configure_extension(writer)
          IDL.log(3, 'Configuring ExF CorbaCompExecSource extension')
          # make writer look for templates in ExF folder first
          # (requires CORBA4CCM extension to be loaded first)
          writer.template_root = File.join(writer.template_root, 'corba', 'exf')
          writer.overload_template(:pre_extra_include, 'corba/exf/pre_extra_include')
        end
      end
    end # ExF
  end # CCMX11
end # IDL
