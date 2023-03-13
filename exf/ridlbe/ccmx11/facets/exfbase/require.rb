#--------------------------------------------------------------------
# @file    require.rb
# @author  Martin Corino
#
# @brief   RIDL ExF base facet loader
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------

module IDL
  module CCMX11
    module ExFBase
      ROOT = 'ridlbe/ccmx11/facets/exfbase'
    end
  end
end

# base modules
['config'
].each do |f|
  require "#{IDL::CCMX11::ExFBase::ROOT}/#{f}"
end
