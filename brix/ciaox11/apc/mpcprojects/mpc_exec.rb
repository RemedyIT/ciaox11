#--------------------------------------------------------------------
# @file    mpc_exec.rb
# @author  Marijke Hengstmengel
#
# @brief   mpc registry for executor projects
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------
require 'pathname'
require 'brix/ciaox11/apc/mpcprojects/mpc_compile.rb'


module AxciomaPC

  module MPC

    class ExecProject < MPC::CompileProject
      def initialize(recipe, combined=false)
        super(:exec, recipe)
        project_dependencies << "#{mpc_id}#{COMP_LEM_NM_EXT}" unless combined
        link_libs << "#{recipe.shared_name}#{COMP_LEM_NM_EXT}" unless combined
        #Add event. extra sources from recipe
        @sources << recipe.sources
        @headers << recipe.headers
        @sources << (recipe.idl_without_ext.collect { |ifs| ((ifs + EXEC_F) << EXT_CPP) })
        @headers << (recipe.idl_without_ext.collect { |ifs| ((ifs + EXEC_F) << EXT_HEADER) })
        @headers << ((recipe.gen_dir + '/') << recipe.export_name << '_' << @project_postfix << EXPORT_HEADER)
        # if the recipe specifies it's own defaults overrule here
        if !recipe.base_projects.default.empty?
          @base_projects.assign(recipe.base_projects.default)
        else
          # otherwise add our defaults
          @base_projects << %w{ciaox11_executor ciaox11_logger}
        end
        # add any additional base projects defined in the recipe
        @base_projects << recipe.base_projects.plus
        # remove any base projects so specified in the recipe
        @base_projects.delete(recipe.base_projects.min)
        @dynamic_names = [recipe.export_name.upcase << '_' << @project_postfix.upcase + '_BUILD_DLL']
        # if a combined component library is required
        # add stub, lem and svnt specs also
        if combined
          project_dependencies << "#{mpc_id}_comp_gen"
          # stub
          if recipe.needs_stub?
            @base_projects << %w(ciaox11_ccm_session_stub)
            recipe.idl_files.each do |idlfn, fidl|
              @headers << ((recipe.gen_dir + '/') << ::File.basename(idlfn, '.idl') << STUB_F << EXT_HEADER)
              if fidl.creates_stubcode? || fidl.needs_anytype?  # stub code?
                @sources << ((recipe.gen_dir + '/') << ::File.basename(idlfn, '.idl') << STUB_F << EXT_CPP)
              end
            end
            @headers << ((recipe.gen_dir + '/') << recipe.export_name << STUB_NM_EXT << EXPORT_HEADER)
            @dynamic_names << (recipe.export_name.upcase << STUB_NM_EXT.upcase + '_BUILD_DLL')
          end
          # lem
          @sources << (recipe.idl_without_ext.collect { |ifs| ((recipe.gen_dir + '/') << ifs << LEM_STUB_F << EXT_CPP) })
          @headers << (recipe.idl_without_ext.collect { |ifs| ((recipe.gen_dir + '/') << ifs << LEM_STUB_F << EXT_HEADER) })
          @headers << ((recipe.gen_dir + '/') << recipe.export_name << LEM_STUB_NM_EXT << EXPORT_HEADER)
          @dynamic_names << (recipe.export_name.upcase << LEM_STUB_NM_EXT.upcase + '_BUILD_DLL')
          # svnt
          @sources << (recipe.idl_without_ext.collect { |ifs| ((recipe.gen_dir + '/') << ifs << SVNT_F << EXT_CPP) })
          @headers << (recipe.idl_without_ext.collect { |ifs| ((recipe.gen_dir + '/') << ifs << SVNT_F << EXT_HEADER) })
          @headers << ((recipe.gen_dir + '/') << recipe.export_name << SVNT_NM_EXT << EXPORT_HEADER)
          @dynamic_names << (recipe.export_name.upcase << SVNT_NM_EXT.upcase + '_BUILD_DLL')
        end
      end

      def template_path
        'compile/exec'
      end

      def dynamic_names
        @dynamic_names
      end

      def set_stub
        link_libs << "#{recipe.shared_name}#{STUB_NM_EXT}"
        project_dependencies << "#{mpc_id}#{STUB_NM_EXT}"
      end
    end

  end # MPC

end #AxciomaPC
