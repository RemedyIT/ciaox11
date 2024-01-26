#--------------------------------------------------------------------
# @file    struct.rb
# @author  Marcel Smit
#
# @brief   structvisitor
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------
require 'ridlbe/c++11/visitors/include'
require 'ridlbe/ccmx11/visitors/mixins/ccm_names'

module IDL
  module CCMX11
    # Reopen visitor class to add DDS specifics
    #
    class StructVisitor < Cxx11::NodeVisitorBase
      include CcmNames

      optional_template :life_cycle_traits

      def annotations
        # Add appendable when it is not final available
         ann = node.annotations.dup
         unless ann[:'final'].first
           ann << IDL::AST::Annotation.new('appendable', {})
         end
         # Determine correct value for DDS nested annotation
         nested = 'TRUE'
         nested = 'FALSE' if has_toplevel_annotation?
         ann << IDL::AST::Annotation.new('nested', {value: nested})
      end
    end # StructVisitor
  end # CCMX11
end # IDL
