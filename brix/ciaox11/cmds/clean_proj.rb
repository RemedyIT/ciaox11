#--------------------------------------------------------------------
# @file    clean_proj.rb
# @author  Marijke Hengstmengel
#
# @brief  Remove generated files from an axcioma project
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------
require 'brix/ciaox11/apc/apc'
require 'brix/ciaox11/apc/project'

module BRIX11
  module CIAOX11
    class RemoveProject < Command::Base
      DESC = 'Remove generated files from AXCIOMA project.'.freeze

      def self.setup(optparser, options)
        optparser.banner = "#{DESC}\n\n" +
                           "Usage: #{options[:script_name]} apc clean'\n\n"
      end

      def run(*args)
        # return project if  exist
        project = AxciomaPC::Project.load_project(:never)

        if options[:verbose] > 5
          project.dump
        end

        if !project
          raise Command::CmdError, 'Unable to locate AXCIOMA project root'
        end

        # setup the mpc files for the project without actually generating
        # them on disk, so they can be removed
        project.prepare(true)
        AxciomaPC::MPC.remove(project)

        prj = Project.handler(options[:config][:project_type])
        unless !prj.project_exists?(nil, project.root_path)
          options[:make] = BRIX11::Common::Make::OPTIONS.dup
          options[:make][:clean] = true
          options[:make][:build] = false
          options[:make][:genbuild] = false
          options[:make][:project] = project.root_path
          BRIX11::Common::Make.new(entry, options).run(nil)
        end

        makefiles = prj.make_files

        pp = File.join(project.root_path, "**/#{makefiles}*")
        Dir.glob(pp).each do |path|
          File.delete(path)
        end

        # remove with apc generated idl files
        project.generated_idl.each do |idf|
          File.delete(idf) if File.exist?(idf)
        end

        # remove gen_dirs, unless gen_dir is same as recipe dir  or gen_dir was an already existing dir
        # with 'not generated' files
        project.recipe_files.each { |_k, rcpf| rcpf.clean }

        # lib dir, difficult to remove, maybe it already exists before making the project and maybe it contains user libs
        # but we always remove it if it is empty
        if Dir.empty?(project.libout)
          FileUtils.remove_dir(project.libout)
        end

        # Finally delete project object
        AxciomaPC::Project.clean_project(project)

         # return always true, so in case of multiple brix commands, the next command is invoked
         true
      end
      Command.register('apc|axp:clean', DESC, CIAOX11::RemoveProject)
    end # RemoveProject
  end # CIAOX11
end # BRIX11
