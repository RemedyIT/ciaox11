#--------------------------------------------------------------------
# @file    recipe_ext.rb
# @author  Martin Corino
#
# @brief  ARR messaging interaction pattern specializations
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------

module AxciomaPC

  module ARR

    # Extension module for DataIdlRecipe
    module DataIDLExtension

      def process_arr_data_dependencies(project_dependencies)
        [:ami4ccm_lem_gen, :lem_gen, :ami4ccm_lem_stub, :lem_stub].each do |prjtype|
          if mpc_proj = mpc_file[prjtype]
            mpc_proj.add_dependencies(project_dependencies, prjtype)
          end
        end
      end

      def get_arr_data_dependencies(project_dependencies, idl_prj_dependencies)
        project_dependencies.merge(idl_prj_dependencies, :lem_gen, :lem_stub)
        project_dependencies.merge(idl_prj_dependencies, :ami4ccm_lem_gen, :ami4ccm_lem_stub)
      end

    end

    AxciomaPC::DataIdlRecipe.send(:include, DataIDLExtension)

    # Extension module for ComponentRecipe
    module ComponentExtension

      def needs_ami?
        @idl_files.each_value.any? {|fidl| fidl.properties[:has_ami4ccm_receptacle] == true }
      end

      def setup_comp_gen_ami(project_dependencies)
        mpc_obj = mpc_file[:comp_gen]
        mpc_obj.add_dependencies(project_dependencies, :ami4ccm_lem_gen)
        mpc_obj.idl_flags.add('-Gami4ccm,comp')
      end

      def setup_lem_comp_ami(project_dependencies)
        return if self.combined_lib?
        mpc_obj = mpc_file[:comp_lem]
        mpc_obj.add_dependencies(project_dependencies, :ami4ccm_lem_stub)
      end

      def setup_svnt_comp_ami(project_dependencies)
        return if self.combined_lib?
        mpc_obj = mpc_file[:comp_svnt]
        mpc_obj.add_dependencies(project_dependencies, :ami4ccm_lem_stub)
      end

      def setup_exec_lib_ami(project_dependencies)
        mpc_obj = mpc_file[:exec]
        mpc_obj.add_dependencies(project_dependencies, :ami4ccm_lem_stub)

        mpc_obj.lib_paths << lib_paths
        mpc_obj.link_libs << libs
        mpc_obj.base_projects << 'ciaox11_ami4ccm_stub'
     end

    end

    AxciomaPC::ComponentRecipe.send(:include, ComponentExtension)

  end # ARR

end
