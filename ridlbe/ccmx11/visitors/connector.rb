#--------------------------------------------------------------------
# @file    connector.rb
# @author  Marijke Hengstmengel
#
# @brief   visitor class(es)
#
# @copyright Copyright (c) Remedy IT Expertise BV
#----------------------------------------------------------------------
require 'ridlbe/ccmx11/visitors/component.rb'

module IDL
  module CCMX11

    class ConnectorVisitor < ComponentVisitor

      def base
        (@base = visitor(ConnectorVisitor)).visit(@node.base) unless @base
        @base
      end

      def all_operations(inc_implicit = false)  # incl. inherited
        inc_implicit ? implicit_operations : []
      end

      def skel_cxxname
         @node.skel_cxxname
      end

      def scoped_skel_cxxname
        @node.scoped_skel_cxxname
      end

      def scoped_skel_cxxnamespace
        @node.scoped_skel_cxxnamespace
      end

      def is_abstract?
        false
      end

      def is_templated?
        unless !@templated.nil?
          n = @node.enclosure
          @templated = false
          while n
            @templated = true if IDL::AST::Module === n && n.is_templated?
            @tpl_module = n if @templated
            return @templated if @templated
            n = n.enclosure
          end
        end
        @templated ? true : false
      end

      def template_args
        @template_args ||= if is_templated?
                             @tpl_module.template_params
                           else
                             []
                           end
      end

      def template_name
        "#{cxxname}_Connector_T"
      end

      # template mapping

      map_template :typecode, :typecode
      map_template :tao_typecode, :component_typecode
      map_template :component, :connector
      map_template :component, :component

      optional_template :connector_pre_extra
      optional_template :connector_extended_port_extra
    end

  end
end
