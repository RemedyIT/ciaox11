// -*- C++ -*-
/**
 * @file    dds_condition.h
 * @author  Marcel Smit
 *
 * @brief   Wrapper facade for DDS
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDSX11_IMPL_CONDITION_H_
#define DDSX11_IMPL_CONDITION_H_

#include "dds/dds_export.h"
#include "dds/dds_native_entity_t.h"
#include "idl/dds_dcpsC.h"
#include "dds/dds_proxy_traits_t.h"

#if !defined (DDSX11_HAS_VENDOR_TYPEDEFS)
namespace DDS_Native {
  namespace DDS {
    class Condition;
  }
}
#endif /* DDSX11_HAS_VENDOR_TYPEDEFS */

namespace DDSX11
{
  class DDSX11_IMPL_Export DDS_Condition_proxy final
    : public virtual IDL::traits<::DDS::Condition>::base_type
    , public virtual NativeEntityBase_T<DDS_Native::DDS::Condition>
  {
  public:
    /// Constructor
    explicit DDS_Condition_proxy (DDS_Native::DDS::Condition * condition);

    /// Destructor
    ~DDS_Condition_proxy () override = default;

    bool get_trigger_value () override;
  private:
    DDS_Condition_proxy() = delete;
    DDS_Condition_proxy(const DDS_Condition_proxy&) = delete;
    DDS_Condition_proxy(DDS_Condition_proxy&&) = delete;
    DDS_Condition_proxy& operator=(const DDS_Condition_proxy&) = delete;
    DDS_Condition_proxy& operator=(DDS_Condition_proxy&&) = delete;
  };

  using condition_trait = entity_traits< ::DDS::Condition, DDS_Condition_proxy, DDS_Native::DDS::Condition>;
} /* DDS_X11 */

#endif /* DDSX11_IMPL_CONDITION_H_ */
