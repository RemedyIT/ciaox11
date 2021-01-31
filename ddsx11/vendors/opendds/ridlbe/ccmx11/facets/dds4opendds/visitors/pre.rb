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

      def opendds_support_include
        # return without any output directories prefixed
        idl_base+params[:dds_idl_pfx]+'C.h'
      end

      def opendds_native_stub_include
        # return without any output directories prefixed
        idl_base+params[:dds_idl_pfx]+'C.h'
      end

      def opendds_typesupport_impl_include
        # return without any output directories prefixed
        idl_base+params[:opendds_typesupportimpl_pfx]+params[:hdr_ext]
      end

    end # PreVisitor

  end # Cxx11
end # IDL
