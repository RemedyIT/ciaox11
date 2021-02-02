#--------------------------------------------------------------------
# @file    request_reply.rb
# @author  Martin Corino
#
# @brief  Synchronous Request/Reply interaction pattern specializations
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------

module AxciomaPC

  module SRR

    module ComponentInteractionHandler

      def self.setup_component(recipe)
        BRIX11.log(4, '[%s|SRR] setup_component', self)
        #noop
      end

      def self.process_component_dependencies(recipe, project_dependencies)
        BRIX11.log(4, '[%s|SRR] process_component_dependencies', self)
        #noop
      end

    end

    module DataInteractionHandler

      def self.setup_data(recipe, fidl)
        if fidl.properties[:needs_lem]
          recipe.add_lem_proj(fidl)
        else
          # Although no lem is needed, the stub headers are included,
          # so the included dirs must be set here.
          # by not specifying the recipe for the :lem_stub dependency (nil) this is a noop
          # but the linked :stub dependency is active and pulled in
          fidl.project_dependencies <<
              MPC::Dependency.new(:lem_stub, MPC::LinkDependency.new(:stub, recipe))
        end
      end

      def self.process_data_dependencies(recipe, project_dependencies)
        recipe.process_srr_data_dependencies(project_dependencies)
      end

      def self.get_data_dependencies(recipe, idl_prj_dependencies, project_dependencies)
        recipe.get_srr_data_dependencies(project_dependencies, idl_prj_dependencies)
      end

    end

  end # SRR

  ComponentRecipe.register_interaction_handler(:srr, SRR::ComponentInteractionHandler)
  DataIdlRecipe.register_interaction_handler(:srr, SRR::DataInteractionHandler)

  module SRR
    module Receptacle
      def verify
        BRIX11.log(4, "[%s] verify", self)
        generate_port(@config[:multiple] ? 'uses multiple' : 'uses', @config[:type_name])
      end
    end
    module Facet
      def verify
        BRIX11.log(4, "[%s] verify", self)
        generate_port('provides', @config[:type_name])
      end
    end
  end

  # patch ComponentRecipe::PortDefinition for srr ports component
  class ComponentRecipe::PortDefinition

    class Configurator
      #srr
      def uses(itf_name=nil, multiple=nil)
        @port.uses(itf_name, multiple)
      end

      #facet
      def provides(itf_name=nil)
        @port.provides(itf_name)
      end
    end

    # extend the known ports list
    self.possible_ports.concat(%w(provides uses))

    def uses(intf_name, multiple=nil)
      @config[:kind] = :receptacle
      @config[:type_name] = intf_name
      if ::Hash === multiple && multiple.size == 1
        @config[:multiple] = multiple[:multiple]
      else
        raise "Invalid :multiple specification #{multiple}." unless multiple.nil?
      end
      self.extend SRR::Receptacle
    end

    def provides(intf_name)
      @config[:kind] = :facet
      @config[:type_name] = intf_name
      self.extend SRR::Facet
    end

  end

end

# load specializations and extensions
Dir.glob(File.join(File.dirname(__FILE__), 'request_reply', '*.rb')).each do |fnm|
  require fnm
end
