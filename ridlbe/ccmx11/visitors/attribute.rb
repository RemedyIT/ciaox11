#--------------------------------------------------------------------
# @file    attribute.rb
# @author  Marijke Hengstmengel
#
# @brief   visitor class(es)
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------
require 'ridlbe/c++11/visitors/exception'

module IDL
  module Cxx11

    # Reopen AttributeVisitor class to add CCMX11 specifics
    #
    class AttributeVisitor

      def interface_with_cxx11_interface(interface_for_att = nil)
        # set interface_for_att to node.enclosure unless passed as arg or @interface already set
        interface_for_att ||= node.enclosure unless @interface || !node?
        # (re)set @interface if interface_for_att isn't nil
        if interface_for_att
          if NodeVisitorBase === interface_for_att
            @interface = interface_for_att
          else
            if  interface_for_att.is_a?(IDL::AST::Component)
              @interface = visitor(IDL::CCMX11::ComponentVisitor)
              @interface.visit(interface_for_att)
            else
              @interface = interface_without_cxx11_interface(interface_for_att)
            end
          end
        end
        @interface
      end

      alias_method_chain :interface, :cxx11_interface

      def is_readonly?
        @node.readonly
      end

      #Used for attributes of extended ports
      #remove prefix extended_port_name, we don't want the expanded_copy name but the original attribute name
      def attribute_name_without_extended_port(extended_port)
        @attribute_name ||= node.name
        @attribute_name.slice!(extended_port + '_')
        @attribute_name
      end
    end
  end
end
