/**
 * @file   ciaox11_corba_util.cpp
 * @author Martin Corino
 *
 * @brief CIAOX11 CORBA deployment utility methods
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#include "ciaox11_corba_util.h"
#include "ciaox11/config/ciaox11_config_util.h"
#include "ciaox11/config/ciaox11_config_valuesC.h"
#include "ccm/ccm_objectC.h"
#include "ciaox11/logger/log.h"

#include <string>

namespace CIAOX11
{
  namespace Corba
  {
    namespace Utility
    {
      IDL::traits<CORBA::Object>::ref_type
      get_provider_reference (const Components::ConfigValues& cfgval)
      {
        CIAOX11_LOG_INFO ("CORBA::Utility::get_provider_reference - "
                            "retrieving provider reference");

        CORBA::Any cvalue;

        // Extract provided peer endpoint reference
        if (!Config::Utility::find_config_value (cfgval, CIAOX11::PEER_ENDPOINT_REFERENCE, cvalue))
        {
          CIAOX11_LOG_ERROR ("CORBA::Utility::get_provider_reference - "
                              "missing peer endpoint reference");
          return {};
        }
        IDL::traits<CORBA::Object>::ref_type peer_ref;
        if (!(cvalue >>= peer_ref))
        {
          CIAOX11_LOG_ERROR ("CORBA::Utility::get_provider_reference - "
                              "unable to extract peer endpoint reference");
          return {};
        }

        // Determine peer endpoint type
        if (!Config::Utility::find_config_value (cfgval, CIAOX11::PEER_ENDPOINT_TYPE, cvalue))
        {
          CIAOX11_LOG_ERROR ("CORBA::Utility::get_provider_reference - "
                              "unable to determine endpoint type");
          return {};
        }
        uint32_t eptype {};
        if (!(cvalue >>= eptype))
        {
          CIAOX11_LOG_ERROR ("CORBA::Utility::get_provider_reference - "
                              "unable to extract endpoint type value");
          return {};
        }

        CIAOX11_LOG_INFO ("CORBA::Utility::get_provider_reference - "
                           "found endpoint type " <<
                           (eptype == CIAOX11::INTERNAL_ENDPOINT ?
                               "INTERNAL ENDPOINT" : (eptype == CIAOX11::EXTERNAL_ENDPOINT ?
                                               "EXTERNAL ENDPORT" : "EXTERNAL REFERENCE")) <<
                           " with peer reference <" << peer_ref << ">");

        // in case of an internal endpoint the provided reference should be
        // the facet provider reference
        if (eptype != CIAOX11::INTERNAL_ENDPOINT)
        {
          // otherwise we expect either a CCMObject reference and a port name
          // or the facet provider reference to determine which we attempt to
          // narrow to CCMObject
          IDL::traits<Components::CCMObject>::ref_type facet_provider =
            IDL::traits<Components::CCMObject>::narrow (peer_ref);
          if (facet_provider)
          {
            // if we were provided with a CCMObject reference we need a port name
            // to retrieve the facet reference
            if (!Config::Utility::find_config_value (cfgval, CIAOX11::PEER_ENDPOINT_PORT, cvalue))
            {
              CIAOX11_LOG_ERROR ("CORBA::Utility::get_provider_reference - "
                                 "missing peer endpoint port name");
              return {};
            }
            std::string epport;
            if (!(cvalue >>= epport))
            {
              CIAOX11_LOG_ERROR ("CORBA::Utility::get_provider_reference - "
                                 "unable to extract peer endpoint port name");
              return {};
            }
            if (epport.empty())
            {
              CIAOX11_LOG_ERROR ("CORBA::Utility::get_provider_reference - "
                                 "received an empty port name");
              return {};
            }
            // query the facet provider for the facet reference
            CORBA::Any refval;
            try
            {
              CIAOX11_LOG_DEBUG ("CORBA::Utility::get_provider_reference - " <<
                                 "Calling provide facet <" << epport << ">");
              facet_provider->provide_facet (epport, refval);
            }
            catch (const Components::InvalidName &ex)
            {
              CIAOX11_LOG_ERROR ("CORBA::Utility::get_provider_reference - failed for facet <" << epport
                                  << "> with exception <" <<  ex << ">");
              return {};
            }
            // extract the facet reference
            if (!(refval >>= peer_ref))
            {
              CIAOX11_LOG_ERROR ("CORBA::Utility::get_provider_reference - "
                                  "unable to extract provided facet reference");
              return {};
            }
          }
          // else we assume the provided reference is the facet reference
        }

        return peer_ref;
      }
    }
  }
}
