#--------------------------------------------------------------------
# @file    union.rb
# @author  Marcel Smit
#
# @brief   union visitor
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------
require 'ridlbe/c++11/visitors/include'

module IDL
  module CCMX11
    # Reopen visitor class to add DDS specifics
    #
    class UnionMemberVisitor
      def dds_native_nondefault_labels(switchtype)
        node.labels.collect { |_l| _l == :default ? nil : switchtype.is_a?(::IDL::Type::ScopedName) ? '::DDS_Native' + expression_to_s(_l) : expression_to_s(_l) }.compact
      end

      def is_string_type?
        ::IDL::Type::String === self._resolved_idltype
      end

      def is_array_type?
        ::IDL::Type::Array === self._resolved_idltype
      end
    end

    class UnionVisitor
      def native_scoped_switch_cxxtype
        self.switchtype.is_a?(::IDL::Type::ScopedName) ? '::DDS_Native' + scoped_switch_cxxtype : scoped_switch_cxxtype
      end

      optional_template :life_cycle_traits

      def annotations
        # Add appendable when it is not final available
         ann = node.annotations.dup
         unless ann[:'final'].first
           ann << IDL::AST::Annotation.new('appendable', {})
         end
        ann
      end
    end
  end # CCMX11
end # IDL
