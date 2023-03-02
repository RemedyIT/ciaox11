#--------------------------------------------------------------------
# @file    stubsource.rb
# @author  Marijke Hengstmengel
#
# @brief   Writer class for stub source
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------
require 'ridlbe/c++11/writers/stubsource'

module IDL
  module Cxx11
    # Reopen StubSourceWriter class to add CCMX11 specifics
    #
    class StubSourceWriter
      def visit_attribute(node)
        return if node.enclosure.is_a?(IDL::AST::Component) ||
                  node.enclosure.is_a?(IDL::AST::Connector) ||
                  node.enclosure.is_local?
        visitor(AttributeVisitor).visit_attribute(node)
      end
    end # StubSourceWriter
  end
end
