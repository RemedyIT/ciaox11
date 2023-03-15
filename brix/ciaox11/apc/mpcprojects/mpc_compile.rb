#--------------------------------------------------------------------
# @file    mpc_compile.rb
# @author  Marijke Hengstmengel
#
# @brief   mpc registry for compile projects
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------#
require 'pathname'

module AxciomaPC
  module MPC
    class LinkDependency < CompileDependency
      # returns all necessary link libraries resulting from this dependency
      def libs
        # start with libraries resulting from direct dependencies
        libs = ::Set.new(recipes.inject([]) { |list, rcp| list.concat(rcp.mpc_file[project_type].lib_dependencies) })
        # now add libraries resulting from indirect dependencies
        dependencies.each do |idep|
          libs.merge(idep.libs)
        end
        libs
      end

      # returns all necessary link library search paths resulting from this dependency
      def lib_paths
        # start with library search paths resulting from direct dependencies
        lib_paths = ::Set.new(recipes.inject([]) { |list, rcp| list.concat(rcp.mpc_file[project_type].lib_paths) })
        # now add library search paths resulting from indirect dependencies
        dependencies.each do |idep|
          lib_paths.merge(idep.lib_paths)
        end
        lib_paths
      end

      def to_s
        "APC::MPC::LinkDependency{#{project_type}}"
      end
    end # LinkDependency

    class CompileProject < MPC::Project

      # file extensions
      EXT_CPP = '.cpp'
      EXT_HEADER = '.h'
      EXPORT_HEADER = '_export.h'

      # name modifiers
      SVNT_NM_EXT = '_svnt'
      SVNT_F = '_svnt'
      STUB_NM_EXT = '_stub'
      STUB_F = 'C'
      LEM_STUB_F = 'EC'
      COMP_LEM_NM_EXT = '_comp_lem'
      EXEC_NM_EXT = '_exec'
      EXEC_F = '_exec'

      def initialize(type, recipe)
        super(type, recipe)
        @sources = Util::UniqueStringList.new(:ws)
        @headers = Util::UniqueStringList.new(:ws)
        @link_libs = Util::UniqueStringList.new(:ws)
        @link_lit_libs = Util::UniqueStringList.new(:ws)
        @lib_paths = Util::UniqueStringList.new(:ws)
        @lib_out = recipe.project.libout
        lib_paths << @lib_out
        includes << ::File.expand_path(recipe.gen_dir, recipe.recipe_file.path)
      end

      def shared_name
        "#{recipe.shared_name}_#{@project_postfix}"
      end

      def dynamic_names
        [ recipe.export_name.upcase << '_' << @project_postfix.upcase + '_BUILD_DLL' ]
      end

      def template_path
        'compile'
      end

      def sources
        @sources
      end

      def headers
        @headers
      end

      def lib_paths
        @lib_paths
      end

      def lib_out(path=nil)
        if path
          lib_paths.delete(@lib_out) if @lib_out
          lib_paths << (@lib_out = path)
        end
        @lib_out
      end
      alias :set_libout_path :lib_out

      def link_libs
        @link_libs
      end

      def lib_dependencies
        link_libs.to_a + (wants_build? ? [shared_name] : [])
      end

      def link_lit_libs
        @link_lit_libs
      end

      def add_dependency(dep)
        super
        link_libs << dep.libs
        lib_paths << dep.lib_paths
      end
      protected :add_dependency

      # derived implementation; automatically adds source and header file(s) for
      # each added project (IDL) file
      def add_project_file(fullpath)
        super
        # get base name without .idl extension
        fileid = ::File.basename(fullpath, '.idl')
        add_sources(fileid)
        add_headers(fileid)
      end

      def wants_build?
        !@sources.empty?
      end

      # derived classes implement versions to add derived source(s)
      def add_sources(prj_fileid)
      end

      # derived classes implement versions to add derived source(s)
      def add_headers(prj_fileid)
      end
    end # CompileProject

    class StubProject < CompileProject
      def initialize(recipe)
        super(:stub, recipe)
        @project_postfix = 'stub'
        base_projects(%w(taox11_lib))
        project_dependencies << "#{mpc_id}_idl_gen"
        # add default sources and headers
        @headers << ((recipe.gen_dir + '/') << recipe.export_name << '_' << @project_postfix << EXPORT_HEADER)
      end

      def add_sources(idf)
        @sources << ((recipe.gen_dir + '/') << idf << STUB_F << EXT_CPP)
      end

      def add_headers(idf)
        @headers << ((recipe.gen_dir + '/') << idf << STUB_F << EXT_HEADER)
      end
    end

    class CompStubProject < CompileProject
      def initialize(recipe)
        super(:comp_stub, recipe)
        @project_postfix = 'stub'
        base_projects(%w(ciaox11_ccm_session_stub))
        project_dependencies << "#{mpc_id}_comp_gen"
        # add default sources and headers
        recipe.idl_files.each do |idlfn, fidl|
          @headers << ((recipe.gen_dir + '/') << ::File.basename(idlfn, '.idl') << STUB_F << EXT_HEADER)
          if fidl.creates_stubcode? || fidl.needs_anytype?  # stub code?
            @sources << ((recipe.gen_dir + '/') << ::File.basename(idlfn, '.idl') << STUB_F << EXT_CPP)
          end
        end
        @headers << ((recipe.gen_dir + '/') << recipe.export_name << STUB_NM_EXT << EXPORT_HEADER)
      end
    end

    class CompLemStubProject < CompileProject
      def initialize(recipe)
        super(:comp_lem, recipe)
        @project_postfix = 'comp_lem'
        project_dependencies << "#{mpc_id}_comp_gen"
        base_projects(%w(ciaox11_ccm_session_stub))
        # add default sources and headers
        @sources << (recipe.idl_without_ext.collect { |ifs| ((recipe.gen_dir + '/') << ifs << LEM_STUB_F << EXT_CPP) })
        @headers << (recipe.idl_without_ext.collect { |ifs| ((recipe.gen_dir + '/') << ifs << LEM_STUB_F << EXT_HEADER) })
        @headers << ((recipe.gen_dir + '/') << recipe.export_name << LEM_STUB_NM_EXT << EXPORT_HEADER)
      end

      #overwrite because we must use here always the LEM_STUB_NM_EXT
      def dynamic_names
        [recipe.export_name.upcase << LEM_STUB_NM_EXT.upcase + '_BUILD_DLL']
      end

      def set_stub
        link_libs << (recipe.shared_name + STUB_NM_EXT)
        project_dependencies << "#{mpc_id}#{STUB_NM_EXT}"
      end
    end

    # For components and connectors
    class SvntProject < CompileProject
      def initialize(recipe)
        super(:comp_svnt, recipe)
        @project_postfix = 'svnt'
        if recipe.type == :component
          project_dependencies << "#{mpc_id}#{COMP_LEM_NM_EXT}"
          link_libs << "#{recipe.shared_name}#{COMP_LEM_NM_EXT}"
        end
        base_projects(%w(ciaox11_ccm_session_stub))
        # add default sources and headers
        @sources << (recipe.idl_without_ext.collect { |ifs| ((recipe.gen_dir + '/') << ifs << SVNT_F << EXT_CPP) })
        @headers << (recipe.idl_without_ext.collect { |ifs| ((recipe.gen_dir + '/') << ifs << SVNT_F << EXT_HEADER) })
        @headers << ((recipe.gen_dir + '/') << recipe.export_name << SVNT_NM_EXT << EXPORT_HEADER)
      end

      def set_stub
        link_libs << (recipe.shared_name + STUB_NM_EXT)
      end
    end
  end # MPC
end #AxciomaPC
