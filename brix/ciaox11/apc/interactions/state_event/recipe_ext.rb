#--------------------------------------------------------------------
# @file    recipe_ext.rb
# @author  Martin Corino
#
# @brief  SEV interaction pattern recipe specializations
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------

require 'fileutils'

module AxciomaPC
  module SEV
    # Extension module for DataIdlRecipe
    module DataIDLExtension
      class << self
        # list of possible DDS IDL generation projects (vendor specific)
        def dds_idl_gen_prj
          @dds_idl_gen_prj ||= []
        end
      end

      def process_sev_data_dependencies(project_dependencies)
        dds_idl_gen_prj.each do |prjtype|
          if mpc_proj = mpc_file[prjtype]
            mpc_proj.add_dependencies(project_dependencies, prjtype)
          end
        end
      end

      def get_sev_data_dependencies(project_dependencies, idl_prj_dependencies)
        project_dependencies.merge(idl_prj_dependencies, :stub)
      end
    end # DataIDLExtension

    AxciomaPC::DataIdlRecipe.send(:include, DataIDLExtension)

    # State-Event interface recipe
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

        def topic_seq=(name)
          @recipe.topic_seq = name
        end

        def topic_seq_suffix=(name)
          @recipe.topic_seq = name
        end

        def topic_if=(name)
          @recipe.topic_if = name
        end

        def topic_if_suffix=(name)
          @recipe.topic_if_suffix = name
        end
      end

      CONFIGURATOR = InterfaceConfigurator

      class << self
        def vendor_idl_includes
          @vendor_idl_includes ||= []
        end
      end

      def self.create(rcp_file, id, topic, idl, idl_inc, gendir, topic_ns, topic_seq, topic_seq_suffix, topic_if, topic_if_suffix)
        self.new(rcp_file, id) do |ifr|
          ifr.topic = topic
          ifr.idl(idl)
          ifr.idl_includes(idl_inc)
          ifr.gen_dir(gendir)
          ifr.topic_namespace = topic_ns
          ifr.topic_seq = topic_seq
          ifr.topic_seq_suffix = topic_seq_suffix
          ifr.topic_if = topic_if
          ifr.topic_if_suffix = topic_if_suffix
        end
      end

      def initialize(rcpfile, name, &block)
        super(rcpfile, name)
        #defaults
        @type = :sev_interface
        @export_name = nil # defaults to interface_name
        @topic_idl = nil
        configure(&block)
      end

      def create_interface_idl
        BRIX11.log(4, '[%s] generating DDS4CCM Interface IDL [%s]', self, interface_idl_path)
        # check output path
        gendir_ = File.dirname(interface_idl_path)
        # if the folder does not exists yet and it is inside the project space create it here
        if !File.exist?(gendir_) && project.is_project_path?(gendir_)
          FileUtils.mkdir_p(gendir_)
        end
        BRIX11.log_warning("cannot access output path for DDS4CCM Interface IDL [#{gendir_}]") unless File.exist?(gendir_)
        # generate
        # basic RIDL arguments; use '--search-includepath' to have RIDL search for the input file in one
        # of the given include directories
        ridl_args = %w{--search-includepath -Sa -St -SS -Ssh -Scc -Sch -Scp -Gdds4ccm,lem}
        # add topic and output args
        ridl_args << "-Wb,dds_topic=#{self.topic}" << '-o' << gendir_
        ridl_args << "-Wb,dds_topic_namespace=#{self.topic_namespace}" unless self.topic_namespace.nil?
        ridl_args << "-Wb,dds_topic_seq_suffix=#{self.topic_seq_suffix}" unless self.topic_seq_suffix.nil?
        ridl_args << "-Wb,dds_topic_if_suffix=#{self.topic_if_suffix}" unless self.topic_if_suffix.nil?
        ridl_args << "-Wb,dds_topic_seq=#{self.topic_seq}" unless self.topic_seq.nil?
        ridl_args << "-Wb,dds_topic_if=#{self.topic_if}" unless self.topic_if.nil?
        # specify user defined include paths
        ridl_args.concat self.get_relative_paths(self.idl_includes + self.project.idl_includes).collect { |p| "-I#{p}" }
        # specify system include path
        ridl_args << "-I#{BRIX11::Exec.get_run_environment('TAOX11_ROOT')}"
        # add input file
        ridl_args << self.idl.first
        BRIX11.log(5, '[%s] generating SEV interface IDL with %s', self, ridl_args)
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
        # mark the idl file for state/event interaction pattern requirements
        idlfile.interaction_types << :sev
        # no need to scan this generated file
        idlfile.set_scanned
        # add this receipe as the owner recipe
        idlfile.recipes << self
        # make sure the topic IDL is scanned and registered
        self.collect_idl_files
        # register topic IDL as include of interface IDL
        idlfile.includes << idl_files.values.first
        # replace the topic IDL by the created interface IDL for collection/scanning
        idl_files.clear
        add_idl_file(idlfile)
        # register required State/Event specific include paths and macros to facilitate IDL scanner
        ciaox11_root = BRIX11::Exec.get_run_environment('CIAOX11_ROOT')
        (idlfile.properties[:includepaths] ||= []) << (File.join(ciaox11_root, 'connectors/dds4ccm/idl') + File::SEPARATOR)
        idlfile.properties[:includepaths].concat(InterfaceRecipe.vendor_idl_includes)
        (idlfile.properties[:macros] ||= {}).merge!({
          'CIAOX11_DDS4CCM_STATE' => true,
          'CIAOX11_DDS4CCM_EVENT' => true
        })
      end

      # only allow a single topic IDL file
      def idl(idlfiles=nil)
        if idlfiles
          BRIX11.log_fatal("SE interface recipe #{self.recipe_file.full_path} only allows a single topic IDL to be defined!") if idlfiles.size > 1
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
        @interface_name ||= "#{File.basename(self.idl.first, '.*')}SE"
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

      def topic_seq=(name)
        @topic_seq = name
      end

      def topic_seq
        @topic_seq
      end

      def topic_seq_suffix=(name)
        @topic_seq_suffix = name
      end

      def topic_seq_suffix
        @topic_seq_suffix
      end

      def topic_if=(name)
        @topic_if = name
      end

      def topic_if
        @topic_if
      end

      def topic_if_suffix=(name)
        @topic_if_suffix = name
      end

      def topic_if_suffix
        @topic_if_suffix
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
        "#{scope_}::#{@topic_if || "#{topic_name_}#{@topic_if_suffix || 'Interface'}"}"
      end

      def mpc_name
        File.join(self.recipe_file.path, interface_name + '.mpc')
      end

      def to_s
        "APC::SEV::InterfaceRecipe[#{recipe_id}]"
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
            if int_type == :sev
              BRIX11.log(4, '[%s] idl_prj_dependencies : %s', self, idl_prj_dependencies)
              project_dependencies.merge(idl_prj_dependencies, :lem_gen, :dds_lem_gen, :dds_lem_stub)
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
        # Is there already a dds_lem_gen project for this interface idl?
        prj_dependencies = fidl.project_dependencies
        if mpc_idl_obj = mpc_file[:dds_lem_gen]
          # return if the specified IDL file is already part of MPC project
          return if mpc_idl_obj.has_project_file?(fidl.full_path)

          mpc_stub_obj = mpc_file[:dds_lem_stub]
        else
          # create LEM IDL compiler project
          mpc_idl_obj = MPC::IDLProject.new(:dds_lem_gen, self)
          mpc_file.add_mpc_project(mpc_idl_obj)

          # get idl_includes set in recipe and set in project file
          mpc_idl_obj.includes << idl_includes << project.idl_includes
          # set dependency for se_idl_gen project
          mpc_idl_obj.project_dependencies <<  "#{mpc_id}_se_idl_gen"

          # create LEM stub project
          mpc_stub_obj = MPC::DdsLemStubProject.new( self)
          mpc_file.add_mpc_project(mpc_stub_obj)
        end

        # lem_gen project exist, but idl file is not yet part of this project,
        # so add idl file to idl_files for idl-project
        # and to sources and headers for lem_stub-project
        mpc_idl_obj.add_project_file(fidl.full_path)
        mpc_stub_obj.add_project_file(fidl.full_path)

        # register resulting project dependencies for IDL file
        prj_dependencies <<
            MPC::CompileDependency.new(:dds_lem_gen, self) <<
            MPC::LinkDependency.new(:dds_lem_stub, self)
      end
      private :add_lem_proj

      def setup_project_interaction(fidl, *interaction_types)
        # make lem for event_conn_interface.idl
        # and after this, we need the stub for included idl
        BRIX11.log(3, '[%s] setup_project_interaction : %s, interaction_types = %s', self, fidl, interaction_types)

        # no stubs will be created for IDL in this type of recipe
        # this type of recipe only considers the :sev interaction type

        # add LEM projects if :sev interaction applies
        if interaction_types.include?(:sev)
          add_lem_proj(fidl)
        end

        fidl.includes.each do |ifidl|
          BRIX11.log(4, '[%s] process_project_dependency : inc %s', self, ifidl)
          if ifidl.is_member?
            # get recipe for included IDL to process interaction type and register
            # dependencies for included IDL
            rcp = ifidl.recipes.first
            rcp.setup_project_interaction(ifidl, :sev)
          end
        end
      end

      def setup_projects
        BRIX11.log(3, '[%s] setup projects', self)
        if @topic_idl  # should always be there
          # always setup the project to generate the <base_idl>SE.idl file
          mpc_obj = MPC::IDLProject.new(:se_idl_gen, self)
          mpc_obj.add_project_file(@topic_idl.full_path)
          self.mpc_file.add_mpc_project(mpc_obj)
          # set topic switch
          mpc_obj.add_idl_flags("-Wb,dds_topic=#{self.topic}")
          mpc_obj.add_idl_flags("-Wb,dds_topic_namespace=#{self.topic_namespace}") unless self.topic_namespace.nil?
          mpc_obj.add_idl_flags("-Wb,dds_topic_seq_suffix=#{self.topic_seq_suffix}") unless self.topic_seq_suffix.nil?
          mpc_obj.add_idl_flags("-Wb,dds_topic_if_suffix=#{self.topic_if_suffix}") unless self.topic_if_suffix.nil?
          mpc_obj.add_idl_flags("-Wb,dds_topic_seq=#{self.topic_seq}") unless self.topic_seq.nil?
          mpc_obj.add_idl_flags("-Wb,dds_topic_if=#{self.topic_if}") unless self.topic_if.nil?

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
                rcp.get_dependencies(ifidl, [:sev], project_dependencies)
              end
            end
          end
        end
        if mpc_proj = mpc_file[:dds_lem_gen]
          mpc_proj.add_dependencies(project_dependencies, :idl_gen)
        end
        if mpc_proj = mpc_file[:dds_lem_stub]
          mpc_proj.add_dependencies(project_dependencies, :stub)
        end
      end

    end # InterfaceRecipe

    AxciomaPC::Recipe.register_recipe(:sev_interface, InterfaceRecipe)

    # Extension module for ComponentRecipe
    module ComponentExtension
      def setup_comp_gen_sev(project_dependencies)
        mpc_obj = mpc_file[:comp_gen]
        # add SEV base project
        mpc_obj.base_projects << 'ciaox11_dds4ccm'
        mpc_obj.add_dependencies(project_dependencies, :dds_lem_gen)
      end

      def setup_stub_comp_sev(project_dependencies)
        return if self.combined_lib?
        if mpc_obj = mpc_file[:comp_stub]
          # add SEV base project
          mpc_obj.base_projects << 'ciaox11_dds4ccm_lem_stub'
          mpc_obj.add_dependencies(project_dependencies, :dds_lem_stub)
          mpc_obj.add_dependencies(project_dependencies, :stub)
        end
      end

      def setup_lem_comp_sev(project_dependencies)
        return if self.combined_lib?
        mpc_obj = mpc_file[:comp_lem]
        # add SEV base project
        mpc_obj.base_projects << 'ciaox11_dds4ccm_lem_stub'
        mpc_obj.add_dependencies(project_dependencies, :dds_lem_stub)
        mpc_obj.add_dependencies(project_dependencies, :stub)
      end

      def setup_svnt_comp_sev(project_dependencies)
        return if self.combined_lib?
        mpc_obj = mpc_file[:comp_svnt]
        # add SEV base project
        mpc_obj.base_projects << 'ciaox11_dds4ccm_lem_stub'
        mpc_obj.add_dependencies(project_dependencies, :dds_lem_stub)
        mpc_obj.add_dependencies(project_dependencies, :stub)
      end

      def setup_exec_lib_sev(project_dependencies)
        mpc_obj = mpc_file[:exec]
        # add SEV base project
        mpc_obj.base_projects << 'ciaox11_dds4ccm_lem_stub'
        mpc_obj.add_dependencies(project_dependencies, :dds_lem_stub)
        mpc_obj.add_dependencies(project_dependencies, :stub)
      end
    end

    AxciomaPC::ComponentRecipe.send(:include, ComponentExtension)
  end # SEV
end
