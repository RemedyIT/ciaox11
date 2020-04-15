#--------------------------------------------------------------------
# @file    templatedconnector_extensions.rb
# @author  Martin Corino
#
# @brief   PSDD4CCM extensions for templated connector generation
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------

module IDL

  module CCMX11

    module PSDD4CCM

      module TemplatedConnectorImplSourceExt

        module WriterExtension
          def self.included(base)
            base.class_eval do
              def enter_connector(node)
                 visitor(PSDD4CCM::ConnectorVisitor).visit_connector(node)
              end
            end
          end
        end

        def self.configure_extension(writer)
          IDL.log(3, 'Configuring PSDD4CCM TemplatedConnectorImplSourceExt extension')
          # make writer look for templates in psdd4ccm folder first
          writer.template_root = File.join(writer.template_root, 'psdd4ccm')
          # append event strategy include template
          writer.append_template(:pre, :pre_psdd4ccm_evs)
          # append regular template with PSDD4CCM template
          writer.append_template(:pre, :pre_psdd4ccm)
        end
      end

    end # PSDD4CCM

  end # CCMX11

end # IDL
