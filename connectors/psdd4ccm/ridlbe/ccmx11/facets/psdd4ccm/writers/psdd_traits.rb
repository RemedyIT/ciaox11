#--------------------------------------------------------------------
# @file    psdd_traits.rb
# @author  Martin Corino
#
# @brief   Writer class for the serialization traits for PSDD4CCM
#
# @copyright Copyright (c) Remedy IT Expertise BV
# Chamber of commerce Rotterdam nr.276339, The Netherlands
#--------------------------------------------------------------------
require 'ridlbe/c++11/writerbase'
require 'ridlbe/c++11/writers/helpers/include_guard_helper'
require 'ridlbe/ccmx11/facets/psdd4ccm/visitors/mixin/psdd_traits'

module IDL

  module CCMX11

    module PSDD4CCM

      class PSDDTraitsWriter < Cxx11::CxxCodeWriterBase

        helper CCMX11::VersionHelper
        helper Cxx11::IncludeGuardHelper

        def initialize(output = STDOUT, opts = {})
          super
          self.template_root = 'psdd_traits'
          @file = File.basename(params[:idlfile], File.extname(params[:idlfile]))
          @include_guard = "__RIDL_PSDD_#{(@file || '').to_random_include_guard}_INCLUDED__"
        end

        attr_accessor :include_guard

        def pre_visit(parser)
          visitor(PreVisitor).visit
        end

        def post_visit(parser)
          visitor(PostVisitor).visit
        end

        def visit_include(node)
          visitor(IncludeVisitor).visit(node)
        end

        def visit_enum(node)
          # Convert all enums.
          visitor(EnumVisitor).visit_enum(node)
        end

        def enter_struct(node)
          unless is_supported_type?(node.idltype)
            IDL.log(1, "IDL::CCMX11::PSDD4CCM: ignoring unsupported type #{node.scoped_cxxname} for psdd traits generation")
            return
          end
          visitor(StructVisitor) do |v|
            v.singleton_class.__send__(:include, CCMX11::PSDD::StructMixin)
            v.visit(node)
            # check for valid keys
            v.key_members.each do |_km|
              unless is_valid_keytype?(_km.node.idltype)
                IDL.fatal("IDL::CCMX11::PSDD4CCM: unsupported key #{_km.cxxname} in struct #{v.scoped_cxxname}")
              end
            end
          end.visit_struct
        end

        def enter_union(node)
          unless is_supported_type?(node.idltype)
            IDL.log(1, "IDL::CCMX11::PSDD4CCM: ignoring unsupported type #{node.scoped_cxxname} for psdd traits generation")
            return
          end
          visitor(UnionVisitor).visit_union(node)
        end

        def visit_typedef(node)
          return if IDL::Type::ScopedName === node.idltype # alias typedef
          idl_type = node.idltype.resolved_type
          case idl_type
          when IDL::Type::Sequence
            unless is_supported_type?(idl_type)
              IDL.log(1, "IDL::CCMX11::PSDD4CCM: ignoring unsupported type #{node.scoped_cxxname} for psdd traits generation")
              return
            end
            visitor(SequenceVisitor).visit_sequence(node)
          when IDL::Type::Array
            unless is_supported_type?(idl_type)
              IDL.log(1, "IDL::CCMX11::PSDD4CCM: ignoring unsupported type #{node.scoped_cxxname} for psdd traits generation")
              return
            end
            visitor(ArrayVisitor).visit_array(node)
          when IDL::Type::String, IDL::Type::WString
            # check for bounded strings
            if idl_type.size
              visitor(Cxx11::StringVisitor).visit_string(node)
            end
          end
        end

        private

        def is_supported_type?(idltype)
          idl_type = idltype.resolved_type
          case idl_type
          when IDL::Type::Any,
              IDL::Type::Native,
              IDL::Type::Object,
              IDL::Type::Interface,
              IDL::Type::ValueBase,
              IDL::Type::Valuebox,
              IDL::Type::Valuetype,
              IDL::Type::Fixed,
              IDL::Type::Home,
              IDL::Type::Component,
              IDL::Type::Exception
            false
          when IDL::Type::Struct,
              IDL::Type::Union
            idl_type.node.members.all? { |_m| is_supported_type?(_m.idltype.resolved_type) }
          when IDL::Type::Sequence,
              IDL::Type::Array
            is_supported_type?(idl_type.basetype.resolved_type)
          else
            true
          end
        end

        def is_valid_keytype?(idltype)
          idl_type = idltype.resolved_type
          case idl_type
          when IDL::Type::Sequence
              IDL::Type::Array
            false
          else
            true
          end
        end

      end # PSDDTraitsWriter

    end # PSDD4CCM

  end # CCMX11

end # IDL
