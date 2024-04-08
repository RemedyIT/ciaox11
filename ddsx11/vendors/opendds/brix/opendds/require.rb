#--------------------------------------------------------------------
# @file    require.rb
# @author  Martin Corino
#
# @brief   BRIX11 OPENDDS brix collection loader
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------

module BRIX11
  module CIAOX11
    module OPENDDS
      ROOT = File.dirname(__FILE__)
      TITLE = 'OPENDDS'.freeze
      DESC = 'BRIX11 OPENDDS brix collection'.freeze
      COPYRIGHT = "Copyright (c) 2014-#{Time.now.year} Remedy IT Expertise BV, The Netherlands".freeze
      VERSION = { major: 2, minor: 6, release: 0 }

      Collection.configure(:opendds, ROOT, TITLE, DESC, COPYRIGHT, VERSION) do |cfg|
        # declare dependency on :ciaox11 collection (forces it to load first)
        cfg.add_collection(:ciaox11)

        cfg.on_setup do |optparser, options|
          if Exec.mswin?
            search_path_env = 'PATH'
          else
            search_path_env = 'LD_LIBRARY_PATH'
          end

          # Check whether we have OpenDDS in our package
          dds_root = Exec.get_run_environment('DDS_ROOT')
          opendds = dds_root && File.file?(File.join(dds_root, 'dds', 'Version.h'))

          if opendds
            # should we prepare for crossbuilds?
            if BRIX11.options.config.crossbuild
              # derive cross host env OpenDDS folder from native env folder
              opendds_folder = File.basename(dds_root)
              x11_host_root = (Exec.get_run_environment('X11_HOST_ROOT') || '')
              # update library search paths for host (tool) libs
              Exec.update_run_environment(search_path_env, [File.join(x11_host_root, opendds_folder, 'lib')], :append)
              # update executable search path for host deployment tools
              Exec.update_run_environment('PATH', [File.join(x11_host_root, opendds_folder, 'bin')], :prepend)
            else # or regular build environment
              # update library search paths for (tool) libs
              Exec.update_run_environment(search_path_env, [File.join(dds_root, 'lib')], :append)
              # update executable search path for deployment tools
              Exec.update_run_environment('PATH', [File.join(dds_root, 'bin')], :prepend)
            end
          end
        end
      end

      # no commands to load, only APC extensions
      require "brix/opendds/apc/require"
    end
  end
end
