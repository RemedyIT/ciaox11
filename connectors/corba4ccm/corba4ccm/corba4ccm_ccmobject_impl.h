/**
 * @file    corba4ccm_ccmobject_impl.h
 * @author  Johnny Willemsen
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#ifndef CIAOX11_CORBA4CCM_CCMOBJECT_IMPL_H
#define CIAOX11_CORBA4CCM_CCMOBJECT_IMPL_H

#include /**/ "ace/pre.h"

#include "ccm/ccm_objectS.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "connectors/corba4ccm/corba4ccm/corba4ccm_stub_export.h"

namespace CCM_CORBA
{
  /**
   * @class CCMObject_impl
   *
   * Servant implementation of CCMObject. It
   * holds a reference to the POA and the unique component id.
   * It uses the CORBA POA to retrieve the needed CORBA facet
   * servant.
   */
  class CORBA4CCM_STUB_Export CCMObject_impl final
    : public CORBA::servant_traits<Components::CCMObject>::base_type
  {
  public:
    /**
     * Constructor
     * @param poa The POA on which this servant is going to be activated,
     * this POA will also be used to activate all CORBA facet servants
     * related to this component
     * @param name The unique name of this component
     */
    CCMObject_impl (
      IDL::traits<PortableServer::POA>::ref_type poa,
      std::string component_name);

    /// Destructor
    virtual ~CCMObject_impl () override = default;

    /**
     * Retrieve the CORBA facet servant for the provided facet name.
     * When no facet servant can be found a Components::InvalidName() exception
     * will be thrown
     */
    void provide_facet (const std::string& facet_name, CORBA::Any& facet_ref) override;

  private:
    //@{
    /** Illegal to be called. Deleted explicitly to let the compiler detect any violation */
    CCMObject_impl () = delete;
    CCMObject_impl (const CCMObject_impl&) = delete;
    CCMObject_impl (CCMObject_impl&&) = delete;
    CCMObject_impl& operator= (const CCMObject_impl& x) = delete;
    CCMObject_impl& operator= (CCMObject_impl&& x) = delete;
    //@}

  private:
    /// The POA on which this servant is going to be activated
    IDL::traits<PortableServer::POA>::ref_type poa_;
    /// The unique name of this component
    std::string component_name_;
  };
}

#include /**/ "ace/post.h"

#endif /* CIAOX11_CORBA4CCM_CCMOBJECT_IMPL_H */
