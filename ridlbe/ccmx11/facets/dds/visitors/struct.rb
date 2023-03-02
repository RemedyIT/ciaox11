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
    end # StructVisitor

    class StructMemberVisitor
      def has_key_annotation?
        !self.annotations[:key].empty?
      end
    end
  end # CCMX11
end # IDL
