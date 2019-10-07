#--------------------------------------------------------------------
# @file    include.rb
# @author  Johnny Willemsen
#
# @brief   Include visitor dds4ccm
#
# @copyright (c) Remedy IT Expertise BV
# Chamber of commerce Rotterdam nr.276339, The Netherlands
#--------------------------------------------------------------------
require 'ridlbe/c++11/visitors/include'

module IDL
  module Cxx11
    # Reopen visitor class to add dds include specifics
    class IncludeVisitor
      def ddsx11_typesupport_include?
        !%w{ccm_dds.idl Components.idl}.include?(File.basename(node.filename))
      end

      def ddsx11_typesupport_include
        self.include_directory + '/' + File.basename(node.filename, '.*') + params[:dds_typesupport_pfx] + params[:hdr_ext]
      end
    end
  end
end
