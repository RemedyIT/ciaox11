#--------------------------------------------------------------------
# @file    require.rb
# @author  Martin Corino
#
# @brief   CCMX11 PSDD4CCM facet loader
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------

module IDL

  module CCMX11

    module PSDD4CCM

      ROOT = 'ridlbe/ccmx11/facets/psdd4ccm'

    end

  end

end

# base modules
[ 'config',
].each do |f|
  require "#{IDL::CCMX11::PSDD4CCM::ROOT}/#{f}"
end

# As the order in which facets in the context of a single backend are loaded is not
# guaranteed and for performance reasons it may be better to postpone loading remaining
# facet code (visitors, writers and/other code) till the #on_process_input code is called.

# visitors
Dir.glob(File.join(File.dirname(__FILE__), 'visitors', '*.rb')).each do |f|
  require File.join(IDL::CCMX11::PSDD4CCM::ROOT, 'visitors', File.basename(f, '.*'))
end

# writers
Dir.glob(File.join(File.dirname(__FILE__), 'writers', '*.rb')).each do |f|
  require File.join(IDL::CCMX11::PSDD4CCM::ROOT, 'writers', File.basename(f, '.*'))
end
