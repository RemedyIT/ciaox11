#--------------------------------------------------------------------
# @file    port_type.rb
# @author  Marijke Hengstmengel
#
# @brief   Base port handler class
#
# @copyright Copyright (c) Remedy IT Expertise BV
# Chamber of commerce Rotterdam nr.276339, The Netherlands
#--------------------------------------------------------------------
module AxciomaPC

  class PortType

    class Configurator
      def initialize(port_type)
        @port_type = port_type
      end

      def method_missing(method, *args, &block)
        raise "Unknown property #{method} for #{@port_type.to_s}"
      end
    end

    CONFIGURATOR = Configurator

    def initialize(recipe)
      @recipe = recipe
    end

    def setup
      # noop
    end

    attr_reader :recipe

    def configure(&block)
      cfg = self.class::CONFIGURATOR.new(self)
      block.call(cfg)
    end

    def mpc_file
      recipe.mpc_file
    end

    def project
      recipe.project
    end

    def get_relative_paths(inc_paths)
      recipe.get_relative_paths(inc_paths)
    end

    def idl_includes
      recipe.idl_includes
    end

    def handle_recipe(rcp_deps, dep_idlgen_incdir)
      # noop
    end

    def to_s
      "#{recipe}@Port<#{recipe.get_port_type}>"
    end

  end # PortType

end # AxciomaPC

# load all interaction pattern port type implementations
Dir.glob(File.join(File.dirname(__FILE__), 'port_types', '*.rb')).each do |fnm|
  require fnm
end
