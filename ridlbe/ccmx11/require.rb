#--------------------------------------------------------------------
# @file    require.rb
# @author  Martin Corino
#
# @brief   CCMX11 language mapping loader
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------

# base modules
[ 'config',
  'visitorbase',
  'writerbase'
  ].each do |f|
  require File.join('ridlbe', 'ccmx11', f)
end

# visitors
Dir.glob(File.join(File.dirname(__FILE__), 'visitors', '*.rb')).each do |f|
  require File.join('ridlbe', 'ccmx11', 'visitors', File.basename(f, '.*'))
end

# writers
Dir.glob(File.join(File.dirname(__FILE__), 'writers', '*.rb')).each do |f|
  require File.join('ridlbe', 'ccmx11', 'writers', File.basename(f, '.*'))
end
