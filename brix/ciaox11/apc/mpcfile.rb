#--------------------------------------------------------------------
# @file    mpcfile.rb
# @author  Marijke Hengstmengel
#
# @brief   Base MPC project classes
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------#
require 'set'

module AxciomaPC
  module MPC
    def self.generate(project)
      options = {}
      BRIX11::GenFile.transaction do
        # iterate mpc registry
        project.mpc_files.each do |path, mpc_file|
          BRIX11.log(3, '[MPC] generating mpc file %s', path)
          w = APCWriter.new(BRIX11::GenFile.new(path), options, mpc_file)
          w.visit_ciaox11_mpc
        end
      end
    end

    def self.remove(project)
      project.mpc_files.each_key do |path|
        BRIX11.log(4, '[MPC] removing mpc file %s', path)
        ::File.delete(path) if ::File.exist?(path)
      end
    end

    class Dependency
      def initialize(prjtype=nil, *deps)
        @project_type = prjtype || :none
        @dependencies = MPC::Dependencies.new << deps
      end
      attr_reader :project_type, :dependencies

      # returns all prerequisite projects resulting from this dependency
      def prerequisite_projects
        # return all unique projects from indirect dependencies
        preqs = ::Set.new
        dependencies.each do |idep|
          preqs.merge(idep.prerequisite_projects)
        end
        preqs
      end

      # returns all necessary include paths resulting from this dependency
      def includes
        # return includes resulting from indirect dependencies
        incs = ::Set.new
        dependencies.each do |idep|
          incs.merge(idep.includes)
        end
        incs
      end

      # returns all necessary link libraries resulting from this dependency
      def libs
        # return link libraries resulting from indirect dependencies
        llibs = ::Set.new
        dependencies.each do |idep|
          llibs.merge(idep.libs)
        end
        llibs
      end

      # returns all necessary link library search paths resulting from this dependency
      def lib_paths
        # return all library search paths resulting from indirect dependencies
        libpaths = ::Set.new
        dependencies.each do |idep|
          libpaths.merge(idep.lib_paths)
        end
        libpaths
      end

      def dup
        self.class.new(project_type, dependencies)
      end

      def merge(dep)
        raise "[#{self}] ERROR - merging different project type [#{dep.project_type}]" if project_type != dep.project_type
        @dependencies.merge(dep.dependencies)
      end

      def to_s
        "APC::MPC::Dependency{#{project_type}}"
      end

      def dump(indent=0, out=STDERR)
        out.puts (' ' * indent) + self.to_s
        dependencies.dump(indent + 2, out)
      end
    end # Dependency

    class CompileDependency < Dependency
      def initialize(prjtype=nil, recipe=nil, *deps)
        super(prjtype, *deps)
        @recipes = if recipe
                      ::Set.new(::Set === recipe ? recipe : [recipe].flatten)
                    else
                      ::Set.new
                    end
      end
      attr_reader :recipes

      # returns all prerequisite projects resulting from this dependency
      def prerequisite_projects
        # start with all direct dependencies
        preqs = ::Set.new(recipes.collect { |rcp| (rcp.mpc_file[project_type].wants_build? && rcp.mpc_file[project_type].project_name) || nil }.compact)
        # now collect all (unique) recorded dependencies for these direct prerequisites
        preq_deps = recipes.inject([]) { |list, rcp| list.concat(rcp.mpc_file[project_type].project_dependencies) }
        # now add all projects from indirect dependencies that are not covered by direct dependencies
        dependencies.each do |idep|
          preqs.merge(idep.prerequisite_projects - preq_deps)
        end
        preqs
      end

      # returns all necessary include paths resulting from this dependency
      def includes
        # start with includes resulting from direct dependencies
        incs = ::Set.new(recipes.inject([]) { |list, rcp| list.concat(rcp.mpc_file[project_type].include_dependencies) })
        # now add includes resulting from indirect dependencies
        dependencies.each do |idep|
          incs.merge(idep.includes)
        end
        incs
      end

      def dup
        self.class.new(project_type, recipes, dependencies)
      end

      def merge(dep)
        super
        @recipes.merge(dep.recipes) if CompileDependency === dep
      end

      def to_s
        "APC::MPC::CompileDependency{#{project_type}}"
      end

      def dump(indent=0, out=STDERR)
        out.puts (' ' * indent) + self.to_s
        out.puts (' ' * (indent + 2)) + "[#{recipes.to_a.join(',')}]"
        dependencies.dump(indent + 2, out)
      end
    end # CompileDependency

    class Dependencies
      def initialize
        @table = ::Hash.new
      end

      def find(prjtype)
        @table[prjtype]
      end
      alias :[] :find

      def add(dep)
        if Enumerable === dep
          dep.each { |d| add(d) }
        elsif @table[dep.project_type]
          @table[dep.project_type].merge(dep)
        else
          @table[dep.project_type] = dep
        end
        self
      end
      alias :<< :add

      def project_types
        @table.keys
      end

      def merge(deps, *prjtypes)
        if prjtypes.empty?
          prjtypes = deps.project_types
        end
        prjtypes.each do |prjtype|
          if dep = deps.find(prjtype)
            self << dep
          end
        end
        self
      end

      def each(&block)
        @table.each_value(&block)
      end

      def to_s
        "APC::MPC::Dependencies{#{project_types.join(',')}}"
      end

      def dump(indent=0, out=STDERR)
        out.puts (' ' * indent) + self.to_s
        self.each { |dep| dep.dump(indent + 2, out) }
      end

    end # Dependencies

    class File

      @mpc_projects = []

      def initialize(full_path, project)
        @full_path = full_path
        @project = project
        @mpc_projects = {}
      end

      attr_reader :full_path

      def name
        ::File.basename(@full_path)
      end

      def mpc_file_dir
        ::File.dirname(@full_path)
      end

      def add_mpc_project(mpc_project)
        mpc_project.mpc_file = self
        @mpc_projects[mpc_project.type] = mpc_project
        self
      end
      alias :<< :add_mpc_project

      def mpc_projects
        @mpc_projects.values
      end

      def find(prjtype)
        @mpc_projects[prjtype]
      end
      alias :[] :find

      def to_s
        "APC::MPC::File{#{full_path}}"
      end

    end # File

    class Project

      def initialize (type, recipe)
        @recipe = recipe
        @type = type
        @project_postfix = @type.to_s
        @includes = Util::UniqueStringList.new(:ws)
        @base_projects = Util::UniqueStringList.new(:ws)
        @project_dependencies = Util::UniqueStringList.new(:ws)
        @project_files = Util::UniqueStringList.new
        @mpc_file = nil
      end

      attr_accessor :mpc_file
      attr_accessor :recipe , :type , :base_projects
      attr_reader :project_dependencies

      def to_s
        "#{@mpc_file}@#{project_name}"
      end

      def recipe_id
        recipe.recipe_id
      end

      def mpc_id
        recipe.mpc_id
      end

      def base_projects(base_prj=nil)
        @base_projects.assign(base_prj) if base_prj
        @base_projects
      end

      def mpc_file_dir
        @mpc_file.mpc_file_dir
      end

      def project_postfix(s=nil)
        @project_postfix = s.to_s if s
        @project_postfix
      end

      def project_name
        "#{mpc_id}_#{@project_postfix}"
      end

      def template_path
        ''
      end

      # set/get the include directories
      def includes(dirs=nil)
        @includes.assign(dirs) if dirs
        @includes
      end

      def include_dependencies
        includes.to_a
      end

      # add a project (IDL) file
      # in derived project classes this may automatically
      # add derived files as sources/headers
      def add_project_file(fullpath)
        @project_files << fullpath
      end

      def has_project_file?(fullpath)
        @project_files.include?(fullpath)
      end

      def wants_build?
        !@project_files.empty?
      end

      # in derived classes this may simply return the list
      # of project files or a (partially) derived list
      def sources
        []
      end

      def add_dependencies (deps, deptype, include_prereq=true)
        if dep = deps.find(deptype)
          project_dependencies << dep.prerequisite_projects if include_prereq
          add_dependency(dep)
        end
      end

      def add_dependency(dep)
        includes << dep.includes
      end
      protected :add_dependency

    end # Project
  end # MPC
end #AxciomaPC

require 'brix/ciaox11/apc/mpcprojects/mpc_compile.rb'
require 'brix/ciaox11/apc/mpcprojects/mpc_exec.rb'
require 'brix/ciaox11/apc/mpcprojects/mpc_idl.rb'
