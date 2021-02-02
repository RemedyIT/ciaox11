#--------------------------------------------------------------------
# @file    servantheader.rb
# @author  Marijke Hengstmengel
#
# @brief   Writer class for servant header
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------
require 'ridlbe/c++11/writers/servantheader'
require 'ridlbe/ccmx11/writers/helpers/version_helper'

module IDL
  module Cxx11

    # Reopen ServantHeaderWriter class to add CCMX11 specifics
    #
    class ServantHeaderWriter

      helper CCMX11::VersionHelper

      def visit_attribute(node)
        return if node.enclosure.is_a?(IDL::AST::Component) ||
                  node.enclosure.is_a?(IDL::AST::Connector) ||
                  node.enclosure.is_local? ||
                  node.enclosure.is_abstract?
        visitor(AttributeVisitor).visit_attribute(node)
      end

    end

  end # Cxx11
end # IDL
