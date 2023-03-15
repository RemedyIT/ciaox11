#--------------------------------------------------------------------
# @file    attribute_definition.rb
# @author  Marijke Hengstmengel
#
# @brief   Holds component attribute definition from component recipe
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------

module AxciomaPC
  class ComponentRecipe < Recipe
    class AttributeDefinition
      BASIC_TYPES = %w{
        string
        wstring
        float
        double
        long\ double
        short
        unsigned\ short
        long
        unsigned\ long
        long\ long
        unsigned\ long\ long
        octet
        char
        wchar
        boolean
      }

      class Configurator
        def initialize(attrib)
          @attrib = attrib
        end

        def type(type = nil)
          @attrib.set_type(type)
        end

        def readonly(readonly)
          @attrib.readonly(readonly)
        end

        def method_missing(method, *args, &block)
          raise "Unknown property #{method} for attribute #{@attrib.name}"
        end
      end

      CONFIGURATOR = Configurator

      attr_reader :idl_attribute, :name, :type

      def initialize(name, comp)
        @name = name
        @readonly = false
        @comp = comp
      end

      def recipe
        @comp.recipe
      end

      def set_type(type)
        # check if type isn't nil, checking here and not already in the Configurator, makes it possible
        # to give a meaningful error message
        if type.nil?
          raise "[#{self}] Type of attribute '#{name}' is nil!"
        end

        @type = type.strip
      end

      def readonly(readonly = nil)
        @readonly = readonly unless readonly.nil?
        @readonly
      end

      def configure(&block)
        cfg = self.class::CONFIGURATOR.new(self)
        block.call(cfg)
      end

      def verify
        BRIX11.log(4, "[%s] verify", self)
        @idl_attribute = find_idl_attr
      end

      def find_idl_attr
        return nil if BASIC_TYPES.include?(@type)

        # look at the idl files mentioned in the component recipe
        # these idl files must be in the same dir as the recipe or otherwise in the
        # project idl_includes dirs.
        recipe.idl.each do |idf|
          if File.exist?(File.join(recipe.recipe_file.full_path, idf))
            idf_full_path = File.join(recipe.recipe_file.full_path, idf)
          else
            recipe.project.idl_includes.each do |ii|
              if File.exist?(File.join(ii, idf))
                idf_full_path = File.join(ii, idf)
              end
            end
          end
          # Scan the idl file found for the attribute type
          if idf_full_path
            idl_file = recipe.project.add_idl_file(idf_full_path)
            idl_scanner = IDLFileScannerAttr.new(recipe)
            if idl_scanner.idl_has_attrib_def?(idl_file, @type)
              return idf
            end
          else
            BRIX11.log_warning("[#{self}] IDL file #{idf} not found!")
          end
        end
        nil
      end
      protected :find_idl_attr

      def to_s
        "#{@comp}\##{name}"
      end
    end
  end
end
