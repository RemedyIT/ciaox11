#--------------------------------------------------------------------
# @file    ddsidl.rb
# @author  Marcel Smit
#
# @brief   writer class for the DDS specific IDL
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------
require 'ridlbe/c++11/writerbase'
require 'ridlbe/c++11/writers/helpers/include_guard_helper'

module IDL

  module CCMX11

    module DDSX11

      class DDSIDLWriter < Cxx11::CxxCodeWriterBase
        helper Cxx11::IncludeGuardHelper

        attr_accessor :include_guard

        def initialize(output = STDOUT, opts = {})
          super
          self.template_root = 'idl/dds'
          @include_guard = "__RIDL_DDS_ENTITIES_#{(File.basename(params[:idlfile], File.extname(params[:idlfile])) || '').to_random_include_guard}_IDL__"
          @dds_native_module = false
          @last_module = nil
          @module_stack = []
        end

        def enter_module(node)
          super
          mark_namespace_begin(node)
        end

        def leave_module(node)
          mark_namespace_end(node)
          super
        end

        def pre_visit(parser)
          visitor(PreVisitor).visit
        end

        def post_visit(parser)
          end_dds_native_namespace if @dds_native_module
          visitor(PostVisitor).visit
        end

        def visit_include(node)
          visitor(IncludeVisitor).visit(node)
        end

        def enter_struct(node)
          check_namespace_begin
          visitor(::IDL::Cxx11::StructVisitor).visit_struct(node)
        end

        def visit_enum(node)
          check_namespace_begin
          visitor(EnumVisitor).visit_enum(node)
        end

        def enter_union(node)
          check_namespace_begin
          visitor(UnionVisitor).visit_union(node)
        end

        def visit_typedef(node)
          check_namespace_begin
          visitor(TypedefVisitor).visit_typedef(node)
        end

      private

        def check_namespace_begin
          start_dds_native_namespace unless @dds_native_module
          if @last_module
            printiln('module ' + @last_module.unescaped_name)
            printiln('{')
            inc_nest
            @module_stack << @last_module
            @last_module = nil
          end
        end

        def mark_namespace_begin(node)
          check_namespace_begin
          @last_module = node
        end

        def mark_namespace_end(node)
          if @last_module == node
            @last_module = nil
          elsif @module_stack.last == node
            dec_nest
            println()
            printiln("}; // module #{node.unescaped_name}")
            @module_stack.pop
          end
        end

        def start_dds_native_namespace
          println()
          printiln('module DDS_Native')
          printiln('{')
          inc_nest
          @dds_native_module = true
        end

        def end_dds_native_namespace
          dec_nest
          println()
          printiln('}; // module DDS_Native')
          @dds_native_module = false
        end

      end # DDSIDLWriter

    end # DDSX11

  end # CCMX11

end # IDL
