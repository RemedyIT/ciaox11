#--------------------------------------------------------------------
# @file    dataidl.rb
# @author  Marijke Hengstmengel
#
# @brief   data recipes
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------#
require 'pathname'
require 'set'

module AxciomaPC

  class DataIdlRecipe < Recipe

    class DataConfigurator < Recipe::Configurator
      def initialize(recipe)
        super
      end

      #not used yet
    end

    CONFIGURATOR = DataConfigurator

    class << self

      def interaction_handlers
        @interaction_handlers ||= {}
      end
      private :interaction_handlers

      def interaction_patterns
        interaction_handlers.keys
      end

      def register_interaction_handler(pattern, handler)
        interaction_handlers[pattern.to_s.to_sym] ||= []
        interaction_handlers[pattern.to_s.to_sym] << handler
      end

      def handle_interaction_setup(recipe, interaction_type, fidl)
        interaction_handlers[interaction_type].each {|ih| ih.setup_data(recipe, fidl) } if interaction_handlers.has_key?(interaction_type)
      end

      def handle_interaction_dependencies(recipe, interaction_type, project_dependencies)
        interaction_handlers[interaction_type].each {|ih| ih.process_data_dependencies(recipe, project_dependencies) } if interaction_handlers.has_key?(interaction_type)
      end

      def get_interaction_dependencies(recipe, interaction_type, idl_prj_dependencies, project_dependencies)
        interaction_handlers[interaction_type].each {|ih| ih.get_data_dependencies(recipe, idl_prj_dependencies, project_dependencies) } if interaction_handlers.has_key?(interaction_type)
      end
    end


    def initialize(rcpfile, name, &block)
      super(rcpfile, name)
      @type = :data
      configure(&block) if block_given?
    end


    def to_s
      "APC::DataIdlRecipe{#{@recipe_id}}"
    end

    def dump(indent=0, out=STDERR)
      super(indent, out, "shared_name: [#{@shared_name}] export_name: [#{@export_name}]")
    end

    def create_stub_proj
      unless mpc_file[:idl_gen]
        mpc_idl_obj = MPC::IDLProject.new(:idl_gen, self)
        mpc_file.add_mpc_project(mpc_idl_obj)
        #set idl_includes set in recipe and set in  project file
        mpc_idl_obj.includes << idl_includes << project.idl_includes

        mpc_stub_obj = MPC::StubProject.new(self)
        mpc_file.add_mpc_project(mpc_stub_obj)
      end
    end

    def add_stub_proj(fidl)
      # return if the specified IDL file is already part of MPC project
      return if mpc_file[:idl_gen] && mpc_file[:idl_gen].has_project_file?(fidl.full_path)

      # make sure there is a stub project for this recipe
      create_stub_proj

      # get the :idl_gen project (if any)
      mpc_idl_obj = mpc_file[:idl_gen]

      # add the IDL file to the stub projects and set it's dependencies
      prj_dependencies = fidl.project_dependencies

      # idl project exist, but idl file is not already part of this project, so add idl file to idl_files for idl-project
      mpc_idl_obj.add_project_file(fidl.full_path)
      mpc_idl_obj.base_projects << 'taox11_anytypecode' if fidl.needs_anytype?

      # register resulting project dependencies for IDL file
      prj_dependencies << MPC::CompileDependency.new(:idl_gen, self)

      wants_stub = (fidl.creates_stubcode? || fidl.needs_anytype?)

      if wants_stub
        # get the :stub project
        mpc_stub_obj = mpc_file[:stub]

        # stub project exist, but idl file is not already part of this project, so add idl file to
        # sources and headers for stub-project
        mpc_stub_obj.base_projects << 'taox11_anytypecode' if fidl.needs_anytype?
        mpc_stub_obj.add_project_file(fidl.full_path)

        # enabe code and export header generation
        mpc_idl_obj.set_stub_flags
      end

      # register resulting project dependencies for IDL file
      prj_dependencies << MPC::LinkDependency.new(:stub, self)
    end

    # add managed IDLFile
    def add_idl_file(idl_file, name=nil)
      idl_file.recipes << self unless idl_file.recipes.include?(self)
      @idl_files[name || idl_file.full_path] = idl_file
    end

    def handle_interaction_setup(interaction_type, fidl)
      self.class.handle_interaction_setup(self, interaction_type, fidl)
    end
    protected :handle_interaction_setup

    def handle_interaction_dependencies(interaction_type, project_dependencies)
      self.class.handle_interaction_dependencies(self, interaction_type, project_dependencies)
    end
    protected :handle_interaction_dependencies

    def get_interaction_dependencies(interaction_type, idl_prj_dependencies, project_dependencies)
      self.class.get_interaction_dependencies(self, interaction_type, idl_prj_dependencies, project_dependencies)
    end
    protected :get_interaction_dependencies

    # setup any required MPC projects for this recipe
    def setup_projects
      BRIX11.log(3, '[%s] setup projects', self)
      # always create stub projects for data IDL
      # if it has any IDL files
      # create_stub_proj unless idl_files.empty?
    end

    # handle interaction specific setup of the MPC projects for this
    # recipe and register project dependencies for the specified IDL file
    def setup_project_interaction(fidl, *interaction_types)
      BRIX11.log(3, '[%s] setup project interaction : %s interaction type(s) = %s', self, fidl, interaction_types)

      # always add IDL file to stub projects
      add_stub_proj(fidl)

      # let interaction helpers handle setup for all required interaction types
      interaction_types.each do |int_type|
        handle_interaction_setup(int_type, fidl)
      end

      # propagate recursively
      fidl.includes.each do |ifidl|
        BRIX11.log(4, '[%s] process project dependency : include %s', self, ifidl)
        # only if this IDL file is a member of this project
        if ifidl.is_member?
          rcp = ifidl.recipes.first
          # propagate lem property to included IDL
          ifidl.properties[:needs_lem] = true if fidl.properties[:needs_lem]
          # have recipe for included IDL process interaction types and register dependencies
          # for included IDL
          rcp.setup_project_interaction(ifidl, *interaction_types)
        end
      end
    end

    # handle the combined dependencies defined for the *included* IDL files
    # of all IDL files of this recipe
    # (not for our own IDL files because those dependencies we know and should
    #  have handled in #setup_projects & #setup_project_interaction)
    def process_project_dependencies
      BRIX11.log(3, '[%s] process project dependencies', self)

      return if idl_files.empty? # nothing to do?

      # collect all interaction types and the project dependencies
      interaction_types = Set.new
      project_dependencies = MPC::Dependencies.new
      @idl_files.each_value do |fidl|
        # iterate all included IDL files (if any)
        fidl.includes.each do |ifidl|
          BRIX11.log(4, '[%s] process project dependencies : %s includes %s', self, fidl, ifidl)
          # only if this is a project member
          if ifidl.is_member?
            BRIX11.log(4, '[%s] process project dependencies : %s specifies %s', self, ifidl, ifidl.interaction_types.to_a)
            # get dependencies for included idl files unless it's part
            # of this recipe itself
            unless ifidl.recipes.first == self
              interaction_types.merge(ifidl.interaction_types)
              rcp = ifidl.recipes.first
              rcp.get_dependencies(ifidl, ifidl.interaction_types, project_dependencies)
            end
          end
        end
      end

      # in case for some reason the IDL generation has not been created yet,
      # create it now
      unless mpc_file[:idl_gen]
        @idl_files.each_value { |fidl| add_stub_proj(fidl) }
      end

      # process collected dependencies for included IDL
      mpc_file[:idl_gen].add_dependencies(project_dependencies, :idl_gen)
      if mpc_stub_proj = mpc_file[:stub]
        mpc_stub_proj.add_dependencies(project_dependencies, :stub)
      end

      # now handle interaction specific dependencies
      interaction_types.each do |int_type|
        handle_interaction_dependencies(int_type, project_dependencies)
      end
    end

    # collect the default and interaction specific dependencies for
    # the specified IDL file of this recipe and recursively for all it's
    # included IDL files
    def get_dependencies(fidl, interaction_types, project_dependencies)
      BRIX11.log(3, '[%s] get dependencies : %s; interaction type(s) = %s', self, fidl, interaction_types.to_a)

      idl_prj_dependencies = fidl.project_dependencies

      # by default the stub dependencies apply
      project_dependencies.merge(idl_prj_dependencies, :idl_gen, :stub)

      # check all required interaction types
      if !interaction_types.nil?
        interaction_types.each do |int_type|
          get_interaction_dependencies(int_type, idl_prj_dependencies, project_dependencies)
        end
      end

      # recursively collect dependencies for included IDL
      fidl.includes.each do |ifidl|
        BRIX11.log(4, '[%s] process project dependency : include %s', self, ifidl)
        # only if this is a project member
        if ifidl.is_member?
          rcp = ifidl.recipes.first
          # get project dependencies for included IDL
          rcp.get_dependencies(ifidl, interaction_types, project_dependencies)
        end
      end
    end

  end

  Recipe.register_recipe(:base, DataIdlRecipe)

end
