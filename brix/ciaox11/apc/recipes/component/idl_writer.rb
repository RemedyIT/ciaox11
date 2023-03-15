#--------------------------------------------------------------------
# @file    idl_writer.rb
# @author  Marijke Hengstmengel
#
# @brief   Writer for component idl files from component definition
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------

module AxciomaPC
  class ComponentIDLWriter < BRIX11::Generate::Writer

    def initialize(output, options)
      @options = options
      super(output)
    end

    helper_method :idl_name, :module_names,
                  :component_name, :included_idl, :def_name, :ports, :attributes, :ttc_idl, :pragmas

    def module_names
      @options[:modules] || []
    end

    def component_name
      @options[:comp_name] || []
    end

    def included_idl
      @options[:idl] || []
    end

    def idl_name
      @options[:name]
    end

    def def_name
      self.idl_name.upcase + '_IDL'
    end

    def ports
      @options[:ports]
    end

    def attributes
      @options[:attributes]
    end

    def ttc_idl
      if @options[:ttc]
        '#include <ccm_timed_trigger.idl>'
      end
    end

    def pragmas
      pragmas = []
      pragmas = ports.collect { |p| p.pragma.to_s unless p.pragma.blank? }.reject{ |c| c.nil? || c.empty? }
      pragmas
    end

  end # ComponentIDLWriter
end
