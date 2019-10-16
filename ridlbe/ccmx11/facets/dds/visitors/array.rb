#--------------------------------------------------------------------
# @file    array.rb
# @author  Marcel Smit
#
# @brief   array visitor
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------
require 'ridlbe/c++11/visitors/include'

module IDL

  module CCMX11

    # Reopen visitor class to add DDS specifics
    #
    class ArrayVisitor

      def dds_native_element_cxxtype
        "::DDS_Native::#{strip_global_scope self.scoped_cxxname}"
      end

      def sizes
        self._resolved_idltype.sizes.collect { |s| "[#{IDL::Expression::ScopedName === s ? s.node.name : s.to_s}]" }.join
      end

      optional_template :life_cycle_traits
    end # ArrayVisitor

  end # CCMX11

end # IDL
