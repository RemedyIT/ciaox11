#--------------------------------------------------------------------
# @file    psdd_traits.rb
# @author  Martin Corino
#
# @brief   PSDD mixin for visitors
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------

module IDL
  module CCMX11
    module PSDD
      module MemberMixin
        def is_key?
          !self.annotations[:key].empty?
        end

        def is_key_only?
          is_key? &&
              case node.idltype.resolved_type
              when IDL::Type::Union
                false
              when IDL::Type::Struct
                visitor(StructVisitor) do |v|
                  v.singleton_class.__send__(:include, PSDD::StructMixin)
                  v.visit(node.idltype.resolved_type.node)
                end.has_key_only?
              else
                true
              end
        end
      end

      module StructMixin
        # overload
        def members
          unless @members
            super.each {|_m| _m.singleton_class.__send__(:include, MemberMixin) }
          end
          super
        end

        def has_key?
          members.any? { |_m| _m.is_key? }
        end

        def has_key_only?
          @psdd_key_only ||= members.all? {|_m| _m.is_key_only? }
        end

        def has_no_key?
          @psdd_no_key ||= members.all? { |_m| !_m.is_key? }
        end

        def key_members
          members.select { |_m|  _m.is_key? }
        end

        def data_members
          members.select { |_m|  !_m.is_key? }
        end
      end
    end
  end
end
