#--------------------------------------------------------------------
# @file    templatedconnector_extensions.rb
# @author  Martin Corino
#
# @brief   DDS4CCM extensions for templated connector generation
#
# @copyright Copyright (c) Remedy IT Expertise BV
# Chamber of commerce Rotterdam nr.276339, The Netherlands
#--------------------------------------------------------------------

module IDL

  module CCMX11

    module DDS4CCM

      module TemplatedConnectorImplSourceExt
        def self.configure_extension(writer)
          IDL.log(3, 'Configuring DDS4CCM TemplatedConnectorImplSourceExt extension')
          # make writer look for templates in dds4ccm folder first
          writer.template_root = File.join(writer.template_root, 'dds4ccm')
          # override regular template with DDS4CCM template
          writer.override_template(:pre, :pre_dds4ccm)
        end
      end # TemplatedConnectorImplSourceExt

    end # DDS4CCM

  end # CCMX11

end # IDL
