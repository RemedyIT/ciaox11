#--------------------------------------------------------------------
# @file    corba4ccm_port.rb
# @author  Martin Corino
#
# @brief  ExF corba4ccm port extension
#
# @copyright Copyright (c) Remedy IT Expertise BV
# Chamber of commerce Rotterdam nr.276339, The Netherlands
#--------------------------------------------------------------------
module AxciomaPC

  module CORBA4CCM

    # reopen Port class
    class Port < PortType
      # add chain method
      def setup_recipe_idl_with_exf(inc_fidl)
        # do we support ExF?
        if recipe.exf
          # check if ExF skeletons might be needed
          check_exf_skel_requirement(inc_fidl)
        end
        setup_recipe_idl_without_exf(inc_fidl)
      end

      # add ExF extension method
      def check_exf_skel_requirement(fidl)
        fidl.properties[:exf_skel] = true if fidl.properties[:needs_skel]
        fidl.includes.each { |ifidl| check_exf_skel_requirement(ifidl) if ifidl.is_member? }
      end
      private :check_exf_skel_requirement

      # add chain method
      def create_conn_gen_with_exf
        mpcobj = create_conn_gen_without_exf
        mpcobj.base_projects << 'ciaox11_exf_idl' if self.recipe.exf
        mpcobj
      end

      def create_conn_lib_with_exf
        mpcobj = create_conn_lib_without_exf
        mpcobj.base_projects << 'ciaox11_exf_amh' if self.recipe.exf
        mpcobj
      end

      # create patched method chains
      alias_method_chain :setup_recipe_idl, :exf
      alias_method_chain :create_conn_gen, :exf
      alias_method_chain :create_conn_lib, :exf
    end

    # add ExF specific interaction handler
    module ExF
      module DataInteractionHandler

        def self.setup_data(recipe, fidl)
          # does the IDL file need full skeletons?
          if fidl.properties[:needs_skel]
            if mpc_idl_obj = recipe.mpc_file[:skel_gen]
              # check if ExF support flag needs to be added
              mpc_idl_obj.base_projects << 'ciaox11_exf_idl' if fidl.properties[:exf_skel]
              # now update the skel compiler project
              mpc_skel_obj = recipe.mpc_file[:skel]
              # do we need ExF base project?
              mpc_skel_obj.base_projects << 'ciaox11_exf_amh' if fidl.properties[:exf_skel]
              # could be that we add this multiple times but that is no problem as
              # #base_projects is a unique string list
            end
          end
        end

        def self.process_data_dependencies(_recipe, _project_dependencies)
          # noop
        end

        def self.get_data_dependencies(_recipe, _idl_prj_dependencies, _project_dependencies)
          # noop
        end

      end
    end

  end # CORBA4CCM

  # register ExF specific interaction handler
  DataIdlRecipe.register_interaction_handler(:corba4ccm, CORBA4CCM::ExF::DataInteractionHandler)

end # AxciomaPC
