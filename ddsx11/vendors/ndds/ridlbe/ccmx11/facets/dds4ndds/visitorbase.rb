#--------------------------------------------------------------------
# @file    visitorbase.rb
# @author  Johnny Willemsen
#
# @brief   base class for DDS visitors
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------
require 'ridlbe/c++11/visitorbase'

module IDL
  module Cxx11
    # Reopen C++11 VisitorBase to add custom RTI Connext DDS handler
    #
    class VisitorBase
      # For all implied C++11 types we need the escaped C++ namespace but the unescaped C++ name
      # because we add a postfix to the name which always results in a unique name which doesn't
      # conflict with a C++ keyword (for example Foo::structDataWriter), but rtiddsgen doesn't do
      # that, uses the cxxname
      def native_scoped_name_prefix
        '::DDS_Native' + (!scoped_enclosure_cxxname.empty? ? '::' : '') + "#{scoped_enclosure_cxxname}::#{cxxname}"
      end

      def native_scoped_seq_cxxtype
        "#{native_scoped_name_prefix}RTISeq"
      end
    end # VisitorBase
  end # Cxx11
end # IDL
