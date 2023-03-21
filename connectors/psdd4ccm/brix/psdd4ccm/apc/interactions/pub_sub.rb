#--------------------------------------------------------------------
# @file    pub_sub.rb
# @author  Martin Corino
#
# @brief  Publish/Subscribe interaction pattern specializations
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------

module AxciomaPC
  module PS
    module ComponentInteractionHandler
      def self.setup_component(recipe)
        BRIX11.log(3, '[%s|PS] setup_component', self)
        # noop
      end

      def self.process_component_dependencies(recipe, project_dependencies)
        BRIX11.log(3, '[%s|PS] process_component_dependencies', self)
        recipe.setup_comp_gen_pubsub(project_dependencies)
        recipe.setup_stub_comp_pubsub(project_dependencies)
        recipe.setup_lem_comp_pubsub(project_dependencies)
        recipe.setup_svnt_comp_pubsub(project_dependencies)
        recipe.setup_exec_lib_pubsub(project_dependencies)
      end
    end

    module DataInteractionHandler
      def self.setup_data(recipe, fidl)
        # noop
      end

      def self.process_data_dependencies(recipe, project_dependencies)
        recipe.process_ps_data_dependencies(project_dependencies)
      end

      def self.get_data_dependencies(recipe, idl_prj_dependencies, project_dependencies)
        recipe.get_ps_data_dependencies(project_dependencies, idl_prj_dependencies)
      end
    end
  end

  ComponentRecipe.register_interaction_handler(:pubsub, PS::ComponentInteractionHandler)
  DataIdlRecipe.register_interaction_handler(:pubsub, PS::DataInteractionHandler)

  module PS
    module PortBase
      def generate_pubsub_port(type, type_name)
        # check if type_name isn't nil, checking here and not already in the Configurator, makes it possible
        # to give a meaningful error message
        if type_name.nil?
          BRIX11.log_error("[#{self}] Topic type of port is nil!")
        else
          set_type type
          ps_data_idl = find_idl_type(type_name) do |n|
                t = n.idltype.resolved_type
                case t
                when IDL::Type::Any,
                     IDL::Type::Object,
                     IDL::Type::Native,
                     IDL::Type::ValueBase,
                     IDL::Type::Valuetype,
                     IDL::Type::Valuebox,
                     IDL::Type::TemplateModule,
                     IDL::Type::Home,
                     IDL::Type::Component,
                     IDL::Type::Porttype,
                     IDL::Type::Exception,
                     IDL::Type::Const
                   false
                else
                   true
                end
              end
          # did we find user defined IDL or is this a basic type
          unless ps_data_idl || ComponentRecipe::AttributeDefinition::BASIC_TYPES.include?(type_name)
            raise "No valid data type #{type_name} found for component recipe #{recipe.recipe_id}!"
          end
          generate_pubsub_interface_recipe(type_name, ps_data_idl)
          @idl_interface = @interface_recipe.interface_name + '.idl'
        end
      end
      protected :generate_pubsub_port

      def generate_pubsub_interface_recipe(type_name, ps_data_idl)
        BRIX11.log(4, "[%s] generate_pubsub_interface_recipe : type_name=%s, ps_data_idl=%s", self, type_name, ps_data_idl)
        # create implicit interface recipe if no explicit or implicit version is defined
        ps_name = if ps_data_idl
                     File.basename(ps_data_idl, '.idl') + 'PS'
                   else
                     type_name.tr(' ', '_') + 'PS'
                   end
        idlmatch = recipe.project.match_idl_files(ps_name + '.idl')
        topic = type_name
        if !idlmatch.empty?
          intf_idl_file = idlmatch.find do |fidl|
            if rcp = fidl.recipes.first
              PS::InterfaceRecipe === rcp && rcp.topic == topic
            else
              # found no recipe for #{base_name+'PS.idl'}
              false
            end
          end
        # else not found file #{base_name+'PS.idl'}
        end
        # if no existing recipe found create implicit one.
        # in same dir and recipefile as type or as component if basic type
        @interface_recipe = if intf_idl_file
          # found existing recipe with derived  *PS.idl"
          intf_idl_file.recipes.first
        else
          intf_base_idl_file = nil
          if ps_data_idl
            # find recipe file with recipe for ps_data_idl
            idlmatch = recipe.project.match_idl_files(File.basename(ps_data_idl))
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
            # else not found file #{base_name+'.idl'} in project yet
            end
            if intf_base_idl_file
              rec_base = intf_base_idl_file.recipes.first
            else
              #  also no recipe found for  #{base_name+'.idl'}"
              idldep_file = recipe.project.add_idl_file(ps_data_idl)
              # make implicit recipe for base
              recipe.check_idl_recipe(idldep_file)
              rec_base = idldep_file.recipes.first
            end
          else
            # basic type so no data recipe to use
            rec_base = recipe # use component recipe itself
          end

          # Now we can create interface recipe
          intf_recipe =
            PS::InterfaceRecipe.create(rec_base.recipe_file,
              ps_name,
              topic,
              ps_data_idl ? File.basename(ps_data_idl) : nil,
              nil, # = same dir as recipe file and ps_data_idl
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
      protected :generate_pubsub_interface_recipe
    end
    module SubscriberPort
      def verify
        BRIX11.log(4, "[%s] verify", self)
        generate_pubsub_port('uses', @config[:typename])
        set_intf_name @interface_recipe.topic_interface_module + '::Subscriber'
        inports = @config[:interaction].inject({}) do |hsh, int|
                    case int
                    when Hash
                      int.inject(hsh) { |h, (k, v)| h[k.to_sym] = v.to_s; h }
                    when String, Symbol
                      hsh[int.to_sym] = "#{name}_#{int}"
                    when NilClass
                      hsh.merge!({ listen: "#{name}_listen", get: "#{name}_get" })
                    else
                      BRIX11.log_fatal("[#{self}] Invalid interactions specified!")
                    end
                    hsh
                  end
        inports.each do |p, n|
          if p == :listen
            port = ComponentRecipe::PortDefinition.new(n, @comp)
            port.set_type 'provides'
            port.set_intf_name @interface_recipe.topic_interface_module + '::Listener'
            if !@comp.port_exist?(port)
              @comp.add_port(port)
            end
          elsif p == :get
            port = ComponentRecipe::PortDefinition.new(n, @comp)
            port.set_type 'uses'
            port.set_intf_name @interface_recipe.topic_interface_module + '::Getter'
            if !@comp.port_exist?(port)
              @comp.add_port(port)
            end
          else
            BRIX11.log_fatal("[#{self}] Invalid interaction #{p} specified!")
          end
        end

        # add interface IDL include path to component recipe
        recipe.idl_includes << File.dirname(@interface_recipe.interface_idl_path)
      end
    end
    module PublisherPort
      def verify
        BRIX11.log(4, "[%s] verify", self)
        generate_pubsub_port('uses', @config[:typename])
        set_intf_name @interface_recipe.topic_interface_module + '::Publisher'

        # add interface IDL include path to component recipe
        recipe.idl_includes << File.dirname(@interface_recipe.interface_idl_path)
      end
    end
  end

  # patch ComponentRecipe::PortDefinition for pubsub ports component
  class ComponentRecipe::PortDefinition

    # reopen and extend Configurator
    class Configurator
      def publishes(type_name=nil)
        @port.publishes(type_name)
      end

      def subscribes(type_name=nil, *interaction)
        @port.subscribes(type_name, *interaction)
      end
    end

    # extend the known ports list
    self.possible_ports.concat(%w(publishes subscribes))

    def publishes(type_name)
      @config[:kind] = :publishes
      @config[:typename] = type_name
      self.extend PS::PortBase
      self.extend PS::PublisherPort
    end

    def subscribes(type_name, *interaction)
      @config[:kind] = :subscribes
      @config[:typename] = type_name
      @config[:interaction] = interaction
      self.extend PS::PortBase
      self.extend PS::SubscriberPort
    end
  end
end

# load specializations and extensions
Dir.glob(File.join(File.dirname(__FILE__), 'pub_sub', '*.rb')).each do |fnm|
  require fnm
end
