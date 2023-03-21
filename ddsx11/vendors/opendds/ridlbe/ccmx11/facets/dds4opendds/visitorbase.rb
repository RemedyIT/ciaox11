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
    # Reopen C++11 VisitorBase to add custom OpenDDS handler
    #
    class VisitorBase
      def native_scoped_seq_cxxtype
        "#{native_scoped_name_prefix}OpenDDSSeq"
      end
    end # VisitorBase
  end # Cxx11
end # IDL
