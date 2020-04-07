#--------------------------------------------------------------------
# @file    include.rb
# @author  Martin Corino
#
# @brief   Include visitor PSDD4CCM
#
# @copyright (c) Remedy IT Expertise BV
# Chamber of commerce Rotterdam nr.276339, The Netherlands
#--------------------------------------------------------------------
require 'ridlbe/c++11/visitors/include'

module IDL
  module Cxx11

    # Reopen visitor class to add psdd traits specifics
    #
    class IncludeVisitor
      def psdd_traits_include?
        File.basename(node.filename) != 'ccm_psdd.idl'
      end

      def psdd_traits_include
        self.include_directory + '/' + File.basename(node.filename, '.*')+params[:psdd_traits_pfx]+params[:hdr_ext]
      end
    end
  end
end
