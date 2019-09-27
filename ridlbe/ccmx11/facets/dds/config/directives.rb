#--------------------------------------------------------------------
# @file    directives.rb
# @author  Martin Corino
#
# @brief   DDSX11 facet configuration, adds AXCIOMA 2
# annotation support, see #4729
#
# @copyright Copyright (c) Remedy IT Expertise BV
# Chamber of commerce Rotterdam nr.276339, The Netherlands

#--------------------------------------------------------------------

module IDL
  module CCMX11
    module DDSX11
      module ScannerPatch
        def self.included(base)
          base.class_eval do
            alias_method_chain :next_identifier, :ndds
            alias_method_chain :extract_annotation, :ndds
          end
        end

        def next_identifier_with_ndds(first = nil)
          # first perform regular scanner pass
          token = next_identifier_without_ndds(first)
          # are we parsing an annotation?
          if @in_annotation
            # did we find an identifier?
            if token.first == :identifier
              # now check if we stopped scanning the identifier at a '-'
              if @in.lookc == ?-
                # extract '-' and append to identifier
                token[1] += '-'
                @in.skipc
                # scan next part of identifier (recursively in case the '-'s are repeated)
                token2 = next_identifier_with_ndds
                parse_error "invalid annotation identifier encountered: #{token.last}" unless token2.first == :identifier
                token[1] += token2.last
              end
            end
          end
          token
        end

        def extract_annotation_with_ndds
          @ndds_annotation_level ||= 0  # set to 0 if not set before

          # increase the level to signal we're parsing an annotation body (optionally recursive)
          @ndds_annotation_level += 1 # inc level
          # now first perform regular extraction
          token, annbody = extract_annotation_without_ndds
          # next check if we have an undefined annotation body followed by a boolean
          if annbody.nil? && !token.nil? && token.first == :boolean_literal
            # define an annotation body with a boolean 'value' member
            annbody = { value: token.last }
            # let them know we used up the token
            token = nil
          end

          # leaving annotation body
          @ndds_annotation_level -= 1 # dec level
          [token, annbody]
        end
      end
    end
  end
end
