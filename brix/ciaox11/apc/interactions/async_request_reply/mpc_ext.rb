#--------------------------------------------------------------------
# @file    mpc_ext.rb
# @author  Marijke Hengstmengel
#
# @brief  Asynch request and reply specializations
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------

# make sure MPC base definitions are loaded
require 'brix/ciaox11/apc/mpcfile.rb'

module AxciomaPC
  module MPC
    # add  asynch request and reply MPC IDL project specializations
    MPC::IDLProject::DEFAULTS.merge!({
      ami4ccm_lem_idl_gen: {
         add_idl_flags: '-Gami4ccm,Aidl-only -Scc -Sch -Scp',
         export: false,
         base_projects: %w{ciaox11_ami4ccm_idldefaults},
         auto_dependencies: []
      },
      ami4ccm_lem_gen: {
         add_idl_flags: '-Gxhst',
         export: false, ## set false so we can add our own export flags
         base_projects: %w{ciaox11_ami4ccm_idldefaults},
         auto_dependencies: []
      },
    })

    AMI4CCM_NM_EXT = '_ami4ccm'

    class AMI4CCMStubProject < MPC::CompileProject

      def initialize(recipe)
        super(:ami4ccm_lem_stub, recipe)
        project_dependencies << "#{mpc_id}_ami4ccm_idl_gen_stubs"
        project_dependencies << "#{mpc_id}#{STUB_NM_EXT}"
        link_libs << "#{recipe.shared_name}#{STUB_NM_EXT}"
        base_projects << %w(ciaox11_ami4ccm_stub)
        # add default sources and headers
        @headers.concat((recipe.gen_dir + '/') << recipe.export_name << AMI4CCM_NM_EXT << STUB_NM_EXT << EXPORT_HEADER)
      end

      # overwrite because we can't use  @project_postfix ('_ami')
      # we must use here AMI4CCM_NM_EXT ('_ami4ccm'), because this is used in the export header generation
      def dynamic_names
        [(recipe.export_name.upcase + AMI4CCM_NM_EXT.upcase) << STUB_NM_EXT.upcase << '_BUILD_DLL']
      end

      def add_sources(idf)
        @sources.concat((recipe.gen_dir + '/') << idf << 'A' << STUB_F << EXT_CPP)
      end

      def add_headers(idf)
        @headers.concat((recipe.gen_dir + '/') << idf << 'A' << STUB_F << EXT_HEADER)
      end

    end
  end # MPC
end # AxciomaPC
