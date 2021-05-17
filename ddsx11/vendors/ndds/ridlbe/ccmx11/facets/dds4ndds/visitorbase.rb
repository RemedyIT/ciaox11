#--------------------------------------------------------------------
# @file    visitorbase.rb
# @author  Marcel Smit
#
# @brief   base class for DDS visitors
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------
require 'ridlbe/c++11/visitorbase'

module IDL

  module Cxx11

    # Reopen C++11 VisitorBase to add custom RTI Connext DDS handled
    #
    class VisitorBase

      # For all implied C++11 types we need the escaped C++ namespace but the unescaped C++ name
      # because we add a postfix to the name which always results in a unique name which doesn't
      # conflict with a C++ keyword (for example Foo::structDataWriter), but rtiddsgen doesn't do
      # that, uses the cxx name
      def native_scoped_name_prefix
        scoped_cxxtype.start_with?('::') ? "DDS_Native::#{scoped_enclosure_cxxname}::#{cxxname}" : "#{cxxname}"
      end
    end # VisitorBase

  end # Cxx11

end # IDL
