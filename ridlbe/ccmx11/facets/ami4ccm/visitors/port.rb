#--------------------------------------------------------------------
# @file    port.rb
# @author  Marijke Hengstmengel
#
# @brief   visitor class(es)
#
# @copyright Copyright (c) Remedy IT Expertise BV
#----------------------------------------------------------------------
require 'ridlbe/c++11/visitors/interface.rb'
require 'ridlbe/ccmx11/visitors/mixins/ccm_names.rb'

module IDL
  module CCMX11

    # Reopen PortVisitor class to add AMI4CCM specifics
    class PortVisitor < Cxx11::NodeVisitorBase

      def is_ami4ccm_port?
        (port_type == :receptacle && properties[:ami4ccm_receptacles].include?(scoped_cxxname)) ? true : false
      end

      def gen_reply_handler_exec(extra_props = {})
        visit_template('reply_handler', extra_props)
      end

      def ami4ccm_rh_executor
        "AMI4CCM_#{interface_type.cxxname}ReplyHandler_#{cxxname}_i"
      end

    end
  end
end