#--------------------------------------------------------------------
# @file    compexec_extensions.rb
# @author  Martin Corino
#
# @brief   ExF extensions for CORBA4CCM connector executor generation
#
# @copyright Copyright (c) Remedy IT Expertise BV
# Chamber of commerce Rotterdam nr.276339, The Netherlands
#--------------------------------------------------------------------
require 'ridlbe/c++11/writerbase'

module IDL

  module CCMX11

    module ExF

      module CorbaCompExecHeaderExt

        def self.configure_extension(writer)
          IDL.log(3, 'Configuring ExF CorbaCompExecHeader extension')
          # make writer look for templates in ExF folder first
          # (requires CORBA4CCM extension to be loaded first)
          writer.template_root = File.join(writer.template_root, 'exf')
        end

      end

      module CorbaCompExecSourceExt

        def self.configure_extension(writer)
          IDL.log(3, 'Configuring ExF CorbaCompExecSource extension')
          # make writer look for templates in ExF folder first
          # (requires CORBA4CCM extension to be loaded first)
          writer.template_root = File.join(writer.template_root, 'exf')
          # append ExF template after regular template
          writer.append_template(:pre, :pre_exf)
        end
      end

    end # ExF

  end # CCMX11

end # IDL
