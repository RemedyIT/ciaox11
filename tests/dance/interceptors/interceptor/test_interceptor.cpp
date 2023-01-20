/**
 * @file    test_interceptor.cpp
 * @author  Marcel Smit
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#include "test_interceptor.h"

#include "ccm/ComponentsC.h"
#include "ccm/ccm_objectC.h"
#include "dancex11/deployment/deployment_connectionC.h"
#include "ciaox11/testlib/ciaox11_testlog.h"

namespace DAnCEX11
{
  Test_Interceptor::~Test_Interceptor ()
  {
    uint32_t _instances;
    // Count the corba connectors as well.
    if (this->node_ == "SenderNode")
    {
      _instances = 4;
    }
    else
    {
      _instances = 2;
    }

    if (this->configure_invoked_ == 1)
      {
        CIAOX11_TEST_INFO << "OK : configure was invoked" << std::endl;
      }
    else
      {
        CIAOX11_TEST_ERROR << "ERROR : configure was not invoked" << std::endl;
      }
    if (this->preprocess_plan_ == 1)
      {
        CIAOX11_TEST_INFO << "OK : pre-process plan was invoked" << std::endl;
      }
    else
      {
        CIAOX11_TEST_ERROR << "ERROR : pre-process plan was not invoked" << std::endl;
      }
    if (this->pre_install_invoked_ == _instances)
    {
      CIAOX11_TEST_INFO << "OK : pre install was invoked" << std::endl;
    }
    else
    {
      CIAOX11_TEST_ERROR << "ERROR : pre install was not invoked " << _instances << " times but <"
        << this->pre_install_invoked_ << "> time(s)"
        << std::endl;
    }
    if (this->post_install_invoked_ == _instances)
    {
      CIAOX11_TEST_INFO << "OK : post install was invoked" << std::endl;
    }
    else
    {
      CIAOX11_TEST_ERROR << "ERROR : post install was not invoked " << _instances << " times but <"
        << this->post_install_invoked_ << "> time(s)"
        << std::endl;
    }
    if (this->post_configured_invoked_ == _instances)
    {
      CIAOX11_TEST_INFO << "OK : post configured was invoked" << std::endl;
    }
    else
    {
      CIAOX11_TEST_ERROR << "ERROR : post configured was not invoked " << _instances <<" times but <"
        << this->post_configured_invoked_ << "> time(s)"
        << std::endl;
    }
    if (this->post_activate_invoked_ == _instances)
    {
      CIAOX11_TEST_INFO << "OK : post activate was invoked" << std::endl;
    }
    else
    {
      CIAOX11_TEST_ERROR << "ERROR : post activate was not invoked " << _instances << " times but <"
        << this->post_activate_invoked_ << "> time(s)"
        << std::endl;
    }
    if (this->post_passivate_invoked_ == _instances)
    {
      CIAOX11_TEST_INFO << "OK : post passivate was invoked" << std::endl;
    }
    else
    {
      CIAOX11_TEST_ERROR << "ERROR : post passivate was not invoked " << _instances << " times but <"
        << this->post_passivate_invoked_ << "> time(s)"
        << std::endl;
    }
    if (this->post_remove_invoked_ == _instances)
    {
      CIAOX11_TEST_INFO << "OK : post remove was invoked" << std::endl;
    }
    else
    {
      CIAOX11_TEST_ERROR << "ERROR : post remove was not invoked " << _instances << " times but <"
        << this->post_remove_invoked_ << "> time(s)"
        << std::endl;
    }
    if (this->node_ == "SenderNode")
      {
        // Corba connectors. Two facets.
        if (this->post_endpoint_reference_invoked_ == 2)
          {
            CIAOX11_TEST_INFO << "OK : post endpoint reference was invoked twice" << std::endl;
          }
        else
          {
            CIAOX11_TEST_ERROR << "ERROR : post endpoint reference was invoked <"
              << this->post_endpoint_reference_invoked_ << "> time(s) on the "
              << "Sender-node" << std::endl;
          }
        // only the receptacles will receive a pre/post (dis)connect.
        if (this->pre_connect_invoked_ == 4)
          {
            CIAOX11_TEST_INFO << "OK : pre connect was invoked" << std::endl;
          }
        else
          {
            CIAOX11_TEST_ERROR << "ERROR : pre connect was not invoked four times but <"
              << this->pre_connect_invoked_ << "> time(s)"
              << std::endl;
          }
        if (this->post_connect_invoked_ == 4)
          {
            CIAOX11_TEST_INFO << "OK : post connect was invoked" << std::endl;
          }
        else
          {
            CIAOX11_TEST_ERROR << "ERROR : post connect was not invoked four times but <"
              << this->post_connect_invoked_ << "> time(s)"
              << std::endl;
          }
        if (this->pre_disconnect_invoked_ == 4)
          {
            CIAOX11_TEST_INFO << "OK : pre disconnect was invoked" << std::endl;
          }
        else
          {
            CIAOX11_TEST_ERROR << "ERROR : pre disconnect was not invoked four times but <"
              << this->pre_disconnect_invoked_ << "> time(s)"
              << std::endl;
          }
        if (this->post_disconnect_invoked_ == 4)
          {
            CIAOX11_TEST_INFO << "OK : post disconnect was invoked" << std::endl;
          }
        else
          {
            CIAOX11_TEST_ERROR << "ERROR : post disconnect was not invoked four times but <"
              << this->post_disconnect_invoked_ << "> time(s)"
              << std::endl;
          }
      }
    else
      {
        // Three connections on the receiver side of which one facet connection
        if (this->post_endpoint_reference_invoked_ == 3)
          {
            CIAOX11_TEST_INFO << "OK : post endpoint reference was invoked three times" << std::endl;
          }
        else
          {
            CIAOX11_TEST_ERROR << "ERROR : post endpoint reference was not invoked three times but <"
              << this->post_endpoint_reference_invoked_ << "> time(s) on the "
              << "Receiver-node" << std::endl;
          }
        // only the receptacles will receive a pre/post (dis)connect.
        if (this->pre_connect_invoked_ == 1)
          {
            CIAOX11_TEST_INFO << "OK : pre connect was invoked once" << std::endl;
          }
        else
          {
            CIAOX11_TEST_ERROR << "ERROR : pre connect was invoked <"
              << this->pre_connect_invoked_ << "> time(s)."
              << std::endl;
          }
        if (this->post_connect_invoked_ == 1)
          {
            CIAOX11_TEST_INFO << "OK : post connect was invoked once" << std::endl;
          }
        else
          {
            CIAOX11_TEST_ERROR << "ERROR : post connect was invoked <"
              << this->post_connect_invoked_ << "> time(s)."
              << std::endl;
          }
        if (this->pre_disconnect_invoked_ == 1)
          {
            CIAOX11_TEST_INFO << "OK : pre disconnect was invoked once" << std::endl;
          }
        else
          {
            CIAOX11_TEST_ERROR << "ERROR : pre disconnect was invoked <"
              << this->pre_disconnect_invoked_ << "> time(s)."
              << std::endl;
          }
        if (this->post_disconnect_invoked_ == 1)
          {
            CIAOX11_TEST_INFO << "OK : post disconnect was invoked once" << std::endl;
          }
        else
          {
            CIAOX11_TEST_ERROR << "ERROR : post disconnect was invoked <"
              << this->post_disconnect_invoked_ << "> time(s)."
              << std::endl;
          }
      }
  }

  void
  Test_Interceptor::check_instances (const ::Deployment::DeploymentPlan &plan,
    const std::string &method)
  {
    if (this->node_.compare ("SenderNode") == 0)
      {
        bool found_1 {}, found_2 {};
        for (const Deployment::InstanceDeploymentDescription& idd : plan.instance ())
        {
          if (idd.name () == "InterceptorSenderInstance1")
            found_1 = true;
          if (idd.name () == "InterceptorSenderInstance2")
            found_2 = true;
        }
        // We're on the sender node.
        if (found_1 && found_2)
          {
            CIAOX11_TEST_INFO << "Test_Interceptor::check_instances : <" << method << "> "
              << "OK : Correct instance names for the Sender found."
              << std::endl;
          }
        else
          {
            CIAOX11_TEST_ERROR << "Test_Interceptor::check_instances : <" << method << "> "
              << "ERROR : Incorrect names for the Sender instances found."
              << std::endl;
          }
      }
    else
      {
        bool found {};
        for (const Deployment::InstanceDeploymentDescription& idd : plan.instance ())
        {
          if (idd.name () == "InterceptorReceiverInstance1")
            found = true;
        }
        // We're on the receiver node.
        if (found)
          {
            CIAOX11_TEST_INFO << "Test_Interceptor::check_instances : <" << method << "> "
              << "OK : Correct instance name for the Receiver found."
              << std::endl;
          }
        else
          {
            CIAOX11_TEST_ERROR << "Test_Interceptor::check_instances : <" << method << "> "
              << "ERROR : Incorrect name for the Receiver instance found."
              << std::endl;
          }
      }
  }

  void
  Test_Interceptor::check_connections (const ::Deployment::DeploymentPlan &plan,
    const std::string &method)
  {
    CIAOX11_TEST_INFO << "Test_Interceptor::check_connections : <" << method << "> "
      << "Number of connections on " << this->node_ << " node found  <"
      << plan.connection ().size () << ">" << std::endl;
    size_t const nr_connections = plan.connection().size ();

    if (this->node_ == "SenderNode")
    {
      if (nr_connections != 4)
        {
          CIAOX11_TEST_ERROR << "Test_Interceptor::check_connections : <" << method << "> "
            << "ERROR : wrong number of connections found : "
            << "expected <4> - found <" << nr_connections << ">"
            << std::endl;
          return;
        }
      bool error = false;
      for (Deployment::PlanConnectionDescription conn : plan.connection ())
        if (conn.name () != "Sender_CORBA_connector1.srr_facet:InterceptorSenderInstance1.run_my_foo" &&
            conn.name () != "Sender_CORBA_connector1.srr_receptacle:Receiver_CORBA_connector.srr_facet" &&
            conn.name () != "Sender_CORBA_connector2.srr_facet:InterceptorSenderInstance2.run_my_foo" &&
            conn.name () != "Sender_CORBA_connector2.srr_receptacle:Receiver_CORBA_connector.srr_facet")
          {
            CIAOX11_TEST_ERROR << "Test_Interceptor::check_connections : <" << method << "> "
              << "ERROR : Incorrect name found : "
              << "found <" << conn.name () << ">"
              << std::endl;
            error = true;
          }
      if (!error)
        {
          CIAOX11_TEST_INFO << "Test_Interceptor::check_connections : <" << method << "> "
            << "OK : connections have correct names."
            << std::endl;
        }
    }
    else if (this->node_ == "ReceiverNode")
    {
      if (nr_connections != 3)
        {
          CIAOX11_TEST_ERROR << "Test_Interceptor::check_connections : <" << method << "> "
            << "ERROR : wrong number of connections found : "
            << "expected <3> - found <" << nr_connections << ">"
            << std::endl;
          return;
        }
      bool error = false;
      for (Deployment::PlanConnectionDescription conn : plan.connection ())
        if (conn.name () != "Receiver_CORBA_connector.srr_receptacle:InterceptorReceiverInstance1.prov_my_foo" &&
            conn.name () != "Sender_CORBA_connector1.srr_receptacle:Receiver_CORBA_connector.srr_facet" &&
            conn.name () != "Sender_CORBA_connector2.srr_receptacle:Receiver_CORBA_connector.srr_facet")
          {
            CIAOX11_TEST_ERROR << "Test_Interceptor::check_connections : <" << method << "> "
              << "ERROR : Incorrect name found : "
              << "found <" << conn.name () << ">"
              << std::endl;
            error = true;
          }
      if (!error)
        {
          CIAOX11_TEST_INFO << "Test_Interceptor::check_connections : <" << method << "> "
            << "OK : connections have correct names."
            << std::endl;
        }
    }
  }

  void
  Test_Interceptor::check_reference (const CORBA::Any &ref,
    const std::string &method)
  {
    CIAOX11_TEST_INFO << "Test_Interceptor::check_reference : <" << method << "> called"
                      << std::endl;

    // Only for remote connections; thus the two corba connectors on the
    // sender side.
    if (this->node_ == "ReceiverNode")
      return;

    IDL::traits<CORBA::Object>::ref_type ep;
    ref >>= ep;
    if (ep == nullptr)
      {
        // The provided reference could be nil since we're using
        // CORBA connectors.
        return;
      }
    IDL::traits<::Interceptor::Foo>::ref_type reference =
      IDL::traits<::Interceptor::Foo>::narrow (ep);
    if (reference == nullptr)
      {
        CIAOX11_TEST_ERROR << "Test_Interceptor::check_reference : <" << method << "> "
          << "ERROR : Unable narrow provided reference to "
          << "its implementation - node <" << this->node_
          << ">." << std::endl;
        return;
      }

    CIAOX11_TEST_INFO << "Test_Interceptor::check_reference : <" << method << "> storing reference"
                      << std::endl;

    this->foo_list_.push_back (reference);
  }

  void
  Test_Interceptor::test_references ()
  {
    CIAOX11_TEST_INFO << "Test_Interceptor::test_references called"
                      << std::endl;

    // Only for remote connections; thus the two corba connectors on the
    // sender side.
    if (this->node_ == "ReceiverNode")
      return;

    for (IDL::traits<::Interceptor::Foo>::ref_type& reference : this->foo_list_)
    {
      CIAOX11_TEST_INFO << "Test_Interceptor::test_references calling cached reference"
                        << std::endl;

      uint16_t output, input = 2;
      try
      {
        uint16_t result = reference->do_foo (input, output);
        if (result != input + 2)
          {
            CIAOX11_TEST_ERROR << "Test_Interceptor::test_references "
              << "ERROR : Unexpected result after invocation of \'foo\' : "
              << "expected <4> - received <" << result << ">"
              << std::endl;
          }
        else
          {
            CIAOX11_TEST_INFO << "Test_Interceptor::test_references "
              << "OK : Correct result after invocation of \'foo\' : "
              << "expected <4>" << std::endl;
          }
        if (output != input + 1)
          {
            CIAOX11_TEST_ERROR << "Test_Interceptor::test_references "
              << "ERROR : Unexpected output after invocation of \'foo\' : "
              << "expected <3> - received <" << output << ">"
              << std::endl;
          }
        else
          {
            CIAOX11_TEST_INFO << "Test_Interceptor::test_references "
              << "OK : Correct output after invocation of \'foo\' : "
              << "expected <3>" << std::endl;
          }
      }
      catch (...)
      {
        CIAOX11_TEST_WARNING << "Test_Interceptor::test_references "
          << "caught exception whilst invoking \'foo\' on <"
          << this->node_ << ">; connection probably not yet complete." << std::endl;
      }
    }
  }

  void
  Test_Interceptor::configure (const ::Deployment::Properties &)
  {
    CIAOX11_TEST_INFO << "Test_Interceptor::configure : "
      << "configure was invoked"
      << std::endl;
    ++this->configure_invoked_;
  }

  void
  Test_Interceptor::preprocess_plan (Deployment::DeploymentPlan &plan)
  {
    CIAOX11_TEST_INFO << "Test_Interceptor::preprocess_plan : "
      << "Pre process plan was invoked"
      << std::endl;
    ++this->preprocess_plan_;
    if (!plan.instance ().empty ())
      {
        this->node_ = plan.instance ()[0].node ();

        CIAOX11_TEST_INFO << "Test_Interceptor::preprocess_plan : "
          << "We're on node <" << this->node_ << ">"
          << std::endl;
      }
    else
      {
        CIAOX11_TEST_INFO << "Test_Interceptor::preprocess_plan : "
          << "ERROR : Unable to determine the node name."
          << std::endl;
      }
    // Add a -new- instance on the fly
    if (this->node_.compare ("Receiver") == 0)
      {
        Deployment::MonolithicDeploymentDescriptions::size_type implementationRef;
        for (implementationRef = 0;
          implementationRef < plan.implementation ().size ();
          ++implementationRef)
          {
            if (plan.implementation ()[implementationRef].name ().compare ("InterceptorReceiverImplementation") == 0)
              {
                break;
              }
          }
        CIAOX11_TEST_INFO << "Test_Interceptor::preprocess_plan : "
          << "Found the receiver's implementation reference : <"
          << implementationRef << ">" << std::endl;

        Deployment::InstanceDeploymentDescription inst;
        inst.implementationRef (ACE_Utils::truncate_cast<uint32_t> (implementationRef));
        inst.name ("InterceptorReceiverInstance1");
        inst.node ("Receiver");
        // Should be added before the 'remote' LM, identified as
        // "Locality Manager [hash]
        plan.instance ().insert (plan.instance().begin ()+1, inst);
      }
    this->check_instances (plan, "preprocess_plan");
  }

  void
  Test_Interceptor::pre_install (Deployment::DeploymentPlan &plan,
    uint32_t instanceRef)
  {
    CIAOX11_TEST_INFO << "Test_Interceptor::pre_install : "
      << "Pre install invoked for <" << instanceRef
      << "> - name <" << plan.instance ()[instanceRef].name ()
      << "> - node <" << plan.instance ()[instanceRef].node () << ">"
      << std::endl;
    ++this->pre_install_invoked_;
  }

  void
  Test_Interceptor::post_install (const Deployment::DeploymentPlan &plan,
    uint32_t index,
    const CORBA::Any &reference,
    const CORBA::Any &)
  {
    CIAOX11_TEST_INFO << "Test_Interceptor::post_install : "
      << "Post install invoked for <" << index
      << "> - name <" << plan.instance ()[index].name ()
      << "> - node <" << plan.instance ()[index].node () << ">"
      << std::endl;
    ++this->post_install_invoked_;
    IDL::traits<Components::CCMObject>::ref_type ccm_object_ref;
    if (!(reference >>= ccm_object_ref))
    {
      CIAOX11_TEST_ERROR << "Test_Interceptor::post_install : "
        << "ERROR : Failed to extract provided reference."
        << std::endl;
    }

    // MCO@20140715 - no use testing the reference value as it is
    //                a valid condition to have a nil value in case of components
    //                without any non-local facets (which in this test applies
    //                to the Sender)
  }

  void
  Test_Interceptor::post_endpoint_reference (const Deployment::DeploymentPlan &plan,
    uint32_t connectionRef,
    const CORBA::Any & /*endpoint_reference*/,
    const CORBA::Any &/*exception_thrown*/)
  {
    CIAOX11_TEST_INFO << "Test_Interceptor::post_endpoint_reference : "
      << "Post endpoint reference invoked for <" << connectionRef
      << "> - name <" << plan.connection ()[connectionRef].name ()
      << "> - node <" << this->node_ << ">"
      << std::endl;
    ++this->post_endpoint_reference_invoked_;
    this->check_connections (plan, "post_endpoint_reference");
    // MCO @ 20150825 - not possible to test the references here as
    //                  the connections are not setup here so while a
    //                  valid reference may be provided that reference may
    //                  not be capable of completely routing the message
  }

  void
  Test_Interceptor::pre_connect (Deployment::DeploymentPlan &plan,
    uint32_t connection_index,
    CORBA::Any &provided_reference)
  {
    CIAOX11_TEST_INFO << "Test_Interceptor::pre_connect : "
      << "Pre connect invoked for <" << connection_index
      << "> - name <" << plan.connection ()[connection_index].name ()
      << "> - node <" << this->node_ << ">"
      << std::endl;
    this->check_connections (plan, "pre_connect");
    ++this->pre_connect_invoked_;
    this->check_reference (provided_reference, "pre_connect");
  }

  void
  Test_Interceptor::post_connect (const Deployment::DeploymentPlan &plan,
    uint32_t index,
    const CORBA::Any &)
  {
    CIAOX11_TEST_INFO << "Post connect invoked for <" << index
      << "> - name <" << plan.instance ()[index].name ()
      << "> - node <" << plan.instance ()[index].node () << ">"
      << std::endl;
    ++this->post_connect_invoked_;
    this->check_connections (plan, "post_connect");
  }

  void
  Test_Interceptor::pre_disconnect (Deployment::DeploymentPlan &plan,
    uint32_t connection_index)
  {
    CIAOX11_TEST_INFO << "Test_Interceptor::pre_disconnect : "
      << "Pre disconnect invoked for <" << connection_index
      << "> - name <" << plan.connection ()[connection_index].name ()
      << "> - node <" << this->node_ << ">"
      << std::endl;
    this->check_connections (plan, "pre_disconnect");
    ++this->pre_disconnect_invoked_;
  }

  void Test_Interceptor::post_disconnect (const Deployment::DeploymentPlan &plan,
    uint32_t connectionRef,
    const CORBA::Any &)
  {
    CIAOX11_TEST_INFO << "Test_Interceptor::post_disconnect : "
      << "Post disconnect invoked for <" << connectionRef
      << "> - name <" << plan.connection ()[connectionRef].name ()
      << "> - node <" << this->node_ << ">"
      << std::endl;
    this->check_connections (plan, "post_disconnect");
    ++this->post_disconnect_invoked_;
  }

  void
  Test_Interceptor::post_configured (const Deployment::DeploymentPlan &plan,
    uint32_t index,
    const CORBA::Any &)
  {
    CIAOX11_TEST_INFO << "Post configured invoked for <" << index
      << "> - name <" << plan.instance ()[index].name ()
      << "> - node <" << plan.instance ()[index].node () << ">"
      << std::endl;
    this->check_instances (plan, "post_configured");
    ++this->post_configured_invoked_;
  }


  void
  Test_Interceptor::post_activate (const Deployment::DeploymentPlan &plan,
    uint32_t index,
    const CORBA::Any &)
  {
    CIAOX11_TEST_INFO << "Post activate invoked for <" << index
      << "> - name <" << plan.instance ()[index].name ()
      << "> - node <" << plan.instance ()[index].node () << ">"
      << std::endl;
    this->check_instances (plan, "post_activate");
    ++this->post_activate_invoked_;
    if (plan.instance ()[index].name () == "InterceptorSenderInstance1" ||
          plan.instance ()[index].name () == "InterceptorSenderInstance2")
    {
      // now it's safe to test the references we intercepted
      this->test_references ();
    }
  }


  void
  Test_Interceptor::post_passivate (const Deployment::DeploymentPlan &plan,
    uint32_t index,
    const CORBA::Any &)
  {
    CIAOX11_TEST_INFO << "Post passivate invoked for <" << index
      << "> - name <" << plan.instance ()[index].name ()
      << "> - node <" << plan.instance ()[index].node () << ">"
      << std::endl;
    this->check_instances (plan, "post_passivate");
    ++this->post_passivate_invoked_;
  }


  void
  Test_Interceptor::post_remove (const Deployment::DeploymentPlan &plan,
    uint32_t index,
    const CORBA::Any &)
  {
    CIAOX11_TEST_INFO << "Post remove invoked for <" << index
      << "> - name <" << plan.instance ()[index].name ()
      << "> - node <" << plan.instance ()[index].node () << ">"
      << std::endl;
    this->check_instances (plan, "post_remove");
    ++this->post_remove_invoked_;
  }

  void
  Test_Interceptor::unexpected_event (const Deployment::DeploymentPlan &/*plan*/,
    uint32_t /*instanceRef*/,
    const CORBA::Any &/*exception_thrown*/,
    const std::string &/*error*/)
  {
    // TODO: find a way to test this.
  }
}

extern "C"
{
  void
  create_test_interceptor (
    IDL::traits<DAnCEX11::DeploymentInterceptor>::ref_type& interceptor)
  {
    interceptor = CORBA::make_reference<DAnCEX11::Test_Interceptor> ();
  }
}
