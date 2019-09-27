#--------------------------------------------------------------------
# @file    include.rb
# @author  Marcel Smit
#
# @brief   Include visitor NDDS
#
# @copyright (c) Remedy IT Expertise BV
# Chamber of commerce Rotterdam nr.276339, The Netherlands
#--------------------------------------------------------------------
require 'ridlbe/c++11/visitors/include'

module IDL
  module Cxx11

    # Reopen visitor class to add dds include specifics
    #
    class IncludeVisitor
      def dds_idl_include
        self.include_directory + '/' + File.basename(node.filename, '.*')+params[:dds_idl_pfx]+params[:idlext]
      end

      def dds_udt_traits_include
        self.include_directory + '/' + File.basename(node.filename, '.*')+params[:dds_traits_pfx]+params[:hdr_ext]
      end
    end
  end
end
