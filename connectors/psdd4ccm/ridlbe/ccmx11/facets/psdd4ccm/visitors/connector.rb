#--------------------------------------------------------------------
# @file    connector.rb
# @author  Martin Corino
#
# @brief   PSDD4CCM extension for connector visitor
#
# @copyright Copyright (c) Remedy IT Expertise BV
#----------------------------------------------------------------------

module IDL
  module CCMX11

    module PSDD4CCM

      # extend
      class ConnectorVisitor < CCMX11::ConnectorVisitor

        def psdd4ccm_event_strategy_template
          '::CIAOX11::PSDD4CCM::DefaultPushConsumerEventStrategy_T'
        end

        # overload
        def template_name
          "CIAOX11::PSDD::Event_Connector_T"
        end

      end

    end

  end
end
