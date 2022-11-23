#--------------------------------------------------------------------
# @file    compsvnt_extensions.rb
# @author  Marijke Hengstmengel
#
# @brief   ExF extensions for AMI4CCM connector servant generation
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------
require 'ridlbe/c++11/writerbase'

module IDL

  module CCMX11

    module ExF

      module AmiExFSvntConnectorSourceExt

        def self.configure_extension(writer)
          IDL.log(3, 'Configuring AmiExFSvntConnectorSourceExt extension')

          # make writer look for templates in ExF folder first
          # (requires AMI4CCM extension to be loaded first)
          writer.override_template(:pre_extra_include, 'ami/exf/pre_extra_include')
          writer.override_template(:component_configure, 'ami/exf/component_configure')
          writer.override_template(:component_obtain_facet_executor, 'ami/exf/component_obtain_facet_executor')
        end

      end

    end # ExF

  end # CCMX11

end # IDL
