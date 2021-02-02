#--------------------------------------------------------------------
# @file    componentexecutor.rb
# @author  Marijke Hengstmengel
#
# @brief   walker class for component and connector executor
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------
require 'ridlbe/c++11/writerbase'
require 'ridlbe/c++11/writers/helpers/include_guard_helper'

module IDL

  module CCMX11

    module AmiComponentExecutorHeaderEx

      module WriterExtension

        def self.included(base)
          base.class_eval do
            helper_method :has_ami4ccm_receptacles?

            def has_ami4ccm_receptacles?
              properties[:ami4ccm_receptacles].size > 0
            end

            def pre_visit_with_ami(parser)
              properties[:ami4ccm_receptacles] = parser.ami4ccm_receptacles
              pre_visit_without_ami(parser)
            end

            alias_method_chain :pre_visit, :ami

            def visit_include_with_ami(node)
              visitor(IncludeVisitor).visit(node)
              visit_include_without_ami(node)
            end

            alias_method_chain :visit_include, :ami
          end
        end

      end

      def self.configure_extension(writer)
        writer.append_template(:component_end_extra, 'ami/component_end_extra')
        writer.append_template(:include, 'ami/include')
      end

    end

    module AmiComponentExecutorSourceEx

      module WriterExtension

        def self.included(base)
          base.class_eval do
            helper_method :has_ami4ccm_receptacles?

            def has_ami4ccm_receptacles?
              properties[:ami4ccm_receptacles].size > 0
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
        writer.append_template(:component_end_extra, 'ami/component_end_extra')
      end

    end

  end # CCMX11

end # IDL
