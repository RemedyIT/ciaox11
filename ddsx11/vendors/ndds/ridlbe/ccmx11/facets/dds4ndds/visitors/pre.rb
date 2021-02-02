#--------------------------------------------------------------------
# @file    pre.rb
# @author  Johnny Willemsen
#
# @brief   previsitor
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------
require 'ridlbe/c++11/visitors/include'

module IDL
  module Cxx11

    # Reopen visitor class to add DDSX11 specifics
    #
    class PreVisitor

      def ndds_native_stub_include
        # return without any output directories prefixed
        idl_base + params[:dds_idl_pfx] + '.h'
      end

      def ndds_support_include
        # return without any output directories prefixed
        idl_base + params[:dds_idl_pfx] + 'Support.h'
      end

    end # PreVisitor

  end # Cxx11
end # IDL
