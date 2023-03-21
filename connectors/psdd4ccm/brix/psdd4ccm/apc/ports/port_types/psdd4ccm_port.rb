#--------------------------------------------------------------------
# @file    psdd4ccm_port.rb
# @author  Martin Corino
#
# @brief  PSDD4CCM port specializations
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------

module AxciomaPC
  module PSDD4CCM
    class Port < PortType

      class Configurator < PortType::Configurator
        def topic(name)
          @port_type.topic = name
        end
        def topic_namespace(name)
          @port_type.topic_namespace = name
        end
        def topic_sequence_suffix(name)
          @port_type.topic_seq_suffix = name
        end
        def topic_interface_suffix(name)
          @port_type.topic_if_suffix = name
        end
        def topic_sequence(name)
          @port_type.topic_seq = name
        end
        def topic_interface(name)
          @port_type.topic_if = name
        end
        def middleware(*names)
          @port_type.middleware(*names.flatten)
        end
        def disable_context_switch
          @context_switch_disabled = true
        end
      end

      CONFIGURATOR = Port::Configurator

      class << self
        def middleware_implementations
          @middleware_impl ||= []
        end
      end

      def initialize(recipe)
        super
      end

      def setup
        BRIX11.log(3, "[%s] setup", self)
        # create implicit interface recipe if no explicit version is defined
        idlmatch = project.match_idl_files(interface_name + '.idl')
        intf_idl_file = idlmatch.find do |fidl|
          if rcp = fidl.recipes.first
             PS::InterfaceRecipe === rcp && rcp.topic == topic
          else
            false
          end
        end
        # if no existing recipe found create implicit one here
        @interface_recipe = if intf_idl_file
          intf_recipe = intf_idl_file.recipes.first
          # make sure the details are correctly set
          intf_recipe.topic_namespace ||= @topic_namespace
          intf_recipe.topic_sequence ||= @topic_seq
          intf_recipe.topic_sequence_suffix ||= @topic_seq_suffix
          intf_recipe.topic_interface ||= @topic_if
          intf_recipe.topic_interface_suffix ||= @topic_if_suffix
          intf_recipe
        else
          intf_recipe =
            PS::InterfaceRecipe.create(recipe.recipe_file,
                                        interface_name,
                                        topic,
                                        recipe.idl,
                                        recipe.idl_includes,
                                        recipe.gen_dir,
                                        @topic_namespace,
                                        @topic_seq,
                                        @topic_seq_suffix,
                                        @topic_if,
                                        @topic_if_suffix)
          # add to same recipe file as the current recipe
          recipe.recipe_file.add_recipe(intf_recipe)
          intf_recipe
        end
      end

      def interface_name
        unless @interface_name
          if recipe.idl.empty?
            @interface_name = topic.tr(' ', '_') + 'PS'
          else
            @interface_name = "#{File.basename(recipe.idl.first, '.*')}PS"
          end
        end
        @interface_name
      end

      def topic=(name)
        @topic = name.to_s
      end

      def topic_namespace=(name)
        @topic_namespace = name
      end

      def topic_if_suffix=(name)
        @topic_if_suffix = name
      end

      def topic_seq_suffix=(name)
        @topic_seq_suffix = name
      end

      def topic_seq=(name)
        @topic_seq = name
      end

      def topic_if=(name)
        @topic_if = name
      end

      def middleware(*names)
       @middleware = names.collect do |n|
          n = n.to_s.downcase.to_sym
          if Port.middleware_implementations.include?(n)
            n
          else
            raise "Invalid middleware :#{n} specified. Valid middleware is #{Port.middleware_implementations}."
          end
       end.compact unless names.empty?
       @middleware || [Port.middleware_implementations.first]
      end

      def disable_context_switch
        @context_switch_disabled = true
      end

      def context_switch_disabled?
        !!@context_switch_disabled
      end

      def topic
        BRIX11.log_warning("[#{self}] Topic specification missing!") unless @topic
        @topic || ''
      end

      def setup_projects
        BRIX11.log(3, '[%s] setup projects ', self)
        mpc_obj = create_conn_gen
        mpc_file.add_mpc_project(mpc_obj)

        middleware.each do |mw|
          mpc_obj = create_conn_lib(mw)
          mpc_file.add_mpc_project(mpc_obj)
        end

        recipe.idl_files.each do |_, fidl|
          inc_fidl = project.idl_files[fidl.full_path]
          rcp = inc_fidl.recipes.first
          # set the interaction type
          rcp.setup_project_interaction(inc_fidl, :psdd4ccm)
        end

        # Also for the pubsub interface file, which the connector needs,
        # setup the project files,
        # in case this isn't done already via a pubsub component
        inc_fidl = project.idl_files[@interface_recipe.interface_idl_path]
        rcp = inc_fidl.recipes.first
        rcp.setup_project_interaction(inc_fidl, :pubsub)
      end

      def process_project_dependencies
        project_dependencies = MPC::Dependencies.new
        recipe.idl_files.each do |_, fidl|
          BRIX11.log(3, '[%s] process_project_dependencies %s', self, fidl)
          inc_fidl = project.idl_files[fidl.full_path]
          rcp = inc_fidl.recipes.first
          rcp.get_dependencies(inc_fidl, [:pubsub, :psdd4ccm], project_dependencies)

          fidl.includes.each do |ifidl|
            if ifidl.is_member?
              rcp = ifidl.recipes.first
              rcp.get_dependencies(ifidl, [:pubsub, :psdd4ccm], project_dependencies)
            end
          end
        end
        inc_fidl = project.idl_files[@interface_recipe.interface_idl_path]
        @interface_recipe.get_dependencies(inc_fidl, [:pubsub, :psdd4ccm], project_dependencies)

        BRIX11.log(3, '[%s] process_project_dependencies inc_fidl: %s %s', self, inc_fidl, project_dependencies)

        setup_conn_gen(project_dependencies)
        setup_conn_lib(project_dependencies)
      end

      def create_conn_gen
        MPC::IDLProject.new(:psdd_conn_gen, self.recipe)
      end

      def create_conn_lib(mw)
        MPC::PSDDConnProject.new(self.recipe, mw)
      end

      def setup_conn_gen(project_dependencies)
        mpc_obj = mpc_file[:psdd_conn_gen]
        mpc_obj.add_project_file(@interface_recipe.interface_idl_path)

        # idl_includes: idl in recipe self, concat with includes given in project root apcrc file
        mpc_obj.includes << idl_includes << project.idl_includes

        # Also needed the gen_dir from the original recipe of the idl_files for the includes
        recipe.idl_files.each do |n, idf|
          org_fidl = project.idl_files[idf.full_path]
          rcp = org_fidl.recipes.first
          mpc_obj.includes << File.expand_path(rcp.gen_dir, rcp.recipe_file.path)
        end
        mpc_obj.add_dependencies(project_dependencies, :idl_gen)
        mpc_obj.add_dependencies(project_dependencies, :psdd_lem_gen)
        mpc_obj
      end

      def setup_conn_lib(project_dependencies)
        middleware.each do |mw|
          mpc_obj = mpc_file[:"psdd_#{mw}_conn"]
          BRIX11.log(4, '[%s] setup_conn_lib  mpc_obj: %s %s', self, mpc_obj, project_dependencies)

          mpc_obj.add_dependencies(project_dependencies, :psdd_traits_gen)
          mpc_obj.add_dependencies(project_dependencies, :psdd_lem_stub)
          mpc_obj.add_dependencies(project_dependencies, :stub)
        end
      end

      def mpc_name
        '_psdd4ccm'
      end

    end # Port

    module DataInteractionHandler
      def self.setup_data(recipe, fidl)
        prj_dependencies = fidl.project_dependencies
        if mpc_idl_obj = recipe.mpc_file[:psdd_traits_gen]
          # return if the specified IDL file is already part of MPC project
          return if mpc_idl_obj.has_project_file?(fidl.full_path)
        else
          mpc_idl_obj = MPC::IDLProject.new(:psdd_traits_gen, recipe)
          recipe.mpc_file.add_mpc_project(mpc_idl_obj)
          # set idl_includes set in recipe and set in  project file
          mpc_idl_obj.includes << recipe.idl_includes << recipe.project.idl_includes
        end
        # add idl file to new traits project
        mpc_idl_obj.add_project_file(fidl.full_path)
        # register resulting project dependencies for IDL file
        prj_dependencies <<
            MPC::CompileDependency.new(:psdd_traits_gen, recipe) <<
            MPC::LinkDependency.new(:stub, recipe)
        fidl.includes.each do|ifidl|
          ifidl.interaction_types << :pubsub
        end
      end

      def self.process_data_dependencies(recipe, project_dependencies)
        if mpc_proj = mpc_file[:psdd_traits_gen]
          mpc_proj.add_dependencies(project_dependencies, :psdd_traits_gen)
        end
      end

      def self.get_data_dependencies(recipe, idl_prj_dependencies, project_dependencies)
        BRIX11.log(4, '[%s] get_data_dependencies[psdd4ccm] : %s', recipe, project_dependencies)
        project_dependencies.merge(idl_prj_dependencies,
                                   :lem_gen, :lem_stub, :psdd_traits_gen)
      end
    end
  end # PSDD4CCM

  ConnectorRecipe.register_port_type(:psdd4ccm, PSDD4CCM::Port)
  DataIdlRecipe.register_interaction_handler(:psdd4ccm, PSDD4CCM::DataInteractionHandler)
end

# load specializations and extensions
Dir.glob(File.join(File.dirname(__FILE__), 'psdd4ccm', '*.rb')).each do |fnm|
  require fnm
end
