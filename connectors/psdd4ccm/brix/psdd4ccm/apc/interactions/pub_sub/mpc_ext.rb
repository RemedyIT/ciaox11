#--------------------------------------------------------------------
# @file    mpc_ext.rb
# @author  Martin Corino
#
# @brief  PubSub MPC specializations
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------

# make sure MPC base definitions are loaded
require 'brix/ciaox11/apc/mpcfile.rb'

module AxciomaPC
  module MPC
    # Add State/Event MPC IDL project specializations
    MPC::IDLProject::DEFAULTS.merge!({
      psdd_traits_gen: {
        add_idl_flags: '-Gpsdd4ccm,traits -Scc -Sch -Scdr -Scp',
        base_projects: %w{ciaox11_psdd4ccm_idl},
        auto_dependencies: %w{}
      },
      psdd_lem_gen: {
        add_idl_flags: '-Glem,gen -Gxhst -Scdr -Scp',
        project_postfix: 'lem_gen',
        export: true,
        base_projects: %w{ciaox11_psdd4ccm_idl ciaox11_psdd4ccm},
        auto_dependencies: %w{}
      },
      ps_idl_gen: {
        add_idl_flags: '-Gpsdd4ccm,lem -Scc -Sch -Scp -Scdr',
        base_projects: %w{ciaox11_psdd4ccm_idl ciaox11_psdd4ccm},
        auto_dependencies: %w{}
      },
    })
    class PSDDLemStubProject < MPC::CompileProject

      def initialize(recipe)
        super(:psdd_lem_stub, recipe)
        project_dependencies << "#{mpc_id}_lem_gen"
        project_postfix('lem_stub')
        @base_projects = %w{ciaox11_psdd4ccm_stub}
        # add default sources and headers
        @sources.concat([
            ((recipe.gen_dir + "/") << recipe.interface_name << 'C.cpp'),
            ((recipe.gen_dir + "/") << recipe.interface_name << 'EC.cpp')
        ])
        @headers.concat([
            ((recipe.gen_dir + "/") << recipe.interface_name << 'C.h'),
            ((recipe.gen_dir + "/") << recipe.interface_name << 'EC.h'),
            ((recipe.gen_dir + "/") << recipe.export_name << '_stub_export.h'),
            ((recipe.gen_dir + "/") << recipe.export_name << '_lem_stub_export.h')
        ])
      end

      def dynamic_names
        [ "#{recipe.export_name.upcase}_STUB_BUILD_DLL",
          "#{recipe.export_name.upcase}_LEM_STUB_BUILD_DLL" ]
      end

    end
  end # MPC
end # AxciomaPC
