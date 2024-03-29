#--------------------------------------------------------------------
# @file    make.rb
# @author  Martin Corino
#
# @brief   Project builder extension  (common:make)
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------
require 'brix11/command'

module BRIX11
  module Common
    class Make < Command::Base
      class ListBuilder
        module MPCBuilder
          def self.check_build(dir)
            # an MPC build project dir should contain an .mpc file itself
            # OR it's subdirectories must contain .mpc files
            # the root should *not* contain an aprc file
            Dir.glob(File.join(dir, 'aprc')).empty? && Dir.glob(File.join(dir, '**', '*.mpc')).any? { |p| File.file?(p) }
          end
        end

        module APCBuilder
          def self.check_build(dir)
            # an APC build project dir should contain an aprc file itself
            !Dir.glob(File.join(dir, 'aprc')).empty?
          end

          def self.do_build(cmd, path)
            rc = true
            # if clean requested do so
            if cmd.options[:make][:clean]
              Sys.in_dir(path) do
                options = cmd.options.dup
                CIAOX11::RemoveProject.new(cmd.entry, options).run(nil)
              end
            end
            # do we need to build?
            if cmd.options[:make][:build]
              # should we (re-)generate?
              if cmd.options[:make][:genbuild]
                # create new command options
                options = cmd.options.dup
                options[:axpcreate] = CIAOX11::CreateProject::OPTIONS.dup
                Sys.in_dir(path) do
                  unless CIAOX11::CreateProject.new(cmd.entry, options).run(nil)
                    BRIX11.log_error("Failed to generate project for #{path}.")
                    rc = false
                  end
                end
              end
              # get project handler
              prj = Project.handler(options[:config][:project_type], options[:config][:project_compiler])
              if prj.project_exists?(path)
                # create new command options
                options = cmd.options.dup
                options[:axpmake] = CIAOX11::MakeProject::OPTIONS.dup
                options[:axpmake][:debug] = cmd.options[:make][:debug]
                options[:axpmake][:make_opts] = cmd.options[:make][:make_opts].dup
                options[:axpmake][:noredirect] = cmd.options[:make][:noredirect]
                Sys.in_dir(path) do
                  unless CIAOX11::MakeProject.new(cmd.entry, options).run(nil)
                    BRIX11.log_error("Failed to build project for #{path}.")
                    rc = false
                  end
                end
              else
                BRIX11.log_error("Cannot find project at #{path}")
                rc = false
              end
            end
            rc
          end
        end # APCBuilder

        self.builders[:apc] = APCBuilder
      end # ListBuilder
    end # Make
  end # Common
end # BRIX11
