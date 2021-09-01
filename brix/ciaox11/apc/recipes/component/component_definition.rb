#--------------------------------------------------------------------
# @file    component_definition.rb
# @author  Marijke Hengstmengel
#
# @brief   Holds component definition from component recipe
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------

module AxciomaPC

  class ComponentRecipe < Recipe

    class ComponentDefinition

      class Configurator
        def initialize(comp)
          @comp = comp
        end

        def port(port = nil, type = nil, &_block)
          if block_given?
            raise "Do not use port definition argument (#{type}) when using block form." unless type.nil?
            #example:  intf.port 'run_my_bar_foo_prov' do |p|
            #          p.provides 'Foo::MyFoo'
            #          end
            @comp.port(port, &_block)
          else
            #example:  intf.port 'run_my_bar_foo_prov' , provides: 'Foo::MyFoo'
            @comp.port(port, type)
          end
        end

        def attribute(attrib, type = nil, &_block)
          if block_given?
            raise "Do not use attribute type argument (#{type}) when using block form." unless type.nil?
            @comp.attribute(attrib, &_block)
          else
            @comp.attribute(attrib, type)
          end
        end

        def method_missing(method, *args, &block)
          raise "Unknown property #{method} for #{@recipe.to_s}"
        end
      end

      CONFIGURATOR = Configurator

      def initialize(recipe, &block)
        @recipe = recipe
        @attributes = []
        @ports = []
        configure(&block) if block_given?
      end

      attr_reader :recipe, :ports, :attributes

      def configure(&block)
        cfg = self.class::CONFIGURATOR.new(self)
        block.call(cfg)
      end

      def verify
        BRIX11.log(4, "[%s] verify", self)
        # verify all ports
        @ports.each do |p|
          p.verify
          # check port
          if p.type.nil?
            raise "[#{p}] Type of port is not defined!"
          end
          if p.intf_name.nil?
            raise "[#{p}] Port interface is not defined!"
          end
        end
        # verify all attributes
        @attributes.each { |a| a.verify }
        # generate component IDL
        comp_fidl_ = create_component_idl
        # register as recipe owned IDL
        comp_fidl_.recipes << @recipe
        # replace component IDL for recipe
        @recipe.idl_files.clear
        @recipe.idl_files.merge!(comp_fidl_.name => comp_fidl_)
        # rescan recipe IDL
        @recipe.collect_idl_files
      end

      def setup_projects
        BRIX11.log(4, "[%s] setup_projects", self)
        @ports.each { |p| p.setup_projects }
      end

      def create_component_idl
        # create output path
        file_name_ = File.join(@recipe.recipe_file.path, "#{@recipe.recipe_id}.idl")
        # keep administration of generated idl files
        idl_file = @recipe.project.add_idl_file(file_name_, :generated)
        if @recipe.project.autogenerate == :allways || (@recipe.project.autogenerate == :ifneeded && !File.exist?(file_name_))
          BRIX11.log(5, 'generating component IDL [%s]', file_name_)

          options_ = {
            name: @recipe.recipe_id,
            modules: @recipe.comp_name.split('::'),
            attributes: @attributes,
            ports: @ports,
            idl: Util::UniqueStringList.new
          }
          options_[:comp_name] = options_[:modules].pop

          @ports.each do |p|
            if p.type == 'uses' && p.intf_name == 'CCM_TT::TT_Scheduler'
               # no user defined idl_interface, use always <ccm_timed_trigger.idl>
               options_[:ttc] = true
            else
              options_[:idl] << p.idl_interface
            end
          end

          @attributes.each do |a|
            options_[:idl] << a.idl_attribute
          end

          # execute file creation task for IDL file
          BRIX11::GenFile.transaction do
            w = ComponentIDLWriter.new(BRIX11::GenFile.new(file_name_), options_)
            w.visit_comp_idl
          end
        else
          # mark as scanned so no scanning will be attempted
          idl_file.set_scanned
        end
        idl_file
      end
      private :create_component_idl

      def port(port_name, kind = nil, &_block)
        if !port_name
          raise "Port name is missing in component recipe."
        end
        port = PortDefinition.new(port_name, self)
        if block_given?
          port.configure(&_block)
        else  # type of port isn't given as block but but as condensed definition
            if Hash === kind
              if kind.size > 1
                raise "Only a single port definition tuple allowed. Specifying #{kind} is invalid."
              else
                kind.each do |(method_, arg_)|
                  if port.possible_ports.include?(method_.to_s) && port.respond_to?(method_)
                    if ::Array === arg_
                      port.send(method_, *arg_)
                    else
                      port.send(method_, arg_)
                    end
                  else
                    raise "Invalid port definition :#{method_}. Valid port kinds are #{port.possible_ports}."
                  end
                end
              end
            else
              method_ = kind
              if port.possible_ports.include?(method_.to_s) && port.respond_to?(method_)
                port.send(method_)
              else
                raise "Invalid port definition :#{method_}. Valid port kinds are #{port.possible_ports}."
              end
            end
        end
        @ports << port
      end

      def port_exist?(port)
        found = false
        @ports.each do |p|
          if p.type == port.type &&
             p.name == port.name &&
             p.intf_name == port.intf_name
             found = true
             break if found
          end
        end
        found
      end

      def add_port(port)
        @ports << port
      end

      def attribute(attrib, attrib_def=nil, &block)
        attribute = AttributeDefinition.new(attrib, self)
        if block_given?
          attribute.configure(&block)
          # Does block contain a type definition?
          if attribute.type.nil?
            raise "Type of attribute '#{attrib}' is missing."
          end
        else # type and readonly flag of attribute aren't given as block but as condensed definition in  attrib_def
          unless attrib_def && attrib_def[:type]
            raise "Type of attribute '#{attrib}' is missing."
          else
            type_name = attrib_def[:type]
            attribute.set_type(type_name)
            attribute.readonly( attrib_def[:readonly])
          end
        end
        @attributes << attribute
      end

      def to_s
        "#{@recipe}:#{@recipe.comp_name}"
      end

    end # ComponentDefinition
  end
end
