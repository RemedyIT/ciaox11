#--------------------------------------------------------------------
# @file    corba4ccm_idl.rb
# @author  Marcel Smit
#
# @brief   CORBA connector IDL file writer
#
# @copyright Copyright (c) Remedy IT Expertise BV
# Chamber of commerce Rotterdam nr.276339, The Netherlands
#--------------------------------------------------------------------
require 'ridlbe/c++11/writerbase'
require 'ridlbe/c++11/writers/helpers/include_guard_helper'

module IDL

  module CCMX11

    module CORBA

      class IDLForCorbaConnectorWriter <  Cxx11::CxxCodeWriterBase
        helper Cxx11::IncludeGuardHelper

        def initialize(output = STDOUT, opts = {})
          super
          self.template_root = 'cc_idl'
          @include_guard = "__RIDL_CORBA_#{(File.basename(params[:idlfile], File.extname(params[:idlfile])) || '').to_random_include_guard}_IDL__"
        end

        attr_accessor :include_guard

        def pre_visit(parser)
          visitor(PreVisitor).visit
        end

        def post_visit(parser)
          visitor(PostVisitor).visit
        end

        def enter_interface(node)
          visitor(InterfaceVisitor).visit_interface(node) if is_conn_interface?(node)
        end

      protected

        def is_conn_interface?(node)
          (!node.is_local?) && (!node.is_abstract?) && (params[:conn_intf].blank? || params[:conn_intf] == node.scoped_name)
        end

      end #IDLForCorbaConnectorWriter

    end # CORBA
  end # CCMX11
end # IDL
