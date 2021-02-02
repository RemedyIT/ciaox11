#--------------------------------------------------------------------
# @file    visitorbase.rb
# @author  Marcel Smit
#
# @brief   base class for DDS visitors
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------
require 'ridlbe/c++11/visitorbase'

module IDL

  module Cxx11

    # Reopen C++11 VisitorBase to add CCMX11 specific properties
    #
    class VisitorBase

      # Need to put more native here, shouldn't add "DDS_Native" to templates
      def native_type_name
        scoped_cxxtype.start_with?('::') ? "DDS_Native#{scoped_cxxtype}" : "#{scoped_cxxtype}"
      end

      def typedef_sequence_dds_type_needed?
        params[:gen_typedef_sequence_dds_type]
      end

      def typedef_sequence_dds_type
        # No cxxname since we're writing to IDL
        return "typedef sequence<#{unescaped_name}> #{name}Seq;"
      end

      def strip_global_scope(typename)
        typename.sub(/^::/, '')
      end

      def idl_type_name
        self.strip_global_scope self._idltype.idltype_name
      end

      def type_name
        strip_global_scope(scoped_cxxtype)
      end

      def has_toplevel_annotation?
        # 20190730 Add support for AXCIOMA 2 top-level annotation, issue #4729
        annot = self.annotations[:'top-level'].first || self.annotations[:TopLevel].first
        return false if annot.nil?
        return annot.fields[:value].nil? || annot.fields[:value]
      end

      def typesupport_export_include?
        params[:typesupport_export_include]
      end

      def typesupport_export_include
        params[:typesupport_export_include]
      end

      def typesupport_export_macro
        params[:typesupport_export_macro] ? params[:typesupport_export_macro] + ' ' : ''
      end
    end # VisitorBase

  end # Cxx11

end # IDL
