#--------------------------------------------------------------------
# @file    require.rb
# @author  Martin Corino
#
# @brief   BRIX11 PSDD4CCM ZMQ brix collection loader
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------

module BRIX11
  module CIAOX11
    module PSDD4CCM_ZMQ
      ROOT = File.dirname(__FILE__)
      TITLE = 'PSDD4CCM_ZMQ'
      DESC = 'BRIX11 PSDD4CCM ZMQ brix collection'
      COPYRIGHT = "Copyright (c) 2014-#{Time.now.year} Remedy IT Expertise BV, The Netherlands"
      VERSION = { major: 1, minor: 0, release: 0 }

      Collection.configure(:psdd4ccm_zmq, ROOT, TITLE, DESC, COPYRIGHT, VERSION) do |cfg|

        # declare dependency on :psdd4ccm collection (forces it to load first)
        cfg.add_collection(:psdd4ccm)

        cfg.on_setup do |_optparser, _options|
        end

      end

      # no commands to load, only APC extensions
      require "brix/psdd4ccm_zmq/apc/require"
    end
  end
end
