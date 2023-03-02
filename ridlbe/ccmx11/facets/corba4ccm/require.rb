#--------------------------------------------------------------------
# @file    require.rb
# @author  Marijke Hengstmengel
#
# @brief   CCMX11 CORBA facet loader
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------

module IDL
  module CCMX11
    module CORBA
      ROOT = 'ridlbe/ccmx11/facets/corba4ccm'
    end
  end
end

# base modules
['config'].each do |f|
  require "#{IDL::CCMX11::CORBA::ROOT}/#{f}"
end

# As the order in which facets in the context of a single backend are loaded is not
# guaranteed and for performance reasons it may be better to postpone loading remaining
# facet code (visitors, writers and/other code) till the #on_process_input code is called.

# writers
Dir.glob(File.join(File.dirname(__FILE__), 'writers', '*.rb')).each do |f|
  require File.join(IDL::CCMX11::CORBA::ROOT, 'writers', File.basename(f, '.*'))
end
