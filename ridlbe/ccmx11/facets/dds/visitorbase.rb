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
    # Reopen C++11 VisitorBase to add DDSX11 specific properties
    #
    class VisitorBase
      # For all implied C++11 types we do not need the escaped C++ namespace but the unescaped C++ name
      # because we add a postfix to the name which always results in a unique name which doesn't
      # conflict with a C++ keyword (for example Foo::structDataWriter)
      def native_scoped_name_prefix
        '::DDS_Native' + (!scoped_enclosure_cxxname.empty? ? '::' : '') + "#{scoped_enclosure_cxxname}::#{name}"
      end

      def native_scoped_cxxtype
        (scoped_cxxtype.start_with?('::') ? '::DDS_Native' : '') + "#{scoped_cxxtype}"
      end

      def native_scoped_seq_cxxtype
        "#{native_scoped_name_prefix}Seq"
      end

      def scoped_seq_cxxtype
        (!scoped_enclosure_cxxname.empty? ? '::' : '') + "#{scoped_enclosure_cxxname}::#{name}Seq"
      end

      def scoped_implied_idl_prefix
        (!scoped_enclosure_cxxname.empty? ? '::' : '') + "#{scoped_enclosure_cxxname}::#{name}"
      end

      def typedef_sequence_dds_type_needed?
        # Only generate a implied unbounded sequence typedef when there is not in the enclosing scope a typedef of our type
        # with a Seq postfix already
        @node.enclosure.select_members { |m| m.is_a?(IDL::AST::Typedef) && m.idltype.is_a?(IDL::Type::Sequence) && (m.idltype.basetype.resolved_type.is_a?(IDL::Type::Struct) || m.idltype.basetype.resolved_type.is_a?(IDL::Type::Union)) && m.idltype.basetype.resolved_type.resolved_node == @node && m.unescaped_name == sequence_dds_type && m.idltype.size.nil? }.empty?
      end

      def sequence_dds_type
        "#{name}Seq"
      end

      def typedef_sequence_dds_type
        # No cxxname since we're writing to IDL
        "typedef sequence<#{unescaped_name}> #{sequence_dds_type};"
      end

      def strip_global_scope(typename)
        typename.sub(/^::/, '')
      end

      def has_toplevel_annotation?
        # 20190730 Add support for AXCIOMA 2 top-level annotation, issue #4729
        annot = self.annotations[:'top-level'].first || self.annotations[:TopLevel].first
        return false if annot.nil?

        annot.fields[:value].nil? || annot.fields[:value]
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
