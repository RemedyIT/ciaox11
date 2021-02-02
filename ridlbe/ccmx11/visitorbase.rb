#--------------------------------------------------------------------
# @file    visitorbase.rb
# @author  Martin Corino
#
# @brief   base class for visitors
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------
require 'ridlbe/c++11/visitorbase'

module IDL
  module Cxx11

    # Reopen C++11 VisitorBase to add CCMX11 specific properties
    #
    class VisitorBase

      def exec_export_include?
        params[:exec_export_include] || self.export_include?
      end

      def exec_export_include
        params[:exec_export_include] || self.export_include
      end

      def exec_export_macro
        params[:exec_export_macro] ? params[:exec_export_macro] + ' ' : self.export_macro
      end

      def svnt_export_include?
        params[:svnt_export_include] || self.export_include?
      end

      def svnt_export_include
        params[:svnt_export_include] || self.export_include
      end

      def svnt_export_macro
        params[:svnt_export_macro] ? params[:svnt_export_macro] + ' ' : self.export_macro
      end

      def conn_export_include?
        params[:conn_export_include] || self.export_include?
      end

      def conn_export_include
        params[:conn_export_include] || self.export_include
      end

      def conn_export_macro
        params[:conn_export_macro] ? params[:conn_export_macro] + ' ' : self.export_macro
      end

    end

  end # Cxx11

end # IDL
