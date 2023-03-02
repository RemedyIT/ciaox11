#--------------------------------------------------------------------
# @file    pre_post.rb
# @author  Martin Corino
#
# @brief   CCMX11 visitor class(es) extension
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------

module IDL
  module Cxx11
    class PreVisitor
      optional_template :extra_include
      optional_template :conn_ami_post_pre

      def type_include
        File.basename(params[:idlfile])
      end
    end
  end
end
