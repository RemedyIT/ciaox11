#--------------------------------------------------------------------
# @file    localexecutormapping.rb
# @author  Johnny Willemsen
#
# @brief   walker class for local executor mapping support
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------
require 'ridlbe/c++11/writerbase'
require 'ridlbe/c++11/writers/helpers/include_guard_helper'

module IDL
  module CCMX11
    class LemExecutorIDLWriterBase < Cxx11::CxxCodeWriterBase
      def initialize(output = STDOUT, opts = {})
        super
        self.template_root = 'lem_idl'

        self.disable_scope_tracking = false
      end
      attr_accessor :include_guard
    end

    class LemComponentScanner < Cxx11::CxxCodeWriterBase
      attr_accessor :has_component, :has_connector
      def initialize(output = STDOUT, opts = {})
        super
        self.disable_scope_tracking = true
      end

      def enter_component(node)
        @has_component ||= true
        detect_lem_includes(node)
      end

      def enter_connector(node)
        @has_connector ||= true
        detect_lem_includes(node)
      end

      def visit_include(node)
        node.all_lem_includes.each do |lem_inc|
          add_lem_include(lem_inc)
        end
      end

      def lem_includes
        @lem_includes ||= []
      end

      private

      def add_lem_include(lem_inc)
        # add LEM include; prevent duplicates
        lem_includes << lem_inc unless lem_includes.include?(lem_inc)
      end

      def detect_lem_includes(comp)
        # When the component is derived from another we need to
        # find the lem stub where the base component is defined in
        if comp.base
          detect_included_interface(comp.base)
        end
        comp.ports.each do |port|
          # For an interface used as facet we need to
          # included the interface LEM include, for a
          # receptacle the IDL file defining the interface
          # is already included in the component/connector IDL
          if port.porttype == :facet
            # see if interface declared in include file
            # get port interface node
            intf = port.idltype.resolved_type.node
            detect_included_interface(intf)
          end
        end
      end

      def detect_included_interface(node)
        # see if interface node is leaf of Include node
        while node.enclosure
          if IDL::AST::Include === node.enclosure
            # included interface needs LEM include
            add_lem_include(node.enclosure.filename.sub(/\.idl\Z/i, 'E.idl'))
            break
          end
          node = node.enclosure
        end
      end
    end

    class LemExecutorIDLWriter < LemExecutorIDLWriterBase
      helper_method :has_component?, :has_connector?, :has_lem_includes?, :lem_includes
      helper Cxx11::IncludeGuardHelper

      def initialize(output = STDOUT, opts = {})
        super
        @include_guard = "__RIDL_#{File.basename(params[:lem_output_file] || '').to_random_include_guard}_INCLUDED__"
        if params[:stripped_filename] != nil
          properties[:org_idl_include] = params[:stripped_filename]
        else
          properties[:org_idl_include] = File.basename(params[:idlfile], params[:idlext]) + params[:idlext]
        end
      end

      def has_component?
        @has_component || @has_connector
      end

      def has_connector?
        @has_connector
      end

      def lem_includes
        @lem_includes ||= []
      end

      def has_lem_includes?
        !lem_includes.empty?
      end

      def pre_visit(parser)
        writer(LemComponentScanner) do |w|
          w.visit_nodes(parser)
          @has_component = w.has_component ? true : false
          @has_connector = w.has_connector ? true : false
          @lem_includes = w.lem_includes
        end
        visitor(PreVisitor).visit
      end

      def post_visit(parser)
        visitor(PostVisitor).visit
      end

      def enter_interface(node)
        return if node.is_abstract?

        annot = node.annotations[:"lem"]
        return if annot[0] != nil && annot[0].fields[:value] != nil && annot[0].fields[:value] == false

        visitor(InterfaceVisitor).visit_lem(node)
      end

      def enter_component(node)
        visitor(ComponentVisitor).visit_lem(node)
      end

      def enter_connector(node)
        visitor(ConnectorVisitor).visit_lem(node)
      end

      def module_needs_lem_code?(modnode)
        modnode.match_members do |c|
          if IDL::AST::Interface === c || IDL::AST::ComponentBase === c || IDL::AST::Home === c
            true
          elsif IDL::AST::Module === c
            module_needs_lem_code?(c)
          else
            false
          end
        end
      end

      def enter_module(node)
        super
        if module_needs_lem_code?(node)
          println
          printiln('// generated from LemExecutorIDLWriter#enter_module')
          printiln('module ' + node.unescaped_name)
          printiln('{')
          inc_nest
        end
      end

      def leave_module(node)
        if module_needs_lem_code?(node)
          dec_nest
          println
          printiln("}; // module #{node.unescaped_name}")
          super
        end
      end
    end # LemExecutorIDLWriter

    module LemExecutor
      IDLWriter = LemExecutorIDLWriter

      def self.set_idl_writer(klass)
        remove_const(:IDLWriter) if const_defined?(:IDLWriter)
        const_set(:IDLWriter, klass)
      end
    end
  end # CCMX11
end # module IDL
