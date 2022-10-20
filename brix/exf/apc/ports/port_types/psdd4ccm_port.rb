#--------------------------------------------------------------------
# @file    psdd4ccm_port.rb
# @author  Martin Corino
#
# @brief   ExF PSDD4CCM port extensions
#
# @copyright Copyright (c) Remedy IT Expertise BV
# Chamber of commerce Rotterdam nr.276339, The Netherlands
#--------------------------------------------------------------------

module AxciomaPC

  module PSDD4CCM

    # reopen Port class
    class Port < PortType
      def create_conn_lib_with_exf(mw)
        mpcobj = create_conn_lib_without_exf(mw)
        mpcobj.base_projects << 'ciaox11_exf_core' if self.recipe.exf
        mpcobj
      end

      def setup_conn_gen_with_exf(project_dependencies)
        mpc_obj = setup_conn_gen_without_exf(project_dependencies)
        mpc_obj.base_projects << 'ciaox11_exf_idl' if self.recipe.exf
        mpc_obj
      end

      # create patched method chains
      alias_method_chain :create_conn_lib, :exf if method_defined? :create_conn_lib
      alias_method_chain :setup_conn_gen, :exf
    end # Port

  end # PSDD4CCM

end
