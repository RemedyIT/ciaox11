#--------------------------------------------------------------------
# @file    udttraits.rb
# @author  Marcel Smit
#
# @brief   writer class for the user defined type conversion traits
#          for DDSX11
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------
require 'ridlbe/c++11/writerbase'
require 'ridlbe/c++11/writers/helpers/include_guard_helper'

module IDL
  module CCMX11
    module DDSX11
      class UserDefinedTypeTraitsBaseWriter < Cxx11::CxxCodeWriterBase
        def initialize(output = STDOUT, opts = {})
          super
          self.template_root = 'udt_traits'
        end

        attr_accessor :include_guard
      end

      class UserDefinedTypeTraitsWriter < UserDefinedTypeTraitsBaseWriter
        helper_method :template_args
        helper Cxx11::IncludeGuardHelper
        helper Cxx11::VersionHelper

        def initialize(output = STDOUT, opts = {})
          super
          @include_guard = "__RIDL_DDSX11_#{(File.basename(params[:idlfile], File.extname(params[:idlfile])) || '').to_random_include_guard}_INCLUDED__"
        end

        def template_args
          @template_args
        end

        def pre_visit(parser)
          visit_includes(parser)
          super
        end

        def post_visit(parser)
          super
          visitor(PostVisitor).visit
        end

        def visit_includes(parser)
          writer(UserDefinedTypeTraitsIncludeWriter) do |w|
            w.template_root = self.template_root
            w.include_guard = @include_guard
            w.visit_nodes(parser)
          end
        end

        def enter_struct(node)
          visitor(StructVisitor).visit_struct(node)
        end

        def enter_union(node)
          visitor(UnionVisitor).visit_union(node)
        end

        def visit_include(node)
          visitor(IncludeVisitor).visit(node)
        end

        def visit_typedef(node)
          if ::IDL::Type::Sequence === node.idltype
            if !(::IDL::Type::ScopedName === node.idltype.basetype) ||
                ::IDL::Type::ScopedName === node.idltype.basetype &&
                !(::IDL::AST::Interface === node.idltype.basetype.node)
              # generate conversion traits for types, but not for interfaces.
              visitor(SequenceVisitor).visit_sequence(node)
            end
          elsif ::IDL::Type::Array === node.idltype
            visitor(ArrayVisitor).visit_array(node)
          elsif ::IDL::Type::String === node.idltype
            visitor(TypedefVisitor).visit_string(node)
          end
        end

        def add_include(inc_file)
          @includes << inc_file unless @includes.include?(inc_file)
        end
      end # DDSX11IDLWriter

      class UserDefinedTypeTraitsIncludeWriter < UserDefinedTypeTraitsBaseWriter
        helper Cxx11::IncludeGuardHelper
        helper Cxx11::VersionHelper

        def initialize(output = STDOUT, opts = {})
          super
          @includes = []
        end

        attr_reader :includes

        def post_visit(parser)
          properties[:includes] = @includes
          visitor(PreVisitor).visit
        end

        def visit_typedef(node)
          return if IDL::Type::Native === node.idltype.resolved_type && params[:no_gen_native]
          return if IDL::Type::ScopedName === node.idltype # alias typedef

          idl_type = node.idltype.resolved_type
          case idl_type
          when IDL::Type::String, IDL::Type::WString
            add_include('tao/x11/base/bounded_string_t.h') if idl_type.size.to_i > 0
            add_include('tao/x11/base/bounded_type_traits_t.h') if idl_type.size.to_i > 0
          end
        end

        private

        def add_include(inc_file)
          @includes << inc_file unless @includes.include?(inc_file)
        end
      end # UserDefinedTypeTraitsIncludeWriter
    end # DDSX11
  end # CCMX11
end # IDL
