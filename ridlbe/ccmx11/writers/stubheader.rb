#--------------------------------------------------------------------
# @file    stubheader.rb
# @author  Marijke Hengstmengel
#
# @brief   Writer class for stub header
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------
require 'ridlbe/c++11/writers/stubheader'

module IDL
  module Cxx11

    # Reopen StubHeaderWriter class to add CCMX11 specifics
    #
    class StubHeaderWriter

      def visit_attribute(node)
        return if node.enclosure.is_a?(IDL::AST::Component) ||
                   node.enclosure.is_a?(IDL::AST::Connector)
        visitor(AttributeVisitor).visit_attribute(node)
      end

    end # StubHeaderWriter

  end # Cxx11

end # IDL
