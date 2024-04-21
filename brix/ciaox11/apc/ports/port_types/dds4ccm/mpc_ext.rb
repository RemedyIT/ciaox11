#--------------------------------------------------------------------
# @file    mpc_ext.rb
# @author  Martin Corino
#
# @brief  DDS4CCM MPC specializations
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------

# make sure MPC base definitions are loaded
require 'brix/ciaox11/apc/mpcfile'

module AxciomaPC
  module MPC
    # add State/Event MPC IDL project specializations
    MPC::IDLProject::DEFAULTS.merge!({
       dds_conn_gen: {
           add_idl_flags: '-Gdds4ccm,conn_only -Gxhsv -Gxhcn -Scc -Scph -Sci -Sch',
           export: true,
           base_projects: %w{ciaox11_dds4ccm_idldefaults ciaox11_dds4ccm},
           auto_dependencies: []
       }
    })
  end # MPC
end
