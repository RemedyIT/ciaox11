// -*- C++ -*-
/**
 * @file    dds_wait_set.h
 * @author  Marcel Smit
 *
 * @brief   Wrapper facade for DDS
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDSX11_IMPL_WAIT_SET_H_
#define DDSX11_IMPL_WAIT_SET_H_

#include "dds/dds_export.h"
#include "dds/dds_native_entity_t.h"
#include "idl/dds_dcpsC.h"
#include "dds/dds_proxy_traits_t.h"

namespace DDSX11
{
  /**
    * @class DDS_WaitSet_i
    *
    * @brief   Wrapper facade for DDS Representative (proxy) class for the waitset.
    *
    * Implementation of the waitset functionality.
    */
  class DDSX11_IMPL_Export DDS_WaitSet_proxy final
    : public virtual IDL::traits< ::DDS::WaitSet>::base_type
    , public virtual NativeEntityBase_T<DDS_Native::DDS::WaitSet>
  {

  public:
    /// Constructor
    DDS_WaitSet_proxy ();

    /// Destructor
    virtual ~DDS_WaitSet_proxy ();

    /**
      * Waits for DDS until the attached read/query conditions are met
      * or when a timeout occurs.
      *
      * active_conditions will contain conditions DDS has found.
      */
    virtual ::DDS::ReturnCode_t
    wait (
      ::DDS::ConditionSeq & active_conditions,
      const ::DDS::Duration_t & timeout) override;

    /**
      * Attaches a condition to the waitset. 'wait' will be waiting for
      * this condition.
      */
    virtual ::DDS::ReturnCode_t
    attach_condition (
      IDL::traits< ::DDS::Condition>::ref_type cond) override;

    /**
      * Detaches a condition from the waitset. 'wait' won't be waiting
      * for this condition anymore.
      */
    virtual ::DDS::ReturnCode_t
    detach_condition (
      IDL::traits< ::DDS::Condition>::ref_type cond) override;

    /**
      * Retrieves a list of attached conditions.
      */
    virtual ::DDS::ReturnCode_t
    get_conditions (
      ::DDS::ConditionSeq & attached_conditions) override;

  private:
    DDS_WaitSet_proxy(const DDS_WaitSet_proxy&) = delete;
    DDS_WaitSet_proxy(DDS_WaitSet_proxy&&) = delete;
    DDS_WaitSet_proxy& operator=(const DDS_WaitSet_proxy&) = delete;
    DDS_WaitSet_proxy& operator=(DDS_WaitSet_proxy&&) = delete;
  };
}

#endif /* DDSX11_IMPL_WAIT_SET_H_ */
