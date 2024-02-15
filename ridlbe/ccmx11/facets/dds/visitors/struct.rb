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
        ann = node.annotations.dup
        # Add appendable when it is not final available
        unless ann[:'final'].first
          ann << IDL::AST::Annotation.new('appendable', {})
        end
        # When generating the nested annotation we need to use TRUE/FALSE
        if has_toplevel_annotation?
          nes_annot = ann[:nested].first
          case nes_annot.fields[:value]
          when TrueClass
            nes_annot.fields[:value] = 'TRUE'
          when FalseClass
            nes_annot.fields[:value] = 'FALSE'
          end
        end
        ann
      end
    end # StructVisitor
  end # CCMX11
end # IDL
