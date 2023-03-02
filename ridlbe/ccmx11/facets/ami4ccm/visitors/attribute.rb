#--------------------------------------------------------------------
# @file    attribute.rb
# @author  Marijke Hengstmengel
#
# @brief   visitor class(es)
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------
require 'ridlbe/c++11/visitors/exception'

module IDL
  module Cxx11

    # Reopen AttributeVisitor class to add AMI4CCMX specifics
    #
    class AttributeVisitor
      def gen_attribute(extra_props = {})
        visit_template('attribute', extra_props)
      end
    end
  end
end
