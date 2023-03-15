#--------------------------------------------------------------------
# @file    async_request_reply.rb
# @author  Martin Corino
#
# @brief  Asynchronous messaging interaction pattern specializations
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------

module AxciomaPC
  module ARR
    module ComponentInteractionHandler
      def self.setup_component(recipe)
        BRIX11.log(4, '[%s|ARR] setup_component', self)
        # noop
      end

      def self.process_component_dependencies(recipe, project_dependencies)
        BRIX11.log(4, '[%s|ARR] process_component_dependencies', self)
        recipe.setup_comp_gen_ami(project_dependencies)
        recipe.setup_lem_comp_ami(project_dependencies)
        recipe.setup_svnt_comp_ami(project_dependencies)
        recipe.setup_exec_lib_ami(project_dependencies)
      end
    end

    module DataInteractionHandler
      def self.setup_data(recipe, fidl)
        # lem is also needed for srr and corba4ccm, but ami4ccm requires corba4ccm, so lem generation
        # is done in DataIdl extension of request_reply interactions (#add_lem_proj)
        if fidl.properties[:needs_lem]
          recipe.add_lem_proj(fidl)
        end
        recipe.add_ami_proj(fidl)
      end

      def self.process_data_dependencies(recipe, project_dependencies)
        recipe.process_arr_data_dependencies(project_dependencies)
      end

      def self.get_data_dependencies(recipe, idl_prj_dependencies, project_dependencies)
        recipe.get_arr_data_dependencies(project_dependencies, idl_prj_dependencies)
      end
    end
  end # ARR

  ComponentRecipe.register_interaction_handler(:arr, ARR::ComponentInteractionHandler)
  DataIdlRecipe.register_interaction_handler(:arr, ARR::DataInteractionHandler)


  # Extension module for ComponentRecipe
  module ComponentExtension
    def self.included(base)
      base.send(:include, ComponentExtension::Overloads)
      base.class_eval do
        alias_method_chain :check_idl_node, :arr
      end
    end

    module Overloads
      def check_idl_node_with_arr(idl_scanner, node, delegator)
        check_idl_node_without_arr(idl_scanner, node, delegator)
        # check for support as this may be an unlicensed option
        if delegator.respond_to?(:ami4ccm_receptacles)
          # check all receptacles of component for ami4ccm
          if IDL::AST::Component === node
            node.ports.each do |p|
              if p.porttype == :receptacle
                if delegator.ami4ccm_receptacles.include? p.scoped_name
                  # find IDL file chain providing receptacle interface type
                  included = false
                  enc = p.idltype.node.enclosure
                  while enc
                    if IDL::AST::Include === enc
                      included = true
                      # register IDL file if not yet done
                      ifidl = project.add_idl_file(enc.fullpath)
                      if ifidl.is_member?
                        # register required interaction types for IDL include
                        BRIX11.log(4, '[%s|ARR] set AMI interaction types: %s', self, ifidl)

                        ifidl.interaction_types << :arr
                        ifidl.interaction_types << :srr
                      end
                    end
                    enc = enc.enclosure
                  end
                  # if the type is not from included IDL File
                  unless included
                    BRIX11.log(4, '[%s|ARR] set AMI interaction types: %s', self, idl_scanner.idl_file)
                    idl_scanner.idl_file.interaction_types << :arr
                    idl_scanner.idl_file.interaction_types << :srr
                  end
                  # register AMI receptacle presence
                  idl_scanner.properties[:has_ami_receptacle] = true
                end
              end
            end
          end
        end
      end
    end
  end

  AxciomaPC::ComponentRecipe.send(:include, ComponentExtension)

  module ARR
    module SenderPort
      def verify
        BRIX11.log(4, "[%s] verify", self)
        @pragma = 'ami4ccm receptacle "' + recipe.comp_name + '::' + name + '"'
        generate_port(@config[:multiple] ? 'uses multiple' : 'uses', @config[:type_name])
      end
    end
  end

  # patch ComponentRecipe::PortDefinition for arr ports component
  class ComponentRecipe::PortDefinition
    class Configurator
      # arr
      def sends(itf_name = nil, multiple = nil)
        @port.sends(itf_name, multiple)
      end
    end

    # extend the known ports list
    self.possible_ports.concat(%w(sends))

    def sends(intf_name, multiple = nil)
      @config[:kind] = :sender
      @config[:type_name] = intf_name
      if ::Hash === multiple && multiple.size == 1
        @config[:multiple] = multiple[:multiple]
      else
        raise "Invalid :multiple specification #{multiple}." unless multiple.nil?
      end
      self.extend ARR::SenderPort
    end
  end
end

# load specializations and extensions
Dir.glob(File.join(File.dirname(__FILE__), 'async_request_reply', '*.rb')).each do |fnm|
  require fnm
end
