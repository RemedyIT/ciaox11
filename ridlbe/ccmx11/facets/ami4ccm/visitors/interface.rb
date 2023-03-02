#--------------------------------------------------------------------
# @file    interface.rb
# @author  Marijke Hengstmengel
#
# @brief   visitor class(es)
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------
require 'ridlbe/ccmx11/visitors/mixins/ccm_names'

module IDL
  module Cxx11

    # Reopen InterfaceVisitor class to add AMI4CCM specifics
    #
    class InterfaceVisitor
      def ami4ccm_name
        'AMI4CCM_' + name
      end

      def ami4ccm_reply_handler
        ami4ccm_name + '_reply_handler'
      end

      def ami4ccm_ReplyHandler
        ami4ccm_name + 'ReplyHandler'
      end

      def scoped_ami4ccm_name
        scoped_enclosure_name + '::AMI4CCM_' + name
      end
    end
  end
end
