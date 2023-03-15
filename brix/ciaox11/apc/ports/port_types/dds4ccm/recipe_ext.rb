#--------------------------------------------------------------------
# @file    recipe_ext.rb
# @author  Martin Corino
#
# @brief  DDS4CCM SEV interaction implementation specializations
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------

require 'fileutils'

module AxciomaPC
  module DDS4CCM
    # Extension module for DataIdlRecipe
    module DataIDLExtension
      def dds_idl_file_path(fidl_name)
        File.join(full_gen_path, File.basename(fidl_name, '.idl') + '_dds.idl')
      end

      def dds_typed_entities_stub_noext(fidl)
        File.join(gen_dir, File.basename(fidl.name, '.idl') + '_dds_typed_entitiesC')
      end

      def dds_typesupport_noext(fidl)
        File.join(gen_dir, File.basename(fidl.name, '.idl') + '_typesupport')
      end

      def process_dds4ccm_data_dependencies(project_dependencies, *prjtypes)
        prjtypes.each do |prjtype|
          if mpc_proj = mpc_file[prjtype]
            mpc_proj.add_dependencies(project_dependencies, prjtype)
          end
        end
      end

      def get_dds4ccm_data_dependencies(project_dependencies, idl_prj_dependencies, *prjtypes)
        BRIX11.log(4, '[%s] get_dds4ccm_data_dependencies : %s', self, project_dependencies)
        project_dependencies.merge(idl_prj_dependencies,
                                   :lem_gen, :lem_stub,
                                   *prjtypes)
      end
    end # DataIDLExtension

    AxciomaPC::DataIdlRecipe.send(:include, DataIDLExtension)
  end # DDS4CCM
end
