#--------------------------------------------------------------------
# @file    mpc_ext.rb
# @author  Martin Corino
#
# @brief  DDS4CCM MPC specializations
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------

module AxciomaPC

  module MPC

    # MPC project specialization for DDS4CCM NDDS connector library
    class DdsNddsConnProject < MPC::CompileProject

      def initialize(recipe)
        super(:dds_ndds_conn, recipe)
        base_projects(%w{ciaox11_dds4ccm_impl ciaox11_dds4ccm_base ciaox11_executor})
        project_dependencies << "#{mpc_id}_dds_conn_gen"
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
