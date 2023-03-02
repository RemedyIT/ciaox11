#--------------------------------------------------------------------
# @file    connector.rb
# @author  Martin Corino
#
# @brief   DDS4CCM extension for connector visitor
#
# @copyright Copyright (c) Remedy IT Expertise BV
#----------------------------------------------------------------------

module IDL
  module CCMX11
    # reopen and extend
    class ConnectorVisitor
      def dds4ccm_error_event_strategy_template
        '::CIAOX11::DDS4CCM::DefaultErrorEventStrategy_T'
      end

      def needs_dds4ccm_event_strategy?(ext_port)
        case ext_port.name.to_s
        when 'passive_observer',
          'pull_observer',
          'push_observer',
          'push_state_observer',
          'pull_consumer',
          'push_consumer'
          return true
        end
        false
      end

      def dds4ccm_event_strategy_template(ext_port)
        case ext_port.name.to_s
        when 'passive_observer'
          return '::CIAOX11::DDS4CCM::DefaultPassiveObserverEventStrategy_T'
        when 'pull_observer'
          return '::CIAOX11::DDS4CCM::DefaultPullObserverEventStrategy_T'
        when 'push_observer'
          return '::CIAOX11::DDS4CCM::DefaultPushObserverEventStrategy_T'
        when 'push_state_observer'
          return '::CIAOX11::DDS4CCM::DefaultPushStateObserverEventStrategy_T'
        when 'pull_consumer'
          return '::CIAOX11::DDS4CCM::DefaultPullConsumerEventStrategy_T'
        when 'push_consumer'
          return '::CIAOX11::DDS4CCM::DefaultPushConsumerEventStrategy_T'
        end
      end
    end
  end
end
