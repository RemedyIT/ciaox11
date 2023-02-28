#--------------------------------------------------------------------
# @file    import.rb
# @author  Martin Corino
#
# @brief   Import base backend visitors
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------
require 'ridlbe/c++11/visitors/pre_post'
require 'ridlbe/c++11/visitors/interface'
require 'ridlbe/c++11/visitors/struct'
require 'ridlbe/c++11/visitors/include'
require 'ridlbe/c++11/visitors/operation'
require 'ridlbe/c++11/visitors/attribute'
require 'ridlbe/c++11/visitors/union'

module IDL
  module CCMX11
    PreVisitor = Cxx11::PreVisitor
    PostVisitor = Cxx11::PostVisitor
    InterfaceVisitor = Cxx11::InterfaceVisitor
    StructVisitor = Cxx11::StructVisitor
    StructMemberVisitor = Cxx11::StructMemberVisitor
    IncludeVisitor = Cxx11::IncludeVisitor
    OperationVisitor = Cxx11::OperationVisitor
    AttributeVisitor = Cxx11::AttributeVisitor
    SequenceVisitor = Cxx11::SequenceVisitor
    EnumVisitor = Cxx11::EnumVisitor
    ArrayVisitor = Cxx11::ArrayVisitor
    TypedefVisitor = Cxx11::TypedefVisitor
    UnionVisitor = Cxx11::UnionVisitor
    UnionMemberVisitor = Cxx11::UnionMemberVisitor
  end
end
