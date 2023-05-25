#--------------------------------------------------------------------
# @file    require.rb
# @author  Martin Corino
#
# @brief   BRIX11 PSDD4CCM brix collection loader
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------

module BRIX11
  module CIAOX11
    module PSDD4CCM
      ROOT = File.dirname(__FILE__)
      TITLE = 'PSDD4CCM'.freeze
      DESC = 'BRIX11 PSDD4CCM brix collection'.freeze
      COPYRIGHT = "Copyright (c) 2014-#{Time.now.year} Remedy IT Expertise BV, The Netherlands".freeze
      VERSION = { major: 2, minor: 5, release: 0 }

      Collection.configure(:psdd4ccm, ROOT, TITLE, DESC, COPYRIGHT, VERSION) do |cfg|
        # declare dependency on :ciaox11 collection (forces it to load first)
        cfg.add_collection(:ciaox11)

        cfg.on_setup do |optparser, options|
          unless ENV['RIDL_BE_PATH'] && BRIX11.use_environment?
            # update ridl backend search path
            psdd4ccm_be_path = File.join(Exec.get_run_environment('CIAOX11_ROOT'), 'connectors', 'psdd4ccm')
            Exec.update_run_environment(
              'RIDL_BE_PATH',
                  psdd4ccm_be_path,
                  :append)
            $: << psdd4ccm_be_path unless $:.include?(psdd4ccm_be_path)
          end

          # update documentation config
          Common::GenerateDocumentation::OPTIONS[:docsources]['psdd4ccm'] = ['${CIAOX11_ROOT}/connectors/psdd4ccm/docs']
        end
      end

      # no commands to load, only APC extensions
      require "brix/psdd4ccm/apc/require"
    end
  end
end
