#--------------------------------------------------------------------
# @file    connector.rb
# @author  Marijke Hengstmengel
#
# @brief   AMI connector overrides
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------

module IDL
  module CCMX11
    module AMI4CCM
      module HideFacets
        # override to always return empty
        def non_local_facet_ports
          []
        end
      end
    end # AMI4CCM
  end # CCMX11
end # IDL
