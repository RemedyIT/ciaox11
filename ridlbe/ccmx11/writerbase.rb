#--------------------------------------------------------------------
# @file   writerbase.rb
# @author Martin Corino
#
# @brief  Base class for IDL typecode and client stubs
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------
require 'ridlbe/c++11/writerbase'

module IDL
  module Cxx11

    # Reopen Output writer base class to add CCMX11 specifics
    #
    class CxxCodeWriterBase
      def declare_component(node)
      end
      def enter_component(node)
        return if self.no_scope_tracking?(node)
        @properties[:_context][:scopes].push(node)
        @properties[:_context][:cur_scope] = node
      end
      def leave_component(node)
        return if self.no_scope_tracking?(node)
        @properties[:_context][:scopes].pop
        @properties[:_context][:cur_scope] = @properties[:_context][:scopes].last
      end
      def enter_connector(node)
        return if self.no_scope_tracking?(node)
        @properties[:_context][:scopes].push(node)
        @properties[:_context][:cur_scope] = node
      end
      def leave_connector(node)
        return if self.no_scope_tracking?(node)
        @properties[:_context][:scopes].pop
        @properties[:_context][:cur_scope] = @properties[:_context][:scopes].last
      end

    end # CxxCodeWriterBase

  end
end
