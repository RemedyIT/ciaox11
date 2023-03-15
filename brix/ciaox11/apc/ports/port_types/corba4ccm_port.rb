#--------------------------------------------------------------------
# @file    corba4ccm_port.rb
# @author  Marijke Hengstmengel
#
# @brief  corba4ccm port
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------
module AxciomaPC
  module CORBA4CCM
    class Port < PortType

      class Configurator < PortType::Configurator
        def interface(name)
          @port_type.set_interface(name)
        end
      end

      CONFIGURATOR = Port::Configurator

      def initialize(recipe)
        super
        @interface = nil
      end

      def set_interface(name)
        @interface = name.to_s
      end

      def interface
        @interface
      end

      def setup_projects
        BRIX11.log(3, '[%s] setup projects', self)

        mpc_obj = create_conn_gen
        mpc_file.add_mpc_project(mpc_obj)

        mpc_obj = create_conn_lib
        mpc_file.add_mpc_project(mpc_obj)

        recipe.idl_files.each do |_, fidl|
          inc_fidl = project.idl_files[fidl.full_path]
          setup_recipe_idl(inc_fidl)
        end
      end

      def setup_recipe_idl(inc_fidl)
        rcp = inc_fidl.recipes.first
        # setup for the interaction type
        rcp.setup_project_interaction(inc_fidl, :corba4ccm)
      end
      private :setup_recipe_idl

      def process_project_dependencies
        BRIX11.log(3, '[%s] process project dependencies', self)

        project_dependencies = MPC::Dependencies.new
        recipe.idl_files.each do |_, fidl|
          inc_fidl = project.idl_files[fidl.full_path]
          rcp = inc_fidl.recipes.first
          rcp.get_dependencies(inc_fidl, [:corba4ccm], project_dependencies)
        end

        BRIX11.log(4, '[%s] collected project dependencies : %s', self, project_dependencies)

        setup_conn_gen(project_dependencies)
        setup_conn_lib(project_dependencies)
      end

      def create_conn_gen
        mpcobj = MPC::IDLProject.new(:corba_conn_gen, self.recipe)
        mpcobj.add_idl_flags("-Wb,conn_intf=#{self.recipe.port_handler.interface}") if self.recipe.port_handler.interface
        mpcobj
      end

      def create_conn_lib
        MPC::CorbaConnProject.new(self.recipe)
      end

      def setup_conn_gen(project_dependencies)
        mpc_obj = mpc_file[:corba_conn_gen]
        recipe.idl_files.each { |n, f| mpc_obj.add_project_file(f.full_path) }

        # idl_includes: idl in recipe self, concat with includes given in project root apcrc file
        mpc_obj.includes << idl_includes << project.idl_includes
        # Also needed the own generated output dir
        mpc_obj.includes << File.expand_path(recipe.gen_dir, recipe.recipe_file.path)

        mpc_obj.add_dependencies(project_dependencies, :lem_gen)
      end

      def setup_conn_lib(project_dependencies)
        mpc_obj = mpc_file[:corba_conn]
        BRIX11.log(5, "[%s] setup_conn_lib mpc_obj: %s", self, mpc_obj)

        mpc_obj.add_dependencies(project_dependencies, :skel)
        mpc_obj.add_dependencies(project_dependencies, :lem_stub)
      end

      def mpc_name
        '_cc'
      end

    end

    module DataInteractionHandler
      def self.setup_data(recipe, fidl)
        # always lem needed, despite lem arg
        recipe.add_lem_proj(fidl)
        recipe.add_skel_proj(fidl)
      end

      def self.process_data_dependencies(recipe, project_dependencies)
        recipe.process_corba4ccm_data_dependencies(project_dependencies)
      end

      def self.get_data_dependencies(recipe, idl_prj_dependencies, project_dependencies)
        recipe.get_corba4ccm_data_dependencies(project_dependencies, idl_prj_dependencies)
      end
    end
  end # CORBA4CCM

  ConnectorRecipe.register_port_type(:corba4ccm, CORBA4CCM::Port)
  DataIdlRecipe.register_interaction_handler(:corba4ccm, CORBA4CCM::DataInteractionHandler)
end # AxciomaPC

# load specializations and extensions
Dir.glob(File.join(File.dirname(__FILE__), 'corba4ccm', '*.rb')).each do |fnm|
  require fnm
end
