#--------------------------------------------------------------------
# @file    sequence.rb
# @author  Marcel Smit
#
# @brief   sequence visitor
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------
require 'ridlbe/c++11/visitors/include'

module IDL

  module CCMX11

    # Reopen visitor class to add DDS specifics
    #
    class SequenceVisitor

      def is_string_type?
        ::IDL::Type::String === self._resolved_idltype.basetype.resolved_type
      end

      def is_bounded_string_type?
        is_string_type? && !self._resolved_idltype.basetype.resolved_type.length.nil?
      end

      def is_boolean_type?
        ::IDL::Type::Boolean === self._resolved_idltype.basetype.resolved_type
      end

      def is_integer_type?
        ::IDL::Type::Integer === self._resolved_idltype.basetype.resolved_type
      end

      def is_longlong_type?
        ::IDL::Type::LongLong === self._resolved_idltype.basetype.resolved_type
      end

      def is_ulonglong_type?
        ::IDL::Type::ULongLong === self._resolved_idltype.basetype.resolved_type
      end

      def is_float_type?
        ::IDL::Type::Float === self._resolved_idltype.basetype.resolved_type
      end

      def is_char_type?
        ::IDL::Type::Char === self._resolved_idltype.basetype.resolved_type || ::IDL::Type::WChar === self._resolved_idltype.basetype.resolved_type
      end

    end # SequenceVisitor

  end # CCMX11

end # IDL
