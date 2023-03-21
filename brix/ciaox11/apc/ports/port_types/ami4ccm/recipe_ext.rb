#--------------------------------------------------------------------
# @file    recipe_ext.rb
# @author  Martin Corino
#
# @brief  AMI4CCM ARR interaction implementation specializations
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------

module AxciomaPC
  module AMI4CCM
    # Extension module for DataIdlRecipe
    module DataIDLExtension
      def process_ami4ccm_data_dependencies(project_dependencies)
        if mpc_proj = mpc_file[:lem_gen]
          mpc_proj.add_dependencies(project_dependencies, :lem_gen)
        end
        if mpc_proj = mpc_file[:lem_stub]
          mpc_proj.add_dependencies(project_dependencies, :lem_stub)
        end
      end

      def get_ami4ccm_data_dependencies(project_dependencies, idl_prj_dependencies)
        project_dependencies.merge(idl_prj_dependencies, :lem_gen, :lem_stub, :ami4ccm_lem_gen, :ami4ccm_lem_stub)
      end

      def add_ami_proj(fidl)
        # Is there already a ami stub project for this recipe?
        prj_dependencies = fidl.project_dependencies
        if mpc_idl_obj = mpc_file[:ami4ccm_lem_idl_gen]
          # return if the specified IDL file is already part of MPC project
          return if mpc_idl_obj.has_project_file?(fidl.full_path)

          mpc_idl_stubs_obj = mpc_file[:ami4ccm_lem_gen]

          mpc_stub_obj = mpc_file[:ami4ccm_lem_stub]
        else
          mpc_idl_obj = MPC::IDLProject.new(:ami4ccm_lem_idl_gen, self)
          mpc_file.add_mpc_project(mpc_idl_obj)
          # set idl_includes set in recipe and set in  project file
          mpc_idl_obj.includes << idl_includes << project.idl_includes

          mpc_idl_stubs_obj = MPC::IDLProject.new(:ami4ccm_lem_gen, self)
          mpc_idl_stubs_obj.project_dependencies << mpc_idl_obj.project_name
          mpc_idl_stubs_obj.add_idl_flags "-Wb,base_export_macro=#{export_name.upcase + '_AMI4CCM'}"
          mpc_idl_stubs_obj.add_idl_flags "-Wb,base_export_include=#{export_name.downcase + '_ami4ccm'}"
          mpc_file.add_mpc_project(mpc_idl_stubs_obj)
          # set idl_includes set in recipe and set in  project file
          mpc_idl_stubs_obj.includes << idl_includes << project.idl_includes

          mpc_stub_obj = MPC::AMI4CCMStubProject.new(self)
          mpc_file.add_mpc_project(mpc_stub_obj)
        end

        # add with add_project_file the idl file to idl_files
        # for ami idl-project and to sources and headers for ami stub compile project
        mpc_idl_obj.add_project_file(fidl.full_path)
        mpc_idl_stubs_obj.add_project_file(File.join(full_gen_path, File.basename(fidl.name, '.*') + 'A.idl'))
        mpc_stub_obj.add_project_file(fidl.full_path)

        # register resulting project dependencies for IDL file
        prj_dependencies <<
            MPC::CompileDependency.new(:ami4ccm_lem_gen, self) <<
            MPC::LinkDependency.new(:ami4ccm_lem_stub, self,
                                    MPC::LinkDependency.new(:stub, self))

        # register resulting project dependencies for IDL file
        fidl.includes.each do |ifidl|
          ifidl.interaction_types << :arr
        end
      end
    end # DataIDLExtension
  end # AMI4CCM

  AxciomaPC::DataIdlRecipe.send(:include, AMI4CCM::DataIDLExtension)
end
