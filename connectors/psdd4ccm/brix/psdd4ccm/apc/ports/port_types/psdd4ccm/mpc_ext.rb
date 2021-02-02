#--------------------------------------------------------------------
# @file    mpc_ext.rb
# @author  Martin Corino
#
# @brief  PSDD4CCM MPC specializations
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------

# make sure MPC base definitions are loaded
require 'brix/ciaox11/apc/mpcfile.rb'

module AxciomaPC

  module MPC

    # add PubSub MPC IDL project specializations
    MPC::IDLProject::DEFAULTS.merge!({
       :psdd_conn_gen => {
           :add_idl_flags => '-Gpsdd4ccm,conn_only -Gxhsv -Gxhcn -Scc -Scp -Sci -Sch',
           :export => true,
           :base_projects => %w{ciaox11_psdd4ccm_idl},
           :auto_dependencies => []
       },
    })

    # MPC project specialization for PSDD4CCM connector library
    class PSDDConnProject < MPC::CompileProject

      class << self
        def middleware_base_projects
          @middleware_base_projects ||= {}
        end
      end

      def initialize(recipe, middleware)
        super(:"psdd_#{middleware}_conn", recipe)
        base_projects(%w{ciaox11_executor})
        base_projects << PSDDConnProject.middleware_base_projects[middleware]
        project_dependencies << "#{mpc_id}_psdd_conn_gen"
        # add default sources and headers
        base = recipe.port_handler.interface_name
        @sources.concat([
            ((recipe.gen_dir + '/') << base << '_conn' << EXT_CPP),
            ((recipe.gen_dir + '/') << base << '_svnt' << EXT_CPP)
        ])
        @headers.concat([
            ((recipe.gen_dir + '/') << base << '_conn' << EXT_HEADER),
            ((recipe.gen_dir + '/') << base << '_svnt' << EXT_HEADER),
            ((recipe.gen_dir + '/') << recipe.export_name << '_conn_export' << EXT_HEADER),
            ((recipe.gen_dir + '/') << recipe.export_name << '_svnt_export' << EXT_HEADER)
        ])
        # Add user defined extra sources from recipe
        @sources.concat recipe.sources
        @headers.concat recipe.headers
      end

      def template_path
        'compile/conn'
      end

      def dynamic_names
        [(recipe.export_name.upcase << '_CONN_BUILD_DLL'),
         (recipe.export_name.upcase << '_SVNT_BUILD_DLL')]
      end

    end

  end # MPC

end
