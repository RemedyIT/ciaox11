#--------------------------------------------------------------------
# @file    recipe_ext.rb
# @author  Martin Corino
#
# @brief  CORBA4CCM SRR interaction implementation specializations
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------

module AxciomaPC

  module CORBA4CCM

    # Extension module for DataIdlRecipe
    module DataIDLExtension

      def process_corba4ccm_data_dependencies(project_dependencies)
        [:lem_gen, :skel_gen, :lem_stub, :skel].each do |prjtype|
          if mpc_proj = mpc_file[prjtype]
            mpc_proj.add_dependencies(project_dependencies, prjtype)
          end
        end
      end

      def get_corba4ccm_data_dependencies(project_dependencies, idl_prj_dependencies)
        project_dependencies.merge(idl_prj_dependencies, :lem_gen, :lem_stub)
        project_dependencies.merge(idl_prj_dependencies, :skel_gen, :skel)
      end

      # add skeleton generation projects for data IDL for the benefit of
      # CORBA4CCM connectors
      def add_skel_proj(fidl)
        # Is there already a skel project for this recipe?
        prj_dependencies = fidl.project_dependencies
        if mpc_idl_obj = mpc_file[:skel_gen]
          # return if the specified IDL file is already part of MPC project
          return if mpc_idl_obj.has_project_file?(fidl.full_path)
        else
          # create MPC::IDLProject for skeleton generation
          mpc_idl_obj = MPC::IDLProject.new(:skel_gen, self)
          mpc_file.add_mpc_project(mpc_idl_obj)
          # get idl_includes from recipe and from project
          mpc_idl_obj.includes << idl_includes << project.idl_includes

          # does the IDL file need full skeletons?
          if fidl.properties[:needs_skel]
            # create skel compiler project for full skeleton support
            mpc_skel_obj = MPC::SkelProject.new(self)
            mpc_file.add_mpc_project(mpc_skel_obj)
          end
        end

        # does the IDL file need full skeletons?
        if fidl.properties[:needs_skel]
          # IDL file needs full skeleton implementations so remove the default suppression flag
          mpc_idl_obj.idl_flags.delete '-SS'

          # now update the skel compiler project
          mpc_skel_obj = mpc_file[:skel]
          mpc_skel_obj.add_project_file(fidl.full_path)
          # register resulting project dependencies for IDL file
          prj_dependencies << MPC::LinkDependency.new(:skel,self,
                                                      MPC::LinkDependency.new(:stub, self))
        else
          # Although no skel lib is needed when :needs_skel is false,
          # the skel headers are included in a base idl file including this IDL file
          # that DOES need skeletons; so the included dirs must be set and the
          # skel_gen project (which is always created) added as prerequisite as well
          # as the stub project
          # by not specifying the recipe for the :skel dependency (nil) this is a noop
          # but the linked :skel_gen dependency is active and pulled in
          prj_dependencies << MPC::Dependency.new(:skel,
                                                  MPC::CompileDependency.new(:skel_gen, self),
                                                  MPC::LinkDependency.new(:stub, self))
        end

        # add IDL file to IDL skel generation project
        mpc_idl_obj.add_project_file(fidl.full_path)
        # register resulting project dependencies for IDL file
        prj_dependencies << MPC::CompileDependency.new(:skel_gen, self)

        # data IDL files do not have interaction types after scanning, so add a interaction type here
        fidl.includes.each do|ifidl|
          ifidl.interaction_types << :corba4ccm
        end
      end

      # add LEM generation projects for data IDL for the benefit of
      # CORBA4CCM connectors
      def add_lem_proj(fidl)
        prj_dependencies = fidl.project_dependencies
        # if the idl file doesn't contain an interface, don't generate lem
        if !fidl.properties[:has_interface]
          # Although no lem is needed, the stub headers are included in the base lem stub headers,
          # so the included dirs must be set here.
          # by not specifying the recipe for the :lem_stub dependency (nil) this is a noop
          # but the linked :stub dependency is active and pulled in
          prj_dependencies << MPC::Dependency.new(:lem_stub, MPC::LinkDependency.new(:stub, self))
          return
        end
        # Is there already a lem_gen project for this recipe?
        if mpc_idl_obj = mpc_file[:lem_gen]
          # return if the specified IDL file is already part of MPC project
          return if mpc_idl_obj.has_project_file?(fidl.full_path)

          mpc_stub_obj = mpc_file[:lem_stub]
        else
          mpc_idl_obj = MPC::IDLProject.new(:lem_gen, self)
          mpc_file.add_mpc_project(mpc_idl_obj)
          #set idl_includes set in recipe and set in  project file
          mpc_idl_obj.includes << idl_includes << project.idl_includes

          mpc_stub_obj = MPC::DataLemStubProject.new(:lem_stub, self)
          mpc_file.add_mpc_project(mpc_stub_obj)
        end

        # add idl file to idl_files for idl-project
        mpc_idl_obj.add_project_file(fidl.full_path)
        # add idl file to sources and headers for lem_stub-project
        mpc_stub_obj.add_project_file(fidl.full_path)

        # register resulting project dependencies for IDL file
        prj_dependencies <<
            MPC::CompileDependency.new(:lem_gen, self) <<
            MPC::LinkDependency.new(:lem_stub, self,
                                    MPC::LinkDependency.new(:stub, self))

        # data IDL files do not have interaction types after scanning, so add interaction type here
        # lem is also needed for ami4ccm, but ami4ccm requires corba4ccm, so lem generation
        # is done here
        fidl.includes.each do|ifidl|
          ifidl.interaction_types << :srr
        end
      end
    end

    AxciomaPC::DataIdlRecipe.send(:include, DataIDLExtension)

  end # CORBA4CCM

end
