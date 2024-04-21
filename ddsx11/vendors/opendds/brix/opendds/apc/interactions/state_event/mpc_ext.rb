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
      ddsx11_opendds_idl_gen: {
        add_idl_flags: '-Scc -Sch -Scph -Scdr',
        export: true,
        base_projects: %w{ddsx11_ts_defaults},
        auto_dependencies: %w{}
      },
      ddsx11_opendds_types_gen: {
        base_projects: %w{ddsx11_vendor_ts_defaults dcps_ts_subdir},
        project_postfix: 'ddsx11_opendds_types_gen',
        export: true,
        auto_dependencies: %w{ddsx11_opendds_idl_gen},
        template_path: 'idl/opendds'
      }
    })

    class OpenDDSTsStubProject < MPC::CompileProject
      def initialize(recipe)
        super(:ddsx11_opendds_types, recipe)
        project_dependencies << "#{mpc_id}_ddsx11_opendds_types_gen"
        @base_projects = %w{ddsx11_impl ddsx11_no_idlfiles}
      end

      def add_sources(idf)
        ifs = recipe.dds_idl_file_path(idf)
        ifs_noext = ifs.sub(/\.idl\Z/, '')
        @sources.concat([recipe.get_relative_path(ifs_noext + 'C.cpp'),
                         recipe.get_relative_path(ifs_noext + 'TypeSupportImpl.cpp'),
                         recipe.get_relative_path(ifs_noext + 'TypeSupportC.cpp'),
                         recipe.get_relative_path(ifs_noext + '_typesupport.cpp')].flatten)
      end

      def add_headers(idf)
        ifs = recipe.dds_idl_file_path(idf)
        ifs_noext = ifs.sub(/\.idl\Z/, '')
        @headers.concat([recipe.get_relative_path(ifs_noext + 'C.h'),
                         recipe.get_relative_path(ifs_noext + 'TypeSupportImpl.h'),
                         recipe.get_relative_path(ifs_noext + 'TypeSupportC.h'),
                         recipe.get_relative_path(ifs_noext + '_typesupport.h')].flatten)
      end

      def shared_name
        "#{recipe.shared_name}_ddsx11_opendds_types"
      end

      def dynamic_names
        ["#{recipe.export_name.upcase}_TYPESUPPORT_BUILD_DLL"]
      end
    end
  end # MPC
end # AxciomaPC
