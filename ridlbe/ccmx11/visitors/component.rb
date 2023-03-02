#--------------------------------------------------------------------
# @file    component.rb
# @author  Marijke Hengstmengel
#
# @brief   visitor class(es)
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------
require 'ridlbe/ccmx11/visitors/port'
require 'ridlbe/c++11/visitors/attribute'
require 'ridlbe/ccmx11/visitors/mixins/ccm_names'

module IDL
  module CCMX11
    class ComponentVisitor < Cxx11::NodeVisitorBase
      include CcmNames

      def is_derived?
        node.base ? true : false
      end

      def base
        (@base = visitor(ComponentVisitor)).visit(node.base) unless @base
        @base
      end

      def has_support?
        node.interfaces.any?
      end

      def support_interfaces
        node.interfaces
      end

      def has_ancestors?
        # A component always has ancestors:CCMObject
        true
      end

      def supported_interfaces?
        node.interfaces.any?
      end

      def supported_interfaces
        @supported_interfaces ||= node.interfaces.collect do |i|
          (iv = visitor(InterfaceVisitor)).visit(i)
          iv
        end
      end

      def ports
        @ports ||= node.ports.collect { |p| (pv = visitor(PortVisitor)).visit(p); pv }
      end

      def all_ports  # incl. inherited
        @all_ports ||= node.ports(true).collect do |p|
          (pv = visitor(PortVisitor)).visit(p, node)
          pv
        end
      end

      def extended_ports
        @ext_ports_ ||= collect_resolved_bases([node]).collect do |n|
          n.select_members { |c| IDL::AST::Port === c && (c.porttype == :mirrorport || c.porttype == :port) }
        end.flatten
        @extended_ports ||= @ext_ports_.collect { |p| visitor(PortVisitor) { |v| v.visit(p) } }
      end

      def no_extended_ports
        @no_extended_ports_ ||= collect_resolved_bases([node]).collect do |n|
          n.select_members { |c| IDL::AST::Port === c && (c.porttype != :mirrorport && c.porttype != :port) }
        end.flatten
        @no_extended_ports ||= @no_extended_ports_.collect { |p| visitor(PortVisitor) { |v| v.visit(p) } }
      end

      def non_local_ports
        all_ports.select do |p|
          !p.is_local?
        end
      end

      def non_local_facet_ports
        @non_local_facet_ports ||= all_ports.select do |p|
          p.port_type == :facet && !p.is_local?
        end
      end

      def has_non_local_facet_ports?
        !non_local_facet_ports.empty?
      end

      def interfaces_for_nonlocal_facet_ports
        non_local_facet_ports.inject([]) do |iflst, fp|
          ifcxxname = fp.interface_type.scoped_cxxname
          iflst << fp.interface_type unless iflst.any? { |intf| intf.scoped_cxxname == ifcxxname }
          iflst
        end
      end

      def interfaces_with_multiple_receptacle_ports
        mp_ports = all_ports.select do |p|
           p.port_type == :receptacle && p.is_multiple?
        end
        interface_type = []
        multiple_ports = []
        mp_ports.each do |mp|
          unless interface_type.include?(mp.interface_type.scoped_cxxname)
            interface_type << mp.interface_type.scoped_cxxname
            multiple_ports << mp
          end
        end
        multiple_ports
      end

      def incl_receptacle_port?
        ports.any? { |p| p.port_type == :receptacle }
      end

      def incl_facet_port?
        ports.any? { |p| p.port_type == :facet }
      end

      def incl_multiple_port?
        ports.any? { |p| p.is_multiple? }
      end

      def all_incl_receptacle_port?
        all_ports.any? { |p| p.port_type == :receptacle }
      end

      def all_incl_facet_port?
        all_ports.any? { |p| p.port_type == :facet }
      end

      def all_incl_multiple_port?
        all_ports.any? { |p| p.is_multiple? }
      end

      # all attributes, except the attributes belonging to extended ports.
      def all_attributes_not_from_extended_ports
        unless @all_attributes_not_from_extended_ports
          @all_attributes_not_from_extended_ports = []
          ancestors.each do |an|
            if an.is_a?(IDL::CCMX11::ComponentVisitor) || an.is_a?(IDL::CCMX11::ConnectorVisitor)
              @all_attributes_not_from_extended_ports.concat(an.attributes_not_from_extended_ports)
            end
          end
          @all_attributes_not_from_extended_ports.concat(self.attributes_not_from_extended_ports)
        end
        @all_attributes_not_from_extended_ports
      end

      # attributes, except the attributes belonging to extended ports.
      def attributes_not_from_extended_ports
        unless @attr_no_ext_port
          @attr_no_ext_port = self.attributes_excl_port
          ports_ = node.select_members { |c| IDL::AST::Port === c && (c.porttype != :mirrorport && c.porttype != :port) }
          ports_.each do |p|
             p.attributes.each do |att|
                @attr_no_ext_port << visitor(AttributeVisitor) { |v| v.interface(node); v.visit(att) }
             end
          end
        end
        @attr_no_ext_port
      end

      def attributes
         @attributes ||= node.attributes.collect { |a| (av = visitor(AttributeVisitor)).visit(a); av }
      end

      def all_attributes_incl_mirror_port
        unless @all_attributes_component_and_mirror_port
          @all_attributes_component_and_mirror_port = []
          ancestors.each do |an|
            if an.is_a?(IDL::CCMX11::ComponentVisitor) || an.is_a?(IDL::CCMX11::ConnectorVisitor)
              @all_attributes_component_and_mirror_port.concat(an.get_attributes_incl_mirror_port)
            end
          end
          @all_attributes_component_and_mirror_port.concat(self.get_attributes_incl_mirror_port)
        end
        @all_attributes_component_and_mirror_port
      end

      def get_attributes_incl_mirror_port
        attr_component_and_mirror_ports = []
        # get the attributes from any mirrorports
        node.walk_members do |child|
          if child.is_a?(IDL::AST::Port) && child.porttype == :mirrorport
            child.attributes.each do |att|
              attr_component_and_mirror_ports << visitor(AttributeVisitor) { |v| v.interface(node); v.visit(att) }
            end
          end
        end
        # Now get the Component attributes.
        attr_component_and_mirror_ports.concat(self.attributes_excl_port)
      end

      # Only the Component attributes and the attributes of a mirror port of the component
      def attributes_incl_mirror_port
        unless @attributes_component_and_mirror_port
          @attributes_component_and_mirror_port = self.get_attributes_incl_mirror_port
        end
        @attributes_component_and_mirror_port
      end

      # Only the Component attributes, not the attributes of a port of the component
      def attributes_excl_port
        unless @attributes_component
          @attributes_component = []
          node.walk_members do |child|
            if child.is_a?(IDL::AST::Attribute)
              @attributes_component << visitor(AttributeVisitor) { |v| v.interface(node); v.visit(child) }
            end
          end
        end
        @attributes_component
      end

      def attributes_incl_mirror_port?
        (!attributes_incl_mirror_port.empty?) ? true : false
      end

      def any_mutable_attributes_incl_mirror_port?
        all_attributes_incl_mirror_port.any? { |att| !att.is_readonly? }
      end

      def attributes?
        (!attributes.empty?) ? true : false
      end

      def all_attributes(inc_implicit = false)  # incl. inherited
        @all_attributes ||= node.attributes(true).collect do |att|
          visitor(AttributeVisitor) { |v| v.interface(node); v.visit(att) }
        end
        if inc_implicit
          ccm_node = self._resolve("::Components::CCMObject")
          @all_implicit_attributes ||= ccm_node.attributes(true).collect do |op|
            visitor(OperationVisitor) { |v| v.interface(ccm_node); v.visit(op) }
          end

        end
        @all_attributes + (inc_implicit ? @all_implicit_attributes : [])
      end

      def all_attributes?(inc_implicit = false)
        (!all_attributes(inc_implicit).empty?) ? true : false
      end

      def all_operations(inc_implicit = false)  # incl. inherited
        @all_operations ||= node.operations(true).collect do |op|
          visitor(OperationVisitor) { |v| v.interface(node); v.visit(op) }
        end
        @all_operations + (inc_implicit ? implicit_operations : [])
      end

      def ancestors
        unless @ancestors
          ccmobj = visitor(InterfaceVisitor)
          ccmobj.visit(_resolve("::Components::CCMObject"))
          @ancestors = ccmobj.ancestors
          @ancestors << ccmobj
          @ancestors.concat(collect_ancestors([], node).collect do |ancestor|
            if IDL::AST::Component === ancestor
              (ancestorv = visitor(ComponentVisitor)).visit(ancestor)
              ancestorv
            else
              if
                IDL::AST::Connector === ancestor
                (ancestorv = visitor(ConnectorVisitor)).visit(ancestor)
                ancestorv
              else
                (ancestorv = visitor(InterfaceVisitor)).visit(ancestor)
                ancestorv
              end
            end
          end)
        end
        @ancestors
      end

      def scoped_var_name
        @scoped_var_name ||= scoped_cxxname.gsub('::', '_')
      end

      def op_table_name
        @op_table_name ||= "_tao_#{scoped_var_name}_optable"
      end

      def gen_dynamic_hash_optable(extra_props = {})
        visit_template('_dynamic_hash_optable', extra_props)
      end

      def cxx_ptr_name
        cxxname + PTR_TYPE_SUFFIX
      end

      def skel_cxxname
        node.skel_cxxname
      end

      def scoped_skel_cxxname
        node.scoped_skel_cxxname
      end

      def scoped_skel_cxxnamespace
        node.scoped_skel_cxxnamespace
      end

      def proxy_cxxname
        node.proxy_cxxname
      end

      def scoped_proxy_cxxname
        node.scoped_proxy_cxxname
      end

      def srvproxy_cxxname
        node.srvproxy_cxxname
      end
      def scoped_srvproxy_cxxname
        node.scoped_srvproxy_cxxname
      end

      def executor_cxx_namespace
        scoped_cxxname.scope_to_cxxname + '_Impl'
      end

      def has_concrete_base?
        false
        # node.bases.any? { |_base| !_base.is_abstract? }
      end

      # template mapping

      map_template :component, :component
      map_template :component_ctor, :component_ctor
      map_template :typecode, :typecode
      map_template :tao_typecode, :component_typecode

      # optional templates used in some ridlbe facets

      # corba4ccm & ami4ccm svnt
      optional_template :component_init_connect
      # ami4ccm svnt
      optional_template :context_extra_members
      optional_template :context_extra_connect
      optional_template :context_extra_disconnect
      optional_template :context_extra_receptacles
      # corba facet svnt
      optional_template :component_pre
      optional_template :component_extra_member
      optional_template :component_create
      # ami4ccm lem idl
      optional_template :lem_extra_receptacles
      optional_template :lem_extra_multiple_receptacles
      # ami4ccm comp_exec
      optional_template :component_end_extra
      # ami4ccm connector
      optional_template :connector_extra
      # exf
      optional_template :context_port_set_connection
      optional_template :context_port_reset_connection

     protected

      def implicit_operations
        ccm_node = self._resolve("::Components::CCMObject")
        @all_implicit_operations ||= ccm_node.operations(true).collect do |op|
          visitor(OperationVisitor) { |v| v.interface(self); v.visit(op) }
        end
      end

      def collect_resolved_bases(list = [], n = nil)
        base = (n || node).base
        if base
          base = base.idltype.resolved_type.node if base.is_a?(IDL::AST::Typedef)
          list << base
          collect_resolved_bases(list, base)
        end
        list
      end

      def collect_ancestors(list_, n)
        n.interfaces.inject(list_) do |lst, intf|
          lst << intf unless lst.include?(intf)
          collect_interface_ancestors(lst, intf)
        end
        if n.base
          collect_ancestors(list_, n.base)
          list_ << n.base
        end
        list_
      end

      def collect_interface_ancestors(list_, n)
        n.bases.inject(list_) do |lst, base|
          collect_interface_ancestors(lst, base)
          lst << base unless lst.include?(base)
          lst
        end
      end

      public
      def supported_interface_ids
        @sup_intf_ids ||= (collect_ancestors([], node).collect { |ancestor| ancestor.repository_id } << node.repository_id)
      end
    end
  end
end
