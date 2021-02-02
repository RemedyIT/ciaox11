#--------------------------------------------------------------------
# @file    port.rb
# @author  Marijke Hengstmengel
#
# @brief   visitor class(es)
#
# @copyright Copyright (c) Remedy IT Expertise BV
#----------------------------------------------------------------------
require 'ridlbe/c++11/visitors/interface.rb'
require 'ridlbe/ccmx11/visitors/mixins/ccm_names.rb'

module IDL
  module CCMX11

    class PortVisitor < Cxx11::NodeVisitorBase
      include CcmNames

      def port_type
        node.porttype
      end

      def is_multiple?
        node.multiple?
      end

      def interface_type
        @intftype ||= case port_type
        when :facet, :receptacle
          intf = visitor(InterfaceVisitor)
          class << intf
            include CcmNames
          end
          intf.visit(_resolved_idltype.node)
          intf
        else
          nil
        end
        @intftype
      end

      def visit(node, component_for_port = nil)
        super(node)
        if component_for_port
          @component = visitor(ComponentVisitor)
          @component.visit(component_for_port)
        end
      end

      def component
        unless @component
          @component = visitor(IDL::AST::Connector === node.enclosure ? ConnectorVisitor : ComponentVisitor)
          @component.visit(node.enclosure)
        end
        @component
      end

      #in case of a extended port, the port contains ports
      def ports
        node.ports.collect { |p| (pv = visitor(PortVisitor)).visit(p); pv }
      end

      #remove prefix extended_port_name, we don't want the expanded_copy name but the original port name
      def port_name_without_extended_port(extended_port)
        @port_name ||= node.name
        @port_name.slice!(extended_port + '_')
        @port_name
      end

      def attributes
        node.attributes.collect { |p| (pv = visitor(AttributeVisitor)).visit(p); pv }
      end

      def gen_facet_exec(extra_props = {})
        visit_template('facet_exec', extra_props)
      end

     end
  end
end
