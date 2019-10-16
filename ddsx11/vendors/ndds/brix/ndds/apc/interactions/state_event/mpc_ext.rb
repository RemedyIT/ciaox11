#--------------------------------------------------------------------
# @file    mpc_ext.rb
# @author  Martin Corino
#
# @brief  State and Event MPC specializations
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------

module AxciomaPC

  module MPC

    # Add State/Event MPC IDL project specializations
    MPC::IDLProject::DEFAULTS.merge!({
      :ddsx11_ndds_idl_gen => {
        :add_idl_flags => '-Scc -Sch -Scp -Scdr',
        :export => true,
        :base_projects => %w{ddsx11_ts_defaults},
        :auto_dependencies => %w{}
      },
      :ddsx11_ndds_types_gen => {
        :base_projects => %w{ddsx11_vendor_ts_defaults},
        :project_postfix => 'ddsx11_ndds_types_gen',
        :auto_dependencies => %w{ddsx11_ndds_idl_gen},
        :template_path => 'idl/ndds'
      }
    })

    class NDDSTsStubProject < MPC::CompileProject

      def initialize(recipe)
        super(:ddsx11_ndds_types, recipe)
        project_dependencies << "#{mpc_id}_ddsx11_ndds_types_gen"
        @base_projects = %w{ddsx11_impl}
      end

      def add_sources(idf)
        ifs = recipe.dds_idl_file_path(idf)
        ifs_noext = ifs.sub(/\.idl\Z/, '')
        @sources.concat([ recipe.get_relative_path(ifs_noext+'.cxx'),
          recipe.get_relative_path(ifs_noext+'Plugin.cxx'),
          recipe.get_relative_path(ifs_noext+'Support.cxx'),
          recipe.get_relative_path(ifs_noext+'_typesupport.cpp') ].flatten)
      end

      def add_headers(idf)
        ifs = recipe.dds_idl_file_path(idf)
        ifs_noext = ifs.sub(/\.idl\Z/, '')
        @headers.concat([ recipe.get_relative_path(ifs_noext+'.h'),
                          recipe.get_relative_path(ifs_noext+'Plugin.h'),
                          recipe.get_relative_path(ifs_noext+'Support.h'),
                          recipe.get_relative_path(ifs_noext+'_typesupport.h') ].flatten)
      end

      def shared_name
        "#{recipe.shared_name}_ddsx11_ndds_types"
      end

      def dynamic_names
        [ "#{recipe.export_name.upcase}_TYPESUPPORT_BUILD_DLL" ]
      end
    end

  end # MPC

end # AxciomaPC
