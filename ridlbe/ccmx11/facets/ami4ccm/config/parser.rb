#--------------------------------------------------------------------
# @file    parser.rb
# @author  Marijke Hengstmengel
#
# @brief   IDL frontend customizations for CCMX11 AMI4CCM backend
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------
require 'ridlbe/c++11/config/core'

module IDL
  module CCMX11
    module AMI4CCM
      ###
      # Adds AMI4CCM pragma support
      module PragmaExt
        def self.included(base)
          # add AMI4CCM pragma extension methods
          base.send(:include, Methods)

          # add AMI pragma handlers
          base.add_pragma_handler(:axcioma_ami4ccm_interface) do |_delegator, _curnode, _pragmastr|
            if (rc = (/^ami4ccm\s+interface\s+(.*)/ =~ _pragmastr ? true : false))
              _delegator.add_ami4ccm_interface(::Regexp.last_match(1).strip)
            end
            rc
          end

          base.add_pragma_handler(:axcioma_ami4ccm_receptacle) do |_delegator, _curnode, _pragmastr|
            if (rc = (/^ami4ccm\s+receptacle\s+(.*)/ =~ _pragmastr ? true : false))
               _delegator.add_ami4ccm_receptacle(::Regexp.last_match(1).strip)
            end
            rc
          end

          base.add_pragma_handler(:axcioma_ami4ccm_idl) do |_delegator, _curnode, _pragmastr|
            if (rc = (/^ami4ccm\s+idl\s+(.*)/ =~ _pragmastr ? true : false))
              _delegator.add_ami4ccm_idl_include(::Regexp.last_match(1).strip)
            end
            rc
          end
        end

        module Methods
          def add_ami4ccm_interface(s)
            add_ami_interfaces(s)  # add interface to ami_interfaces registry
            # determin current file name and transform to ami4ccm *A.idl
            aidl = File.basename(@scanner.position.name).gsub(/.idl\Z/, 'A.idl')
            # now automatically register *A.idl
            add_ami4ccm_idl_include_i(aidl)
          end

          def ami4ccm_receptacles
            @ami4ccm_receptacles ||= []
          end

          def add_ami4ccm_receptacle(s)
            # strip start and end characters (should be the '""' or '<>' brackets)
            s = s[1, s.size - 2]
            ami4ccm_receptacles << s
          end

          def add_ami4ccm_idl_include(s)
            # strip start and end characters (should be the '""' or '<>' brackets)
            s = s[1, s.size - 2]
            add_ami4ccm_idl_include_i(s)
          end

          def add_ami4ccm_idl_include_i(s)
            if IDL::AST::Include === @cur
              # if this is parsed from an include file register the ami4ccm idl include there as well
              @cur.add_ami4ccm_idl_include(s)
            end
          end
        end # Methods
      end # Pragma

      ###
      # AST::Include node customization mixin
      module IncludeMixin
        def ami4ccm_idl_includes
          @ami4ccm_idl_includes ||= []
        end

        def add_ami4ccm_idl_include(incfile)
          # prevent double inclusions
          # allows use of "pragma ami4ccm idl" preceding "pragma ami4ccm interface" and registering included idl
          # with path
          unless ami4ccm_idl_includes.any? { |idlinc| File.basename(idlinc) == File.basename(incfile) }
            ami4ccm_idl_includes << incfile
          end
        end

        def has_ami4ccm_idl_includes?
          !ami4ccm_idl_includes.empty?
        end

        def all_ami4ccm_idl_includes
          _all_ami4ccm_idl_incs = ami4ccm_idl_includes.dup
          walk_members do |m|
            _all_ami4ccm_idl_incs.concat m.all_ami4ccm_idl_includes if m.is_a?(IDL::AST::Include)
          end
          _all_ami4ccm_idl_incs
        end
      end # IncludeMixin
    end # AMI4CCM
  end # CCMX11

  # extend with AMI4CCM pragma handling
  Delegator.send(:include, CCMX11::AMI4CCM::PragmaExt) unless Delegator < CCMX11::AMI4CCM::PragmaExt

  # extend with AMI4CCM idl include properties
  AST::Include.send(:include, CCMX11::AMI4CCM::IncludeMixin) unless AST::Include < CCMX11::AMI4CCM::IncludeMixin
end # IDL
