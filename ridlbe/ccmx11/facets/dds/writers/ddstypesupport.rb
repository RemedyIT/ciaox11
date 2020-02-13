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

      class DDSTypeSupportHeaderWriter < Cxx11::CxxCodeWriterBase
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

        def enter_module(node)
          super
          println()
          printiln('// generated from DDSTypeSupportHeaderWriter')
          printiln('namespace ' + node.cxxname)
          printiln('{')
          inc_nest
        end

        def leave_module(node)
          dec_nest
          println()
          printiln("} // namespace #{node.cxxname}")
          super
        end

        def enter_struct(node)
          visitor(StructVisitor).visit_factory(node)
        end

        def enter_union(node)
          visitor(UnionVisitor).visit_factory(node)
        end
      end # DDSTypeSupportHeaderWriter

      class DDSTraitsWriter < Cxx11::CxxCodeWriterBase
        helper Cxx11::IncludeGuardHelper
        helper Cxx11::VersionHelper

        def initialize(output = STDOUT, opts = {})
          super
        end

        attr_accessor :include_guard

        def pre_visit(parser)
        end

        def post_visit(parser)
        end

        def enter_module(node)
        end

        def leave_module(node)
        end

        def enter_struct(node)
          visitor(StructVisitor).visit_toplevel(node)
        end

        def enter_union(node)
          visitor(UnionVisitor).visit_toplevel(node)
        end
      end # DDSTraitsWriter

      class DDSX11TraitsWriter < Cxx11::CxxCodeWriterBase
        helper Cxx11::IncludeGuardHelper
        helper Cxx11::VersionHelper

        def initialize(output = STDOUT, opts = {})
          super
        end

        attr_accessor :include_guard

        def pre_visit(parser)
        end

        def post_visit(parser)
        end

        def enter_module(node)
        end

        def leave_module(node)
        end

        def enter_struct(node)
          visitor(StructVisitor).visit_toplevel_seq(node)
        end

        def enter_union(node)
          visitor(UnionVisitor).visit_toplevel_seq(node)
        end
      end # DDSX11TraitsWriter

      class DDSTypeSupportSourceWriter < Cxx11::CxxCodeWriterBase
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

        def enter_module(node)
          super
          println()
          printiln('// generated from DDSTypeSupportSourceWriter')
          printiln('namespace ' + node.cxxname)
          printiln('{')
          inc_nest
        end

        def leave_module(node)
          dec_nest
          println()
          printiln("} // namespace #{node.cxxname}")
          super
        end

        def enter_struct(node)
          visitor(StructVisitor).visit_factory(node)
        end

        def enter_union(node)
          visitor(StructVisitor).visit_factory(node)
        end
      end # DDSTypeSupportSourceWriter

    end # DDSX11

  end # CCMX11

end # IDL
