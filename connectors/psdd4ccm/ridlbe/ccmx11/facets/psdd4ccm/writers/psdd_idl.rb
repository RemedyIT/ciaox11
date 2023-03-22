#--------------------------------------------------------------------
# @file    psdd_idl.rb
# @author  Martin Corino
#
# @brief   writer class for the PSDD4CCM PSDD connector IDL
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------
require 'ridlbe/c++11/writerbase'
require 'ridlbe/c++11/writers/helpers/include_guard_helper'

module IDL
  module CCMX11
    module PSDD4CCM
      class PSDDIDLWriter < Cxx11::CxxCodeWriterBase
        helper Cxx11::IncludeGuardHelper

        helper_method :topic_idl

        def initialize(output = STDOUT, opts = {})
          super
          self.template_root = 'psdd_idl'
          @include_guard = "__RIDL_#{(File.basename(params[:idlfile], File.extname(params[:idlfile])) || '').to_random_include_guard}_IDL__"
        end

        attr_accessor :include_guard

        def topic_idl
          File.basename(params[:idlfile])
        end

        def pre_visit(parser)
          visitor(PreVisitor) do |v|
            # make sure the pre-template generates correctly
            v.properties[:no_topic_idl] = params[:no_input]
            v.visit
            if params[:no_input]
              # there no nodes that will be visited
              # topic should be a basic IDL type so
              # simply generate here
              v.properties[:topic_namespaces] =
                  (params[:psdd_topic_namespace] && params[:psdd_topic_namespace].split('::')) || []
              v.properties[:topic_sequence] =
                  (params[:psdd_topic] && params[:psdd_topic_seq]) ||
                      "#{params[:psdd_topic]}#{params[:psdd_topic_seq_suffix] || 'Seq'}"
              v.properties[:topic_interface] =
                  (params[:psdd_topic] && params[:psdd_topic_if]) ||
                      "#{params[:psdd_topic]}#{params[:psdd_topic_if_suffix] || 'Interface'}"
              v.properties[:scoped_name] = params[:psdd_topic]
              v.visit_psdd_interface
            end
          end
        end

        def post_visit(parser)
          visitor(PostVisitor).visit
        end

        def enter_struct(node)
          visitor(StructVisitor) do |v|
            init_visitor(v, node)
            v.visit_psdd_interface(node)
          end if is_psdd_topic?(node)
        end

        def enter_union(node)
          visitor(UnionVisitor) do |v|
            init_visitor(v, node)
            v.visit_psdd_interface(node)
          end if is_psdd_topic?(node)
        end

        def visit_typedef(node)
          idl_type = node.idltype.resolved_type
          case idl_type
          when IDL::Type::Struct,
              IDL::Type::Union,
              IDL::Type::String,
              IDL::Type::WString
            visitor(TypedefVisitor) do |v|
              init_visitor(v, node)
              v.visit_psdd_interface(node)
            end if is_psdd_topic?(node)
          else
            if idl_type.is_pod?
              visitor(TypedefVisitor) do |v|
                init_visitor(v, node)
                v.visit_psdd_interface(node)
              end if is_psdd_topic?(node)
            end
          end
        end

      protected

        def init_visitor(v, node)
          v.properties[:topic_namespaces] =
              (params[:psdd_topic_namespace] && params[:psdd_topic_namespace].split('::')) ||
                  node.scopes[0, node.scopes.length - 1].collect { |s| s.name }
          v.properties[:topic_sequence] =
              (params[:psdd_topic] && params[:psdd_topic_seq]) ||
                  "#{node.name}#{params[:psdd_topic_seq_suffix] || 'Seq'}"
          v.properties[:topic_interface] =
              (params[:psdd_topic] && params[:psdd_topic_if]) ||
                  "#{node.name}#{params[:psdd_topic_if_suffix] || 'Interface'}"
        end

        def is_psdd_topic?(node)
          if params[:psdd_topic].blank? || params[:psdd_topic] == node.scoped_name
            annot = node.annotations[:TopLevel]
            return false if annot[0] == nil
            return true if annot[0].fields[:value] == nil

            annot[0].fields[:value]
          end
          false
        end
      end # PSDDIDLWriter
    end # PSDD4CCM
  end # CCMX11
end # IDL
