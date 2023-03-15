#--------------------------------------------------------------------
# @file    stringlist.rb
# @author  Martin Corino
#
# @brief   StringList classes
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------

module AxciomaPC
  module Util
    class StringList
      include ::Enumerable

      def initialize(sep = nil, val = nil)
        @value = []
        @separator = sep || "\n"
        self << val if val
      end

      def join_sep(sep=nil)
        s_ = (sep || @separator)
        s_ == :ws ? ' ' : s_
      end
      protected :join_sep

      def split_value(val)
        val.to_s.strip.split(@separator == :ws ? /\s+/ : @separator)
      end
      protected :split_value

      attr_reader :value, :separator

      def &(val)
        val = self.class === val ? val : self.dup.assign(val)
        @value & val.to_a
      end

      def append_values(*vals)
        @value.concat vals
        self
      end
      protected :append_values

      def concat(val)
        if val
          if ::Enumerable === val
            append_values(*val.inject([]) { |lv, el| lv.concat(split_value(el)) })
          else
            append_values(*split_value(val))
          end
        end
        self
      end
      alias :<< :concat

      def add(val)
        if val
          if ::Enumerable === val
            append_values(*val.collect { |el| el.to_s })
          else
            append_values(val.to_s)
          end
        end
        self
      end

      def +(val)
        self.dup << val
      end

      def -(val)
        self.dup.delete(val)
      end

      def empty?
        @value.empty?
      end

      def size
        @value.size
      end

      def assign(val)
        return if self == val # check for self assignment
        self.clear << val
      end

      def clear
        @value = []
        self
      end

      def include?(val)
        if Regexp === val
          (@value.detect { |el| val =~ el }) != nil
        else
          val_sl = (::Enumerable === val ? val : self.dup.assign(val))
          val_sl.all? { |s| @value.include?(s) }
        end
      end

      def delete(val)
        if Regexp === val
          @value.delete(@value.detect { |el| val =~ el })
        else
          val_sl = (::Enumerable === val ? val : self.dup.assign(val))
          val_sl.each { |s| @value.delete(s) }
        end
        self
      end

      def each(&block)
        @value.each(&block)
      end

      def join(_sep = nil)
        @value.join(join_sep(_sep))
      end

      def dup
        self.class.new(@separator, @value.collect { |s| s.dup })
      end

      def to_s(sep = nil)
        self.join(sep)
      end

      def to_ary
        @value
      end

      def to_a
        @value
      end
    end # StringList

    class UniqueStringList < StringList
      def append_values(*vals)
        super(*vals).value.uniq!
        self
      end
    end # UniqueStringList

    class Flags < UniqueStringList
      def initialize(val = nil)
        super(:ws, val)
      end

      def split_value(val)
        eval("%w{#{val.to_s}}")
      end
      protected :split_value

      def dup
        self.class.new(@value.collect { |s| s.dup })
      end
    end # Flags
  end # Util
end # AxciomaPC
