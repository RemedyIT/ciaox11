#--------------------------------------------------------------------
# @file    componentexecutor.rb
# @author  Marijke Hengstmengel
#
# @brief   walker class for component and connector executor
#
# @copyright Copyright (c) Remedy IT Expertise BV
# Chamber of commerce Rotterdam nr.276339, The Netherlands
#--------------------------------------------------------------------
require 'ridlbe/c++11/writerbase'
require 'ridlbe/c++11/writers/helpers/include_guard_helper'

module IDL

  module CCMX11

    class ComponentExecutorBaseWriter < Cxx11::CxxCodeWriterBase
      def initialize(output = STDOUT, opts = {})
        super
        self.template_root = 'comp_exec'
        self.disable_scope_tracking = false
      end

      attr_accessor :include_guard
    end

    class ComponentExecutorHeaderWriter < ComponentExecutorBaseWriter
      helper Cxx11::IncludeGuardHelper

      def initialize(output = STDOUT, opts = {})
        super
        self.template_root = File.join(self.template_root, 'hdr')
        properties[:header_name] = File.basename(params[:comp_exec_output_hdr]).gsub('.', '_')
        @include_guard = "__RIDL_#{File.basename(params[:comp_exec_output_hdr] || '').to_random_include_guard}_INCLUDED__"
        # include without any output directories prefixed
        properties[:comp_exec_lem_stub_include] = File.basename(params[:idlfile], params[:idlext])+params[:lem_pfx]+'C'+params[:hdr_ext]
      end

      def pre_visit(parser)
        visitor(PreVisitor).visit
      end

      def post_visit(parser)
        visitor(PostVisitor).visit
      end

      def enter_component(node)
        visitor(ComponentVisitor).visit_component(node)
      end

      def enter_connector(node)
        visitor(ConnectorVisitor).visit_component(node)
      end

    end # ComponentExecutorHeaderWriter

    class ComponentExecutorSourceWriter < ComponentExecutorBaseWriter
      def initialize(output = STDOUT, opts = {})
        super
        self.template_root = File.join(self.template_root, 'src')
        properties[:comp_exec_header] = File.basename(params[:comp_exec_output_hdr])
        properties[:source_name] = File.basename(params[:comp_exec_output_src]).gsub('.', '_')
      end

      def pre_visit(parser)
        visitor(PreVisitor).visit
      end

      def post_visit(parser)
        visitor(PostVisitor).visit
      end

      def enter_component(node)
        visitor(ComponentVisitor).visit_component(node)
      end

      def enter_connector(node)
        visitor(ConnectorVisitor).visit_component(node)
      end

    end # ComponentExecutorSourceWriter


    module ComponentExecutor

      HeaderWriter = ComponentExecutorHeaderWriter
      SourceWriter = ComponentExecutorSourceWriter

      def self.set_header_writer(klass)
        remove_const(:HeaderWriter) if const_defined?(:HeaderWriter)
        const_set(:HeaderWriter, klass)
      end

      def self.set_source_writer(klass)
        remove_const(:SourceWriter) if const_defined?(:SourceWriter)
        const_set(:SourceWriter, klass)
      end

    end

  end # CCMX11

end # IDL
