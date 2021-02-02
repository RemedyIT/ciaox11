#--------------------------------------------------------------------
# @file    parser.rb
# @author  Martin Corino
#
# @brief   IDL frontend customizations for CCMX11 backend
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------

module IDL

  module CCMX11

    ###
    # Delegator extension mixin to add CCMX11 customization
    module DelegatorExt
        def self.included(base)
          # add CCMX11 pragma extension methods
          base.send(:include, Methods)

          # add pragma handlers
          base.add_pragma_handler(:axcioma_lem) do |_delegator, _curnode, _pragmastr|
            # 20190729, add backwards compatibility for ciao lem, see devportal #4737
            if (rc = (/^(ciao|axcioma)\s+lem\s+(.*)/ =~ _pragmastr ? true : false))
              _delegator.add_lem_include($2.strip)
            end
            rc
          end

          base.add_pragma_handler(:axcioma_impl) do |_delegator, _curnode, _pragmastr|
            # 20190729, added backwards compatibility for dds4ccm impl, see devportal #4738
            if (rc = (/^(dds4ccm|axcioma)\s+impl\s+(.*)/ =~ _pragmastr ? true : false))
              _delegator.add_impl_include($2.strip)
            end
            rc
          end
        end

        module Methods
          def add_lem_include(s)
            # strip start and end characters (should be the '""' or '<>' brackets)
            s = s[1, s.size-2]
            if IDL::AST::Include === @cur
              IDL.log(3, "registering LEM include [#{s}] from #{@cur.filename}")
              # if this is parsed from an include file register the lem include there
              @cur.add_lem_include(s)
            end
          end

          def add_impl_include(s)
            # strip start and end characters (should be the '""' or '<>' brackets)
            s = s[1, s.size-2]
            (@impl_includes ||= []) << s
            if IDL::AST::Include === @cur
              # if this is parsed from an include file register the template include there
              @cur.add_impl_include(s)
            end
          end
        end # Methods

    end # DelegatorExt

    ###
    # AST::Include node customization mixin
    module IncludeMixin
      def lem_includes
        @lem_includes ||= []
      end

      def add_lem_include(incfile)
        self.lem_includes << incfile
      end

      def has_lem_includes?
        !self.lem_includes.empty?
      end

      def all_lem_includes
        _all_lem_incs = lem_includes.dup
        walk_members do |m|
          _all_lem_incs.concat m.all_lem_includes if m.is_a?(IDL::AST::Include)
        end
        _all_lem_incs
      end

      def impl_includes
        @impl_includes ||= []
      end

      def add_impl_include(incfile)
        self.impl_includes << incfile
      end

      def has_impl_includes?
        !self.impl_includes.empty?
      end

      def all_impl_includes
        _all_impl_incs = impl_includes.dup
        walk_members do |m|
          _all_impl_incs.concat(m.all_impl_includes) if m.is_a?(IDL::AST::Include)
        end
        _all_impl_incs
      end
    end # IncludeMixin

    ###
    # AST::ComponentBase node customization mixin
    module ComponentBaseMixin
      def proxy_cxxname
        cxxname+Cxx11::STUB_PROXY_SUFFIX
      end
      def scoped_proxy_cxxname
        scoped_cxxname+Cxx11::STUB_PROXY_SUFFIX
      end
      def srvproxy_cxxname
        cxxname+Cxx11::SRV_PROXY_SUFFIX
      end
      def scoped_srvproxy_cxxname
        scoped_skel_cxxnamespace+'::'+srvproxy_cxxname
      end
      def scoped_skel_cxxnamespace
        ((enclosure && !enclosure.scopes.empty?) ? enclosure.scoped_cxxname+'::' : '')+'POA'
      end
      def skel_cxxname
        cxxname
      end
      def scoped_skel_cxxname
        scoped_skel_cxxnamespace+'::'+skel_cxxname
      end
    end # ComponentBaseMixin

  end # CCMX11

  # extend with CCMX11 pragma handling
  Delegator.send(:include, CCMX11::DelegatorExt)

  # extend with CCMX11 lem&impl pragma properties
  AST::Include.send(:include, CCMX11::IncludeMixin)

  # extend with CCMX11 naming extensions
  AST::ComponentBase.send(:include, CCMX11::ComponentBaseMixin)

end # IDL
