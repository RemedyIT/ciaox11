#--------------------------------------------------------------------
# @file    include.rb
# @author  Marijke Hengstmengel
#
# @brief   Include visitor ami4ccm
#
# @copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------
require 'ridlbe/c++11/visitors/include'

module IDL
  module Cxx11

    # Reopen visitor class to add ami4ccm specifics
    #
    class IncludeVisitor

      # def has_ami4ccm_idl_includes?
      #   @node.has_ami4ccm_idl_includes?
      # end

      def has_ami4ccm_receptacles?
        !self.properties[:ami4ccm_receptacles].empty?
      end

      # def ami4ccm_idl_includes
      #   @node.ami4ccm_idl_includes.map
      # end

      def has_ami4ccm_idl_includes?
        !self.ami4ccm_idl_includes.empty?
      end

      def ami4ccm_idl_includes # incl inherited
        @all_ami4ccm_impl_incs ||= @node.all_ami4ccm_idl_includes
      end

      def ami4ccm_idl_lem_includes
        chomp_str =  params[:idlext]
        @node.all_ami4ccm_idl_includes.map {|inc| inc.chomp(chomp_str) + params[:stub_pfx]+params[:hdr_ext]}
      end

      def has_ami4ccm_idl_lem_includes?
        !self.ami4ccm_idl_lem_includes.empty?
      end

    end
  end
end
