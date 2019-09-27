#--------------------------------------------------------------------
# @file    dds4ccm_port.rb
# @author  Martin Corino
#
# @brief  DDS4CCM port specializations
#
# @copyright Copyright (c) Remedy IT Expertise BV
# Chamber of commerce Rotterdam nr.276339, The Netherlands
#--------------------------------------------------------------------

module AxciomaPC

  module DDS4CCM

    Port.middleware_implementations << :ndds

    # initialize the vendor IDL include path for the SEV interface recipe
    # this solution requires that only one DDS vendor is configured for AXCIOMA
    SEV::InterfaceRecipe.vendor_idl_includes <<
        (File.join(BRIX11::Exec.get_run_environment('CIAOX11_ROOT'), 'ddsx11/vendors/ndds/idl')+File::SEPARATOR)

    # reopen Port class
    class Port < PortType

      def setup_projects_with_ndds
        setup_projects_without_ndds
        if middleware.include?(:ndds)
          mpc_obj = create_ndds_conn_lib
          mpc_file.add_mpc_project(mpc_obj)

          recipe.idl_files.each do |_,fidl|
            inc_fidl = project.idl_files[fidl.full_path]
            rcp = inc_fidl.recipes.first
            #set the interaction type
            rcp.setup_project_interaction(inc_fidl, :dds4ccm_ndds)
          end

          # Also for the state event interface file, which the connector needs,
          # setup the project files,
          # in case this isn't done already via a sev component
          inc_fidl = project.idl_files[@interface_recipe.interface_idl_path]
          rcp = inc_fidl.recipes.first
          rcp.setup_project_interaction(inc_fidl, :sev)
        end
      end

      def process_project_dependencies_with_ndds
        project_dependencies = process_project_dependencies_without_ndds
        setup_ndds_conn_lib(project_dependencies) if middleware.include?(:ndds)
        project_dependencies
      end

      def create_ndds_conn_lib
        MPC::DdsNddsConnProject.new(self.recipe)
      end

      def setup_conn_gen_with_ndds(project_dependencies)
        mpc_obj = setup_conn_gen_without_ndds(project_dependencies)
        mpc_obj.add_dependencies(project_dependencies, :ddsx11_ndds_idl_gen) if middleware.include?(:ndds)
        mpc_obj
      end

      def setup_ndds_conn_lib(project_dependencies)
        mpc_obj = mpc_file[:dds_ndds_conn]
        BRIX11.log(4, '[%s] setup_ndds_conn_lib  mpc_obj: %s %s', self, mpc_obj, project_dependencies)

        mpc_obj.add_dependencies(project_dependencies, :ddsx11_ndds_types)
        mpc_obj.add_dependencies(project_dependencies, :dds_lem_stub)
        mpc_obj.add_dependencies(project_dependencies, :stub)
      end

      # create patched method chains
      alias_method_chain :setup_projects, :ndds
      alias_method_chain :process_project_dependencies, :ndds
      alias_method_chain :setup_conn_gen, :ndds

    end # Port

    module NDDSDataInteractionHandler

      def self.setup_data(recipe, fidl)
        recipe.add_ndds_proj(fidl)
      end

      def self.process_data_dependencies(recipe, project_dependencies)
        recipe.process_dds4ccm_data_dependencies(project_dependencies,
                                                 :ddsx11_ndds_idl_gen,
                                                 :ddsx11_ndds_types_gen,
                                                 :ddsx11_ndds_types)
      end

      def self.get_data_dependencies(recipe, idl_prj_dependencies, project_dependencies)
        recipe.get_dds4ccm_data_dependencies(project_dependencies, idl_prj_dependencies,
                                             :ddsx11_ndds_idl_gen, :ddsx11_ndds_types)
      end

    end

  end # DDS4CCM

  DataIdlRecipe.register_interaction_handler(:dds4ccm_ndds, DDS4CCM::NDDSDataInteractionHandler)

end

# load specializations and extensions
Dir.glob(File.join(File.dirname(__FILE__), 'dds4ccm', '*.rb')).each do |fnm|
  require fnm
end
