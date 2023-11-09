#--------------------------------------------------------------------
# @file    require.rb
# @author  Martin Corino
#
# @brief   BRIX11 ExF brix collection loader
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------

module BRIX11
  module CIAOX11
    module ExF
      ROOT = File.dirname(__FILE__)
      TITLE = 'ExF'.freeze
      DESC = 'BRIX11 ExF brix collection'.freeze
      COPYRIGHT = "Copyright (c) 2014-#{Time.now.year} Remedy IT Expertise BV, The Netherlands".freeze
      VERSION = { major: 2, minor: 5, release: q }

      Collection.configure(:exf, ROOT, TITLE, DESC, COPYRIGHT, VERSION) do |cfg|
        # declare dependency on :ciaox11 collection (forces it to load first)
        cfg.add_collection(:ciaox11)
        # declare optional dependencies on :ndds, :opendds and :psdd4ccm collections (i.e. load if available)
        cfg.add_optional_collection(:ndds)
        cfg.add_optional_collection(:opendds)
        cfg.add_optional_collection(:psdd4ccm)

        cfg.on_setup do |optparser, options|
          unless ENV['RIDL_BE_PATH'] && BRIX11.use_environment?
            # update ridl backend search path taking crossbuild config into account
            exf_be_path = if BRIX11.options.config.crossbuild
                            File.join(Exec.get_run_environment('X11_HOST_ROOT') || '', 'ciaox11', 'exf')
                          else
                            File.join(Exec.get_run_environment('CIAOX11_ROOT'), 'exf')
                          end
            Exec.update_run_environment(
              'RIDL_BE_PATH',
                  exf_be_path,
                  :append)
            $: << exf_be_path unless $:.include?(exf_be_path)
          end

          # update documentation config
          Common::GenerateDocumentation::OPTIONS[:docsources]['exf'] = ['${CIAOX11_ROOT}/exf/docs']
        end
      end

      # no commands to load, only APC extensions
      require "brix/exf/apc/require"
    end
  end
end
