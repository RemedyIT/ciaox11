#--------------------------------------------------------------------
# @file    port_definition.rb
# @author  Marijke Hengstmengel
#
# @brief   Holds component port definition from component recipe
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------

module AxciomaPC
  class ComponentRecipe < Recipe

    class PortDefinition

      class Configurator
        def initialize(port)
          @port = port
        end

        def timed_trigger
          @port.timed_trigger
        end

        def method_missing(method, *args, &block)
          raise "Unknown property #{method} for port #{@port}"
        end
      end

      CONFIGURATOR = Configurator

      module TimedTriggerPort
        def verify
          set_type 'uses'
          set_intf_name 'CCM_TT::TT_Scheduler'
        end
      end

      class << self
        def possible_ports
          @possible_ports ||= %w(timed_trigger)
        end
      end

      # pragma is used in asynch_request_reply, but has to be declared here for the idl_writer
      attr_reader :type, :intf_name, :name, :idl_interface, :pragma

      def initialize(name, comp)
        @name = name
        @comp = comp
        @possible_ports = %w(timed_trigger)
        @config = {}
      end

      def recipe
        @comp.recipe
      end

      def set_type(type)
        @type = type
      end

      def set_intf_name(name)
        @intf_name = name
      end

      def possible_ports
        self.class.possible_ports
      end

      def verify
        ## noop
      end

      def setup_projects
        ## noop
      end

      def timed_trigger
        self.extend TimedTriggerPort
        @config[:kind] = :timed_trigger
      end

      def generate_port(type, intf_name = nil)
        # check if intf_name isn't nil, checking here and not already in the Configurator, makes it possible
        # to give a meaningful error message
        if intf_name.nil?
          BRIX11.log_error("[#{self}] Interface of port is nil!")
        else
          set_type type
          set_intf_name intf_name
          found_idl = find_idl_type(intf_name) do |n|
                IDL::Type::Interface === n.idltype.resolved_type
              end
          if found_idl
            @idl_interface = File.basename(found_idl)
          else
            BRIX11.log_error("[#{self}] No valid Interface type #{intf_name} found!")
          end
        end
      end
      protected :generate_port

      def find_idl_type(type_name, &type_check)
        recipe.idl.each do |idf|
          # look at the idl files mentioned in the component recipe
          # these idl files must be in the same dir as the recipe or otherwise in the
          # project idl_includes dirs.
          if File.exist?(File.join(recipe.recipe_file.path, idf))
            idf_full_path = File.join(recipe.recipe_file.path, idf)
          else
            recipe.project.idl_includes.each do |ii|
              if File.exist?(File.join(ii, idf))
                idf_full_path = File.join(ii, idf)
                break
              end
            end
          end
          # Scan the idl file found for the (module::)-type_name
          if idf_full_path
            idl_file = recipe.project.add_idl_file(idf_full_path)
            idl_scanner = IDLFileScannerType.new(recipe)
            if idl_scanner.idl_has_type?(idl_file, type_name, &type_check)
              return idf_full_path
            end
          else
            BRIX11.log_warning("[#{self}] IDL file #{idf} not found.")
          end
        end
        nil
      end
      protected :find_idl_type

      def configure(&block)
        cfg = self.class::CONFIGURATOR.new(self)
        block.call(cfg)
      end

      def to_s
        "#{@comp}\##{name}"
      end

    end
  end
end
