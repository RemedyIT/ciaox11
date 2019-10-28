#--------------------------------------------------------------------
# @file    state_event.rb
# @author  Martin Corino
#
# @brief  State and Event interaction pattern specializations
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------

module AxciomaPC

  module SEV

    module ComponentInteractionHandler

      def self.setup_component(recipe)
        BRIX11.log(3, '[%s|SEV] setup_component', self)
        #noop
      end

      def self.process_component_dependencies(recipe,project_dependencies)
        BRIX11.log(3, '[%s|SEV] process_component_dependencies', self)
        recipe.setup_comp_gen_sev(project_dependencies)
        recipe.setup_stub_comp_sev(project_dependencies)
        recipe.setup_lem_comp_sev(project_dependencies)
        recipe.setup_svnt_comp_sev(project_dependencies)
        recipe.setup_exec_lib_sev(project_dependencies)
      end

    end

    module DataInteractionHandler

      def self.setup_data(recipe, fidl)
        #noop
      end

      def self.process_data_dependencies(recipe, project_dependencies)
        recipe.process_sev_data_dependencies(project_dependencies)
      end

      def self.get_data_dependencies(recipe, idl_prj_dependencies, project_dependencies)
        recipe.get_sev_data_dependencies(project_dependencies, idl_prj_dependencies)
      end


    end

  end

  ComponentRecipe.register_interaction_handler(:sev, SEV::ComponentInteractionHandler)
  DataIdlRecipe.register_interaction_handler(:sev, SEV::DataInteractionHandler)

  module SEV
    module PortBase
      def generate_sev_port(type, type_name)
        # check if type_name isn't nil, checking here and not already in the Configurator, makes it possible
        # to give a meaningful error message
        if type_name.nil?
          BRIX11.log_error("[#{self}] Type of port is nil!")
        else
          set_type type
          sev_data_idl = find_idl_type(type_name) do |n|
                IDL::Type::Struct === n.idltype.resolved_type
              end
          unless sev_data_idl
            raise "[#{self}] No valid Struct type #{type_name} found!"
          end
          generate_sev_interface_recipe(type_name, sev_data_idl)
          @idl_interface = File.basename(sev_data_idl, '.idl') + 'SE.idl'
        end
      end
      protected :generate_sev_port

      def generate_sev_interface_recipe(type_name, sev_data_idl)
        # create implicit interface recipe if no explicit or implicit version is defined
        base_name = File.basename(sev_data_idl, '.idl')
        idlmatch = recipe.project.match_idl_files(base_name+'SE.idl')
        topic = type_name
        if !idlmatch.empty?
          intf_idl_file = idlmatch.find do |fidl|
            if rcp = fidl.recipes.first
              SEV::InterfaceRecipe === rcp && rcp.topic == topic
            else
              # found no recipe for #{base_name+'SE.idl'}
              false
            end
          end
        # else not found file #{base_name+'SE.idl'}
        end
        # if no existing recipe found create implicit one. in same dir and recipe as interface
        @interface_recipe = if intf_idl_file
          # found recipe with derived  *SE.idl"
          intf_idl_file.recipes.first
        else
          #find recipe file with recipe for #{base_name+'.idl'}
          idlmatch = recipe.project.match_idl_files(base_name + '.idl')
          if !idlmatch.empty?
            intf_base_idl_file = idlmatch.find do |fidl|
              if rcp = fidl.recipes.first
                # found recipe for #{base_name+'.idl'}"
                DataIdlRecipe === rcp
              else
                # no recipe found yet for #{base_name+'.idl'}"
                false
              end
            end
          #else not found file #{base_name+'.idl'} in project yet
          end
          if intf_base_idl_file
            rec_base = intf_base_idl_file.recipes.first
          else
            #  also no recipe found for  #{base_name+'.idl'}"
            idldep_file = recipe.project.add_idl_file(sev_data_idl)
            # make implicit recipe for base
            recipe.check_idl_recipe(idldep_file)
            rec_base = idldep_file.recipes.first
          end

          # Now we can create interface recipe
          intf_recipe =
            SEV::InterfaceRecipe.create(rec_base.recipe_file,
              type_name,
              topic,
              File.basename(sev_data_idl),
              nil, # = same dir as recipe file and sev_data_idl
              rec_base.gen_dir,
              nil,
              nil,
              nil,
              nil,
              nil)
          # add to same recipe file as 'base' recipe
          rec_base.recipe_file.add_recipe(intf_recipe)
          # scan the recipes IDL file since that phase has passed here
          intf_recipe.collect_idl_files
          intf_recipe
        end
      end
      protected :generate_sev_interface_recipe

      def extra_listener_port(name, comp)
        port = ComponentRecipe::PortDefinition.new(name,comp)
        port.set_type 'provides'
        port.set_intf_name 'CCM_DDS::ConnectorStatusListener'
        #check if already a ConnectorStatusListener exist for this InterFace
        if !comp.port_exist?(port)
          comp.add_port(port)
        end
      end
      protected :extra_listener_port
    end
    module WriterPort
      def verify
        BRIX11.log(4, "[%s] verify", self)
        # for dds4ccm write or update port always add
        # provides CCM_DDS::ConnectorStatusListener connector_status_#{intf_name};
        extra_listener_port('connector_status_' + @config[:typename], @comp)

        generate_sev_port('port', @config[:typename])
        set_intf_name @interface_recipe.topic_interface_module+'::DDS_Write'
      end
    end
    module UpdaterPort
      def verify
        BRIX11.log(4, "[%s] verify", self)
        # for dds4ccm write or update port always add
        # provides CCM_DDS::ConnectorStatusListener connector_status_#{intf_name};
        extra_listener_port('connector_status_' + @config[:typename], @comp)

        generate_sev_port('port', @config[:typename])
        set_intf_name @interface_recipe.topic_interface_module+'::DDS_Update'
      end
    end
    module ReaderPort
      def verify
        BRIX11.log(4, "[%s] verify", self)
        generate_sev_port('port', @config[:typename])
        set_intf_name @interface_recipe.topic_interface_module+'::DDS_Read'
      end
    end
    module GetterPort
      def verify
        BRIX11.log(4, "[%s] verify", self)
        generate_sev_port('port', @config[:typename])
        set_intf_name @interface_recipe.topic_interface_module+'::DDS_Get'
      end
    end
    module MonitorPort
      def verify
        BRIX11.log(4, "[%s] verify", self)
        generate_sev_port('port', @config[:typename])
        set_intf_name @interface_recipe.topic_interface_module+'::DDS_Listen'
      end
    end
    module ObserverPort
      def verify
        BRIX11.log(4, "[%s] verify", self)
        generate_sev_port('port', @config[:typename])
        set_intf_name @interface_recipe.topic_interface_module+'::DDS_StateListen'
      end
    end
  end

  # patch ComponentRecipe::PortDefinition for sev ports component
  class ComponentRecipe::PortDefinition

    class Configurator
      def writes(type_name=nil)
        @port.writes(type_name)
      end

      def updates(type_name=nil)
        @port.updates(type_name)
      end

      def reads(type_name=nil)
        @port.reads(type_name)
      end

      def gets(type_name=nil)
        @port.gets(type_name)
      end

      def monitors(type_name=nil)
        @port.monitors(type_name)
      end

      def observes(type_name=nil)
        @port.observes(type_name)
      end
    end

    # extend the known ports list
    self.possible_ports.concat(%w(writes updates reads gets monitors observes))

    def writes(type_name)
      @config[:kind] = :writes
      @config[:typename] = type_name
      self.extend SEV::PortBase
      self.extend SEV::WriterPort
    end

    def monitors(type_name)
      @config[:kind] = :monitors
      @config[:typename] = type_name
      self.extend SEV::PortBase
      self.extend SEV::MonitorPort
    end

    def updates(type_name)
      @config[:kind] = :updates
      @config[:typename] = type_name
      self.extend SEV::PortBase
      self.extend SEV::UpdaterPort
    end

    def reads(type_name)
      @config[:kind] = :reads
      @config[:typename] = type_name
      self.extend SEV::PortBase
      self.extend SEV::ReaderPort
    end

    def gets(type_name)
      @config[:kind] = :observes
      @config[:typename] = type_name
      self.extend SEV::PortBase
      self.extend SEV::GetterPort
    end

    def observes(type_name)
      @config[:kind] = :observes
      @config[:typename] = type_name
      self.extend SEV::PortBase
      self.extend SEV::ObserverPort
    end
  end
end

# load specializations and extensions
Dir.glob(File.join(File.dirname(__FILE__), 'state_event', '*.rb')).each do |fnm|
  require fnm
end

