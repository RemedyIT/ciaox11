#--------------------------------------------------------------------
# @file    operation.rb
# @author  Marijke Hengstmengel
#
# @brief   visitor class(es)
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------
require 'ridlbe/ccmx11/visitors/mixins/ccm_names'

module IDL
  module Cxx11

    # Reopen OperationVisitor class to add AMI4CCM specifics
    #
    class OperationVisitor
      include CCMX11::CcmNames

      def gen_operation(extra_props = {})
        visit_template('operation', extra_props)
      end
    end

    class ArgumentVisitor
    # out or inout argument of operation becomes in argument of ReplyHandler
      def idl_arg_type_rph
        case direction
          when :in
            ""
          when :out
            "in #{idltype_name}"
          else
            "in #{idltype_name}"
        end
      end

      def idl_arg_type
        case direction
          when :in
            "in #{idltype_name}"
          when :out
            "out #{idltype_name}"
          else
            "inout #{idltype_name}"
        end
      end
    end

  end
end
