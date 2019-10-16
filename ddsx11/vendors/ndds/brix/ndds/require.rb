#--------------------------------------------------------------------
# @file    require.rb
# @author  Martin Corino
#
# @brief   BRIX11 NDDS brix collection loader
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------

module BRIX11

  module CIAOX11

    module NDDS

      ROOT = File.dirname(__FILE__)
      TITLE = 'NDDS'.freeze
      DESC = 'BRIX11 NDDS brix collection'.freeze
      COPYRIGHT = "Copyright (c) 2014-#{Time.now.year} Remedy IT Expertise BV, The Netherlands".freeze
      VERSION = {major: 0, minor: 1, release: 0}

      Collection.configure(:ndds, ROOT, TITLE, DESC, COPYRIGHT, VERSION) do |cfg|

        # declare dependency on :ciaox11 collection (forces it to load first)
        cfg.add_collection(:ciaox11)

        cfg.on_setup do |optparser, options|
          # if we have NDDSHOME and NDDSARCHITECTURE set to valid values
          if Exec.get_run_environment('NDDSHOME') && Exec.get_run_environment('NDDSARCHITECTURE') &&
              File.directory?(File.join(Exec.get_run_environment('NDDSHOME'),'lib', Exec.get_run_environment('NDDSARCHITECTURE')))
            # we need to derive a valid NDDSSCRIPTDIR
            # newer versions of NDDS (>= 6) have rtiddsgen here
            if File.directory?(File.join(Exec.get_run_environment('NDDSHOME'),'scripts'))
              Exec.update_run_environment('NDDSSCRIPTDIR', File.join(Exec.get_run_environment('NDDSHOME'),'scripts'))
            else
              # older versions have rtiddsgen here
              Exec.update_run_environment('NDDSSCRIPTDIR', File.join(Exec.get_run_environment('NDDSHOME'),'bin'))
            end
          end
        end

      end

      # no commands to load, only APC extensions
      require "brix/ndds/apc/require"
    end

  end

end
