#--------------------------------------------------------------------
# @file    util.rb
# @author  Martin Corino
#
# @brief   Utilities loader
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------

Dir.glob(File.join(File.dirname(__FILE__), 'util', '*.rb')).each do |fnm|
  require fnm
end
