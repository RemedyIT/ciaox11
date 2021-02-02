#--------------------------------------------------------------------
# @file    gencompidl.rb
# @author  Marijke Hengstmengel
#
# @brief   Generate component for CIAOX11 project
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------
require 'brix11/command'

module BRIX11
  module CIAOX11

    class GenerateCompIDL < Command::Base

      DESC = 'Generate component idl for CIAOX11 project.'.freeze

      OPTIONS = {
          name: 'test_comp',
          modules: [],
          component: 'Test_comp'
      }

      def self.setup(optparser, options)
        options[:gencompidl] = OPTIONS.dup
        optparser.banner = "#{DESC}\n\n" +
                           "Usage: #{options[:script_name]} gen[erate] compidl [options] [NAME]\n\n" +
                           "       NAME := name to use for IDL file; default 'test_comp'\n\n"

        optparser.on('-c', '--component', '=NAME',
                     'Defines name to use for component.',
                     'Use scoped name (i.e. <name>::[<name>::]::<name>) to generate enclosing module(s).',
                     'Default: derived from IDL file basename with first character uppercased') {|v|
                       options[:gencompidl][:modules] = v.split('::');
                       options[:gencompidl][:component] = options[:gencompidl][:modules].pop
                     }

        optparser.on('-I[FILE]', '--with-idl=[FILE]',
                     'Create includes for FILE , an idl file containing interfaces and defines.',
                     'Specify filename without extension. Separate with \',\' when more than one.',
                     'Default: Generate includes for IDL files in working dir') {|v|
                     options[:gencompidl][:idl] = (v ? v.split(',') : true)}

        optparser.on('-r', '=INTERFACENAME PORTNAME',
                     'Defines interface and name to use for a receptacle. ',
                     'Use scoped interface name (i.e. <name>::[<name>::]::<name>) to generate enclosing module(s).')
        optparser.on('-f', '=INTERFACENAME PORTNAME',
                     'Defines interface and name to use for a facet. ',
                     'Use scoped interface name (i.e. <name>::[<name>::]::<name>) to generate enclosing module(s).')
        optparser.on('-a', '=INTERFACENAME PORTNAME',
                     'Defines interface and name to use for an ami4ccm facet and creates an ami4ccm receptacle pragma for it. ',
                     'Use scoped interface name (i.e. <name>::[<name>::]::<name>) to generate enclosing module(s).')

      end

      def run(argv)
        argv ||= []
        unless argv.empty? || Command.is_command_arg?(argv.first, options) || argv.first.start_with?('-')
          options[:gencompidl][:name] = argv.shift
        end
        unless options[:gencompidl][:component]
          options[:gencompidl][:component] = options[:gencompidl][:name].sub(/\A(.)/) { $1.upcase }
        end

        # define file creation task for IDL file
        file_create "#{options[:gencompidl][:name]}.idl" do |t|
          w = CompIDLWriter.new(GenFile.new(t.name), options[:gencompidl])
          w.visit_comp_idl
        end
        # run all required tasks for IDL file
         run_tasks "#{options[:gencompidl][:name]}.idl"
      end

      class CompIDLWriter < Generate::Writer
        def initialize(output, options)
          @options = options
          super(output)
        end

        helper_method :project_name, :module_names,
                      :component_name, :idl_names

        def project_name
          @options[:name]
        end
        def module_names
          @options[:modules]
        end
        def component_name
          @options[:component]
        end
        def idl_names
          @options[:idl] || []
        end

      end

      Command.register('generate:compidl', DESC, CIAOX11::GenerateCompIDL)
    end # GenerateIDL

  end # Common
end # BRIX11
