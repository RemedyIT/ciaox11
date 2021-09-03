/**
 * @file    ciaox11_connection_handler.cpp
 * @author Johnny Willemsen, Martin Corino
 *
 * @brief Common connection handling logic for components.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#include "ciaox11_connection_handler.h"
#include "ciaox11_handler_common.h"
#include "ciaox11/logger/log.h"
#include "dancex11/deployment/deployment_invalidconnectionC.h"
#include "ciaox11/deployment/handlers/ciaox11_state.h"
#include "ciaox11/config/ciaox11_config_valuesC.h"

namespace CIAOX11
{
  void
  Connection_Handler::provide_endpoint_reference (const Deployment::DeploymentPlan & plan,
                                                  uint32_t connectionRef,
                                                  CORBA::Any& endpoint_reference)
  {
    Deployment::PlanConnectionDescription const &conn = plan.connection ()[connectionRef];

    CIAOX11_LOG_DEBUG ("Connection_Handler::provide_endpoint_reference - " <<
                       "Getting reference for  <" << conn.name () << ">");

    try
    {
      // we also collect references for local connection setup as these might be needed
      // for certain collocated setups

      // collect references for provider (facet) endpoints in the connections
      for (Deployment::PlanSubcomponentPortEndpoints::size_type i = 0;
           i < conn.internalEndpoint ().size ();
           ++i)
      {
        Deployment::PlanSubcomponentPortEndpoint const & port_endpoint = conn.internalEndpoint ()[i];
        if (port_endpoint.provider ())
        {
          IDL::traits<CORBA::Object>::ref_type ref;

          std::string const component_name = plan.instance ()[port_endpoint.instanceRef ()].name ();

          IDL::traits<Components::CCMObject>::ref_type ccm_object =
            Deployment_Common::get_ccm_object (component_name);

          if (!ccm_object)
          {
            CIAOX11_LOG_INFO ("Connection_Handler::provide_endpoint_reference - " <<
                              "Nil reference for component <" << component_name << ">");
            // it is not mandatory (anymore) for components to provide a ccm_object reference
            // this is currently only provided by components providing CORBA facets
          }
          else
          {
            switch (port_endpoint.kind ())
            {
              case Deployment::CCMComponentPortKind::Facet:
                CIAOX11_LOG_DEBUG ("Connection_Handler::provide_endpoint_reference - " <<
                                  "Calling provide facet for <" << conn.name () << ">:<" << port_endpoint.portName () << ">");

                ccm_object->provide_facet (port_endpoint.portName (), endpoint_reference);
                break;

              default:
                // should actually never happen as we already checked this to be a provider endpoint
                // and we currently only support facet providers
                throw ::Deployment::InvalidConnection (conn.name (),
                                                       "Invalid provider port type.");
            }
          }
          return;
        }
      }
    }
    catch (const ::Deployment::InvalidConnection &)
    {
      // pass through
      throw;
    }
    catch (const CORBA::Exception &ex)
    {
      std::ostringstream err;
      err << ex;
      CIAOX11_LOG_ERROR ("Connection_Handler::provide_endpoint_reference - " <<
                         "Caught CORBA exception <" << conn.name () << ">:<" << err.str () << ">");
      throw ::Deployment::InvalidConnection (conn.name (), err.str ());
    }
    catch (const std::exception &ex)
    {
      CIAOX11_LOG_ERROR ("Component_Handler::provide_endpoint_reference - " <<
                         "Caught C++ std::exception <" << conn.name () << ">:<" <<
                         ex << ">");
      throw ::Deployment::InvalidConnection (conn.name (), ex.what ());
    }
    catch (...)
    {
      CIAOX11_LOG_ERROR ("Connection_Handler::provide_endpoint_reference - " <<
                         "Caught unknown C++ exception <" << conn.name () << ">");
      throw ::Deployment::InvalidConnection (conn.name (), "Unknown C++ exception whilst establishing connection");
    }
  }

  void
  Connection_Handler::connect_instance (const Deployment::DeploymentPlan & plan,
                                        uint32_t c_id,
                                        const CORBA::Any & provided_reference)
  {
    const ::Deployment::PlanConnectionDescription &conn =
      plan.connection ()[c_id];

    uint32_t const endpointRef = this->retrieve_endpoint (conn);

    const ::Deployment::PlanSubcomponentPortEndpoint &endpoint =
      conn.internalEndpoint ()[endpointRef];

    CIAOX11_LOG_DEBUG ("Connection_Handler::connect_instance - " <<
                       "Connecting " << IDL::traits< ::Deployment::CCMComponentPortKind>::write (endpoint.kind ())
                       << " connection <" << conn.name () << ">:<" << plan.instance ()[endpoint.instanceRef ()].name () << ">");

    try
    {
      if (this->is_local_connection (plan, conn))
      {
        this->connect_local_port (plan, conn, endpointRef, endpoint,
                                  provided_reference);
      }
      else
      {
        switch (endpoint.kind ())
        {

          case Deployment::CCMComponentPortKind::Facet:
            if (!conn.externalReference().empty () || !conn.externalEndpoint ().empty ())
            {
              this->connect_non_local_facet (plan,
                                             conn,
                                             endpoint,
                                             provided_reference);
            }
            else
            {
              CIAOX11_LOG_DEBUG ("Connection_Handler::connect_instance - " <<
                         "Skipping Facet end of connection <" << conn.name () << ">");
            }
            break;

          case Deployment::CCMComponentPortKind::SimplexReceptacle:
          case Deployment::CCMComponentPortKind::MultiplexReceptacle:

            this->connect_non_local_receptacle (plan,
                                                conn,
                                                endpoint,
                                                provided_reference);
            break;

          default:
            CIAOX11_LOG_ERROR ("Connection_Handler::connect_instance - " <<
                       "Unsupported kind <"
                       << IDL::traits< ::Deployment::CCMComponentPortKind>::write (endpoint.kind ())
                       << "> for connection <" << conn.name () << ">");
            throw ::Deployment::InvalidConnection (conn.name (),
                                                 "Unsupported port type");

        }
      }
    }
    catch (const ::Deployment::InvalidConnection &ex)
    {
      CIAOX11_LOG_ERROR ("Connection_Handler::connect_instance - " <<
                         "Caught InvalidConnection exception while connecting "
                         << IDL::traits< ::Deployment::CCMComponentPortKind>::write (endpoint.kind ())
                         << " <" << conn.name () << ">:<" << ex << ">");
      throw;
    }
    catch (const CORBA::Exception &ex)
    {
      std::ostringstream err;
      err << ex;
      CIAOX11_LOG_ERROR ("Connection_Handler::connect_instance - " <<
                         "Caught CORBA exception while connecting "
                         << IDL::traits< ::Deployment::CCMComponentPortKind>::write (endpoint.kind ())
                         << " <" << conn.name () << ">:<" << err.str () << ">");
      throw ::Deployment::InvalidConnection (conn.name (), err.str ());
    }
    catch (const std::exception &ex)
    {
      CIAOX11_LOG_ERROR ("Component_Handler::connect_instance - " <<
                         "Caught C++ std::exception while connecting "
                         << IDL::traits< ::Deployment::CCMComponentPortKind>::write (endpoint.kind ())
                         << "<" << conn.name () << ">:<" <<
                         ex << ">");
      throw ::Deployment::InvalidConnection (conn.name (), ex.what ());
    }
    catch (...)
    {
      CIAOX11_LOG_ERROR ("Connection_Handler::connect_instance - " <<
                         "Caught unknown C++ exception while connecting "
                          << IDL::traits< ::Deployment::CCMComponentPortKind>::write (endpoint.kind ())
                          << " <" << conn.name () << ">");
      throw ::Deployment::InvalidConnection (conn.name (), "Unknown C++ Exception");
    }
  }

  void
  Connection_Handler::disconnect_instance (const ::Deployment::DeploymentPlan &plan,
                                           uint32_t c_id)
  {
    const ::Deployment::PlanConnectionDescription &conn =
      plan.connection ()[c_id];

    uint32_t endpointRef = this->retrieve_endpoint (conn);

    const ::Deployment::PlanSubcomponentPortEndpoint &endpoint =
      conn.internalEndpoint ()[endpointRef];

    CIAOX11_LOG_DEBUG ("Connection_Handler::disconnect_instance - " <<
                       "Disconnecting "
                       << IDL::traits< ::Deployment::CCMComponentPortKind>::write (endpoint.kind ())
                       << "connection <" << conn.name () << ">:<"
                       << plan.instance ()[endpoint.instanceRef ()].name () << ">");

    try
    {
      if (this->is_local_connection (plan, conn))
      {
        this->disconnect_local_port (plan, conn, endpointRef, endpoint);
      }
      else
      {
        switch (endpoint.kind ())
        {
          case Deployment::CCMComponentPortKind::Facet:
          case Deployment::CCMComponentPortKind::SimplexReceptacle:
          case Deployment::CCMComponentPortKind::MultiplexReceptacle:
            this->disconnect_non_local (plan, conn, endpoint, endpoint.portName ());
            break;

          default:
            CIAOX11_LOG_ERROR ("Connection_Handler::disconnect_instance - " <<
                       "Unsupported kind <"
                       << IDL::traits< ::Deployment::CCMComponentPortKind>::write (endpoint.kind ())
                       << "> for connection <" << conn.name () << ">");
            throw ::Deployment::InvalidConnection (conn.name (),
                                                   "Unsupported port type");

        }
      }
    }
    catch (const ::Deployment::InvalidConnection &)
    {
      // pass through
      throw;
    }
    // Since DANCE shuts down the Locality managers simultaneously,
    // it could be that one locality manager is shutdown while the
    // other wants to disconnect from this locality manager. Therefor
    // we catch an OBJECT_NOT_EXIST, TRANSIENT and a COMM_FAILURE at this point
    // Once DANCE has been fixed in that manner, these catches can be removed.
    catch (const CORBA::COMM_FAILURE &ex)
    {
      std::ostringstream err;
      err << ex;
      CIAOX11_LOG_ERROR ("Connection_Handler::disconnect_instance - " <<
                         "Caught COMM_FAILURE exception while disconnecting "
                         << IDL::traits< ::Deployment::CCMComponentPortKind>::write (endpoint.kind ())
                         << " <" << conn.name () << ">:<" << err.str () << ">");
      throw ::Deployment::InvalidConnection (conn.name (),
                                             err.str ());
    }
    catch (const CORBA::OBJECT_NOT_EXIST &ex)
    {
      std::ostringstream err;
      err << ex;
      CIAOX11_LOG_ERROR ("Connection_Handler::disconnect_instance - " <<
                         "Caught OBJECT_NOT_EXIST exception while disconnecting "
                         << IDL::traits< ::Deployment::CCMComponentPortKind>::write (endpoint.kind ())
                         << " <" << conn.name () << ">:<" << err.str () << ">");
      throw ::Deployment::InvalidConnection (conn.name (),
                                             err.str ());
    }
    catch (const CORBA::TRANSIENT &ex)
    {
      std::ostringstream err;
      err << ex;
      CIAOX11_LOG_ERROR ("Connection_Handler::disconnect_instance - " <<
                         "Caught TRANSIENT exception while disconnecting "
                         << IDL::traits< ::Deployment::CCMComponentPortKind>::write (endpoint.kind ())
                         << " <" << conn.name () << ">:<" << err.str () << ">");
      throw ::Deployment::InvalidConnection (conn.name (),
                                             err.str ());
    }
    catch (const CORBA::Exception &ex)
    {
      std::ostringstream err;
      err << ex;
      CIAOX11_LOG_ERROR ("Connection_Handler::disconnect_instance - " <<
                         "Caught CORBA exception while disconnecting "
                         << IDL::traits< ::Deployment::CCMComponentPortKind>::write (endpoint.kind ())
                         << " <" << conn.name () << ">:<" << err.str () << ">");
      throw ::Deployment::InvalidConnection (conn.name (), err.str ());
    }
    catch (const std::exception &ex)
    {
      CIAOX11_LOG_ERROR ("Component_Handler::disconnect_instance - " <<
                         "Caught C++ std::exception while connecting "
                         << IDL::traits< ::Deployment::CCMComponentPortKind>::write (endpoint.kind ())
                         << "<" << conn.name () << ">:<" <<
                         ex << ">");
      throw ::Deployment::InvalidConnection (conn.name (), ex.what ());
    }
    catch (...)
    {
      CIAOX11_LOG_ERROR ("Connection_Handler::disconnect_instance - " <<
                         "Caught unknown C++ exception while disconnecting "
                         << IDL::traits< ::Deployment::CCMComponentPortKind>::write (endpoint.kind ())
                         << " <" << conn.name () << ">");
      throw ::Deployment::InvalidConnection (conn.name (), "Unknown C++ Exception");
    }
  }
  // plan used for getting component name
  void
  Connection_Handler::connect_non_local_facet (const ::Deployment::DeploymentPlan & plan,
                                               const ::Deployment::PlanConnectionDescription &conn,
                                               const ::Deployment::PlanSubcomponentPortEndpoint &endpoint,
                                               const ::CORBA::Any & provided_reference)
  {
    CIAOX11_LOG_DEBUG ("Connection_Handler::connect_non_local_facet - "
                       "connection <" << conn.name () << ">:<" <<
                       plan.instance ()[endpoint.instanceRef ()].name () << ">");

    // the local endpoint is a facet and the peer
    // either an external reference or an external endpoint
    // this is a non-standard connection setup for which no standard
    // handling exists
    // only minimal checks are performed and actual handling is up to
    // interceptors and/or custom component connection handling

    std::string const component_name (plan.instance ()[endpoint.instanceRef ()].name ());
    IDL::traits<CIAOX11::ExecutorLocator>::ref_type executor_locator =
      fetch_component (component_name);

    if (!executor_locator)
    {
      throw ::Deployment::InvalidConnection (conn.name (), "Cannot locate facet executor locator");
    }

    // setup connection properties
    DAnCEX11::Utility::PROPERTY_MAP connection_props;
    Components::ConfigValues conn_config;

    // Retrieve the component's configuration
    fetch_component_configuration (component_name, conn_config);
    for (const Components::ConfigValue& cval : conn_config)
    {
      connection_props[cval.name ()] = cval.value ();
    }

    // add the connection properties
    connection_props[CIAOX11::PEER_ENDPOINT_REFERENCE] = provided_reference;
    CORBA::Any eptype;
    CORBA::Any epport;
    if (!conn.externalReference ().empty ())
    {
      eptype <<= CIAOX11::EXTERNAL_REFERENCE;
      epport <<= conn.externalReference ()[0].portName ();
    }
    else if (!conn.externalEndpoint ().empty ())
    {
      eptype <<= CIAOX11::EXTERNAL_ENDPOINT;
      epport <<= conn.externalEndpoint ()[0].portName ();
    }
    connection_props[CIAOX11::PEER_ENDPOINT_TYPE] = eptype;
    connection_props[CIAOX11::PEER_ENDPOINT_PORT] = epport;

    // collect merged set
    conn_config.clear ();
    Deployment_Common::collect_config_values (connection_props, conn_config);


    CIAOX11_LOG_DEBUG ("Connection_Handler::connect_non_local_facet - "
                       "connecting facet <" << endpoint.portName () <<
                       "> of <" << component_name << ">");

    // connect the component's receptacle to the facet executor
    if (!executor_locator->connect (endpoint.portName (),
                                    {},
                                    conn.name (),
                                    conn_config))
    {
      throw ::Deployment::InvalidConnection (conn.name (),
                                             "Connecting facet failed.");
    }

#if defined (CIAOX11_PRE_ESTABLISH_CONNECTIONS)
    this->validate_connection(conn.name (), provided);
#endif

    CIAOX11_LOG_DEBUG ("Connection_Handler::connect_non_local_facet - " <<
                       "Connection <" << conn.name () << "> created");
 }

  void
  Connection_Handler::connect_non_local_receptacle (const ::Deployment::DeploymentPlan & plan,
                                                    const ::Deployment::PlanConnectionDescription &conn,
                                                    const ::Deployment::PlanSubcomponentPortEndpoint &endpoint,
                                                    const ::CORBA::Any & provided_reference)
  {
    std::string const component_name = plan.instance ()[endpoint.instanceRef ()].name ();
    IDL::traits<CIAOX11::ExecutorLocator>::ref_type executor_locator =
        fetch_component (component_name);

    if (!executor_locator)
    {
      CIAOX11_LOG_ERROR ("Connection_Handler::connect_non_local_receptacle - " <<
                         "Nil executor locator reference for <" << conn.name () << ">:<" << component_name << ">");
      throw ::Deployment::InvalidConnection (conn.name (),
                                             "Receptacle component not deployed.");
    }

    // setup connection properties
    DAnCEX11::Utility::PROPERTY_MAP connection_props;
    Components::ConfigValues conn_config;

    // Retrieve the component's configuration
    fetch_component_configuration (component_name, conn_config);
    for (const Components::ConfigValue& cval : conn_config)
    {
      connection_props[cval.name ()] = cval.value ();
    }

    // add the connection properties
    connection_props[CIAOX11::PEER_ENDPOINT_REFERENCE] = provided_reference;
    CORBA::Any eptype;
    CORBA::Any epport;
    if (!conn.externalReference ().empty ())
    {
      eptype <<= CIAOX11::EXTERNAL_REFERENCE;
      epport <<= conn.externalReference ()[0].portName ();
    }
    else if (!conn.externalEndpoint ().empty ())
    {
      eptype <<= CIAOX11::EXTERNAL_ENDPOINT;
      epport <<= conn.externalEndpoint ()[0].portName ();
    }
    else // two internal endpoints
    {
      eptype <<= CIAOX11::INTERNAL_ENDPOINT;
      // in this case the provided reference is always assumed to be the
      // remote facet reference;
      // we cannot provide the facet port name here as that plan information
      // is not available here
    }
    connection_props[CIAOX11::PEER_ENDPOINT_TYPE] = eptype;
    connection_props[CIAOX11::PEER_ENDPOINT_PORT] = epport;

    // collect merged set
    conn_config.clear ();
    Deployment_Common::collect_config_values (connection_props, conn_config);

    CIAOX11_LOG_DEBUG ("Connection_Handler::connect_non_local_receptacle - "
                       "connecting receptacle <" << endpoint.portName () <<
                       "> of <" << component_name << ">");

    // connect the component's receptacle to the facet executor
    if (!executor_locator->connect (endpoint.portName (),
                                    {},
                                    conn.name (),
                                    conn_config))
    {
      throw ::Deployment::InvalidConnection (conn.name (),
                                             "Connecting receptacle failed.");
    }

#if defined (CIAOX11_PRE_ESTABLISH_CONNECTIONS)
    this->validate_connection(conn.name (), provided);
#endif

    CIAOX11_LOG_DEBUG ("Connection_Handler::connect_non_local_receptacle - " <<
                       "Connection <" << conn.name () << "> created");
  }

  // plan and endpoint used for getting component name
  // component name used to get executor locator
  void
  Connection_Handler::disconnect_non_local (const ::Deployment::DeploymentPlan & plan,
                                            const Deployment::PlanConnectionDescription &conn,
                                            const ::Deployment::PlanSubcomponentPortEndpoint &endpoint,
                                            const std::string& port_name)
  {
    CIAOX11_LOG_DEBUG ("Connection_Handler::disconnect_non_local - " <<
                       "Disconnecting connection <" << conn.name () << ">");

    std::string const component_name = plan.instance ()[endpoint.instanceRef ()].name ();
    IDL::traits<CIAOX11::ExecutorLocator>::ref_type executor_locator =
            fetch_component (component_name);

    if (!executor_locator)
    {
      CIAOX11_LOG_ERROR ("Connection_Handler::disconnect_non_local - " <<
                         "Nil executor locator reference for <" << conn.name () <<
                         ">:<" << component_name << ">");
      throw ::Deployment::InvalidConnection (conn.name (),
                                             "Nil executor locator reference.");
    }

    if (!executor_locator->disconnect (port_name,
                                       conn.name ()))
    {
      throw ::Deployment::InvalidConnection (conn.name (),
                                             "Disconnecting failed.");
    }
  }

  void
  Connection_Handler::connect_local_port (const ::Deployment::DeploymentPlan & plan,
                                          const ::Deployment::PlanConnectionDescription &conn,
                                          uint32_t endpointRef,
                                          const ::Deployment::PlanSubcomponentPortEndpoint &receptacle_endpoint,
                                          const ::CORBA::Any & provided_reference)
  {
    CIAOX11_LOG_DEBUG ("Connection_Handler::connect_local_port - " <<
                       "Connecting connection <" << conn.name () <<
                       ">:<" << plan.instance ()[receptacle_endpoint.instanceRef ()].name () << ">");

    uint32_t const facet_endpointRef = (endpointRef + 1) % 2;
    if (!(receptacle_endpoint.kind () == Deployment::CCMComponentPortKind::SimplexReceptacle ||
              receptacle_endpoint.kind () == Deployment::CCMComponentPortKind::MultiplexReceptacle) ||
          conn.internalEndpoint ()[facet_endpointRef].kind () != Deployment::CCMComponentPortKind::Facet)
    {
      CIAOX11_LOG_ERROR ("Connection_Handler::connect_local_port - " <<
                         "Wrong endpoints for <" << conn.name () << ">");

      throw ::Deployment::InvalidConnection (
          conn.name (),
          "Local connections require a receptacle and a facet");
    }

    const ::Deployment::PlanSubcomponentPortEndpoint &facet_endpoint =
      conn.internalEndpoint ()[facet_endpointRef];

    CIAOX11_LOG_DEBUG ("Connection_Handler::connect_local_port - " <<
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
      CIAOX11_LOG_ERROR ("Container_i::connect_local_port - " <<
                         "Unable to find executor locator for component " <<
                         user_instance);

      throw ::Deployment::InvalidConnection (
          conn.name (),
          "Receptacle component not deployed.");
    }

    // Get exec locator for provider component
    const std::string &provider_instance =
        plan.instance ()[facet_endpoint.instanceRef ()].name ();
    IDL::traits<CIAOX11::ExecutorLocator>::ref_type provider_exec_locator =
        fetch_component (provider_instance);

    if (!provider_exec_locator)
    {
      throw ::Deployment::InvalidConnection (
          conn.name (),
          "Cannot find executor locator");
    }

    // setup connection properties
    DAnCEX11::Utility::PROPERTY_MAP connection_props;
    Components::ConfigValues conn_config;

    // Retrieve the user component's configuration
    fetch_component_configuration (user_instance, conn_config);
    for (const Components::ConfigValue& cval : conn_config)
    {
      connection_props[cval.name ()] = cval.value ();
    }

    // Retrieve and merge the provider component's configuration
    // (provider properties overwrite user properties)
    conn_config.clear ();
    fetch_component_configuration (provider_instance, conn_config);

    for (const Components::ConfigValue& cval : conn_config)
    {
      connection_props[cval.name ()] = cval.value ();
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

    CIAOX11_LOG_DEBUG ("Connection_Handler::connect_local_port - " <<
                       "Retrieving local facet executor reference from executor locator for facet <" << facet_endpoint.portName () << ">");
    // Get the local facet executor for this connection from the provider component
    IDL::traits<CORBA::Object>::ref_type facet_ref =
        provider_exec_locator->obtain_facet_executor (facet_endpoint.portName (),
                                                      conn_config);
    if (!facet_ref)
    {
      // either a provided facet reference or the local executor reference should be available
      CIAOX11_LOG_ERROR ("Connection_Handler::connect_local_port - " <<
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
      throw ::Deployment::InvalidConnection (
          conn.name (),
          "Local connect failed.");
    }

#if defined (CIAOX11_PRE_ESTABLISH_CONNECTIONS)
    this->validate_connection(conn.name (), facet);
#endif

    CIAOX11_LOG_DEBUG ("Connection_Handler::connect_local_port - " <<
                       "Connected <" << plan.instance ()[facet_endpoint.instanceRef ()].name () << ">"\
                         ":<" << facet_endpoint.portName () << "> "\
                       "to <" << plan.instance ()[receptacle_endpoint.instanceRef ()].name () << ">"\
                         ":<" << receptacle_endpoint.portName () << ">");
  }

  void
  Connection_Handler::disconnect_local_port (const ::Deployment::DeploymentPlan & plan,
                                             const ::Deployment::PlanConnectionDescription &conn,
                                             uint32_t endpointRef,
                                             const ::Deployment::PlanSubcomponentPortEndpoint &receptacle_endpoint)
  {
    uint32_t facet_endpointRef = (endpointRef + 1) % 2;
    if (!(receptacle_endpoint.kind () == Deployment::CCMComponentPortKind::SimplexReceptacle ||
              receptacle_endpoint.kind () == Deployment::CCMComponentPortKind::MultiplexReceptacle) ||
          conn.internalEndpoint ()[facet_endpointRef].kind () != Deployment::CCMComponentPortKind::Facet)
    {
      CIAOX11_LOG_ERROR ("Connection_Handler::disconnect_local_port - " <<
                         "Wrong endpoints for <" << conn.name () << ">");

      throw ::Deployment::InvalidConnection (
          conn.name (),
          "Local connections require a receptacle and a facet");
    }

    const ::Deployment::PlanSubcomponentPortEndpoint &facet_endpoint =
      conn.internalEndpoint ()[facet_endpointRef];

    CIAOX11_LOG_DEBUG ("Connection_Handler::disconnect_local_port - " <<
                       "Disconnecting <" << plan.instance ()[facet_endpoint.instanceRef ()].name () <<
                         ":" << facet_endpoint.portName () << "> "\
                       "from <" << plan.instance ()[receptacle_endpoint.instanceRef ()].name () <<
                         ":" << receptacle_endpoint.portName () << ">");

    // Get exec locator for user component
    IDL::traits<CIAOX11::ExecutorLocator>::ref_type user_exec_locator =
          fetch_component (
              plan.instance ()[receptacle_endpoint.instanceRef ()].name ());

    if (!user_exec_locator)
    {
      CIAOX11_LOG_ERROR ("Container_i::disconnect_local_port - " <<
                         "Unable to find executor locator for component " <<
                         plan.instance ()[receptacle_endpoint.instanceRef ()].name ());

      throw ::Deployment::InvalidConnection (
          conn.name (),
          "Unable to find executor locator.");
    }

    // Disconnect the component's receptacle from the facet (executor) reference
    if (!user_exec_locator->disconnect (receptacle_endpoint.portName (),
                                        conn.name ()))
    {
      throw ::Deployment::InvalidConnection (
          conn.name (),
          "Local disconnect failed.");
    }

    CIAOX11_LOG_DEBUG ("Connection_Handler::disconnect_local_port - " <<
                       "Disconnected <" << plan.instance ()[facet_endpoint.instanceRef ()].name () << ">"\
                         ":<" << facet_endpoint.portName () << "> "\
                       "from <" << plan.instance ()[receptacle_endpoint.instanceRef ()].name () << ">"\
                         ":<" << receptacle_endpoint.portName () << ">");
  }

#if defined (CIAOX11_PRE_ESTABLISH_CONNECTIONS)
  void
  Connection_Handler::validate_connection (const std::string& conn,
                                           IDL::traits<CORBA::Object>::ref_type obj)
  {
    try
    {
      if (obj)
      {
        CORBA::PolicyList pl;
        if (obj->_validate_connection (pl))
        {
          CIAOX11_LOG_DEBUG ("Connection_Handler::validate_connection - " <<
                            "Validated connection <" << conn << ">");
        }
        else
        {
          CIAOX11_LOG_ERROR ("Connection_Handler::validate_connection - " <<
                            "Failed to validated connection <" << conn << ">");
        }
      }
    }
    catch (const ::CORBA::Exception &ex)
    {
//        ex._tao_print_exception("Connection_Handler::validate_connection");
    }
  }
#endif

  bool
  Connection_Handler::is_local_connection (
      const Deployment::DeploymentPlan & plan,
      const Deployment::PlanConnectionDescription &conn)
  {
    // in case the connection description defines 2 internal endpoints
    // (in the context of the current locality) it could be a local connection
    if (conn.internalEndpoint ().size () == 2)
    {
      // two internal endpoints for components installed in the same container are
      // considered local
      Deployment::PlanSubcomponentPortEndpoint const & port_endpoint = conn.internalEndpoint ()[0];
      std::string const comp1_name = plan.instance ()[port_endpoint.instanceRef ()].name ();
      Deployment::PlanSubcomponentPortEndpoint const & port_endpoint2 = conn.internalEndpoint ()[1];
      std::string const comp2_name = plan.instance ()[port_endpoint2.instanceRef ()].name ();
      if (DEPLOYMENT_STATE->component_container_id(comp1_name) ==
              DEPLOYMENT_STATE->component_container_id(comp2_name))
      {
        return true;
      }
    }
    return false;
  }

  uint32_t
  Connection_Handler::retrieve_endpoint (const Deployment::PlanConnectionDescription &conn)
  {
    if (conn.internalEndpoint ().empty ())
    {
      // this should never happen
      CIAOX11_LOG_ERROR ("Connection_Handler::retrieve_endpoint - " <<
                     "Connection lacks internalEndpint <" << conn.name () << ">");
      throw ::Deployment::InvalidConnection (conn.name (),
                                     "No internal endpoint for connection.");
    }
    // When two internal endpoints defined, get the 'consuming' endpoint
    // (Publisher, Emitter, Receptacle).
    // In case the the 'consuming' endpoint is external, we need to connect,
    // using the providing endpoint. Therefor returning zero.
    if (conn.internalEndpoint ().size () > 1)
    {
      if (!conn.internalEndpoint ()[1].provider ())
        return 1;
    }
    return 0;
  }

  IDL::traits<CIAOX11::ExecutorLocator>::ref_type
  Connection_Handler::fetch_component (const std::string& id)
  {
    return DEPLOYMENT_STATE->fetch_component (id);
  }

  void
  Connection_Handler::fetch_component_configuration (
      const std::string& id,
      Components::ConfigValues& config)
  {
    DEPLOYMENT_STATE->fetch_component_configuration (id, config);
  }
}
