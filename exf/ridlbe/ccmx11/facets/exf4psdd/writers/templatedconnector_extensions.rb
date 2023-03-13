#--------------------------------------------------------------------
# @file    templatedconnector_extensions.rb
# @author  Martin Corino
#
# @brief   ExF for PSDD4CCM extensions for templated connector generation
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------

module IDL
  module CCMX11
    module ExF4PSDD
      module TemplatedConnectorImplSourceExt
        module WriterExtension
          def self.included(base)
            base.class_eval do
              def enter_connector(node)
                visitor(ExF4PSDD::ConnectorVisitor).visit_connector(node)
              end
            end
          end
        end

        def self.configure_extension(writer)
          IDL.log(3, 'Configuring ExF4PSDD TemplatedConnectorImplSourceExt extension')
          # make writer look for templates in exf folder first
          writer.template_root = File.join(writer.template_root, 'exf')
          # # override template with ExF4PSDD template
          # writer.override_template(:pre, :pre_exf4psdd)
        end
      end
    end # ExF4PSDD
  end # CCMX11
end # IDL
