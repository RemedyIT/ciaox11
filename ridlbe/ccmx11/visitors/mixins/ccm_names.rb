#--------------------------------------------------------------------
# @file    ccm_names.rb
# @author  Marijke Hengstmengel
#
# @brief   visitors mixin for CCM names (lem names)
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------
module IDL
  module CCMX11
    module CcmNames

      #original escaped name used in composed name with 'CCM_'
      def ccm_name
        'CCM_'+name
      end

      #original escaped name for using in composed names
      def lem_name
        name
      end

      #needed for generating idl from idl
      def scoped_unescaped_ccm_name
        ((@node.enclosure && !@node.enclosure.scopes.empty?) ? scoped_enclosure_unescaped_name+'::'+ccm_name : ccm_name)
      end
      #needed for generating idl from idl
      def scoped_unescaped_type
        ((@node.enclosure && !@node.enclosure.scopes.empty?) ? scoped_enclosure_unescaped_name+'::'+unescaped_name : unescaped_name)
      end

      def scoped_ccm_name
        ((@node.enclosure && !@node.enclosure.scopes.empty?) ? '::'+scoped_enclosure_cxxname+'::'+ccm_name : ccm_name)
      end

      def scoped_ccm_name_in_type
        'IDL::traits< ' + scoped_ccm_name + '>::ref_type'
      end

      def scoped_ccm_name_return_type
        scoped_ccm_name_in_type
      end

      def scoped_ccm_name_member_type
        'IDL::traits< ' + scoped_ccm_name + '>::ref_type'
      end

      def scoped_ccm_type
        scoped_ccm_type ||= (((node.enclosure && !node.enclosure.scopes.empty?) ? node.enclosure.scoped_cxxname+'::' : '')+
                                      ccm_name)
      end
    end
  end
end
