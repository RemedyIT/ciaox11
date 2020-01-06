// -*- C++ -*-
/**
 * @file    dds4ccm_facet_base_t.cpp
 * @author  Marcel Smit
 *
 * @brief   Base class for facets. This will keep a reference to the component
 *          which 'manages' the facet.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#include "dds4ccm/impl/dds4ccm_facet_base_t.h"

#include "dds4ccm/logger/dds4ccm_log.h"

namespace CIAOX11
{
  namespace DDS4CCM
  {
    template<typename BASE_TYPE>
    FacetBase<BASE_TYPE>::FacetBase (IDL::traits<CORBA::Object>::weak_ref_type component)
      : component_ (component)
    {
    }

    template<typename BASE_TYPE>
    FacetBase<BASE_TYPE>::~FacetBase ()
    {
    }

    template<typename BASE_TYPE>
    IDL::traits<CORBA::Object>::ref_type
    FacetBase<BASE_TYPE>::_get_component ()
    {
      return this->component_.lock ();
    }
  }
}
