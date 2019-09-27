#--------------------------------------------------------------------
# @file    component.rb
# @author  Marijke Hengstmengel
#
# @brief   visitor class(es)
#
# @copyright Copyright (c) Remedy IT Expertise BV
# Chamber of commerce Rotterdam nr.276339, The Netherlands
#--------------------------------------------------------------------
require 'ridlbe/ccmx11/visitors/port.rb'
require 'ridlbe/c++11/visitors/attribute.rb'
require 'ridlbe/ccmx11/visitors/mixins/ccm_names.rb'

module IDL
  module CCMX11

    # Reopen ComponentVisitor class to add AMI4CCM specifics
    #
    class ComponentVisitor

      def incl_ami4ccm_receptacle?
        ports.any? {|p| p.is_ami4ccm_port? }
      end

      def interfaces_with_multiple_ami4ccm_ports
        mp_ports = all_ports.select do |p|
          p.is_ami4ccm_port?
        end
        interface_type = []
        multiple_ami_ports = []
        mp_ports.each do |mp|
          if !interface_type.include?(mp.interface_type.scoped_cxxname)
            interface_type << mp.interface_type.scoped_cxxname
            multiple_ami_ports << mp
          end
        end
        multiple_ami_ports
      end

    end

  end

end
