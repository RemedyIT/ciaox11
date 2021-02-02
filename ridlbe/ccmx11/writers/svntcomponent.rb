#--------------------------------------------------------------------
# @file    svntcomponent.rb
# @author  Marijke Hengstmengel
#
# @brief   writer class(es)
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------
require 'ridlbe/c++11/writerbase'
require 'ridlbe/ccmx11/writers/helpers/version_helper'
require 'ridlbe/c++11/writers/helpers/include_guard_helper'

module IDL

  module CCMX11

    class SvntComponentBaseWriter < Cxx11::CxxCodeWriterBase
      def initialize(output = STDOUT, opts = {})
        super
        self.template_root = 'svnt'

        self.disable_scope_tracking = true
      end
      attr_accessor :include_guard
    end

    class SvntComponentHeaderWriter < SvntComponentBaseWriter

      class IncludeScanner < Cxx11::CxxCodeWriterBase
        attr_reader :uses_multiple
        attr_reader :has_non_local_facets
        def initialize(output = STDOUT, opts = {})
          super
          self.disable_scope_tracking = true
        end

        def enter_component(node)
          visitor(ComponentVisitor) do |v|
            v.visit(node)
            @has_non_local_facets ||= v.has_non_local_facet_ports?
            @uses_multiple ||= v.incl_multiple_port?
          end
        end

        def enter_connector(node)
          visitor(ConnectorVisitor) do |v|
            v.visit(node)
            @has_non_local_facets ||= v.has_non_local_facet_ports?
            @uses_multiple ||= v.incl_multiple_port?
          end
        end

      end

      helper CCMX11::VersionHelper
      helper Cxx11::IncludeGuardHelper
      helper_method :uses_multiple?

      def initialize(output = STDOUT, opts = {})
        super
        self.template_root = File.join(self.template_root, 'hdr')
        @include_guard = "__RIDL_#{File.basename(params[:svntcomp_output_h] || '').to_random_include_guard}_INCLUDED__"
        properties[:svnt_lem_include] = File.basename(params[:idlfile], params[:idlext]) + params[:lem_pfx] + params[:stub_pfx] + params[:hdr_ext]

        # Get the base svnt header
        base_name = File.basename(params[:idlfile], params[:idlext])
        base_name = base_name.chomp(params[:ccon_pfx])
        properties[:base_svnt_header] = base_name + params[:svnt_impl_pfx] + params[:hdr_ext]
      end

      def uses_multiple?
        @uses_multiple
      end

      def pre_visit(parser)
        writer(IncludeScanner) do |w|
          w.visit_nodes(parser)
          @uses_multiple = w.uses_multiple ? true : false
        end
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

    end # ComponentSvntHeaderWriter

    class SvntComponentSourceWriter < SvntComponentBaseWriter

      # special AST scanner to check for any non-local facets in any component
      class IncludeScanner < Cxx11::CxxCodeWriterBase
        attr_reader :has_non_local_facets
        def initialize(output = STDOUT, opts = {})
          super
          self.disable_scope_tracking = true
        end

        def enter_component(node)
          visitor(ComponentVisitor) do |v|
            v.visit(node)
            @has_non_local_facets ||= v.has_non_local_facet_ports?
          end
        end

        def enter_connector(node)
          visitor(ConnectorVisitor) do |v|
            v.visit(node)
            @has_non_local_facets ||= v.has_non_local_facet_ports?
          end
        end

      end

      def initialize(output = STDOUT, opts = {})
        super
        self.template_root = File.join(self.template_root, 'src')
        properties[:svntc_header] = File.basename(params[:svntcomp_output_h])
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

    end # CorbaComponentSvntSourceWriter

    module SvntComponent

      HeaderWriter = SvntComponentHeaderWriter
      SourceWriter = SvntComponentSourceWriter

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
