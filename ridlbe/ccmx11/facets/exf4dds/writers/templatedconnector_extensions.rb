#--------------------------------------------------------------------
# @file    templatedconnector_extensions.rb
# @author  Martin Corino
#
# @brief   ExF for DDS4CCM extensions for templated connector generation
#
# @copyright Copyright (c) Remedy IT Expertise BV
# Chamber of commerce Rotterdam nr.276339, The Netherlands
#--------------------------------------------------------------------

module IDL

  module CCMX11

    module ExF4DDS

      module TemplatedConnectorImplSourceExt

        module WriterExtension
          def self.included(base)
            base.class_eval do
              def enter_connector(node)
                 visitor(ExF4DDS::ConnectorVisitor).visit_connector(node)
              end
            end
          end
        end

        def self.configure_extension(writer)
          IDL.log(3, 'Configuring ExF4DDS TemplatedConnectorImplSourceExt extension')
          # make writer look for templates in exf folder first
          writer.template_root = File.join(writer.template_root, 'exf')
          # override template with ExF4DDS template
          writer.override_template(:pre, :pre_exf4dds)
        end
      end

    end # DDS4CCM

  end # CCMX11

end # IDL
