#--------------------------------------------------------------------
# @file    idlfile.rb
# @author  Marijke Hengstmengel
#
# @brief   IDL file object
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------
require 'set'

module AxciomaPC
  class IDLFile

    @@nil_creator = Class.new do
      def self.create
        # noop
      end
    end

    attr :name, :path, :state

    def initialize(fp, project, state = nil)
      @name = File.basename(fp)
      @path = File.dirname(fp)
      @project = project
      @state = state || (@project.is_project_path?(fp) ? :member : :extern)
      @mpc_projects = []
      @recipes = []
      @rec_includes = []
      @creator = @@nil_creator
      @scanned = false
      @prj_dependencies = MPC::Dependencies.new
    end

    attr_reader :name, :path, :recipes

    def properties
      @properties ||= {}
    end

    def set_properties(prop)
      properties.merge!(prop)
    end

    def set_scanned(b=true)
      @scanned = (b ? true : false)
    end

    def has_been_scanned?
      @scanned
    end

    def is_member?
      @state != :extern
    end

    def is_generated?
      @state == :generated
    end

    def is_external?
      @state == :external
    end

    # automagic access for properties
    def method_missing(method, *args, &block)
      # only read
      if args.empty?
        if /\A(.*)[\?]\Z/ =~ method.to_s
          # boolean reader
          return properties[$1.to_sym] ? true : false
        else
          # data reader
          return properties[method]
        end
      end
      super
    end

    # define direct accessors for complex/often used properties

    def interaction_types
      properties[:interaction_types] ||= Set.new
    end

    def includes
      properties[:includes] ||= []
    end

    def project_dependencies
      @prj_dependencies
    end

    def set_mpc_project(mpc_project)
      @mpc_projects << mpc_project
    end

    def mpc_projects
      @mpc_projects
    end

    def full_path
      File.join(path, name)
    end

    def exist?
      File.exist? full_path
    end

    def check_existence
      @creator.create unless self.exist?
    end

    def set_creator(creator)
      raise "ERROR: Invalid creator for #{self.to_s}" unless creator.respond_to? :create
      @creator = creator
    end

    def to_s
      "APC::IDLFile{#{full_path}}"
    end

    def dump(indent=0, out=STDERR)
      out.puts (' ' * indent) + self.to_s
      out.puts (' ' * (indent + 2)) + '{'
      properties.each do |k, v|
        out.print "#{' ' * (indent + 4)}#{k} => "
        if k == :includes
          out.puts "[#{v.join(',')}]"
        elsif k == :interaction_types
          out.puts "[#{v.to_a.join(',')}]"
        else
          out.puts "#{v}"
        end
      end
      out.puts (' ' * (indent + 2)) + '}'
      out.puts (' ' * (indent + 2)) + project_dependencies.to_s
      recipes.each { |rcp| out.puts (' ' * (indent + 2)) + rcp.to_s }
      out.puts (' ')
    end
  end
end #AxciomaPC
