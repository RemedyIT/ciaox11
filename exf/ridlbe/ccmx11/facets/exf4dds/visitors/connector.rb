#--------------------------------------------------------------------
# @file    connector.rb
# @author  Martin Corino
#
# @brief   ExF4DDS extension for connector visitor
#
# @copyright Copyright (c) Remedy IT Expertise BV
#----------------------------------------------------------------------

module IDL
  module CCMX11
    module ExF4DDS
      class ConnectorVisitor < CCMX11::ConnectorVisitor
        # overload
        def dds4ccm_error_event_strategy_template
          '::CIAOX11::DDS4CCM::ExF::ErrorEventStrategy_T'
        end

        # overload
        def dds4ccm_event_strategy_template(ext_port)
          case ext_port.name.to_s
          when 'passive_observer'
            return '::CIAOX11::DDS4CCM::ExF::PassiveObserverEventStrategy_T'
          when 'pull_observer'
            return '::CIAOX11::DDS4CCM::ExF::PullObserverEventStrategy_T'
          when 'push_observer'
            return '::CIAOX11::DDS4CCM::ExF::PushObserverEventStrategy_T'
          when 'push_state_observer'
            return '::CIAOX11::DDS4CCM::ExF::PushStateObserverEventStrategy_T'
          when 'pull_consumer'
            return '::CIAOX11::DDS4CCM::ExF::PullConsumerEventStrategy_T'
          when 'push_consumer'
            return '::CIAOX11::DDS4CCM::ExF::PushConsumerEventStrategy_T'
          end
        end
      end
    end
  end
end
