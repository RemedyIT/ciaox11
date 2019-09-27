#--------------------------------------------------------------------
# @file    mpc_ext.rb
# @author  Martin Corino
#
# @brief  State and Event MPC specializations
#
# @copyright Copyright (c) Remedy IT Expertise BV
# Chamber of commerce Rotterdam nr.276339, The Netherlands
#--------------------------------------------------------------------

# make sure MPC base definitions are loaded
require 'brix/ciaox11/apc/mpcfile.rb'

module AxciomaPC

  module MPC

    # Add State/Event MPC IDL project specializations
    MPC::IDLProject::DEFAULTS.merge!({
      :dds_lem_gen => {
        :add_idl_flags => '-Glem,gen -Gxhst -Scdr -Scp',
        :project_postfix => 'lem_gen',
        :export => true,
        :base_projects => %w{ciaox11_idldefaults ciaox11_dds4ccm},
        :auto_dependencies => %w{}
      },
      :se_idl_gen => {
        :add_idl_flags => '-Gdds4ccm,lem -Scc -Sch -Scp -Scdr',
        :base_projects => %w{ciaox11_dds4ccm_idldefaults ciaox11_dds4ccm},
        :auto_dependencies => %w{}
      }
    })

    class DdsLemStubProject < MPC::CompileProject

      def initialize(recipe)
        super(:dds_lem_stub, recipe)
        project_dependencies << "#{mpc_id}_lem_gen"
        project_postfix('lem_stub')
        @base_projects = %w{ciaox11_dds4ccm_lem_stub}
        # add default sources and headers
        @sources.concat([
            ((recipe.gen_dir+"/") << recipe.interface_name << 'C.cpp'),
            ((recipe.gen_dir+"/") << recipe.interface_name << 'EC.cpp')
        ])
        @headers.concat([
            ((recipe.gen_dir+"/") << recipe.interface_name << 'C.h'),
            ((recipe.gen_dir+"/") << recipe.interface_name << 'EC.h'),
            ((recipe.gen_dir+"/") << recipe.export_name << '_stub_export.h'),
            ((recipe.gen_dir+"/") << recipe.export_name << '_lem_stub_export.h')
        ])
      end

      def dynamic_names
        [ "#{recipe.export_name.upcase}_STUB_BUILD_DLL",
          "#{recipe.export_name.upcase}_LEM_STUB_BUILD_DLL" ]
      end

    end

  end # MPC

end # AxciomaPC
