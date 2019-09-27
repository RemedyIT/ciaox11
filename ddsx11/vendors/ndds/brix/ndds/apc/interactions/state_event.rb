#--------------------------------------------------------------------
# @file    state_event.rb
# @author  Martin Corino
#
# @brief  State and Event interaction pattern specializations
#
# @copyright Copyright (c) Remedy IT Expertise BV
# Chamber of commerce Rotterdam nr.276339, The Netherlands
#--------------------------------------------------------------------

# load specializations and extensions
Dir.glob(File.join(File.dirname(__FILE__), 'state_event', '*.rb')).each do |fnm|
  require fnm
end

