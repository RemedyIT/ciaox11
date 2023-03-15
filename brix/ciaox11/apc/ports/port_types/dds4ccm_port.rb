#--------------------------------------------------------------------
# @file    dds4ccm_port.rb
# @author  Marijke Hengstmengel
#
# @brief  DDS4CCM port specializations
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------

module AxciomaPC
  module DDS4CCM
    class Port < PortType

      class Configurator < PortType::Configurator
        def topic(name)
          @port_type.topic = name
        end
        def topic_namespace(name)
          @port_type.topic_namespace = name
        end
        def topic_sequence_suffix(name)
          @port_type.topic_seq_suffix = name
        end
        def topic_interface_suffix(name)
          @port_type.topic_if_suffix = name
        end
        def topic_sequence(name)
          @port_type.topic_seq = name
        end
        def topic_interface(name)
          @port_type.topic_if = name
        end
        def middleware(name)
          @port_type.middleware([name])
        end
        def disable_context_switch
          @port_type.disable_context_switch
        end
      end

      CONFIGURATOR = Port::Configurator

      class << self
        def middleware_implementations
          @middleware_impl ||= []
        end
      end

      def initialize(recipe)
        super
      end

      def setup
        # create implicit interface recipe if no explicit version is defined
        idlmatch = project.match_idl_files(interface_name + '.idl')
        intf_idl_file = idlmatch.find do |fidl|
          if rcp = fidl.recipes.first
             SEV::InterfaceRecipe === rcp && rcp.topic == topic
          else
            false
          end
        end
        # if no existing recipe found create implicit one here
        @interface_recipe = if intf_idl_file
          intf_recipe = intf_idl_file.recipes.first
          # make sure the details are correctly set
          intf_recipe.topic_namespace ||= @topic_namespace
          intf_recipe.topic_seq ||= @topic_seq
          intf_recipe.topic_seq_suffix ||= @topic_seq_suffix
          intf_recipe.topic_if ||= @topic_if
          intf_recipe.topic_if_suffix ||= @topic_if_suffix
          intf_recipe
        else
          intf_recipe =
            SEV::InterfaceRecipe.create(recipe.recipe_file,
                                        interface_name,
                                        topic,
                                        recipe.idl,
                                        recipe.idl_includes,
                                        recipe.gen_dir,
                                        @topic_namespace,
                                        @topic_seq,
                                        @topic_seq_suffix,
                                        @topic_if,
                                        @topic_if_suffix)
          # add to same recipe file as the current recipe
          recipe.recipe_file.add_recipe(intf_recipe)
          intf_recipe
        end
      end

      def interface_name
        @interface_name ||= "#{File.basename(self.recipe.idl.first, '.*')}SE"
      end

      def topic=(name)
        @topic = name.to_s
      end

      def topic_namespace=(name)
        @topic_namespace = name
      end

      def topic_if_suffix=(name)
        @topic_if_suffix = name
      end

      def topic_seq_suffix=(name)
        @topic_seq_suffix = name
      end

      def topic_seq=(name)
        @topic_seq = name
      end

      def topic_if=(name)
        @topic_if = name
      end

      def middleware(*names)
       @middleware = names.collect do |n|
          n = n.to_s.downcase.to_sym
          if Port.middleware_implementations.include?(n)
            n
          else
            raise "Invalid middleware :#{n} specified. Valid middleware is #{Port.middleware_implementations}"
          end
       end.compact unless names.empty?
       # if none specified build all configured/available implementations
       @middleware || [Port.middleware_implementations.first]
      end

      def disable_context_switch
        @context_switch_disabled = true
      end

      def context_switch_disabled?
        !!@context_switch_disabled
      end

      def topic
        BRIX11.log_warning("topic specification missing from #{self.to_s}") unless @topic
        @topic || ''
      end

      def setup_projects
        BRIX11.log(3, '[%s] setup projects ', self)
        mpc_obj = create_conn_gen
        mpc_file.add_mpc_project(mpc_obj)
      end

      def process_project_dependencies
        project_dependencies = MPC::Dependencies.new
        recipe.idl_files.each do |_, fidl|
          BRIX11.log(3, '[%s] process_project_dependencies %s', self, fidl)
          inc_fidl = project.idl_files[fidl.full_path]
          rcp = inc_fidl.recipes.first
          rcp.get_dependencies(inc_fidl, [:sev].concat(middleware.collect { |m| :"dds4ccm_#{m}" }), project_dependencies)

          fidl.includes.each do |ifidl|
            if ifidl.is_member?
              rcp = ifidl.recipes.first
              rcp.get_dependencies(ifidl, [:sev].concat(middleware.collect { |m| :"dds4ccm_#{m}" }), project_dependencies)
            end
          end
        end
        inc_fidl = project.idl_files[@interface_recipe.interface_idl_path]
        @interface_recipe.get_dependencies(inc_fidl, [:sev].concat(middleware.collect { |m| :"dds4ccm_#{m}" }), project_dependencies)

        BRIX11.log(3, '[%s] process_project_dependencies inc_fidl: %s %s', self, inc_fidl, project_dependencies)

        setup_conn_gen(project_dependencies)
        project_dependencies
      end

      def create_conn_gen
        MPC::IDLProject.new(:dds_conn_gen, self.recipe)
      end

      def setup_conn_gen(project_dependencies)
        mpc_obj = mpc_file[:dds_conn_gen]
        mpc_obj.add_project_file(@interface_recipe.interface_idl_path)

        # idl_includes: idl in recipe self, concat with includes given in project root apcrc file
        mpc_obj.includes << idl_includes << project.idl_includes

        #Also needed the gen_dir from the original recipe of the idl_files for the includes
        recipe.idl_files.each do |n, idf|
          org_fidl = project.idl_files[idf.full_path]
          rcp = org_fidl.recipes.first
          mpc_obj.includes << File.expand_path(rcp.gen_dir, rcp.recipe_file.path)
        end
        mpc_obj.add_dependencies(project_dependencies, :idl_gen)
        mpc_obj.add_dependencies(project_dependencies, :dds_lem_gen)
        mpc_obj
      end

      def mpc_name
        '_dds4ccm'
      end

    end # Port
  end # DDS4CCM

  ConnectorRecipe.register_port_type(:dds4ccm, DDS4CCM::Port)
end

# load specializations and extensions
Dir.glob(File.join(File.dirname(__FILE__), 'dds4ccm', '*.rb')).each do |fnm|
  require fnm
end
