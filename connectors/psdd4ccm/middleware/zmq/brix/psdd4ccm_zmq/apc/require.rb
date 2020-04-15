#--------------------------------------------------------------------
# @file    require.rb
# @author  Martin Corino
#
# @brief   PSDD4CCM ZMQ BRIX11 APC extension loader
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------

# load all port implementations
Dir.glob(File.join(File.dirname(__FILE__), 'ports', '*.rb')).each do |fnm|
  require fnm
end
