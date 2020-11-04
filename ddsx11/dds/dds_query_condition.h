// -*- C++ -*-
/**
 * @file    dds_query_condition.h
 * @author  Marcel Smit
 *
 * @brief   Wrapper facade for DDS
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDSX11_IMPL_QUERY_CONDITION_H_
#define DDSX11_IMPL_QUERY_CONDITION_H_

#include "dds/dds_export.h"
#include "dds/dds_native_entity_t.h"
#include "idl/dds_dcpsC.h"
#include "dds/dds_proxy_traits_t.h"

#if !defined (DDSX11_HAS_VENDOR_TYPEDEFS)
namespace DDS_Native {
  namespace DDS {
    class QueryCondition;
  }
}
#endif /* DDSX11_HAS_VENDOR_TYPEDEFS */

namespace DDSX11
{
  class DDSX11_IMPL_Export DDS_QueryCondition_proxy final
    : public virtual IDL::traits< ::DDS::QueryCondition>::base_type
    , public virtual NativeEntityBase_T<DDS_Native::DDS::QueryCondition>
  {
  public:
    /// Constructor
    explicit DDS_QueryCondition_proxy (
      DDS_Native::DDS::QueryCondition * qc);

    /// Destructor
    virtual ~DDS_QueryCondition_proxy () = default;

    bool
    get_trigger_value () override;

    ::DDS::SampleStateMask
    get_sample_state_mask () override;

    ::DDS::ViewStateMask
    get_view_state_mask () override;

    ::DDS::InstanceStateMask
    get_instance_state_mask () override;

    IDL::traits< ::DDS::DataReader>::ref_type
    get_datareader () override;

    std::string
    get_query_expression () override;

    ::DDS::ReturnCode_t
    get_query_parameters (
      ::DDS::StringSeq & query_parameters) override;

    ::DDS::ReturnCode_t
    set_query_parameters (
      const ::DDS::StringSeq & query_parameters) override;

  private:
    DDS_QueryCondition_proxy() = delete;
    DDS_QueryCondition_proxy(const DDS_QueryCondition_proxy&) = delete;
    DDS_QueryCondition_proxy(DDS_QueryCondition_proxy&&) = delete;
    DDS_QueryCondition_proxy& operator=(const DDS_QueryCondition_proxy&) = delete;
    DDS_QueryCondition_proxy& operator=(DDS_QueryCondition_proxy&&) = delete;
  };

  using query_condition_trait = entity_traits< ::DDS::QueryCondition, DDS_QueryCondition_proxy, DDS_Native::DDS::QueryCondition>;
}

#endif /* DDSX11_IMPL_QUERY_CONDITION_H_ */
