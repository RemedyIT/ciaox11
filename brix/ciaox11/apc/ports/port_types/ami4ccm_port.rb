#--------------------------------------------------------------------
# @file    ami4ccm_port.rb
# @author  Marijke Hengstmengel
#
# @brief   ami4ccm port
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------
require 'brix/ciaox11/apc/scanidlfile'

module AxciomaPC

  module AMI4CCM

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
        mpc_obj = create_ami_lem_gen
        mpc_file.add_mpc_project(mpc_obj)


        mpc_obj = create_conn_gen
        mpc_file.add_mpc_project(mpc_obj)

        mpc_obj = create_conn_lib
        mpc_file.add_mpc_project(mpc_obj)

        recipe.idl_files.each do |_,fidl|
          inc_fidl = project.idl_files[fidl.full_path]
          rcp = inc_fidl.recipes.first
          #set the interaction type
          rcp.setup_project_interaction(inc_fidl, :ami4ccm)
        end
      end

      def process_project_dependencies
        BRIX11.log(3, '[%s] process project dependencies', self)

        project_dependencies = MPC::Dependencies.new
        recipe.idl_files.each do |_,fidl|
          inc_fidl = project.idl_files[fidl.full_path]
          rcp = inc_fidl.recipes.first
          rcp.get_dependencies(inc_fidl, [:ami4ccm], project_dependencies)
        end

        BRIX11.log(4, '[%s] collected project dependencies : %s', self, project_dependencies)

        setup_ami_lem_gen(project_dependencies)
        setup_conn_gen(project_dependencies)
        setup_conn_lib(project_dependencies)
      end

      def create_ami_lem_gen
        MPC::IDLProject.new(:ami_lem_gen, self.recipe)
      end

      def create_conn_gen
        mpcobj = MPC::IDLProject.new(:amic_conn_gen, self.recipe)
        mpcobj.add_idl_flags("-Wb,conn_intf=#{self.recipe.port_handler.interface}") if self.recipe.port_handler.interface
        mpcobj
      end

      def create_conn_lib
        MPC::AmiConnProject.new(self.recipe)
      end

      def setup_ami_lem_gen(project_dependencies)
        mpc_obj = mpc_file[:ami_lem_gen]
        recipe.idl_files.collect do |n,f|
          # get generated name for idl_file
          name = f.name.gsub('.idl', 'A.idl')
          # get gen_dir path for recipe managing idl file
          gen_dir = f.recipes.first.full_gen_path
          # get full path for generated idl file
          mpc_obj.add_project_file(File.join(gen_dir, name))
        end

        # idl_includes: idl in recipe self, concat with includes given in project root apcrc file
        mpc_obj.includes << idl_includes << project.idl_includes
        mpc_obj.add_dependencies(project_dependencies, :ami4ccm_lem_gen)
      end


      def setup_conn_gen(project_dependencies)
        mpc_obj = mpc_file[:amic_conn_gen]
        recipe.idl_files.collect { |n,f| mpc_obj.add_project_file(f.full_path) }

        mpc_obj.add_dependencies(project_dependencies, :lem_gen)

        #Also needed the gen_dir from the original recipe of the idl_files for the includes
        recipe.idl_files.each do |n,idf|
          org_fidl = project.idl_files[idf.full_path]
          rcp = org_fidl.recipes.first
          mpc_obj.includes << File.expand_path(rcp.gen_dir,rcp.recipe_file.path)
        end

        # idl_includes: idl in recipe self, concat with includes given in project root apcrc file
        mpc_obj.includes << idl_includes << project.idl_includes
        # Also needed the own generated output dir
        mpc_obj.includes << File.expand_path(recipe.gen_dir,recipe.recipe_file.path)
      end

      def setup_conn_lib(project_dependencies)
        mpc_obj = mpc_file[:amic_conn]
        BRIX11.log(4, '[%s] setup_conn_lib mpc_obj: %s', self, mpc_obj)

        mpc_obj.add_dependencies(project_dependencies, :lem_stub)
        mpc_obj.add_dependencies(project_dependencies, :ami4ccm_lem_stub)
      end

      def mpc_name
        '_ac'
      end

    end

    module DataInteractionHandler

      def self.setup_data(recipe, fidl)
        # lem is needed, but ami4ccm requires corba4ccm, so lem generation
        # is done in Data IDL extension of corba4ccm port
        recipe.add_lem_proj(fidl)
        recipe.add_ami_proj(fidl)
      end
      def self.process_data_dependencies(recipe, project_dependencies)
        recipe.process_ami4ccm_data_dependencies(project_dependencies)
      end
      def self.get_data_dependencies(recipe, idl_prj_dependencies, project_dependencies)
        recipe.get_ami4ccm_data_dependencies(project_dependencies, idl_prj_dependencies)
      end

    end

  end

  ConnectorRecipe.register_port_type(:ami4ccm, AMI4CCM::Port)
  DataIdlRecipe.register_interaction_handler(:ami4ccm, AMI4CCM::DataInteractionHandler)

end # AMI4CCM

# load specializations and extensions
Dir.glob(File.join(File.dirname(__FILE__), 'ami4ccm', '*.rb')).each do |fnm|
  require fnm
end
