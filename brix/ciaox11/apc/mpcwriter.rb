#--------------------------------------------------------------------
# @file    mpcwriter.rb
# @author  Marijke Hengstmengel
#
# @brief   Generate MPC project definition file for CORBA project
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------

require 'brix11/command'

module AxciomaPC

  module MPC

    class ProjectVisitor < BRIX11::Generate::Visitor

      def initialize(mpcprj, output, properties, writer)
        super(output, properties, writer)
        @mpc_project = mpcprj
      end

      def template_path(tpl)
        ::File.join(params[:template_root], @mpc_project.template_path, tpl.to_s)
      end

      # overrule MPC project to return relative paths
      def includes
        @mpc_project.recipe.get_relative_paths(@mpc_project.includes)
      end

      # overrule MPC project to return relative paths
      def lib_paths
        @mpc_project.recipe.get_relative_paths(@mpc_project.lib_paths)
      end

      # overrule MPC project to return relative path
      def lib_out
        @mpc_project.recipe.get_relative_path(@mpc_project.lib_out)
      end

      def self.const_missing(n)
        MPC::Project.const_get(n)
      end

      def resolve_template(sym)
        tpl = self.class.template_map[sym.to_sym]
        unless tpl
          tpl = sym if BRIX11::Template.exists?(template_path(sym))
        end
        tpl
      end

      def visit_template(template, extra_props = {})
        yield(self, template) if block_given?
        if BRIX11::Template.exists?(template_path(template)) || required_template?(template)
          visit_resolved_template(template, extra_props)
        end
      end

      def visit_resolved_template(template, extra_props = {}, _ = nil)
        _file = template_path(template)
        IDL::Base::Visitor.context(self, properties, extra_props).parse(@output, BRIX11::Template.new(_file), extra_props)
        @output.erbout.flush
      end

      def method_missing(m, *args, &block)
        if VISIT_METHOD_RE =~ m
          super
          # sym = $1
          # tpl = resolve_template(sym)
          # raise "Fatal: cannot resolve BRIX11 template #{$1}" unless tpl || optional_template?(sym)
          # define_visit_method(m, tpl, sym)
          # self.send(m, *args, &block)
        else
          target = @mpc_project
          begin
            target.respond_to?(m) ? target.__send__(m, *args, &block) : super(m, *args, &block)
          ensure
            $@.delete_if {|t| %r"\A#{Regexp.quote(__FILE__)}:#{__LINE__-2}:"o =~ t} if $@
          end
        end
      end

      def respond_to_missing?(m, include_private)
        if VISIT_METHOD_RE =~ m
          true
        else
          r = @mpc_project.respond_to?(m, include_private)
          if r && include_private && !self.__getobj__.respond_to?(m, false)
            warn "#{caller(3)[0]}: delegator does not forward private method \##{m}"
            return false
          end
          r
        end
      end

      def initialize_clone(obj) # :nodoc:
        @mpc_project = obj.instance_variable_get(:@mpc_project).clone
      end
      def initialize_dup(obj) # :nodoc:
        @mpc_project = obj.instance_variable_get(:@mpc_project).dup
      end
      private :initialize_clone, :initialize_dup
    end

    class APCWriter < BRIX11::Generate::Writer
      attr_reader :projects

      def initialize(output, opts, mpc_file)
        @mpc_file = mpc_file
        super(output, opts)
        self.template_root = 'apc'
      end

      helper_method   :projects

      def projects
        @projects ||= @mpc_file.mpc_projects.collect {|p| p.wants_build? ? ProjectVisitor.new(p, @output, @properties.dup, self) : nil }.compact
        # MPC::Project list
        @projects
      end
    end

  end # MPC

end # AxciomaPC
