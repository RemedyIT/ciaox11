#--------------------------------------------------------------------
# @file    psdd4ccm_port.rb
# @author  Martin Corino
#
# @brief  PSDD4CCM ZMQ port specializations
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------

module AxciomaPC

  module PSDD4CCM

    Port.middleware_implementations << :zmq

  end # PSDD4CCM

end

# load specializations and extensions
Dir.glob(File.join(File.dirname(__FILE__), 'psdd4ccm', '*.rb')).each do |fnm|
  require fnm
end
