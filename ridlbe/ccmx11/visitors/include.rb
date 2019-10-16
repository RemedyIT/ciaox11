#--------------------------------------------------------------------
# @file    include.rb
# @author  Martin Corino
#
# @brief   Include visitor
#
# @copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------
require 'ridlbe/c++11/visitors/include'

module IDL
  module Cxx11

    # Reopen visitor class to add ccmx11 specifics
    #
    class IncludeVisitor

      def has_impl_includes?(all = true)
        all ? !all_impl_includes.empty? : @node.has_impl_includes?
      end

      def impl_includes(all = true)
        all ? all_impl_includes : @node.impl_includes
      end

    protected

      def all_impl_includes
         @all_impl_incs ||= @node.all_impl_includes
      end

      optional_template :include

    end # IncludeVisitor

  end # Cxx11

end # IDL
