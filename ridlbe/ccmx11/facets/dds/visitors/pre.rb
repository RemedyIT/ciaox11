#--------------------------------------------------------------------
# @file    pre.rb
# @author  Marcel Smit
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
      def ddsx11_incl
        @ddsx11_includes ||= []
      end
      def ddsx11_includes
        if ddsx11_incl.empty?
          self.ddsx11_incl << 'dds/dds_vendor_adapter.h'
          self.ddsx11_incl << 'dds/dds_make_reference.h'
          self.ddsx11_incl << 'dds/dds_domain_participant_factory.h'
          self.ddsx11_incl << 'dds/dds_domain_participant.h'
          self.ddsx11_incl << 'dds/dds_type_support.h'
          self.ddsx11_incl << 'dds/dds_typefactory_t.h'
        end
        ddsx11_incl
      end

      def idl_base
        idl_ext = (params[:idlext] ||= File.extname(params[:idlfile]))
        File.basename(params[:idlfile], idl_ext)
      end

      def stub_include
        idl_base + 'C.h'
      end

      def dds_traits_include
        # return without any output directories prefixed
        idl_base + params[:dds_idl_pfx] + '_traits.h'
      end

      def dds_typesupport_include
        # return without any output directories prefixed
        include = idl_base + params[:dds_typesupport_pfx] + params[:hdr_ext]
      end

      def dds_entity_include
        # return without any output directories prefixed
        idl_base + params[:dds_typed_entities_pfx] + params[:stub_pfx] + params[:hdr_ext]
      end
    end # PreVisitor
  end # Cxx11
end # IDL
