#--------------------------------------------------------------------
# @file    ddstypedentitiesidl.rb
# @author  Marcel Smit
#
# @brief   writer class for the DDS typed entities (typed datareader/datawriter) IDL
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------
require 'ridlbe/c++11/writerbase'
require 'ridlbe/c++11/writers/helpers/include_guard_helper'

module IDL

  module CCMX11

    module DDSX11

      class DDSTypeEntitiesIDLWriter < Cxx11::CxxCodeWriterBase
        helper Cxx11::IncludeGuardHelper

        def initialize(output = STDOUT, opts = {})
          super
          self.template_root = 'idl/typed_entities'
          @include_guard = "__RIDL_DDS_#{(File.basename(params[:idlfile], File.extname(params[:idlfile])) || '').to_random_include_guard}_IDL__"
        end

        attr_accessor :include_guard

        def pre_visit(parser)
          visitor(PreVisitor).visit
        end

        def post_visit(parser)
          visitor(PostVisitor).visit
        end

        def enter_struct(node)
          visitor(StructVisitor) do |v|
            init_visitor(v, node)
            v.visit_entities(node)
          end if is_dds_topic?(node)
        end

        def enter_union(node)
          visitor(UnionVisitor) do |v|
            init_visitor(v, node)
            v.visit_entities(node)
          end if is_dds_topic?(node)
        end

      protected
        def init_visitor(v, node)
          v.properties[:topic_namespaces] =
              (params[:dds_topic_namespace] && params[:dds_topic_namespace].split('::')) ||
                  node.scopes[0, node.scopes.length - 1].collect {|s| s.unescaped_name }
        end

        def is_dds_topic?(node)
          if params[:dds_topic].blank? || params[:dds_topic] == node.scoped_name
            return has_toplevel_annotation?(node)
          end
          false
        end

        def has_toplevel_annotation?(node)
          # 20190730 Add support for AXCIOMA 2 top-level annotation, issue #4729
          annot = node.annotations[:'top-level'].first || node.annotations[:TopLevel].first
          return false if annot.nil?
          return annot.fields[:value].nil? || annot.fields[:value]
        end

      end # DDSTypeEntitiesIDLWriter

    end # DDSX11

  end # CCMX11

end # IDL
