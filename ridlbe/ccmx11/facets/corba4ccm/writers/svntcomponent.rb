#--------------------------------------------------------------------
# @file    svntcomponent.rb
# @author  Martin Corino
#
# @brief   Connector Servant writer class extension
#
# @copyright Copyright (c) Remedy IT Expertise BV
# Chamber of commerce Rotterdam nr.276339, The Netherlands
#--------------------------------------------------------------------
require 'ridlbe/c++11/writerbase'

module IDL

  module CCMX11

    module Corba4ccmSvntConnectorSourceExt

      def self.configure_extension(writer)
        writer.override_template(:component_init_connect, 'corba/component_init_connect')
        writer.overload_template(:pre_extra_include, 'corba/pre_extra_include')
      end

    end

  end # CCMX11

end # IDL
