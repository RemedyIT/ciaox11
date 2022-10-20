#--------------------------------------------------------------------
# @file    ami4ccm_port.rb
# @author  Martin Corino
#
# @brief   ExF ami4ccm port extension
#
# @copyright Copyright (c) Remedy IT Expertise BV
# Chamber of commerce Rotterdam nr.276339, The Netherlands
#--------------------------------------------------------------------

module AxciomaPC

  module AMI4CCM

    # reopen Port class
    class Port < PortType
      # add chain method
      def create_conn_gen_with_exf
        mpcobj = create_conn_gen_without_exf
        mpcobj.base_projects << 'ciaox11_exf_idl' if self.recipe.exf
        mpcobj
      end

      def create_conn_lib_with_exf
        mpcobj = create_conn_lib_without_exf
        mpcobj.base_projects << 'ciaox11_exf_core' if self.recipe.exf
        mpcobj
      end

      # create patched method chains
      alias_method_chain :create_conn_gen, :exf
      alias_method_chain :create_conn_lib, :exf
    end
  end

end # AMI4CCM
