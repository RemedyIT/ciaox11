// -*- C++ -*-
/**
 * @file    dds_read_condition.h
 * @author  Marcel Smit
 *
 * @brief   Wrapper facade for DDS
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDSX11_IMPL_READ_CONDITION_H_
#define DDSX11_IMPL_READ_CONDITION_H_

#include "dds/dds_export.h"
#include "dds/dds_native_entity_t.h"
#include "idl/dds_dcpsC.h"
#include "dds/dds_proxy_traits_t.h"

#if !defined (DDSX11_HAS_VENDOR_TYPEDEFS)
namespace DDS_Native {
  namespace DDS {
    class ReadCondition;
  }
}
#endif /* DDSX11_HAS_VENDOR_TYPEDEFS */

namespace DDSX11
{
  class DDSX11_IMPL_Export DDS_ReadCondition_proxy final
    : public virtual IDL::traits< ::DDS::ReadCondition>::base_type
    , public virtual NativeEntityBase_T<DDS_Native::DDS::ReadCondition>
  {
  public:
    /// Constructor
    explicit DDS_ReadCondition_proxy (DDS_Native::DDS::ReadCondition * rc);

    /// Destructor
    ~DDS_ReadCondition_proxy () override = default;

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

  private:
    DDS_ReadCondition_proxy() = delete;
    DDS_ReadCondition_proxy(const DDS_ReadCondition_proxy&) = delete;
    DDS_ReadCondition_proxy(DDS_ReadCondition_proxy&&) = delete;
    DDS_ReadCondition_proxy& operator=(const DDS_ReadCondition_proxy&) = delete;
    DDS_ReadCondition_proxy& operator=(DDS_ReadCondition_proxy&&) = delete;
  };

  using read_condition_trait = entity_traits< ::DDS::ReadCondition, DDS_ReadCondition_proxy, DDS_Native::DDS::ReadCondition>;
}

#endif /* DDSX11_IMPL_READ_CONDITION_H_ */
