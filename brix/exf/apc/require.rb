#--------------------------------------------------------------------
# @file    require.rb
# @author  Martin Corino
#
# @brief   PSDD4CCM BRIX11 APC extension loader
#
# @copyright Copyright (c) Remedy IT Expertise BV
# Chamber of commerce Rotterdam nr.276339, The Netherlands
#--------------------------------------------------------------------

# load all recipe specializations
Dir.glob(File.join(File.dirname(__FILE__), 'recipes', '*.rb')).each do |fnm|
  require fnm
end

# load all port implementations
Dir.glob(File.join(File.dirname(__FILE__), 'ports', '*.rb')).each do |fnm|
  require fnm
end
