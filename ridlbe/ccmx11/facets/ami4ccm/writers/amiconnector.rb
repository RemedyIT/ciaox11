#--------------------------------------------------------------------
# @file    amiconnector.rb
# @author  Marijke Hengstmengel
#
# @brief   walker class for amiconnector
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------------
require 'ridlbe/c++11/writerbase'
require 'ridlbe/c++11/writers/helpers/include_guard_helper'

module IDL

  module CCMX11

    module AMI4CCM

    class AmiConnectorBaseWriter < Cxx11::CxxCodeWriterBase
      def initialize(output = STDOUT, opts = {})
        super
        self.template_root = 'acon'
        self.disable_scope_tracking = true
      end

      attr_accessor :include_guard
      helper Cxx11::IncludeGuardHelper
    end

    #write the xxxA_conn.idl file for the ami connector
    class AmiConnectorConnIDLWriter < AmiConnectorBaseWriter
      helper_method :is_ami_conn_idl?

      def initialize(output = STDOUT, opts = {})
        super
        self.template_root = File.join(self.template_root, 'idl')
        @include_guard = "__RIDL_#{File.basename(params[:acon_conn_idl] || '').to_random_include_guard}_INCLUDED__"
        properties[:idl_a_file] = File.join(File.basename(params[:idlfile], params[:idlext]) +
                                     params[:ami_idl_pfx] + params[:idlext])
        properties[:acon_lem_stub_include] = File.join(File.basename(params[:idlfile], params[:idlext]) +
                                                params[:ami_idl_conn_pfx] + params[:lem_pfx] + params[:idlext])
      end

      def is_ami_conn_idl?
        true
      end

      def pre_visit(parser)
        visitor(PreVisitor).visit
        super
      end

      def post_visit(parser)
        super
        visitor(PostVisitor).visit
      end

      def enter_module(node)
        super
        println
        printiln('// generated from AmiConnectorConnIDLWriter#enter_module')
        printiln('module ' + node.cxxname)
        printiln('{')
        inc_nest
      end

      def leave_module(node)
        dec_nest
        println
        printiln("}; // module #{node.cxxname}")
        super
      end

      def enter_interface(node)
        visitor(InterfaceVisitor).visit_connector(node) if is_conn_interface?(node)
      end

    protected

      def is_conn_interface?(node)
        (!node.is_local?) && (!node.is_abstract?) && node.has_ami_annotation? && (params[:conn_intf].blank? || params[:conn_intf] == node.scoped_name)
      end

    end # AmiConnectorConnIDLWriter

    #write the xxxA.idl file for the ami interfaces
    class AmiConnectorIDLWriter < AmiConnectorBaseWriter
      helper_method :is_ami_conn_idl?

      def initialize(output = STDOUT, opts = {})
        super
        self.template_root = File.join(self.template_root, 'idl')
        @include_guard = "__RIDL_#{File.basename(params[:acon_idl] || '').to_random_include_guard}_INCLUDED__"
        properties[:acon_lem_stub_include] = File.join(File.basename(params[:idlfile], params[:idlext]) +
                                                params[:ami_idl_pfx] + params[:lem_pfx] + params[:idlext])
      end

      def is_ami_conn_idl?
         false
      end

      def pre_visit(parser)
        properties[:ami4ccm_receptacles] = parser.ami4ccm_receptacles
        visitor(PreVisitor).visit
        super
      end

      def post_visit(parser)
        super
        visitor(PostVisitor).visit
      end

      def visit_include(node)
        visitor(IncludeVisitor).visit(node)
      end

      def enter_module(node)
        super
        println
        printiln('// generated from AmiConnectorIDLWriter#enter_module')
        printiln('module ' + node.cxxname)
        printiln('{')
        inc_nest
      end

      def leave_module(node)
        dec_nest
        println
        printiln("}; // module #{node.cxxname}")
        super
      end

      def enter_interface(node)
        return if node.is_local? || node.is_abstract? || !node.has_ami_annotation?
        visitor(InterfaceVisitor).visit_ami(node)
      end
    end # AmiConnectorIDLWriter

    class AmiConnectorHeaderWriter < AmiConnectorBaseWriter
      def initialize(output = STDOUT, opts = {})
        super
        self.template_root = File.join(self.template_root, 'hdr')
        @include_guard = "__RIDL_#{File.basename(params[:conn_exec_output_hdr] || '').to_random_include_guard}_INCLUDED__"

        properties[:lem_stub_include] = File.basename(params[:idlfile], params[:idlext]) + params[:lem_pfx] + params[:stub_pfx] + params[:hdr_ext]

        #get the base header, remove the A_conn.idl
        base_name = File.basename(params[:idlfile], params[:idlext])
        base_name = base_name.chomp(params[:ami_idl_conn_pfx])
        #generate  the  AmiC.h name
        properties[:ami_stub_include] = base_name + params[:ami_pfx] + params[:stub_pfx] + params[:hdr_ext]
        #gnerate the  AS.h name
        properties[:svntc_skel_include] = base_name + params[:ami_idl_pfx] + params[:srv_pfx] + params[:hdr_ext]
      end

      def pre_visit(parser)
        visitor(PreVisitor).visit
      end

      def post_visit(parser)
        visitor(PostVisitor).visit
      end

      def enter_connector(node)
        visitor(ConnectorVisitor).visit_connector(node)
      end
    end # AmiConnectorHeaderWriter

    class AmiConnectorSourceWriter < AmiConnectorBaseWriter
      def initialize(output = STDOUT, opts = {})
        super
        self.template_root = File.join(self.template_root, 'src')
        properties[:acon_header] = File.basename(params[:conn_exec_output_hdr])
      end

      def pre_visit(parser)
        visitor(PreVisitor).visit
      end

      def post_visit(parser)
        visitor(PostVisitor).visit
      end

      def enter_connector(node)
        visitor(ConnectorVisitor).visit_connector(node)
      end
    end # AmiConnectorSourceWriter

    end #AMI4CCM

  end # CCMX11

end # IDL
