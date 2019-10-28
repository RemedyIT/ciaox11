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

        def enter_module(node)
          super
          println()
          printiln('// generated from DDSTypeEntitiesIDLWriter#enter_module')
          printiln('module ' + node.unescaped_name)
          printiln('{')
          inc_nest
        end

        def leave_module(node)
          dec_nest
          println()
          printiln("}; // module #{node.unescaped_name}")
          super
        end

        def enter_struct(node)
          visitor(StructVisitor).visit_entities(node)
        end

        def enter_union(node)
          visitor(UnionVisitor).visit_entities(node)
        end

      end # DDSTypeEntitiesIDLWriter

    end # DDSX11

  end # CCMX11

end # IDL
