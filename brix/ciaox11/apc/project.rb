  #--------------------------------------------------------------------
# @file    project.rb
# @author  Marijke Hengstmengel
#
# @brief  AXP Project class
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------
require 'find'

module AxciomaPC

  # Represents a BRIX11 APC project
  class Project

    RCFILE = RECIPE_FILE_EXT.dup.freeze

    # Provides the DSL interface for APC project files (aprc)
    class Configurator
      def initialize(project)
        @project = project
      end

      # set the BRIX11 project type to generate by default
      def project_type(type)
        @project.project_type(type.to_s)
      end

      # add IDL include paths for all recipes in the project
      def idl_includes(*paths)
        @project.idl_includes << paths.flatten.collect {|ip| File.expand_path(ip, @project.root_path)}
      end

      # set the default library output path for the project
      def libout(path)
        @project.libout(path)
      end

      # add common C++ compiler include paths for the project
      def includes(*dirs)
        # resolve embedded environment variable references
        solved_dirs = dirs.flatten.collect  {|dir|  Util::path_without_env(dir) }

        @project.include_dirs << solved_dirs.flatten.collect {|dir| File.expand_path(dir, @project.root_path) }
        @project.include_dirs
      end

      # add common library search paths for the project
      def libpaths(*paths)
        # resolve environment variable references
        solved_paths = paths.flatten.collect  {|path|  Util::path_without_env(path) }

        @project.lib_paths << solved_paths.flatten.collect {|p| File.expand_path(p, @project.root_path) }
      end

      # add common link libraries for the project
      def libs(*libs)
        @project.libs << libs.flatten
      end

      # add common link library literals for the project
      def lit_libs(*libs)
        @project.lit_libs << libs.flatten
      end

      # do not allow any unknown properties/methods
      def method_missing(method, *args, &block)
        raise "Unknown property #{method} for #{@project.to_s}"
      end
    end

    # Project singleton class methods
    class << self

      # known/loaded project registry
      def projects
        @projects ||= {}
      end

      # retrieve previously loaded project for given root path (if any)
      def get_project(root_path)
        BRIX11.log(1, '[APC::Project] retrieving project [%s]', projects[root_path])
        projects[root_path]
      end

      # (re-)load project for current working environment
      def load_project(autogen = :allways)
        BRIX11.log(2, '[APC::Project] loading project')
        root_path = find_project_root
        # make sure that recipes are loaded and interpreted again
        if !projects[root_path].nil?
          projects[root_path] = nil
        end
        # project doesn't exist yet/anymore.
        # so add a new project
        projects[root_path] = add_project(root_path, autogen)
        BRIX11.log(1, '[%s] loaded project', projects[root_path])
        projects[root_path]
      end

      # deregister project
      def clean_project(project)
        projects[project.root_path] = nil
      end

      private

      # find project root from current working directory
      def find_project_root
        BRIX11.log(2, '[APC::Project] Opening project, looking for project_root')
        curpath = File.expand_path('.')
        begin
          # check if this is the project root
          if File.file?(File.join(curpath, RCFILE))
            # save project root
            BRIX11.log(2, '[APC::Project] Found project config at %s', curpath)
            return curpath
          end
          # not found yet, move one dir up until we reach the root
          curpath = File.expand_path(File.join(curpath, '..'))
        end while !(curpath =~ /^(#{File::SEPARATOR}|.:#{File::SEPARATOR})$/)
        raise BRIX11::Command::CmdError, '[APC::Project] no valid aprc file found!'
      end

      # load and add a new project
      def add_project(root_path, autogen)
        BRIX11.log(2, '[APC::Project] creating project for root %s', root_path)
        prj = AxciomaPC::Project.new(root_path, autogen)
        frc = File.join(root_path, RCFILE)
        if File.file?(frc) && File.readable?(frc)
          prj.configure(File.read(frc), frc)
        else
          raise BRIX11::Command::CmdError, "[APC::Project] cannot access #{frc}!"
        end
        prj.setup
        prj
      end

    end

    def initialize(root_path, autogen = :allways)
      @root_path = root_path
      @autogenerate = autogen
      @idl_files = {}
      @idl_dirs = {}
      @idl_index = {}
      @recipefiles = {}
      @mpcfiles = {}
      @idl_includes = Util::UniqueStringList.new(:ws)
      @include_dirs = Util::UniqueStringList.new(:ws)
      @lib_paths = Util::UniqueStringList.new(:ws)
      @libs = Util::UniqueStringList.new(:ws)
      @lit_libs = Util::UniqueStringList.new(:ws)
      @generated_idl = Util::UniqueStringList.new(:ws)
      @mpc_proj_name_counts = {}
      libout('lib')
    end

    attr_accessor :root_path, :autogenerate

    def configure(code, path)
      prj = Configurator.new(self)
      eval(code, binding, path)
    end

    def project_type(type=nil)
      if type
        BRIX11.log_fatal("Invalid project_type '#{type}' for #{self.to_s}") unless BRIX11::Project.valid_type?(type)
        @project_type = type
      end
      @project_type
    end

    def idl_includes(incs = nil)
      @idl_includes.assign(incs.collect {|ip| File.expand_path(ip, root_path)}) if incs
      @idl_includes
    end

    def libout(path=nil)
      @libout = File.expand_path(path, root_path) if path
      @libout
    end

    def include_dirs(paths=nil)
      @include_dirs.assign(paths) if paths
      @include_dirs
    end

    def lib_paths(paths=nil)
      @lib_paths.assign(paths) if paths
      @lib_paths
    end

    def libs(libs=nil)
      @libs.assign(libs) if libs
      @libs
    end

    def lit_libs(libs=nil)
      @lit_libs.assign(libs) if libs
      @lit_libs
    end

    # check mpc project name prefix usage for this project
    # (to prevent duplicate project names)
    def make_mpc_project_name_prefix(recipe)
      if @mpc_proj_name_counts.has_key? recipe.recipe_id
        # other recipe(s) exist with the same name, so a new
        # mpc_name prefix is necessary to prevent duplicate project names

        # increment the usage count
        @mpc_proj_name_counts[recipe.recipe_id] += 1
        # return the new prefix
        "#{recipe.recipe_id}_#{@mpc_proj_name_counts[recipe.recipe_id]}"
      else
        # the mpc project name prefix for this recipe is not yet registered, so its the first
        @mpc_proj_name_counts[recipe.recipe_id] = 0
        # return the default prefix
        recipe.recipe_id
      end
    end

    # check if given path is part of project tree
    def is_project_path?(path)
      path.start_with?(@root_path) && (path.size == @root_path.size || path[@root_path.size] == File::SEPARATOR)
    end

    # setup/initialize the project
    def setup
      BRIX11.log(2, '[%s] initializing', self)
      # full inventory:
      #   find and read all recipe files
      #   find all idl files
      Dir.chdir(root_path) do
        # collect files in project directories
        collect_files
      end
    end

    # walk through subdirectories to collect all idl, recipe and other files
    def collect_files
      BRIX11.log(3, '[%s] collecting project files', self)

      # collect and load recipes
      Dir.glob("**/*.#{AxciomaPC::RECIPE_FILE_EXT}").each do |path|
        frcp = add_recipe_file(File.expand_path(path, root_path))
        frcp.load_recipes
      end
      BRIX11.log(3, '[%s] all recipes have been loaded', self)

      # setup recipes
      recipe_files.values.each { |frcp| frcp.setup }
      BRIX11.log(3, '[%s] setup of all user defined recipes is done', self)

      # collect and register all project IDL files referenced
      # from recipes (recursively analyzed)
      recipe_files.values.each { |frcp| frcp.collect_idl_files }
      BRIX11.log(3, '[%s] collected and registered all IDL files referenced from recipes', self)

      # verify all recipes and their (collected) IDL files
      recipe_files.values.each { |frcp| frcp.verify }
      BRIX11.log(3, '[%s] verification of all user defined recipes is done', self)

      # check all dependencies of all IDL contained in project recipes
      # => creates implicit recipes for unmanaged project IDL if possible
      #    (checks IDL includes recursively)
      # => error otherwise
      recipe_files.values.each { |frcp| frcp.check_idl_dependencies }
      BRIX11.log(3, '[%s] checked all IDL dependencies for all user defined recipes', self)
    end
    private :collect_files

    # prepare the project for building
    def prepare(no_generate = false)
      BRIX11.log(2, '[%s] preparing', self)

      # process project recipes, setup project MPC specs and register
      # all project dependencies
      recipe_files.each_value do |recipe_file|
        recipe_file.setup_projects
      end

      # process registered project dependencies and update MPC specs
      # accordingly
      recipe_files.each_value do |recipe_file|
        recipe_file.process_project_dependencies
      end

      # if we reach this point everything should be ready to
      # generate the MPC files on disk
      MPC.generate(self) unless no_generate

      BRIX11.log(2, '[%s] MPC files prepared', self)
    end

    # MPC::File registry
    def mpc_files
      @mpcfiles ||= {}
    end

    # add an MPC::File for given path
    def add_mpc_file (path)
      mpc_files[path] = MPC::File.new(path, self)
      mpc_files[path]
    end

    # full registry of known IDL files
    def idl_files
      @idl_files
    end

    # add a 'known' IDL file
    def add_idl_file(fp, state=nil)
      if idl_files.has_key?(fp)
        idl_files[fp]
      else
        BRIX11.log(4, '[%s] registering IDL file %s', self, fp)
        fidl = IDLFile.new(fp, self, state)
        (@idl_dirs[fidl.path] ||= []) << fidl if fidl.is_member?
        (@idl_index[fidl.name] ||= []) << fidl unless fidl.is_external?
        idl_files[fp] = fidl
      end
    end

    # check for a 'member' IDL file for given path
    def has_idl_file?(path)
      idl_files.has_key?(path) && idl_files[path].is_member?
    end

    # get all member IDL files for given directory (non-recursive)
    def get_idl_files(dir)
      @idl_dirs[dir] || []
    end

    # get all project IDL files with given name
    def match_idl_files(idlfnm)
      @idl_index[idlfnm] || []
    end

    # get all IDL filepaths of IDL files generated from recipes
    def generated_idl
      @idl_files.select {|path, fidl| fidl.is_generated? }.keys
    end

    # registry of known recipe files
    def recipe_files
      @recipefiles
    end

    # add a known recipe file
    def add_recipe_file (path, implicit=false)
      frcp = RecipeFile.new(path, self)
      frcp.mark_implicit if implicit
      recipe_files[path] = frcp
    end

    # retrieve enabled features
    def features
      unless @features
        @features = {}
        _ace_root = ::BRIX11::Exec.get_run_environment('ACE_ROOT')
        _cfg_file = File.join(_ace_root, 'bin', 'MakeProjectCreator', 'config', 'default.features')
        if File.exist?(_cfg_file)
          File.readlines(_cfg_file).each do |ln|
            if /\A\s*\w+\s*=\s*1\s*\Z/ =~ ln  # only match enabled features
              feature = ln.split('=').first.strip
              @features[feature.to_sym] = true
            end
          end
          BRIX11.log(3, "[#{self}] loaded features : #{@features}")
        end
      end
      @features
    end
    private :features

    # match feature requirements
    def check_features(*required_features)
      required_features.all? {|rf| features[rf.to_sym] }
    end

    def to_s
      "APC::Project{#{root_path}}"
    end

    def dump(indent=0, out=STDERR)
      out.puts (' ' * indent) + self.to_s
      out.puts (' ' * (indent + 2)) + '-----'
      recipe_files.each_value { |frcp| frcp.dump(indent + 2, out) }
      out.puts (' ' * (indent + 2)) + '-----'
      idl_files.each_value { |fidl| fidl.dump(indent + 2, out) }
    end

  end

end
