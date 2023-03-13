#--------------------------------------------------------------------
# @file    servantextensions.rb
# @author  Martin Corino
#
# @brief   ExF extensions for CORBA skeleton/servant generation
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------
require 'ridlbe/c++11/writerbase'

module IDL
  module CCMX11
    module ExF
      module CorbaServantHeaderExt
        module WriterExtension
          def self.included(base)
            base.class_eval do
              # override
              def visit_includes(parser)
                writer(Cxx11::ServantHeaderIncludeWriter) do |w|
                  w.include_guard = @include_guard
                  w.includes << 'exf/deployment/amh/ciaox11_exf_amh_base.h'
                  w.visit_nodes(parser)
                end
              end
            end
          end
        end # WriterExtension

        def self.configure_extension(writer)
          IDL.log(3, 'Configuring ExF CorbaServantHeader extension')
          # make writer look for templates in ExF folder first
          writer.template_root = File.join(writer.template_root, 'exf')
          # prepend ExF template before regular template
          writer.prepend_template(:interface_pre, :interface_exf_pre)
        end
      end

      module CorbaServantSourceExt
        module WriterExtension
          def self.included(base)
            base.class_eval do
              # overload
              def enter_interface(node)
                unless node.is_local? || node.is_pseudo? || node.is_abstract?
                  visitor(InterfaceVisitor).visit_exf_pre(node)
                end
                super
              end
            end
          end
        end # WriterExtension

        def self.configure_extension(writer)
          IDL.log(3, 'Configuring ExF CorbaServantSource extension')
          # make writer look for templates in ExF folder first
          writer.template_root = File.join(writer.template_root, 'exf')
        end
      end
    end # ExF
  end # CCMX11
end # IDL
