#--------------------------------------------------------------------
# @file    interface.rb
# @author  Marijke Hengstmengel
#
# @brief   visitor class(es)
#
# @copyright Copyright (c) Remedy IT Expertise BV
# Chamber of commerce Rotterdam nr.276339, The Netherlands
#--------------------------------------------------------------------
require 'ridlbe/ccmx11/visitors/mixins/ccm_names.rb'

module IDL
  module Cxx11

    # Reopen InterfaceVisitor class to add AMI4CCM specifics
    #
    class InterfaceVisitor

      def ami4ccm_cxxname
        'AMI4CCM_' + cxxname
      end

      def ami4ccm_reply_handler
        ami4ccm_cxxname + '_reply_handler'
      end

      def ami4ccm_ReplyHandler
        ami4ccm_cxxname + 'ReplyHandler'
      end

      def scoped_ami4ccm_cxxname
        scoped_enclosure_cxxname.scope_to_cxxname + '::AMI4CCM_' + cxxname
      end

    end
  end
end
