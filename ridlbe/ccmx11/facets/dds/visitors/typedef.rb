#--------------------------------------------------------------------
# @file    typedef.rb
# @author  Marcel Smit
#
# @brief   typedef visitor
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------
require 'ridlbe/c++11/visitors/include'

module IDL
  module CCMX11
    # Reopen visitor class to add DDS specifics
    #
    class TypedefVisitor
      def idl_typedef_type
        idl_declaration = ''

        if self.is_alias?
          idl_declaration += "#{strip_global_scope(self._idltype.idltype_name)} #{node.unescaped_name}"
        elsif self.is_sequence_typedef?
          idl_declaration += 'sequence<'
          typename = strip_global_scope(self._resolved_idltype.basetype.idltype_name)
          idl_declaration += typename
          if self.is_bounded_type?
            idl_declaration += ", #{self._resolved_idltype.size}"
          end
          idl_declaration += "> #{node.name}"
        elsif self.is_map_typedef?
          idl_declaration += 'map<'
          keytype_typename = strip_global_scope(self._resolved_idltype.keytype.idltype_name)
          valuetype_typename = strip_global_scope(self._resolved_idltype.valuetype.idltype_name)
          idl_declaration += "#{keytype_typename}, #{valuetype_typename}"
          if self.is_bounded_type?
            idl_declaration += ", #{self._resolved_idltype.size}"
          end
          idl_declaration += "> #{node.unescaped_name}"
        elsif self.is_array_type?
          typename = strip_global_scope(self._resolved_idltype.basetype.idltype_name)
          idl_declaration += typename
          if self.is_array_type?
            sizes = self._resolved_idltype.sizes.collect { |s| "[#{IDL::Expression::ScopedName === s ? s.node.name : s.to_s}]" }.join
            idl_declaration += " #{node.name}#{sizes}"
          end
        elsif self.is_bounded_type?
          idl_declaration += "#{self._resolved_idltype.idltype_name}<#{self._resolved_idltype.size}> #{node.name}"
        end
        idl_declaration
      end
    end # TypedefVisitor
  end # CCMX11
end # IDL
