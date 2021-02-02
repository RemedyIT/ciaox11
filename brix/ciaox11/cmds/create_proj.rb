#--------------------------------------------------------------------
# @file    create_proj.rb
# @author  Marijke Hengstmengel
#
# @brief  Create an axcioma project using idl and recipe files
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------
require 'brix/ciaox11/apc/apc'
require 'brix/ciaox11/apc/project'

module BRIX11
  module CIAOX11

    class CreateProject < Command::Base
      DESC = 'Make project files for AXCIOMA project.'.freeze

      OPTIONS = {
        mpc: false,
        nogen: false
      }

      def self.setup(optparser, options)
        options[:axpcreate] = OPTIONS.dup
        optparser.banner = "#{DESC}\n\n" +
                           "Usage: #{options[:script_name]} apc prepare [options] [-- [mwc_options]]\n\n"
        optparser.on('-e', '--enable', '=FEATURE',
                     'Enable feature(s). If specifying more than 1 separate by \',\'') {|v|
                        options[:axpcreate][:features] ||= {};
                        v.split(',').each { |f| options[:axpcreate][:features][f] = 1 }
                     }
        optparser.on('-d', '--disable', '=FEATURE',
                     'Disable feature(s). If specifying more than 1 separate by \',\'') {|v|
                        options[:axpcreate][:features] ||= {};
                        v.split(',').each { |f| options[:axpcreate][:features][f] = 0 }
                     }
        optparser.on('-m', '--mpc', 'Do not remove mpc files.') { options[:axpcreate][:mpc] = true }
        optparser.on('-n', '--nogen', 'Do not generate build files (implies \'-m\').') {
                        options[:axpcreate][:mpc] = true
                        options[:axpcreate][:nogen] = true
                     }
      end

      def run(argv)
        argv ||= []
        # Load recipe_files, make recipes,
        project = AxciomaPC::Project.load_project()

        if options[:verbose] > 5
          project.dump
        end

        if !project
          #give error
          return
        end

        #make the  mpcfiles
        project.prepare()

        if options[:verbose] > 5
          project.dump
        end

        unless options[:axpcreate][:nogen]
          # Run MPC to generate build files
          opts = options.dup
          opts[:config][:project_type] = project.project_type if project.project_type
          opts[:genbuild] = BRIX11::Common::GenerateBuild::OPTIONS.dup
          opts[:genbuild][:features] ||= {}
          opts[:genbuild][:features].merge!(opts[:axpcreate][:features] || {})

          #all arguments behind '--' , including '--', must be passed to gen build command unless it is another brix command
          cmdargv = []
          if !argv.empty? && argv.first == '--'
            while !argv.empty?
              break if Command.is_command_arg?(argv.first, options)
              cmdargv << argv.shift
            end
          end

          opts[:genbuild][:recurse] = true
          opts[:genbuild][:project] = project.root_path
          rc = BRIX11::Common::GenerateBuild.new(entry, opts).run(cmdargv)
        end

        if (!options[:axpcreate][:mpc])
          #throw away temporarily mpc files
          #remove mpc files
          AxciomaPC::MPC.remove(project)
        end

        rc
      end

      Command.register('apc|axp:prepare', DESC, CIAOX11::CreateProject)

    end #CreateProject

  end # CIAOX11

end # BRIX11
