#--------------------------------------------------------------------
# @file    ddstypesupport.rb
# @author  Johnny Willemsen
#
# @brief   writer class for the type support header and source
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------
require 'ridlbe/c++11/writerbase'
require 'ridlbe/c++11/writers/helpers/include_guard_helper'

module IDL
  module CCMX11
    module DDSX11
      class DDSTypeSupportBaseWriter < Cxx11::CxxCodeWriterBase
        def initialize(output = STDOUT, opts = {})
          super
        end

      protected

        def init_visitor(v, node)
          v.properties[:topic_namespaces] =
              (params[:dds_topic_namespace] && params[:dds_topic_namespace].split('::')) ||
                  node.scopes[0, node.scopes.length - 1].collect { |s| s.name }
        end

        def is_dds_topic?(node)
          if params[:dds_topic].blank? || params[:dds_topic] == node.scoped_name
            return has_toplevel_annotation?(node)
          end

          false
        end

        def has_toplevel_annotation?(node)
          # 20190730 Add support for AXCIOMA 2 top-level annotation, issue #4729
          annot = node.annotations[:'top-level'].first || node.annotations[:TopLevel].first || node.annotations[:'top_level'].first
          return false if annot.nil?

          annot.fields[:value].nil? || annot.fields[:value]
        end
      end # DDSTypeSupportBaseWriter

      class DDSTypeSupportHeaderWriter < DDSTypeSupportBaseWriter
        helper Cxx11::IncludeGuardHelper
        helper Cxx11::VersionHelper

        def initialize(output = STDOUT, opts = {})
          super
          self.template_root = 'typesupport/hdr'
          @include_guard = "__RIDL_DDS_#{(File.basename(params[:idlfile], File.extname(params[:idlfile])) || '').to_random_include_guard}_TYPESUPPORT_HDR__"
        end

        attr_accessor :include_guard

        def pre_visit(parser)
          visitor(PreVisitor).visit
        end

        def post_visit(parser)
          visitor(PostVisitor).visit

          visit_dds_traits(parser)
        end

        def visit_dds_traits(parser)
          writer(DDSTraitsWriter).visit_nodes(parser)
        end

        def enter_struct(node)
          visitor(StructVisitor) do |v|
            init_visitor(v, node)
            v.visit_factory(node)
          end if is_dds_topic?(node)
        end

        def enter_union(node)
          visitor(UnionVisitor) do |v|
            init_visitor(v, node)
            v.visit_factory(node)
          end if is_dds_topic?(node)
        end
      end # DDSTypeSupportHeaderWriter

      class DDSTraitsWriter < DDSTypeSupportBaseWriter
        helper Cxx11::IncludeGuardHelper
        helper Cxx11::VersionHelper

        def initialize(output = STDOUT, opts = {})
          super
        end

        attr_accessor :include_guard

        def pre_visit(parser); end

        def post_visit(parser); end

        def enter_module(node); end

        def leave_module(node); end

        def enter_struct(node)
          visitor(StructVisitor) do |v|
            init_visitor(v, node)
            v.visit_toplevel(node)
          end if is_dds_topic?(node)
        end

        def enter_union(node)
          visitor(UnionVisitor) do |v|
            init_visitor(v, node)
            v.visit_toplevel(node)
          end if is_dds_topic?(node)
        end
      end # DDSTraitsWriter

      class DDSX11TraitsWriter < DDSTypeSupportBaseWriter
        helper Cxx11::IncludeGuardHelper
        helper Cxx11::VersionHelper

        def initialize(output = STDOUT, opts = {})
          super
        end

        attr_accessor :include_guard

        def pre_visit(parser); end

        def post_visit(parser); end

        def enter_module(node); end

        def leave_module(node); end

        def enter_struct(node)
          visitor(StructVisitor) do |v|
            init_visitor(v, node)
            v.visit_toplevel_seq(node)
          end if is_dds_topic?(node)
        end

        def enter_union(node)
          visitor(UnionVisitor) do |v|
            init_visitor(v, node)
            v.visit_toplevel_seq(node)
          end if is_dds_topic?(node)
        end
      end # DDSX11TraitsWriter

      class DDSTypeSupportSourceWriter < DDSTypeSupportBaseWriter
        helper Cxx11::IncludeGuardHelper
        helper CCMX11::VersionHelper

        def initialize(output = STDOUT, opts = {})
          super
          self.template_root = 'typesupport/src'
          @include_guard = "__RIDL_DDS_#{(File.basename(params[:idlfile], File.extname(params[:idlfile])) || '').to_random_include_guard}_TYPESUPPORT_SRC__"
        end

        attr_accessor :include_guard

        def pre_visit(parser)
          visitor(PreVisitor).visit

          visit_ddsx11_traits(parser)
        end

        def post_visit(parser)
          visitor(PostVisitor).visit
        end

        def visit_ddsx11_traits(parser)
          writer(DDSX11TraitsWriter).visit_nodes(parser)
        end

        def enter_struct(node)
          visitor(StructVisitor) do |v|
            init_visitor(v, node)
            v.visit_factory(node)
          end if is_dds_topic?(node)
        end

        def enter_union(node)
          visitor(StructVisitor) do |v|
            init_visitor(v, node)
            v.visit_factory(node)
          end if is_dds_topic?(node)
        end
      end # DDSTypeSupportSourceWriter
    end # DDSX11
  end # CCMX11
end # IDL
