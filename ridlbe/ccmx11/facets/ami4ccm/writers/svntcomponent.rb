#--------------------------------------------------------------------
# @file    svntcomponent.rb
# @author  Marijke Hengstmengel
#
# @brief   writer class(es) for ami4ccm
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------
require 'ridlbe/c++11/writerbase'
require 'ridlbe/ccmx11/writers/helpers/version_helper'

module IDL
  module CCMX11
    module Ami4ccmSvntComponentHeaderExt
      module WriterExtension
        def self.included(base)
          base.class_eval do
            helper_method :has_ami4ccm?

            def has_ami4ccm?
              params[:ami4ccm]
            end

            def pre_visit_with_ami(parser)
              properties[:ami4ccm_receptacles] = parser.ami4ccm_receptacles
              pre_visit_without_ami(parser)
            end

            alias_method_chain :pre_visit, :ami
          end
        end
      end

      def self.configure_extension(writer)
        writer.params[:ami4ccm] = true
        writer.append_template(:context_extra_members, 'ami/context_extra_members')
        writer.append_template(:context_extra_receptacles, 'ami/context_extra_receptacles')
      end
    end

    module Ami4ccmSvntComponentSourceExt
      module WriterExtension
        def self.included(base)
          base.class_eval do
            helper_method :has_ami4ccm?

            def has_ami4ccm?
              params[:ami4ccm]
            end

            def pre_visit_with_ami(parser)
              properties[:ami4ccm_receptacles] = parser.ami4ccm_receptacles
              pre_visit_without_ami(parser)
            end

            alias_method_chain :pre_visit, :ami
          end
        end
      end

      def self.configure_extension(writer)
        writer.params[:ami4ccm] = true
        writer.append_template(:context_extra_connect, 'ami/context_extra_connect')
        writer.append_template(:context_extra_disconnect, 'ami/context_extra_disconnect')
        writer.append_template(:context_extra_receptacles, 'ami/context_extra_receptacles')
      end
    end

    module Ami4ccmSvntConnectorHeaderExt
      module WriterExtension
        def self.included(base)
          base.class_eval do
            def enter_connector(node)
              visitor(ConnectorVisitor) do |v|
                v.singleton_class.class_eval do
                  include IDL::CCMX11::AMI4CCM::HideFacets
                end
                v.visit_component(node)
              end
            end
          end
        end
      end
    end

    module Ami4ccmSvntConnectorSourceExt
      module WriterExtension
        def self.included(base)
          base.class_eval do
            # overload
            def pre_visit(parser)
              visitor(PreVisitor).visit
            end

            def enter_connector(node)
              visitor(ConnectorVisitor) do |v|
                v.singleton_class.class_eval do
                  include IDL::CCMX11::AMI4CCM::HideFacets
                end
                v.visit_component(node)
              end
            end
          end
        end
      end

      def self.configure_extension(writer)
        writer.override_template(:component_init_connect, 'ami/component_init_connect')
        writer.override_template(:pre_extra_include, 'ami/pre_extra_include')
      end
    end
  end # CCMX11
end # IDL
