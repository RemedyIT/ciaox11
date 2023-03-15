#--------------------------------------------------------------------
# @file    mpc_ext.rb
# @author  Marijke Hengstmengel
#
# @brief  request and reply specializations
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------

# make sure MPC base definitions are loaded
require 'brix/ciaox11/apc/mpcfile.rb'

module AxciomaPC

  module MPC

    # add synch request and reply MPC IDL project specializations
    MPC::IDLProject::DEFAULTS.merge!({
      lem_gen: {
         add_idl_flags: '-Glem,gen -Gxhlst -Sch -Scc -Scp',
         export: true,
         base_projects: %w{ciaox11_idldefaults},
         auto_dependencies: %w{}
      },
      skel_gen: {
         add_idl_flags: '-Scc -Sch -Scp -Gxhsk',
         del_idl_flags: '-Ssh',
         export: true,
         base_projects: %w{ridl_defaults},
         auto_dependencies: %w{}
      },
    })

    LEM_STUB_NM_EXT = '_lem_stub'
    LEM_STUB_F = 'EC'
    SKEL_NM_EXT = '_skel'
    SKEL_F = 'S'

    class SkelProject < MPC::CompileProject
      def initialize(recipe, skel_idl_files = nil)
        super(:skel, recipe)
        base_projects(%w(taox11_lib taox11_portableserver))
        link_libs << (recipe.shared_name + STUB_NM_EXT)
        project_dependencies << (mpc_id + STUB_NM_EXT)
        project_dependencies << (mpc_id + '_skel_gen')
        # add default sources and headers
        @headers.concat((recipe.gen_dir + '/') << recipe.export_name << '_' << @project_postfix << EXPORT_HEADER)
      end

      def add_sources(idf)
        @sources.concat((recipe.gen_dir + '/') << idf << SKEL_F << EXT_CPP)
      end

      def add_headers(idf)
        @headers.concat((recipe.gen_dir + '/') << idf << SKEL_F << EXT_HEADER)
      end

    end

    class DataLemStubProject < MPC::CompileProject
      def initialize(type, recipe)
        super(type, recipe)
        @project_postfix = 'lem_stub'
        project_dependencies <<  "#{mpc_id}#{STUB_NM_EXT}"
        project_dependencies <<  "#{mpc_id}_lem_gen"
        link_libs << (recipe.shared_name + STUB_NM_EXT)
        base_projects(%w(taox11_lib))
        # add default sources and headers
        @headers.concat((recipe.gen_dir + '/') << recipe.export_name << '_' << @project_postfix << EXPORT_HEADER)
      end

      def set_stub
        link_libs << (recipe.shared_name + STUB_NM_EXT)
        project_dependencies << "#{mpc_id}#{STUB_NM_EXT}"
      end

      def add_sources(idf)
        @sources.concat((recipe.gen_dir + '/') << idf << LEM_STUB_F << EXT_CPP)
      end

      def add_headers(idf)
        @headers.concat((recipe.gen_dir + '/') << idf << LEM_STUB_F << EXT_HEADER)
      end
    end

  end # MPC

end # AxciomaPC
