#--------------------------------------------------------------------
# @file    recipe_ext.rb
# @author  Martin Corino
#
# @brief  PubSub interaction pattern recipe specializations
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------

require 'fileutils'

module AxciomaPC

  module PS

    # Extension module for DataIdlRecipe
    module DataIDLExtension

      def process_ps_data_dependencies(project_dependencies)
        # noop
      end

      def get_ps_data_dependencies(project_dependencies, idl_prj_dependencies)
        project_dependencies.merge(idl_prj_dependencies, :stub)
      end

    end # DataIDLExtension

    AxciomaPC::DataIdlRecipe.send(:include, DataIDLExtension)

    # PubSub interface recipe
    class InterfaceRecipe < Recipe

      class InterfaceConfigurator < Recipe::Configurator
        def initialize(recipe)
          super
        end

        def topic=(name)
          @recipe.topic = name
        end

        def topic_namespace=(name)
          @recipe.topic_namespace = name
        end

        def topic_sequence=(name)
          @recipe.topic_sequence = name
        end

        def topic_sequence_suffix=(name)
          @recipe.topic_sequence_suffix = name
        end

        def topic_interface=(name)
          @recipe.topic_interface = name
        end

        def topic_interface_suffix=(name)
          @recipe.topic_interface_suffix = name
        end
      end

      CONFIGURATOR = InterfaceConfigurator

      def self.create(rcp_file, id, topic, idl, idl_inc, gendir, topic_ns, topic_seq, topic_seq_suffix, topic_if, topic_if_suffix)
        self.new(rcp_file, id) do |ifr|
          ifr.topic = topic
          ifr.idl(idl)
          ifr.idl_includes(idl_inc)
          ifr.gen_dir(gendir)
          ifr.topic_namespace = topic_ns
          ifr.topic_sequence = topic_seq
          ifr.topic_sequence_suffix = topic_seq_suffix
          ifr.topic_interface = topic_if
          ifr.topic_interface_suffix = topic_if_suffix
        end
      end

      def initialize(rcpfile, name, &block)
        super(rcpfile, name)
        #defaults
        @type = :ps_interface
        @export_name = nil # defaults to interface_name
        @topic_idl = nil
        configure(&block)
      end

      def create_interface_idl
        BRIX11.log(4, '[%s] generating PSDD4CCM Interface IDL [%s]', self, interface_idl_path)
        # check output path
        gendir_ = File.dirname(interface_idl_path)
        # if the folder does not exists yet and it is inside the project space create it here
        if !File.exist?(gendir_) && project.is_project_path?(gendir_)
          FileUtils.mkdir_p(gendir_)
        end
        BRIX11.log_warning("cannot access output path for PSDD4CCM Interface IDL [#{gendir_}]") unless File.exist?(gendir_)
        # generate
        # basic RIDL arguments
        ridl_args = %w{-Sa -St -SS -Ssh -Scc -Sch -Scp -Gpsdd4ccm,lem}
        # add topic and output args
        ridl_args << '-o' << gendir_ <<
                     "-Wb,psdd_topic=#{self.topic}"
        ridl_args << "-Wb,psdd_topic_namespace=#{self.topic_namespace}" unless self.topic_namespace.nil?
        ridl_args << "-Wb,psdd_topic_seq_suffix=#{self.topic_sequence_suffix}" unless self.topic_sequence_suffix.nil?
        ridl_args << "-Wb,psdd_topic_if_suffix=#{self.topic_interface_suffix}" unless self.topic_interface_suffix.nil?
        ridl_args << "-Wb,psdd_topic_seq=#{self.topic_sequence}" unless self.topic_sequence.nil?
        ridl_args << "-Wb,psdd_topic_if=#{self.topic_interface}" unless self.topic_interface.nil?
        # specify user defined include paths
        ridl_args.concat self.get_relative_paths(self.idl_includes + self.project.idl_includes).collect {|p| "-I#{p}"}
        # specify system include path
        ridl_args << "-I#{BRIX11::Exec.get_run_environment('TAOX11_ROOT')}"
        if self.idl.empty?
          ridl_args << '--no-input' <<            # no input parsing
                       topic.tr(' ', '_') + '.idl'   # 'fake' input filename as template for output
        else
          # use '--search-includepath' to have RIDL search for the input file in one
          # of the given include directories
          ridl_args << '--search-includepath'
          # add input file
          ridl_args << self.idl.first
        end
        BRIX11.log(5, '[%s] generating PS interface IDL with %s', self, ridl_args)
        # run RIDL in recipe directory
        BRIX11::Sys.in_dir(self.recipe_file.path) do
          BRIX11::ERIDL.run('ccmx11', ridl_args)
        end
      end
      private :create_interface_idl

      def post_configure
        BRIX11.log(4, '[%s] post_configure', self)
        # keep topic idl if any
        @topic_idl = idl_files.values.first
        if project.autogenerate == :allways || (project.autogenerate == :ifneeded && !File.exist?(interface_idl_path))
          # create and register interface IDLFile object with project
          create_interface_idl
        end
        # register as generated IDL in the project
        idlfile = project.add_idl_file(interface_idl_path, :generated)
        # mark the idl file for publish/subscribe interaction pattern requirements
        idlfile.interaction_types << :pubsub
        # no need to scan this generated file
        idlfile.set_scanned
        # add this receipe as the owner recipe
        idlfile.recipes << self
        # make sure the topic IDL is scanned and registered (if any)
        self.collect_idl_files
        # register topic IDL as include of interface IDL (if any)
        idlfile.includes << idl_files.values.first unless idl_files.empty?
        # replace the topic IDL by the created interface IDL for collection/scanning
        idl_files.clear
        add_idl_file(idlfile)
        # register required PubSub specific includepaths and macros to facilitate IDL scanner
        ciaox11_root = BRIX11::Exec.get_run_environment('CIAOX11_ROOT')
        (idlfile.properties[:includepaths] ||= []).concat([
          File.join(ciaox11_root, 'connectors/psdd4ccm/idl') + '/',
        ])
      end

      # only allow a single topic IDL file
      def idl(idlfiles=nil)
        if idlfiles
          BRIX11.log_fatal("PS interface recipe #{self.recipe_file.full_path} only allows a single topic IDL to be defined!") if idlfiles.size > 1
        end
        super
      end

      # add IDLFile
      def add_idl_file(idl_file, name=nil)
        # IDLFiles listed by interface recipes are not managed
        # so we do not register the recipe with the IDLFile
        @idl_files[name || idl_file.full_path] = idl_file
      end

      def interface_name
        unless @interface_name
          if self.idl.empty?
            @interface_name = topic.tr(' ', '_') + 'PS'
          else
            @interface_name = "#{File.basename(self.idl.first, '.*')}PS"
          end
        end
        @interface_name
      end

      # overrule
      def export_name(export_name_=nil)
        @export_name = export_name_.downcase if export_name_
        @export_name ||= interface_name.downcase
      end

      def interface_idl_path
        File.join(full_gen_path, interface_name + '.idl')
      end

      def topic=(name)
        @topic = name.to_s
      end

      def topic
        @topic || ''
      end

      def topic_namespace=(name)
        @topic_namespace = name
      end

      def topic_namespace
        @topic_namespace
      end

      def topic_sequence=(name)
        @topic_sequence = name
      end

      def topic_sequence
        @topic_sequence
      end

      def topic_sequence_suffix=(name)
        @topic_sequence_suffix = name
      end

      def topic_sequence_suffix
        @topic_sequence_suffix
      end

      def topic_interface=(name)
        @topic_interface = name
      end

      def topic_interface
        @topic_interface
      end

      def topic_interface_suffix=(name)
        @topic_interace_suffix = name
      end

      def topic_interface_suffix
        @topic_interace_suffix
      end

      def topic_interface_module
        # get topic scope
        if topic_namespace
          scope_ = topic_namespace
          topic_name_ = topic.split('::').pop
        else
          scope_ = topic.split('::')
          topic_name_ = scope_.pop  # pop and store topic typename itself
          scope_ = scope_.join('::')
        end
        "#{scope_}::#{@topic_interface || "#{topic_name_}#{@topic_interace_suffix || 'Interface'}"}"
      end

      def mpc_name
        File.join(self.recipe_file.path, interface_name + '.mpc')
      end

      def to_s
        "APC::PS::InterfaceRecipe[#{recipe_id}]"
      end

      def dump(indent=0, out=STDERR)
        super(indent, out, "shared_name: [#{@shared_name}] export_name: [#{@export_name}]")
      end

      def get_dependencies(fidl, interaction_types, project_dependencies)
        BRIX11.log(3, '[%s] get_dependencies : %s, interaction_type = %s', self, fidl, interaction_types.to_a)

        idl_prj_dependencies = fidl.project_dependencies

        # check all required interaction types
        if !interaction_types.nil?
          interaction_types.each do |int_type|
            if int_type == :pubsub
              BRIX11.log(4, '[%s] idl_prj_dependencies : %s', self, idl_prj_dependencies)
              project_dependencies.merge(idl_prj_dependencies, :lem_gen, :psdd_lem_gen, :psdd_lem_stub)
            end
          end
        end

        fidl.includes.each do |ifidl|
          if ifidl.is_member?
            rcp = ifidl.recipes.first
            # get project dependencies for included IDL
            rcp.get_dependencies(ifidl, interaction_types, project_dependencies)
          end
        end
      end


      def add_lem_proj(fidl)
        # Is there already a psdd_lem_gen project for this interface idl?
        prj_dependencies = fidl.project_dependencies
        if mpc_idl_obj = mpc_file[:psdd_lem_gen]
          # return if the specified IDL file is already part of MPC project
          return if mpc_idl_obj.has_project_file?(fidl.full_path)

          mpc_stub_obj = mpc_file[:psdd_lem_stub]
        else
          # create LEM IDL compiler project
          mpc_idl_obj = MPC::IDLProject.new(:psdd_lem_gen, self)
          mpc_file.add_mpc_project(mpc_idl_obj)

          # get idl_includes set in recipe and set in project file
          mpc_idl_obj.includes << idl_includes << project.idl_includes
          # set dependency for se_idl_gen project
          mpc_idl_obj.project_dependencies <<  "#{mpc_id}_ps_idl_gen"

          # create LEM stub project
          mpc_stub_obj = MPC::PSDDLemStubProject.new( self)
          mpc_file.add_mpc_project(mpc_stub_obj)
        end

        # lem_gen project exist, but idl file is not yet part of this project,
        # so add idl file to idl_files for idl-project
        # and to sources and headers for lem_stub-project
        mpc_idl_obj.add_project_file(fidl.full_path)
        mpc_stub_obj.add_project_file(fidl.full_path)

        # register resulting project dependencies for IDL file
        prj_dependencies <<
            MPC::CompileDependency.new(:psdd_lem_gen, self) <<
            MPC::LinkDependency.new(:psdd_lem_stub, self)
      end
      private :add_lem_proj

      def setup_project_interaction(fidl, *interaction_types)
        # make lem for event_conn_interface.idl
        # and after this, we need the stub for included idl
        BRIX11.log(3, '[%s] setup_project_interaction : %s, interaction_types = %s', self, fidl, interaction_types)

        # no stubs will be created for IDL in this type of recipe
        # this type of recipe only considers the :pubsub interaction type

        # add LEM projects if :pubsub interaction applies
        if interaction_types.include?(:pubsub)
          add_lem_proj(fidl)
        end

        fidl.includes.each do |ifidl|
          BRIX11.log(4, '[%s] process_project_dependency : inc %s', self, ifidl)
          if ifidl.is_member?
            # get recipe for included IDL to process interaction type and register
            # dependencies for included IDL
            rcp = ifidl.recipes.first
            rcp.setup_project_interaction(ifidl, :pubsub)
          end
        end
      end

      def setup_projects
        BRIX11.log(3, '[%s] setup projects', self)
        if @topic_idl
          # setup the project to generate the <base_idl>PS.idl file
          # except if topic is base type and there is no topic idl
          mpc_obj = MPC::IDLProject.new(:ps_idl_gen, self)
          self.mpc_file.add_mpc_project(mpc_obj)
          # set topic switch
          mpc_obj.add_idl_flags("-Wb,psdd_topic=#{self.topic}")
          mpc_obj.add_idl_flags("-Wb,psdd_topic_namespace=#{self.topic_namespace}") unless self.topic_namespace.nil?
          mpc_obj.add_idl_flags("-Wb,psdd_topic_seq_suffix=#{self.topic_sequence_suffix}") unless self.topic_sequence_suffix.nil?
          mpc_obj.add_idl_flags("-Wb,psdd_topic_if_suffix=#{self.topic_interface_suffix}") unless self.topic_interface_suffix.nil?
          mpc_obj.add_idl_flags("-Wb,psdd_topic_seq=#{self.topic_sequence}") unless self.topic_sequence.nil?
          mpc_obj.add_idl_flags("-Wb,psdd_topic_if=#{self.topic_interface}") unless self.topic_interface.nil?
          mpc_obj.add_project_file(@topic_idl.first.full_path)

          # get idl_includes set in recipe and in project file
          mpc_obj.includes << self.idl_includes << self.project.idl_includes
        end
      end

      def process_project_dependencies
        BRIX11.log(3, '[%s] process_project_dependencies', self)
        project_dependencies = MPC::Dependencies.new
        @idl_files.each do |_, fidl|
          fidl.includes.each do |ifidl|
            if ifidl.is_member?
              rcp = ifidl.recipes.first
              unless rcp == self
                rcp.get_dependencies(ifidl, [:pubsub], project_dependencies)
              end
            end
          end
        end
        if mpc_proj = mpc_file[:psdd_lem_gen]
          mpc_proj.add_dependencies(project_dependencies, :idl_gen)
        end
        if mpc_proj = mpc_file[:psdd_lem_stub]
          mpc_proj.add_dependencies(project_dependencies, :stub)
        end
      end

    end # InterfaceRecipe

    AxciomaPC::Recipe.register_recipe(:ps_interface, InterfaceRecipe)

    # Extension module for ComponentRecipe
    module ComponentExtension

      def setup_comp_gen_pubsub(project_dependencies)
        mpc_obj = mpc_file[:comp_gen]
        # add PS base project
        mpc_obj.base_projects << 'ciaox11_psdd4ccm_idl'
        mpc_obj.add_dependencies(project_dependencies, :psdd_lem_gen)
      end

      def setup_stub_comp_pubsub(project_dependencies)
        return if self.combined_lib?
        if mpc_obj = mpc_file[:comp_stub]
          # add PS base project
          mpc_obj.base_projects << 'ciaox11_psdd4ccm_stub'
          mpc_obj.add_dependencies(project_dependencies, :psdd_lem_stub)
          mpc_obj.add_dependencies(project_dependencies, :stub)
        end
      end

      def setup_lem_comp_pubsub(project_dependencies)
        return if self.combined_lib?
        mpc_obj = mpc_file[:comp_lem]
        # add PS base project
        mpc_obj.base_projects << 'ciaox11_psdd4ccm_stub'
        mpc_obj.add_dependencies(project_dependencies, :psdd_lem_stub)
        mpc_obj.add_dependencies(project_dependencies, :stub)
      end

      def setup_svnt_comp_pubsub(project_dependencies)
        return if self.combined_lib?
        mpc_obj = mpc_file[:comp_svnt]
        # add PS base project
        mpc_obj.base_projects << 'ciaox11_psdd4ccm_stub'
        mpc_obj.add_dependencies(project_dependencies, :psdd_lem_stub)
        mpc_obj.add_dependencies(project_dependencies, :stub)
      end

      def setup_exec_lib_pubsub(project_dependencies)
        mpc_obj = mpc_file[:exec]
        # add PS base project
        mpc_obj.base_projects << 'ciaox11_psdd4ccm_stub'
        mpc_obj.add_dependencies(project_dependencies, :psdd_lem_stub)
        mpc_obj.add_dependencies(project_dependencies, :stub)
      end

    end

    AxciomaPC::ComponentRecipe.send(:include, ComponentExtension)

  end # PS

end
