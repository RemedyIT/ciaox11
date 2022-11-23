/**
 * @file   ciaox11_exf_connection_handler.cpp
 * @author Martin Corino
 *
 * @brief ExF connection handling logic for components.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#include "exf/deployment/handlers/ciaox11_exf_connection_handler.h"

#include "exf/deployment/core/ciaox11_schedule.h"
#include "ciaox11/deployment/handlers/ciaox11_handler_common.h"
#include "ciaox11/logger/log.h"
#include "dancex11/deployment/deployment_invalidconnectionC.h"
#include "ciaox11/config/ciaox11_config_valuesC.h"
#include "ciaox11/deployment/handlers/ciaox11_state.h"

namespace CIAOX11
{
  namespace ExF
  {
    static bool
    check_exf_property (const Components::ConfigValue& cval,
                        const std::string& property_key,
                        const std::string& port_id,
                        DAnCEX11::Utility::PROPERTY_MAP& props)
    {
      CIAOX11_LOG_DEBUG ("ExF::check_exf_property - " <<
                         "checking config value " << cval.name () <<
                         " for port " << port_id <<
                         " against property " << property_key);

      // check if config value id matches property key
      if (cval.name ().compare (0, property_key.size (), property_key) == 0)
      {
        // check for decoration(s)
        if (cval.name ().size () == property_key.size ())
        {
          CIAOX11_LOG_DEBUG ("ExF::check_exf_property - " <<
                             "default found for property " << property_key);

          // undecorated; default setting
          props[property_key] = cval.value ();
        }
        else
        {
          // check for decoration with port name
          if (cval.name ().compare (property_key.size ()+1, port_id.size (), port_id) == 0 &&
              (cval.name ().size () == property_key.size ()+1+port_id.size () ||
                  cval.name ()[property_key.size ()+1+port_id.size ()] == '.'))
          {
            // check for additional decoration with event id
            if (cval.name ().size () > (property_key.size ()+1+port_id.size ()))
            {
              CIAOX11_LOG_DEBUG ("ExF::check_exf_property - " <<
                                 "setting for event '" <<
                                 cval.name ().substr(property_key.size ()+2+port_id.size ()) <<
                                 "' found for property " << property_key);

              // store as event specific setting
              std::string prop_id = property_key +
                                    cval.name ().substr(property_key.size ()+1+port_id.size ());
              props[prop_id] = cval.value ();
            }
            else
            {
              CIAOX11_LOG_DEBUG ("ExF::check_exf_property - " <<
                                 "connection default found for property " << property_key);

              // connection default; set as default (overwriting general default)
              props[property_key] = cval.value ();
            }
          }
          else if (cval.name ().find ('.', property_key.size ()+1) == std::string::npos)
          {
            // could be event specific default (copy as is)
            props[cval.name ()] = cval.value ();
          }
          // else skip; must be for other port/connection
        }
        return true;
      }
      return false;
    }

    void
    Connection_Handler::connect_local_port (const ::Deployment::DeploymentPlan & plan,
                                            const ::Deployment::PlanConnectionDescription &conn,
                                            uint32_t endpointRef,
                                            const ::Deployment::PlanSubcomponentPortEndpoint &receptacle_endpoint,
                                            const CORBA::Any & provided_reference)
    {
      CIAOX11_LOG_DEBUG ("ExF::Connection_Handler::connect_local_port - " <<
                         "Connecting connection <" << conn.name () <<
                         ">:<" << plan.instance ()[receptacle_endpoint.instanceRef ()].name () << ">");

      uint32_t facet_endpointRef = (endpointRef + 1) % 2;
      if (!(receptacle_endpoint.kind () == Deployment::CCMComponentPortKind::SimplexReceptacle ||
                receptacle_endpoint.kind () == Deployment::CCMComponentPortKind::MultiplexReceptacle) ||
            conn.internalEndpoint ()[facet_endpointRef].kind () != Deployment::CCMComponentPortKind::Facet)
      {
        CIAOX11_LOG_ERROR ("ExF::Connection_Handler::connect_local_port - " <<
                           "Wrong endpoints for <" << conn.name () << ">");

        throw ::Deployment::InvalidConnection (conn.name (),
                                               "Local connections requires a receptacle and a facet");
      }

      const ::Deployment::PlanSubcomponentPortEndpoint &facet_endpoint =
        conn.internalEndpoint ()[facet_endpointRef];

      CIAOX11_LOG_DEBUG ("ExF::Connection_Handler::connect_local_port - "\
                         "Connecting <" << plan.instance ()[facet_endpoint.instanceRef ()].name () <<
                           ":" << facet_endpoint.portName () << "> "\
                         "to <" << plan.instance ()[receptacle_endpoint.instanceRef ()].name () <<
                           ":" << receptacle_endpoint.portName () << ">");

      // Get exec locator for user component
      const std::string &user_instance =
           plan.instance ()[receptacle_endpoint.instanceRef ()].name ();
      IDL::traits<CIAOX11::ExecutorLocator>::ref_type user_exec_locator =
            fetch_component (user_instance);

      if (!user_exec_locator)
      {
        CIAOX11_LOG_ERROR ("Container_i::connect_local_facet - "\
                           "Unable to find executor locator for component " <<
                           plan.instance ()[receptacle_endpoint.instanceRef ()].name ());

        throw ::Deployment::InvalidConnection (conn.name (),
                                               "Receptacle component not deployed.");
      }

      // Get exec locator for provider component
      const std::string &provider_instance =
          plan.instance ()[facet_endpoint.instanceRef ()].name ();
      IDL::traits<CIAOX11::ExecutorLocator>::ref_type provider_exec_locator =
          fetch_component (provider_instance);

      if (!provider_exec_locator)
      {
        throw ::Deployment::InvalidConnection (conn.name (), "Cannot locate facet executor locator");
      }

      // setup connection properties
      DAnCEX11::Utility::PROPERTY_MAP connection_props;
      Components::ConfigValues conn_config;

      // Retrieve the user component's configuration
      fetch_component_configuration (user_instance, conn_config);

      // import all ExF properties for this connection and all other (non-ExF) properties
      for (const Components::ConfigValue& cval : conn_config)
      {
        if (!check_exf_property (cval,
                                 ExF::SCHEDULING_PRIORITY,
                                 receptacle_endpoint.portName (),
                                 connection_props)
            &&
            !check_exf_property (cval,
                                 ExF::SCHEDULING_DEADLINE_TYPE,
                                 receptacle_endpoint.portName (),
                                 connection_props)
            &&
            !check_exf_property (cval,
                                 ExF::SCHEDULING_DEADLINE_TIME,
                                 receptacle_endpoint.portName (),
                                 connection_props))
        {
          // other properties just copy
          connection_props[cval.name ()] = cval.value ();
        }
      }

      // Retrieve the provider component's configuration
      conn_config.clear ();
      fetch_component_configuration (provider_instance, conn_config);

      // import all ExF properties for this connection and all other (non-ExF) properties
      for (const Components::ConfigValue& cval : conn_config)
      {
        if (!check_exf_property (cval,
                                 ExF::SCHEDULING_PRIORITY,
                                 facet_endpoint.portName (),
                                 connection_props)
            &&
            !check_exf_property (cval,
                                 ExF::SCHEDULING_DEADLINE_TYPE,
                                 facet_endpoint.portName (),
                                 connection_props)
            &&
            !check_exf_property (cval,
                                 ExF::SCHEDULING_DEADLINE_TIME,
                                 facet_endpoint.portName (),
                                 connection_props))
        {
          // other properties just copy
          connection_props[cval.name ()] = cval.value ();
        }
      }

      // add the connection properties
      connection_props[CIAOX11::PEER_ENDPOINT_REFERENCE] = provided_reference;
      CORBA::Any eptype;
      eptype <<= CIAOX11::INTERNAL_ENDPOINT;
      connection_props[CIAOX11::PEER_ENDPOINT_TYPE] = eptype;
      CORBA::Any epport;
      epport <<= facet_endpoint.portName ();
      connection_props[CIAOX11::PEER_ENDPOINT_PORT] = epport;

      // collect merged set
      conn_config.clear ();
      Deployment_Common::collect_config_values (connection_props, conn_config);

      // Get the local facet from the provider component
      IDL::traits<CORBA::Object>::ref_type facet_ref =
          provider_exec_locator->obtain_facet_executor (facet_endpoint.portName (),
                                                        conn_config);
      if (!facet_ref)
      {
        // either a provided facet reference or the local executor reference should be available
        CIAOX11_LOG_ERROR ("ExF::Connection_Handler::connect_local_port - " <<
                           "Unable to retrieve local facet executor reference from executor locator for facet <" << facet_endpoint.portName () << ">");
        throw ::Deployment::InvalidConnection (conn.name (),
                                               "Unable to retrieve local facet executor reference from executor locator.");
      }

      // connect the component's receptacle to the facet executor
      if (!user_exec_locator->connect (receptacle_endpoint.portName (),
                                       facet_ref,
                                       conn.name (),
                                       conn_config))
      {
        throw ::Deployment::InvalidConnection (conn.name (),
                                               "Local connect failed.");
      }

#if defined (CIAOX11_PRE_ESTABLISH_CONNECTIONS)
      this->validate_connection(conn.name (), facet);
#endif

      CIAOX11_LOG_DEBUG ("ExF::Connection_Handler::connect_local_port - " <<
                         "Connected <" << plan.instance ()[facet_endpoint.instanceRef ()].name () << ">"\
                           ":<" << facet_endpoint.portName () << "> "\
                         "to <" << plan.instance ()[receptacle_endpoint.instanceRef ()].name () << ">"\
                           ":<" << receptacle_endpoint.portName () << ">");
    }
  }

}
