#--------------------------------------------------------------------
# @file    recipe_ext.rb
# @author  Martin Corino
#
# @brief  Synchronous messaging interaction pattern specializations
#
# @copyright Copyright (c) Remedy IT Expertise BV
# Chamber of commerce Rotterdam nr.276339, The Netherlands
#--------------------------------------------------------------------

module AxciomaPC

  module SRR

    # Extension module for DataIdlRecipe
    module DataIDLExtension

      def process_srr_data_dependencies(project_dependencies)
        [:lem_gen, :lem_stub].each do |prjtype|
          if mpc_proj = mpc_file[prjtype]
            mpc_proj.add_dependencies(project_dependencies, prjtype)
          end
        end
      end

      def get_srr_data_dependencies(project_dependencies, idl_prj_dependencies)
        # merge any available lem dependencies whether or not the IDL file needed lem or not
        project_dependencies.merge(idl_prj_dependencies, :lem_gen, :lem_stub)
      end

    end

    AxciomaPC::DataIdlRecipe.send(:include, DataIDLExtension)

  end # SRR

end
