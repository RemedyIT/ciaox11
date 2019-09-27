#--------------------------------------------------------------------
# @file    localexecutormapping.rb
# @author  Marijke Hengstmengel
#
# @brief   walker class for ami4ccm local executor mapping support
#
# @copyright Copyright (c) Remedy IT Expertise BV
# Chamber of commerce Rotterdam nr.276339, The Netherlands
#--------------------------------------------------------------------
require 'ridlbe/c++11/writerbase'

module IDL

  module CCMX11

    module Ami4ccmLemExecutorIDLExt

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

            def visit_include_with_ami(node)
              visit_include_without_ami(node)
              visitor(IncludeVisitor).visit(node)
            end

            alias_method_chain :pre_visit, :ami
            alias_method_chain :visit_include, :ami
          end
        end

      end

      def self.configure_extension(writer)
        writer.params[:ami4ccm] = true
        writer.append_template(:include, 'ami/include')
        writer.append_template(:lem_extra_multiple_receptacles, 'ami/lem_extra_multiple_receptacles')
        writer.append_template(:lem_extra_receptacles, 'ami/lem_extra_receptacles')
      end

    end

  end # CCMX11

end # module IDL
