// -*- C++ -*-
/**
 * @file    dds4ccm_coherent_changes_guard.cpp
 * @author  Marcel Smit
 *
 * @brief   Start and end of coherent changes.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
#include "dds4ccm/impl/dds4ccm_coherent_changes_guard.h"

namespace CIAOX11
{
  namespace DDS4CCM
  {
    Coherent_Changes_Guard::Coherent_Changes_Guard (
      IDL::traits< ::DDS::Publisher >::ref_type publisher,
      bool coherent_write)
      : publisher_ (std::move(publisher))
      , coherent_write_ (coherent_write)
    {
      if (this->coherent_write_)
      {
        this->publisher_->begin_coherent_changes ();
      }
    }

    Coherent_Changes_Guard::~Coherent_Changes_Guard ()
    {
      if (this->coherent_write_)
      {
        this->publisher_->end_coherent_changes ();
      }
    }
  }
}
