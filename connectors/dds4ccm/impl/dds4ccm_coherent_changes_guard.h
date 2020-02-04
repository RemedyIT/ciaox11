// -*- C++ -*-
/**
 * @file    dds4ccm_coherent_changes_guard.h
 * @author  Marcel Smit
 *
 * @brief   Start and end of coherent changes.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDS4CCM_COHERENT_CHANGES_GUARD_H_
#define DDS4CCM_COHERENT_CHANGES_GUARD_H_

#include "dds4ccm/impl/dds4ccm_impl_export.h"
#include "dds4ccm/idl/dds_rtf2_dcpsC.h"

namespace CIAOX11
{
  namespace DDS4CCM
  {
    /**
     * @name Coherent_Changes_Guard
     * @brief Guard class which calls begin_coherent_changes() on
     *        construction and end_coherent_changes() at destruction
     */
    class DDS4CCM_IMPL_Export Coherent_Changes_Guard
    {
    public:
      Coherent_Changes_Guard (
        IDL::traits< ::DDS::Publisher >::ref_type publisher,
        bool coherent_write);
      ~Coherent_Changes_Guard ();

    private:
      IDL::traits< ::DDS::Publisher >::ref_type publisher_;
      bool const coherent_write_;

      Coherent_Changes_Guard() = delete;
      Coherent_Changes_Guard(const Coherent_Changes_Guard&) = delete;
      Coherent_Changes_Guard(Coherent_Changes_Guard&&) = delete;
      Coherent_Changes_Guard& operator=(const Coherent_Changes_Guard&) = delete;
      Coherent_Changes_Guard& operator=(Coherent_Changes_Guard&&) = delete;
    };
  }
}

#endif /* DDS4CCM_COHERENT_CHANGES_GUARD_H_ */
