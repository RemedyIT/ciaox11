#--------------------------------------------------------------------
# @file    servantsource.rb
# @author  Marijke Hengstmengel
#
# @brief   writer class(es)
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------
require 'ridlbe/c++11/writers/servantsource'

module IDL
  module Cxx11
    # Reopen ServantSourceIncludeWriter class to add CCMX11 specifics
    #
    class ServantSourceIncludeWriter
      def visit_attribute(node)
        return if node.enclosure.is_a?(IDL::AST::Component) ||
                  node.enclosure.is_a?(IDL::AST::Connector) ||
                  node.enclosure.is_local? || node.enclosure.is_pseudo? || node.enclosure.is_abstract?
        check_idl_type(node.idltype)
      end
    end # ServantSourceIncludeWriter

    # Reopen ServantSourceSArgTraitsWriter class to add CCMX11 specifics
    #
    class ServantSourceSArgTraitsWriter
      def check_idl_type_with_cxx11_check_idl_type(idl_type)
        res_idl_type = idl_type.resolved_type
        case res_idl_type
        when IDL::Type::Component
          return
          # visitor(CCMX11::ComponentVisitor).visit_sarg_traits(res_idl_type.node) unless is_tracked?(res_idl_type.node)
        else
          check_idl_type_without_cxx11_check_idl_type(idl_type)
        end
      end

      alias_method_chain :check_idl_type, :cxx11_check_idl_type

      def visit_attribute(node)
        return if node.enclosure.is_a?(IDL::AST::Component) ||
                  node.enclosure.is_a?(IDL::AST::Connector) ||
                  node.enclosure.is_local? || node.enclosure.is_pseudo? || node.enclosure.is_abstract?
        check_idl_type(node.idltype)
      end
    end # ServantSourceSArgTraitsWriter
  end # Cxx11
end # IDL
