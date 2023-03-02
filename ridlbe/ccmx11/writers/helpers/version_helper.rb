#--------------------------------------------------------------------
# @file    version_helper.rb
# @author  Marcel Smit
#
# @brief   Helper module for CIAOX11 version check generation
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------

module IDL

  module CCMX11

    module VersionHelper

      def ciaox11_version_header
        "ciaox11/versionx11.h"
      end

      def ciaox11_version
        writer.params[:ciaox11_version]
      end

      def ciaox11_title
        IDL::CCMX11::TITLE
      end

      def ciaox11_version_check
        "#include /**/ \"#{ciaox11_version_header}\"\n\n" +
            "#if CIAOX11_MAJOR_VERSION != #{ciaox11_version[:major]} || " +
            "CIAOX11_MINOR_VERSION != #{ciaox11_version[:minor]} || " +
            "CIAOX11_MICRO_VERSION != #{ciaox11_version[:micro]}\n" +
            "#error This file was generated with another #{ciaox11_title} version " +
            "(#{ciaox11_version[:major]}.#{ciaox11_version[:minor]}.#{ciaox11_version[:micro]}). " +
            "Please re-generate.\n#endif"
      end

    end # VersionHelper

  end # CCMX11

end # IDL
