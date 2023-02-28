#--------------------------------------------------------------------
# @file    cxx_type.rb
# @author  IDL language mapping configuration
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------

module IDL

  # add language mapping specific type customizations for CCMX11

  class Type

    class Home
      include ReferenceType_Mixin
      include IdlType_Mixin
      def cxx_type(scope = nil)
        'TAOX11_CORBA::Home'
      end
      def cxx_typecode
        "_tc_Home"
      end
      def scoped_cxx_typecode
        "TAOX11_CORBA::_tc_Home"
      end
    end # Home

    class Component
      include ReferenceType_Mixin
      include IdlType_Mixin
    end # Component

  end # Type

end # IDL
