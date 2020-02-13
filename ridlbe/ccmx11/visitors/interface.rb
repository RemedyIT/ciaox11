#--------------------------------------------------------------------
# @file    interface.rb
# @author  Marijke Hengstmengel
#
# @brief   visitor class(es)
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------
require 'ridlbe/ccmx11/visitors/mixins/ccm_names.rb'

module IDL
  module Cxx11

    # Reopen InterfaceVisitor class to add CCMX11 specifics
    class InterfaceVisitor
      include CCMX11::CcmNames

      def executor_cxx_namespace
        scoped_cxxname.scope_to_cxxname+'_Impl'
      end

    end
  end
end
