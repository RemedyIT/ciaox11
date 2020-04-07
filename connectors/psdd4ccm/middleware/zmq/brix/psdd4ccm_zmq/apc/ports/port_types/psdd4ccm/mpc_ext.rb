#--------------------------------------------------------------------
# @file    mpc_ext.rb
# @author  Martin Corino
#
# @brief  PSDD4CCM ZMQ MPC specializations
#
# @copyright Copyright (c) Remedy IT Expertise BV
# Chamber of commerce Rotterdam nr.276339, The Netherlands
#--------------------------------------------------------------------

# make sure MPC base definitions are loaded
require 'brix/ciaox11/apc/mpcfile.rb'

module AxciomaPC

  module MPC

    PSDDConnProject.middleware_base_projects[:zmq] = 'ciaox11_psdd4ccm_zmq_impl'

  end # MPC

end
