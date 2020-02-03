#--------------------------------------------------------------------
# @file    connector.rb
# @author  Marijke Hengstmengel
#
# @brief   Connector recipes
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------

module AxciomaPC

  class ConnectorRecipe < Recipe

    class << self
      def port_types
        @port_types ||= {}
      end

      def register_port_type(keyword, klass)
        raise "Attempt to register port type with duplicate keyword #{keyword}" if port_types.has_key?(keyword)
        port_types[keyword.to_s.to_sym] = klass
      end

      def get_port_handler_klass(port_type)
        if !port_types.has_key?(port_type)
          raise "PortType :#{port_type} not implemented. Valid port types are #{port_types.keys}"
        end
        port_types[port_type]
      end

    end

    class ConnectorConfigurator < Recipe::Configurator
      def initialize(recipe)
        super
      end

      def port_type(porttype, &_block)
        if block_given?
          @recipe.port_type(porttype, &_block)
        else
          @recipe.port_type(porttype)
        end
      end
    end

    CONFIGURATOR = ConnectorConfigurator

    def initialize(rcpfile, name, *features, &block)
      super(rcpfile, name)
      #defaults
      @port_type = :corba4ccm
      @type = :connector
      # only configure if required features match
      configure(&block) if check_features(*features)
    end

    def setup
      port_handler.setup
    end

    # add IDLFile
    def add_idl_file(idl_file, name=nil)
      # IDLFiles listed by connector recipes are not managed
      # so we do not register the recipe with the IDLFile
      @idl_files[name || idl_file.full_path] = idl_file
    end

    def idl_files_gen_dir_rel_path(idlfiles, postfix='')
      idlfiles.collect do |n,f|
        #get recipe file belonging to idl_file
        name = f.name.gsub('.idl', "#{postfix}.idl")
        gen_dir = f.recipes.first.gen_dir
        Util::path_rel_to_path(File.join(f.path,gen_dir,name),self.recipe_file.path).to_s
      end
    end

    def port_type(port_type, &_block)
      @port_type = port_type
      if block_given?
        port_handler.configure(&_block)
      end
    end

    def get_port_type
      @port_type
    end

    def port_handler
      @port_handler ||= get_port_handler
    end

    def get_port_handler
      port_type = get_port_type
      port_type = port_type.to_s.to_sym unless Symbol === port_type
      ConnectorRecipe.get_port_handler_klass(port_type).new(self)
    end
    private :get_port_handler

    def mpc_name
      File.join(self.recipe_file.path, recipe_id + port_handler.mpc_name + '.mpc')
    end

    def to_s
      "APC::ConnectorRecipe{#{recipe_id}}"
    end

    def dump(indent=0, out=STDERR)
      super(indent, out, "shared_name: [#{@shared_name}] export_name: [#{@export_name}] port_type: [#{@port_type}]")
    end

    def setup_projects
      BRIX11.log(3, "[#{self}] setup projects")
      # create the handler for the specified PortType
      port_handler_ = self.port_handler
      port_handler_.setup_projects
    end

    def process_project_dependencies
      BRIX11.log(3, "[#{self}] process project dependencies")
      port_handler_ = self.port_handler
      port_handler_.process_project_dependencies
    end

  end

  Recipe.register_recipe(:connector, ConnectorRecipe)

end
