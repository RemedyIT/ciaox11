// -*- C++ -*-
/**
 * @file    dds4ccm_facet_base_t.h
 * @author  Marcel Smit
 *
 * @brief   Base class for facets. This will keep a reference to the component
 *          which 'manages' the facet.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
#ifndef DDS4CCM_FACET_BASE_H_
#define DDS4CCM_FACET_BASE_H_

#include "dds4ccm/impl/dds4ccm_impl_export.h"
#include "tao/x11/object.h"

namespace CIAOX11
{
  namespace DDS4CCM
  {
    template<typename BASE_TYPE>
    class FacetBase
      : public virtual ::IDL::traits< BASE_TYPE >::base_type
    {
    public:
      explicit FacetBase (IDL::traits< CORBA::Object >::weak_ref_type component);

      // using {} since using 'default' will cause an error with message:
      // internal compiler error: in use_thunk, at cp/method.c:338
      virtual ~FacetBase ();

      /**
       * Return the reference to the component which manages the facet.
       * Normally the CORBA infrastructure does this for facets, but
       * that doesn't work with a local interface, there CORBA will
       * throw an exception.
       * @return The component which manages the facet
       */
      IDL::traits<CORBA::Object >::ref_type
      _get_component () override;

    private:
      /**
       * Weak reference to the component which manages the facet. This
       * way we don't have a circular dependency and there is no
       * need to set this member to nil at the moment the component
       * is going to shutdown
       */
      IDL::traits< CORBA::Object >::weak_ref_type component_;

      FacetBase() = delete;
      FacetBase(const FacetBase&) = delete;
      FacetBase(FacetBase&&) = delete;
      FacetBase& operator=(const FacetBase&) = delete;
      FacetBase& operator=(FacetBase&&) = delete;
    };
  }
}

#include "dds4ccm/impl/dds4ccm_facet_base_t.cpp"

#endif /* DDS4CCM_FACET_BASE_H_ */
