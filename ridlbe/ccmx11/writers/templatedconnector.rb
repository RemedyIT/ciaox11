#--------------------------------------------------------------------
# @file    templatedconnector.rb
# @author  Marijke Hengstmengel
#
# @brief   walker class for component executor
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------
require 'ridlbe/ccmx11/writers/helpers/version_helper'
require 'ridlbe/c++11/writerbase'
require 'ridlbe/c++11/writers/helpers/include_guard_helper'

module IDL

  module CCMX11

    class TemplatedConnectorImplBaseWriter < Cxx11::CxxCodeWriterBase
      helper Cxx11::IncludeGuardHelper

      attr_accessor :include_guard

      def initialize(output = STDOUT, opts = {})
        super
        self.template_root = 'conn_templ'

        self.disable_scope_tracking = false

        @include_guard = "__RIDL_#{File.basename(params[:conn_exec_output_hdr] || '').to_random_include_guard}_INCLUDED__"
        # include without any output directories prefixed
        properties[:conn_exec_lem_stub_include] = File.basename(params[:idlfile], params[:idlext]) + params[:lem_pfx] + 'C' + params[:hdr_ext]
      end

    end

    class TemplatedConnectorImplHeaderWriter < TemplatedConnectorImplBaseWriter

      helper CCMX11::VersionHelper

      def initialize(output = STDOUT, opts = {})
        super
        self.template_root = File.join(self.template_root, 'hdr')
      end

      def pre_visit(parser)
        visitor(PreVisitor).visit
      end

      def post_visit(parser)
        visitor(PostVisitor).visit
      end

      def enter_connector(node)
        # uses @template_args
        visitor(ConnectorVisitor).visit_connector(node)
      end

    end # TemplatedConnectorImplHeaderWriter

    class TemplatedConnectorImplSourceWriter < TemplatedConnectorImplBaseWriter

      def initialize(output = STDOUT, opts = {})
        super
        self.template_root = File.join(self.template_root, 'src')
        properties[:conn_exec_header] = File.basename(params[:conn_exec_output_hdr])
      end

      def pre_visit(parser)
        visitor(PreVisitor).visit
      end

      def post_visit(parser)
        visitor(PostVisitor).visit
      end

      def visit_include(node)
        visitor(IncludeVisitor).visit(node)
      end

      def enter_connector(node)
         # uses @template_args
         visitor(ConnectorVisitor).visit_connector(node)
      end

    end # TemplatedConnectorImplSourceWriter


  end # CCMX11

end # IDL
