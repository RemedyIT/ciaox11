#--------------------------------------------------------------------
# @file    connector.rb
# @author  Martin Corino
#
# @brief   ExF4PSDD extension for connector visitor
#
# @copyright Copyright (c) Remedy IT Expertise BV
#----------------------------------------------------------------------
require 'ridlbe/ccmx11/facets/psdd4ccm/visitors/connector'

module IDL
  module CCMX11

    module ExF4PSDD

      class ConnectorVisitor < CCMX11::PSDD4CCM::ConnectorVisitor
        # overload
        def psdd4ccm_event_strategy_template
          '::CIAOX11::PSDD4CCM::ExF::PushConsumerEventStrategy_T'
        end
      end

    end

  end
end
