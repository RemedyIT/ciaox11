#--------------------------------------------------------------------
# @file    make_proj.rb
# @author  Martin Corino
#
# @brief  Project maker
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------
require 'brix11/command'
require 'brix/ciaox11/apc/apc'
require 'brix/ciaox11/apc/project'

module BRIX11
  module CIAOX11

    class MakeProject < Command::Base

      DESC = 'Make (build) the AXCIOMA project.'.freeze

      OPTIONS = {
        clean: false,
        build: true,
        debug: false,
      }


      def self.setup(optparser, options)
        options[:axpmake] = OPTIONS.dup
        optparser.banner = "#{DESC}\n\n" +
                           "Usage: #{options[:script_name]} apc make [options] [-- make-options]\n\n"

        optparser.on('-c', '--clean', 'Clean project only.') { options[:axpmake][:clean] = true; options[:axpmake][:build] = false }
        optparser.on('-r', '--rebuild', 'Clean and than build project.') { options[:axpmake][:clean] = true; options[:axpmake][:build] = true }
        optparser.on('--debug', 'Debug build.') { options[:axpmake][:debug] = true }
        optparser.on('--release', 'Release build.') { options[:axpmake][:debug] = false }
        optparser.on('-N', '--no-redirect',
                     'Do not redirect output from child process..',
                     'Default: redirect and filter output.') { |v|
          options[:axpmake][:noredirect] = true
        }
      end

      def run(argv)
        # return project if  exist
        project = AxciomaPC::Project.load_project(:ifneeded)

        if !project
          raise Command::CmdError, 'Unable to locate AXCIOMA project root'
        end


        prj = Project.handler(options[:config][:project_type])
        if prj.project_exists?(nil, project.root_path)
          options[:make] = options[:axpmake].dup
          options[:make][:project] = project.root_path
          return false unless Common::Make.new(entry, options).run(argv)
        else
          raise Command::CmdError, 'Unable to locate AXCIOMA project build files. Has \'apc prepare\' been run?'
        end
        return true
      end

      Command.register('apc|axp:make|build', DESC, CIAOX11::MakeProject)
    end # MakeProject

  end # CIAOX11
end # BRIX11
