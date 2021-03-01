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
          @current_module = -1
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
          check_dds_native_namespace_end
          visitor(PostVisitor).visit
        end

        def visit_include(node)
          visitor(IncludeVisitor).visit(node)
        end

        def declare_struct(node)
          check_namespace_begin
          visitor(StructVisitor).visit_fwd(node)
        end

        def enter_struct(node)
          check_namespace_begin
          visitor(::IDL::Cxx11::StructVisitor).visit_struct(node)
        end

        def visit_enum(node)
          check_namespace_begin
          visitor(EnumVisitor).visit_enum(node)
        end

        def declare_union(node)
          check_namespace_begin
          visitor(UnionVisitor).visit_fwd(node)
        end

        def enter_union(node)
          check_namespace_begin
          visitor(UnionVisitor).visit_union(node)
        end

        def visit_typedef(node)
          case node.idltype.resolved_type
          when IDL::Type::Valuebox,
               IDL::Type::Valuetype,
               IDL::Type::ValueBase,
               IDL::Type::Eventtype,
               IDL::Type::Exception,
               IDL::Type::Native,
               IDL::Type::Object,
               IDL::Type::Interface
            return
          else
            check_namespace_begin
            visitor(TypedefVisitor).visit_typedef(node)
          end
        end

      private

        def check_namespace_begin
          check_dds_native_namespace
          unless @module_stack.empty?
            module_ix = @current_module + 1
            while module_ix < @module_stack.size
              printiln('module ' + @module_stack[module_ix].unescaped_name)
              printiln('{')
              inc_nest
              module_ix += 1
            end
            @current_module = @module_stack.size - 1
          end
        end

        def mark_namespace_begin(node)
          @module_stack << node
        end

        def mark_namespace_end(node)
          if @current_module >= 0 && @module_stack[@current_module] == node
            dec_nest
            println()
            printiln("}; // module #{node.unescaped_name}")
            @current_module -= 1
          end
          @module_stack.pop
        end

        def check_dds_native_namespace
          unless @dds_native_module
            println()
            printiln('module DDS_Native')
            printiln('{')
            inc_nest
            @dds_native_module = true
          end
        end

        def check_dds_native_namespace_end
          if @dds_native_module
            dec_nest
            println()
            printiln('}; // module DDS_Native')
            @dds_native_module = false
          end
        end

      end # DDSIDLWriter

    end # DDSX11

  end # CCMX11

end # IDL
