// -*- C++ -*-
/**
 * @file    dds_status_condition.h
 * @author  Marcel Smit
 *
 * @brief   Wrapper facade for DDS
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDSX11_IMPL_STATUS_CONDITION_H_
#define DDSX11_IMPL_STATUS_CONDITION_H_

#include "dds/dds_export.h"
#include "dds/dds_native_entity_t.h"
#include "idl/dds_dcpsC.h"
#include "dds/dds_proxy_traits_t.h"

#if !defined (DDSX11_HAS_VENDOR_TYPEDEFS)
namespace DDS_Native {
  namespace DDS {
    class StatusCondition;
  }
}
#endif /* DDSX11_HAS_VENDOR_TYPEDEFS */

namespace DDSX11
{
  class DDSX11_IMPL_Export DDS_StatusCondition_proxy final
    : public virtual IDL::traits< ::DDS::StatusCondition>::base_type
    , public virtual NativeEntityBase_T<DDS_Native::DDS::StatusCondition>
  {
  public:
    /// Constructor
    DDS_StatusCondition_proxy (
      DDS_Native::DDS::StatusCondition *sc);

    /// Destructor
    virtual ~DDS_StatusCondition_proxy () = default;

    bool
    get_trigger_value () override;

    ::DDS::StatusMask
    get_enabled_statuses () override;

    ::DDS::ReturnCode_t
    set_enabled_statuses (
      ::DDS::StatusMask mask) override;

    IDL::traits< ::DDS::Entity>::ref_type
    get_entity () override;

  private:
    DDS_StatusCondition_proxy() = delete;
    DDS_StatusCondition_proxy(const DDS_StatusCondition_proxy&) = delete;
    DDS_StatusCondition_proxy(DDS_StatusCondition_proxy&&) = delete;
    DDS_StatusCondition_proxy& operator=(const DDS_StatusCondition_proxy&) = delete;
    DDS_StatusCondition_proxy& operator=(DDS_StatusCondition_proxy&&) = delete;
  };
}

#endif /* DDSX11_IMPL_STATUS_CONDITION_H_ */
