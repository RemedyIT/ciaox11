#--------------------------------------------------------------------
# @file    mpc_ext.rb
# @author  Marijke Hengstmengel
#
# @brief  CORBA4CCM MPC specializations
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------

# make sure MPC base definitions are loaded
require 'brix/ciaox11/apc/mpcfile.rb'

module AxciomaPC
  module MPC
    # add corba4ccm port specializations
    MPC::IDLProject::DEFAULTS.merge!({
      corba_conn_gen: {
           export: true,
           base_projects: %w{ciaox11_corba4ccm_idl},
           auto_dependencies: %w{}
       },
    })

    # MPC project specialization for CORBA4CCM connector library
    class CorbaConnProject < MPC::CompileProject
      CC = '_cc'

      def initialize(recipe)
        super(:corba_conn, recipe)
        project_dependencies << (mpc_id + '_corba_conn_gen')
        # Add event. extra sources from recipe
        @sources.concat recipe.sources
        @headers.concat recipe.headers
        @sources.concat(recipe.idl_without_ext.collect { |ifs| ((recipe.gen_dir + '/') << ifs << CC << EXEC_F << EXT_CPP) })
        @sources.concat(recipe.idl_without_ext.collect { |ifs| ((recipe.gen_dir + '/') << ifs << CC << SVNT_F << EXT_CPP) })
        @sources.concat(recipe.idl_without_ext.collect { |ifs| ((recipe.gen_dir + '/') << ifs << CC << LEM_STUB_F << EXT_CPP) })


        @headers.concat(recipe.idl_without_ext.collect { |ifs| ((recipe.gen_dir + '/') << ifs << CC << EXEC_F << EXT_HEADER) })
        @headers.concat(recipe.idl_without_ext.collect { |ifs| ((recipe.gen_dir + '/') << ifs << CC << SVNT_F << EXT_HEADER) })
        @headers.concat(recipe.idl_without_ext.collect { |ifs| ((recipe.gen_dir + '/') << ifs << CC << LEM_STUB_F << EXT_HEADER) })
        @headers.concat(recipe.idl_without_ext.collect { |ifs| ((recipe.gen_dir + '/') << ifs << CC << STUB_F << EXT_HEADER) })
        @headers.concat((recipe.gen_dir + '/') << recipe.export_name << CC << STUB_NM_EXT << EXPORT_HEADER)
        @headers.concat((recipe.gen_dir + '/') << recipe.export_name << CC << LEM_STUB_NM_EXT << EXPORT_HEADER)
        base_projects(%w(ciaox11_executor ciaox11_corba4ccm_impl))
      end

      def template_path
        'compile/conn'
      end

      def dynamic_names
        [(recipe.export_name.upcase << '_CC_STUB_BUILD_DLL'),
         (recipe.export_name.upcase << '_CC_LEM_STUB_BUILD_DLL'),
         (recipe.export_name.upcase << '_CC_EXEC_BUILD_DLL'),
         (recipe.export_name.upcase << '_CC_SVNT_BUILD_DLL')]
      end
    end
  end # MPC
end
