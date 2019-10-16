#--------------------------------------------------------------------
# @file    componentexecutor.rb
# @author  Marcel Smit
#
# @brief   writer class(es) for corba4ccm facets
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------
require 'ridlbe/c++11/writerbase'
require 'ridlbe/ccmx11/writers/helpers/version_helper'
require 'ridlbe/ccmx11/visitors/component'

module IDL

  module CCMX11

    module CorbaExecComponentHeaderExt

      module WriterExtension
        def self.included(base)
          base.class_eval do
            helper CCMX11::VersionHelper

            def visit_include(node)
              return if File.basename(node.filename) == 'orb.idl'
              at_global_scope do
                visitor(IncludeVisitor).visit(node)
              end
            end
          end
        end

      end

      def self.configure_extension(writer)
        writer.template_root = File.join(writer.template_root, 'corba')
        writer.properties[:svntc_skel_include] =
            File.basename(writer.params[:idlfile],writer.params[:idlext]) + writer.params[:srv_pfx] + writer.params[:hdr_ext]

        # add CORBA4CCM specific template extensions
        writer.add_optional_template(:component_extra_public, IDL::CCMX11::ComponentVisitor)
        writer.add_optional_template(:component_extra_private, IDL::CCMX11::ComponentVisitor)
      end

    end

    module CorbaExecComponentSourceExt
      def self.configure_extension(writer)
        writer.template_root = File.join(writer.template_root, 'corba')

        # add CORBA4CCM specific template extensions
        writer.add_optional_template(:component_extra_impl, IDL::CCMX11::ComponentVisitor)
      end
    end

  end # CCMX11

end # IDL
