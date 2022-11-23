#--------------------------------------------------------------------
# @file    dds4ccm_port.rb
# @author  Martin Corino
#
# @brief   ExF DDS4CCM port extensions
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------

module AxciomaPC

  module DDS4CCM

    # reopen Port class
    class Port < PortType
      def create_ndds_conn_lib_with_exf
        mpcobj = create_ndds_conn_lib_without_exf
        mpcobj.base_projects << 'ciaox11_exf_core' if self.recipe.exf
        mpcobj
      end

      def create_opendds_conn_lib_with_exf
        mpcobj = create_opendds_conn_lib_without_exf
        mpcobj.base_projects << 'ciaox11_exf_core' if self.recipe.exf
        mpcobj
      end

      def setup_conn_gen_with_exf(project_dependencies)
        mpc_obj = setup_conn_gen_without_exf(project_dependencies)
        mpc_obj.base_projects << 'ciaox11_exf_idl' if self.recipe.exf
        mpc_obj
      end

      # create patched method chains
      alias_method_chain :create_ndds_conn_lib, :exf if method_defined? :create_ndds_conn_lib
      alias_method_chain :create_opendds_conn_lib, :exf if method_defined? :create_opendds_conn_lib
      alias_method_chain :setup_conn_gen, :exf
    end # Port

  end # DDS4CCM

end
