#--------------------------------------------------------------------
# @file    mpc_ext.rb
# @author  Marijke Hengstmengel
#
# @brief  AMI4CCM MPC specializations
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------

# make sure MPC base definitions are loaded
require 'brix/ciaox11/apc/mpcfile.rb'

module AxciomaPC

  module MPC

    # add ami4ccm port specializations
    MPC::IDLProject::DEFAULTS.merge!({
       :amic_conn_gen => {
           #:add_idl_flags => '-Gami4ccm,conn -Gxhsv -Gxhcn -Scc -Scp -Sch ',
           :export => true,
           :base_projects => %w{ciaox11_ami4ccm_conn_all_idl},
           :auto_dependencies => %w{ami_lem_gen}
       },
       :ami_lem_gen => {
           :add_idl_flags => '-Glem,gen -Gxhlst -Sch -Scc -Scp',
           :export => true,
           :base_projects => %w{ciaox11_idldefaults},
           :auto_dependencies => %w{}
       },
    })

    # MPC project specialization for AMI4CCM connector library
    class AmiConnProject < MPC::CompileProject
      AC = 'A_conn'

      def initialize(recipe)
        super(:amic_conn, recipe)
        #Add event. extra sources from recipe
        @sources.concat recipe.sources
        @headers.concat recipe.headers
        base_projects(%w(ciaox11_ami4ccm_impl ciaox11_executor))
        project_dependencies << "#{mpc_id}_amic_conn_gen"
        # add default sources and headers
        @sources.concat(recipe.idl_without_ext.collect {|ifs| ((recipe.gen_dir + '/') << ifs << AC << EXEC_F << EXT_CPP) })
        @sources.concat(recipe.idl_without_ext.collect {|ifs| ((recipe.gen_dir + '/') << ifs << AC << SVNT_F << EXT_CPP) })
        @sources.concat(recipe.idl_without_ext.collect {|ifs| ((recipe.gen_dir + '/') << ifs << AC << LEM_STUB_F << EXT_CPP) })
        @sources.concat(recipe.idl_without_ext.collect {|ifs| ((recipe.gen_dir + '/') << ifs << 'A' << LEM_STUB_F << EXT_CPP) })
        @sources.concat(recipe.idl_without_ext.collect {|ifs| ((recipe.gen_dir + '/') << ifs << 'Ami' << STUB_F << EXT_CPP) })

        @headers.concat(recipe.idl_without_ext.collect {|ifs| ((recipe.gen_dir + '/') << ifs << AC << EXEC_F << EXT_HEADER) })
        @headers.concat(recipe.idl_without_ext.collect {|ifs| ((recipe.gen_dir + '/') << ifs << AC << SVNT_F << EXT_HEADER) })
        @headers.concat(recipe.idl_without_ext.collect {|ifs| ((recipe.gen_dir + '/') << ifs << AC << LEM_STUB_F << EXT_HEADER) })
        @headers.concat(recipe.idl_without_ext.collect {|ifs| ((recipe.gen_dir + '/') << ifs << 'A' << LEM_STUB_F << EXT_HEADER) })
        @headers.concat(recipe.idl_without_ext.collect {|ifs| ((recipe.gen_dir + '/') << ifs << 'Ami' << STUB_F << EXT_HEADER) })
      end

      def template_path
        'compile/conn'
      end

      def dynamic_names
        [(recipe.export_name.upcase << '_AMIC_BUILD_DLL'),
         (recipe.export_name.upcase << '_LEM_STUB_BUILD_DLL'),
         (recipe.export_name.upcase << '_LEM_STUB_AMI_CONN_BUILD_DLL'),
         (recipe.export_name.upcase << '_AMI4CCM_CONN_BUILD_DLL'),
         (recipe.export_name.upcase << '_AMI4CCM_SVNT_BUILD_DLL')]
      end

    end

  end # MPC

end
