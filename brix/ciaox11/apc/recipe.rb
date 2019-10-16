#--------------------------------------------------------------------
# @file    recipe.rb
# @author  Marijke Hengstmengel
#
# @brief  DSL component for reading recipes
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------
require 'scanidlfile'
require 'fileutils'

module AxciomaPC

  # Represents a recipe file (a file containing 1 or more recipes)
  class RecipeFile

    def initialize(path, project)
      @name = File.basename(path)
      @path = File.dirname(path)
      @project = project
      @recipes = {}
      @implicit = false
    end

    attr_reader :name, :path, :project

    # load all recipes from file
    def load_recipes
      BRIX11.log(3, '[%s] loading recipes', self)
      begin
        instance_eval(File.read(full_path) ,full_path)
      rescue
        BRIX11.log_error($!.message)
        $!.backtrace.find do |bt|
          file, line, _ = bt.split(':')
          if file == full_path
            BRIX11.show_msg("\t#{file}:#{line}")
            true
          else
            false
          end
        end
        BRIX11.log_fatal("[#{self}] failed to load recipes")
      end
    end

    # mark as implicit recipe file
    def mark_implicit
      @implicit = true
    end

    def is_implicit?
      @implicit
    end

    # returns full path of recipe file
    def full_path
      File.join(@path, @name)
    end

    # capture configured recipe type keywords and create recipes
    def method_missing(method, *args, &block)
      recipe = Recipe.create_recipe(self, method, *args, &block)
      if recipe
        add_recipe(recipe)
        return recipe
      end
      # calling super will cause error if method being called is invalid
      super
    end

    # add a recipe to this file
    def add_recipe(recipe)
      raise "[#{self}] duplicate recipe #{recipe.recipe_id} defined." if @recipes.has_key?(recipe.recipe_id)
      @recipes[recipe.recipe_id] = recipe
    end

    def recipes
      @recipes.values
    end
    private :recipes

    # setup the recipes in this file
    def setup
      recipes.each { |rcp| rcp.setup }
    end

    # verify the recipes in this file
    def verify
      recipes.each {|rcp| rcp.verify }
    end

    # cleanup generated artifacts
    def clean
      recipes.each do |rcp|
        if (!rcp.gen_dir || rcp.gen_dir == '.')
          #do nothing because the user has indicated as generated_code dir, the same dir as the recipe dir
        else
          gen_dir_path = File.join(@path,rcp.gen_dir)
          if Dir.exist?(gen_dir_path)
            # if gen dir is empty or only contains export headers, it is save to remove this dir.
            # Attention: export headers aren't removed with a make clean, so in the case a user has put a export header himself in
            # the gen dir , this file will be removed also
            # solution: adapt mpc to remove generated export headers also.
            files = Dir.entries(gen_dir_path)
            if files.select {|ff| ff !~ /export.h/ && ff !='.' && ff != '..'  }.empty?
              # empty or no other then export file, so remove
              FileUtils.remove_dir(gen_dir_path)
            end
          end
        end
      end
    end

    # collect and register all project IDL files referenced
    # from recipes in this file (recursively analyzed)
    def collect_idl_files
      recipes.each {|rcp| rcp.collect_idl_files }
    end

    # check all dependencies of all IDL referenced in recipes in this file
    def check_idl_dependencies
      recipes.each {|rcp| rcp.check_idl_dependencies }
    end

    # process recipes in this file, setup resulting MPC objects
    # and register project dependencies
    def setup_projects
      recipes.each do |rec_obj|
        rec_obj.setup_projects
      end
    end

    # update all MPC object for project dependencies from recipes
    # in this file
    def process_project_dependencies
      recipes.each do |rec_obj|
        rec_obj.process_project_dependencies
      end
    end

    def to_s
      "APC::RecipeFile{#{full_path}}"
    end

    def dump(indent=0, out=STDERR)
      out.puts (' '*indent)+self.to_s
      recipes.each { |rcp| rcp.dump(indent+2, out) }
    end

  end # RecipeFile

  class Recipe

    # Provides the basic DSL interface for all recipes in recipe files (*.rcp)
    class Configurator
      def initialize(recipe)
        @recipe = recipe
      end

      # add IDL include paths for the recipe
      def idl_includes(*incs)
        @recipe.idl_includes << incs.flatten.compact
      end

      # add IDL files for the recipe
      def idl(*idlfiles)
        @recipe.idl(idlfiles.flatten.compact)
      end

      # set the code generation output path for the recipe
      # (default is 'generated_code')
      def gen_dir(gendir)
        @recipe.gen_dir(gendir.to_s)
      end

      # set the shared library name base for the recipe
      def shared_name(sharedname)
        @recipe.shared_name(sharedname.to_s)
      end

      # set the base export name for the recipe
      def export_name(exportname)
        @recipe.export_name(exportname.to_s)
      end

      # add user defined C/C++ source files for the recipe
      def sources(*srcs)
        @recipe.sources << srcs.flatten.compact
      end

      # add user defined C/C++ header files for the recipe
      def headers(*hdrs)
        @recipe.headers << hdrs.flatten.compact
      end

      # do not allow any unknown properties/methods
      def method_missing(method, *args, &block)
        raise "Unknown property #{method} for #{@recipe.to_s}"
      end
    end

    CONFIGURATOR = Configurator

    # Recipe singleton class methods
    class << self

      # recipe types (derivatives) registry
      def recipe_types
        @recipe_types ||= {}
      end
      private :recipe_types

      # register a recipe class with it's declaration keyword
      def register_recipe(keyword, klass)
        raise "Attempt to register recipe with duplicate keyword #{keyword}" if recipe_types.has_key?(keyword)
        recipe_types[keyword.to_s.to_sym] = klass
      end

      # create/load a recipe for the given keyword
      def create_recipe(rcp_file, keyword, *args, &block)
        keyword = keyword.to_s.to_sym unless Symbol === keyword
        if recipe_types.has_key?(keyword)
          return recipe_types[keyword].new(rcp_file, *args, &block)
        end
        nil
      end

    end

    def initialize(rcpfile, recipe_id)
      #defaults
      @recipe_file = rcpfile
      @recipe_id = recipe_id.to_s
      @idl_files = {}
      @shared_name = @recipe_id.dup
      @export_name = @recipe_id.dup.downcase
      @type = :base
      @idl_includes = Util::UniqueStringList.new(:ws, recipe_file.path.dup)
      @gen_dir = 'generated_code'
      @sources = Util::UniqueStringList.new(:ws)
      @headers = Util::UniqueStringList.new(:ws)
      @lib_paths = Util::UniqueStringList.new(:ws)
      # generate unique prefix for mpc project names for this recipe
      @mpc_id = project.make_mpc_project_name_prefix(self)
    end

    attr_reader :recipe_file, :recipe_id, :mpc_id

    # (post) configuration hook for derived recipes
    def post_configure
      # noop
    end
    protected :post_configure

    # recipe setup hook
    def setup
      # noop
    end

    # recipe verification hook
    def verify
      # noop
    end

    # evaluate the recipe DSL
    def configure(&block)
      cfg = self.class::CONFIGURATOR.new(self)
      block.call(cfg)
      # allow configuration tuning for derived recipes
      post_configure
    end

    # return the project this recipe is part of
    def project
      @recipe_file.project
    end

    # check if the recipe is part of an implicit recipe file
    def is_implicit?
      recipe_file.is_implicit?
    end

    # add and/or return IDL include paths for this recipe
    def idl_includes(incs=nil)
      @idl_includes.assign(incs.collect {|ip| File.expand_path(ip, recipe_file.path)}) if incs
      @idl_includes
    end

    # def recipe_idl_includes
    #   @recipe_idl_includes ||= Util::UniqueStringList.new(:ws)
    # end

    # add and/or return IDL file paths for this recipe
    def idl(idlfiles=nil)
      if idlfiles
        @idl_files = idlfiles.inject({}) {|map, fidl| map[fidl] = nil; map }
      end
      @idl_files.keys
    end

    # return complete IDL files registry for recipe
    def idl_files
      @idl_files
    end

    # get the basenames of all IDL files without extension
    def idl_without_ext
     idl.collect {|idf| File.basename(idf, '.idl')}
    end

    # set/get generated code output folder
    def gen_dir(gendir=nil)
      @gen_dir = "#{gendir}#{gendir.empty? ? '.' : ''}" if gendir
      @gen_dir
    end

    # get expanded path for generated code output folder
    def full_gen_path
      File.expand_path(gen_dir, recipe_file.path)
    end

    # set/get shared library base name
    def shared_name(shared_name=nil)
      @shared_name=shared_name.to_s if shared_name
      @shared_name
    end

    # add/get library search paths
    def lib_paths(lib_path=nil)
      @lib_paths.assign(lib_path) if lib_path
      @lib_paths
    end

    # convert given path relative to recipe file location
    def get_relative_path(path)
      Util::path_rel_to_path(path, recipe_file.path).to_s
    end

    # convert given paths relative to recipe file location
    def get_relative_paths(paths)
      paths.collect do |p|
        get_relative_path(p)
      end
    end

    # add managed IDLFile
    def add_idl_file(idl_file, name=nil)
      idl_file.recipes << self unless idl_file.recipes.include?(self)
      @idl_files[name || idl_file.full_path] = idl_file
    end

    # set/get export base name
    def export_name(export_name=nil)
      @export_name=export_name.downcase if export_name
      @export_name
    end

    # add/get user defined source files
    def sources(sources=nil)
      @sources.assign(sources) if sources
      @sources
    end

    # add/get user defined header files
    def headers(headers=nil)
      @headers.assign(headers) if headers
      @headers
    end

    # get recipe type
    def type
      @type
    end

    # get MPC file name for recipe
    def mpc_name
      File.join(self.recipe_file.path, @mpc_id+'.mpc')
    end

    # get MPC::File for recipe
    def mpc_file
      @mpc_file ||= project.add_mpc_file(mpc_name)
    end

    #================================================================
    # Project setup collection phase

    # find and register all IDLFiles listed and referenced by the recipe
    # scans project managed IDLFiles recursively to determine all included
    # (referenced) IDL files
    def collect_idl_files
      BRIX11.log(4, "[%s] collect_idl_files", self)
      idl_scanner = IDLFileScanner.new(self)
      searchpaths = idl_includes + project.idl_includes
      @idl_files.each_key do |fnidl|
        idl_dir = searchpaths.detect {|sp| ::File.file?(::File.expand_path(fnidl, sp)) }
        # TODO - check exceptions
        raise "[#{recipe_file}] Error: cannot find IDL file #{fnidl}" unless idl_dir
        # register IDL file with project (if not yet done)
        idl_path = ::File.expand_path(fnidl, idl_dir)
        idl_file = project.add_idl_file(idl_path)
        unless idl_file.has_been_scanned?
          # scan IDL files, register includes and other properties
          # and recursively scan includes
          idl_scanner.scan_idl_file(idl_file)
        end
        # now recursively process any included IDL files found
        # (if not registered yet and part of the project)
        idl_file.includes.each do |ifidl|
          process_include(ifidl, idl_scanner)
        end
        # register IDLFile with recipe
        BRIX11.log(4, '[%s] registering %s', self, idl_file)
        add_idl_file(project.idl_files[idl_path], fnidl)
      end
    end

    # check included (referenced) IDL file
    # scan recursively unless the IDLFile has already been scanned or
    # the file is not part of the project space
    def process_include(inc_fidl, idl_scanner)
      # skip analyzing IDL file if already analyzed or not part of project
      return unless inc_fidl.is_member?

      # scan IDL files, register includes and other properties
      # and recursively scan includes
      idl_scanner.scan_idl_file(inc_fidl) unless inc_fidl.has_been_scanned?

      # now recursively process any included IDL files found if not registered yet
      inc_fidl.includes.each do |ifidl|
        process_include(ifidl, idl_scanner)
      end
    end
    protected :process_include

    # IDL Scanner hook
    def check_idl_node(_idl_scanner, _node, _delegator)
      # noop
    end

    #================================================================
    # Project setup verification phase

    # for every listed IDL file check the collected include dependencies
    # and verify if the necessary recipes exist for those that are part of
    # this project
    def check_idl_dependencies
      BRIX11.log(4, "[%s] check_idl_dependencies", self)
      @idl_files.each_value do |fidl|
        # is this IDLFile managed by a recipe yet?
        if fidl.recipes.empty?
          # find/create the recipe to manage this IDLFile
          check_idl_recipe(fidl)
        end
        check_idl_file_dependencies(fidl)
      end
    end

    # check IDLFile dependencies
    def check_idl_file_dependencies(idl_file)
      idl_file.includes.each do |fidldep|
        if fidldep.is_member?
          if fidldep.recipes.empty?
            check_idl_recipe(fidldep)

            # recursively check IDLFile dependencies
            check_idl_file_dependencies(fidldep)
          end
        end
      end
    end
    protected :check_idl_file_dependencies

    # find/create the (implicit) recipe to manage this IDLFile
    def check_idl_recipe(idl_file)
      # determine containing directory
      idl_dir = idl_file.path
      # check for other idl files in directory and whether these are handled by other recipes
      idl_list = project.get_idl_files(idl_dir) - [idl_file]
      # check if any other IDL file is contained by a(n) (implicit) DataIdl recipe
      _data_fidl = idl_list.detect { |_fidl| (!_fidl.recipes.empty?) && DataIdlRecipe === _fidl.recipes.first }
      if _data_fidl
        # is it an implicit recipe?
        if _data_fidl.recipes.first.is_implicit?
          # add this IDL dependency to the implicit recipe found
          _data_fidl.recipes.first.add_idl_file(idl_file, idl_file.name)
        else
          # at least one other IDL file is managed by a user defined DataIdl recipe
          # => Error
          # get the DataIdl recipe file containing any of the other IDL files
          _rcp_file = _data_fidl.recipes.first.recipe_file
          # TODO - check exceptions
          raise "[#{recipe_file.full_path}] Error: IDL include #{idl_file.full_path} not managed by Data recipe in #{_rcp_file}"
        end
      else
        # IDL file is only one or all others are also without recipes so we create internal implicit DataRecipe
        imp_rcpfile = project.add_recipe_file(File.join(idl_dir, 'implicit.'+AxciomaPC::RECIPE_FILE_EXT), true)
        imp_rcp = DataIdlRecipe.new(imp_rcpfile, File.basename(idl_dir).sub('.', '_'))
        imp_rcpfile.add_recipe(imp_rcp)
        imp_rcp.add_idl_file(idl_file, idl_file.name)
      end
    end

    #================================================================
    # Project preparation setup phase

    # called to setup the MPC projects for this recipe
    def setup_projects
      #noop
    end

    # called from #setup_projects of a component or connector recipe
    # referencing (including) the specified IDL file from this recipe
    # to handle interaction specific setup of the MPC projects for this
    # recipe and register project dependencies for the specified IDL file
    def setup_project_interaction(_fidl, *_interaction_types)
      #noop
    end

    #================================================================
    # Project preparation dependency processing phase

    # called to handle the combined dependencies defined for the included IDL files
    # of all IDL files of this recipe
    def process_project_dependencies
      BRIX11.log_warning("missing #process_project_dependencies implementation for #{self.to_s}")
    end

    # called to collect the default and interaction specific dependencies for
    # the specified IDL file of this recipe and recursively for all it's
    # included IDL files
    def get_dependencies(_fidl, _interaction_types, _project_dependencies)
      # noop
    end

    def to_s
      "APC::Recipe{#{recipe_id}}"
    end

    def dump(indent=0, out=STDERR, data=nil)
      out.puts (' '*indent)+self.to_s
      out.puts((' '*(indent+2))+data.to_s) if data
      @idl_files.each { |n,f| out.puts (' '*(indent+2))+"#{n} =>"; f.dump(indent+4, out) }
      out.puts (' ')
    end

  end # Recipe

end # AxciomaPC

# load all recipe specializations
Dir.glob(File.join(File.dirname(__FILE__), 'recipes', '*.rb')).each do |fnm|
  require fnm
end

# load all interaction patterns
Dir.glob(File.join(File.dirname(__FILE__), 'interactions', '*.rb')).each do |fnm|
  require fnm
end

# load all port implementations
Dir.glob(File.join(File.dirname(__FILE__), 'ports', '*.rb')).each do |fnm|
  require fnm
end
