// -*- C++ -*-
/**
 * @file    dds_wait_set.cpp
 * @author  Marcel Smit
 *
 * @brief   Wrapper facade for DDS
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#include "dds/dds_common.h"
#include "dds/dds_wait_set.h"
#include "dds/dds_condition.h"
#include "dds/dds_query_condition.h"
#include "dds/dds_read_condition.h"
#include "logger/ddsx11_log.h"
#include "dds/dds_vendor_conversion_traits.h"

namespace DDSX11
{
  DDS_WaitSet_proxy::DDS_WaitSet_proxy (DDS_Native::DDS::WaitSet* waitset)
    : NativeEntityBase_T<DDS_Native::DDS::WaitSet>(waitset)
  {
    DDSX11_LOG_TRACE ("DDS_WaitSet_proxy::DDS_WaitSet_proxy");
  }

  DDS_WaitSet_proxy::~DDS_WaitSet_proxy ()
  {
#if (DDSX11_NDDS==1)
   // Since this is the only DDS Entity that need to be created as a pointer
    // (its not created by DDS), we need to manually remove it here.
    // The native pointer will be deleted once save goes out of scope.
    std::unique_ptr<DDS_Native::DDS::WaitSet> save (this->get_native_entity ());
    X11_UNUSED_ARG (save);
#endif
  }

  ::DDS::ReturnCode_t
  DDS_WaitSet_proxy::wait (
    ::DDS::ConditionSeq & /*active_conditions*/,
    const ::DDS::Duration_t & timeout)
  {
    DDSX11_LOG_TRACE ("DDS_WaitSet_proxy::wait");

    // active_conditions are NOT used in DDS4CCM. For now, leaving this.
    // See issue #3420
    DDS_Native::DDS::ConditionSeq native_seq;
    ::DDS::ReturnCode_t const retcode =
      ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
        this->native_entity ()->wait (
          native_seq, ::DDSX11::traits< ::DDS::Duration_t>::in (timeout)));

    return retcode;
  }

  ::DDS::ReturnCode_t
  DDS_WaitSet_proxy::attach_condition (
    IDL::traits< ::DDS::Condition>::ref_type cond)
  {
    DDSX11_LOG_TRACE ("DDS_WaitSet_proxy::attach_condition");

    IDL::traits< ::DDS::ReadCondition>::ref_type rc_cond =
      IDL::traits< ::DDS::ReadCondition>::narrow (cond);
    IDL::traits< ::DDS::QueryCondition>::ref_type qc_cond =
      IDL::traits< ::DDS::QueryCondition>::narrow (cond);

    if (qc_cond)
      {
        return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
          this->native_entity ()->attach_condition (
            query_condition_trait::native (qc_cond)));
      }
    else if (rc_cond)
      {
        return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
          this->native_entity ()->attach_condition (
            read_condition_trait::native (rc_cond)));
      }
    return ::DDS::RETCODE_BAD_PARAMETER;
  }

  ::DDS::ReturnCode_t
  DDS_WaitSet_proxy::detach_condition (
    IDL::traits< ::DDS::Condition>::ref_type cond)
  {
    DDSX11_LOG_TRACE ("DDS_WaitSet_proxy::detach_condition");

    IDL::traits< ::DDS::ReadCondition>::ref_type rc_cond =
      IDL::traits< ::DDS::ReadCondition>::narrow (cond);
    IDL::traits< ::DDS::QueryCondition>::ref_type qc_cond =
      IDL::traits< ::DDS::QueryCondition>::narrow (cond);

    if (qc_cond)
      {
        return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
          this->native_entity ()->detach_condition (
            query_condition_trait::native (qc_cond)));
      }
    else if (rc_cond)
      {
        return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
          this->native_entity ()->detach_condition (
            read_condition_trait::native (rc_cond)));
      }
    DDSX11_IMPL_LOG_ERROR ("DDS_WaitSet_proxy::detach_condition - "
      "Unable to narrow the given condition to a ReadCondition "
      "nor a QueryCondition.");

    return ::DDS::RETCODE_BAD_PARAMETER;
  }

  ::DDS::ReturnCode_t
  DDS_WaitSet_proxy::get_conditions (
    ::DDS::ConditionSeq & /*attached_conditions*/)
  {
    DDSX11_LOG_TRACE ("DDS_WaitSet_proxy::get_conditions");

    // get_conditions is NOT used in DDS4CCM. For now, leaving this.
    // See issue #3420
    DDS_Native::DDS::ConditionSeq native_seq;

    return ::DDSX11::traits< ::DDS::ReturnCode_t>::retn (
      this->native_entity ()->get_conditions (native_seq));
  }
}
