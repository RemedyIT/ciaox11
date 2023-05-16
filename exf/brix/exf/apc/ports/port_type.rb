#--------------------------------------------------------------------
# @file    port_type.rb
# @author  Martin Corino
#
# @brief   ExF Port type extension loader
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------

# load all interaction pattern port type implementations
Dir.glob(File.join(File.dirname(__FILE__), 'port_types', '*.rb')).sort.each do |fnm|
  require fnm
end
