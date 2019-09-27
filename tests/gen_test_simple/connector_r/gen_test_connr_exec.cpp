// -*- C++ -*-
/**
 * @file    gen_test_connr_exec.cpp
 * @author  Marijke Hengstmengel
 *
 * @brief   connnector source
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : gen_test_connr_impl.cpp[Header]

#include "gen_test_connr_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl[user_includes]
#include "ciaox11/testlib/ciaox11_testlog.h"
#include <iomanip>
//@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl[user_global_impl]

namespace Hello_MyBaseEvent_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl[user_namespace_impl]
  class TT_Callback final
    : public IDL::traits<CCM_TT::TT_Handler>::base_type
  {
  public:
    TT_Callback (IDL::traits<Hello::CCM_MyBaseEvent>::weak_ref_type component_executor)
      : component_executor_ (std::move(component_executor))
    {
    }

    virtual void
    on_trigger (
        IDL::traits< ::CCM_TT::TT_Timer>::ref_type timer,
        const ::CCM_TT::TT_Duration& time,
        uint32_t round) override;

  private:
    IDL::traits<Hello::CCM_MyBaseEvent>::weak_ref_type component_executor_;
  };

  void
  TT_Callback::on_trigger (
      IDL::traits< ::CCM_TT::TT_Timer>::ref_type timer,
      const ::CCM_TT::TT_Duration& time,
      uint32_t round)
  {
    CIAOX11_TEST_INFO << "TT_Callback::on_trigger - timer[" << timer->id ()
                      << "] @ " << time.sec () << "."
                      << std::right << std::setfill('0') << std::setw(9)
                      << time.nanosec ()
                      << " #" << round
                      << std::endl;

    auto cex = IDL::traits<MyBaseEvent_exec_i>::narrow (this->component_executor_.lock ());
    if (cex)
    {
      cex->send_something ();
    }
    else
    {
      CIAOX11_TEST_ERROR << "TT_Callback::on_trigger - "
        "ERROR: failed to lock component executor" << std::endl;
    }
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl[user_namespace_impl]


  /**
   * Component Executor Implementation Class : MyBaseEvent_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[ctor]
  MyBaseEvent_exec_i::MyBaseEvent_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[ctor]

  MyBaseEvent_exec_i::~MyBaseEvent_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[user_public_ops]
  void
  MyBaseEvent_exec_i::start_publishing ()
  {
    IDL::traits<CCM_TT::TT_Scheduler>::ref_type tt_s = this->context_->get_connection_tt_scheduler ();

    this->ticker_ = tt_s->schedule_repeated_trigger (
        CORBA::make_reference<TT_Callback> (IDL::traits<Hello::CCM_MyBaseEvent>::narrow(this->_lock())),
        CCM_TT::TT_Duration (0, 500000000),
        CCM_TT::TT_Duration (0, 500000000),
        0);

    if (!this->ticker_)
    {
      CIAOX11_TEST_ERROR << "MyBaseEvent_exec_i::start : Error scheduling timer"
       << std::endl;
    }
  }

  void MyBaseEvent_exec_i::send_something ()
  {
    IDL::traits<Hello::MyFoo>::ref_type my_foo =
               this->context_->get_connection_consumer_foo_prov ();
    if (!my_foo)
      {
        CIAOX11_TEST_ERROR << "ERROR: MyBaseEvent_exec_i::send_something: "
          << "get_connection_consumer_foo_prov returns null."
          << std::endl;
        return;
      }

    int32_t hello = my_foo->hello(11);
    if (hello != 11)
      {
        CIAOX11_TEST_ERROR << "ConnectorR:\tERROR: Hello returned an unexpected "
          << "value: expected <11> - got <" << hello << ">."
          << std::endl;
      }

    CIAOX11_TEST_INFO << "ConnectorR:\tInvoked synchronous call hello" << std::endl;

    my_foo->interface_attrib (115);
    CIAOX11_TEST_INFO <<  "ConnectorR:\tInvoked synchronous call interface_attrib (115) " << std::endl;

    int16_t interface_attrib = my_foo->interface_attrib ();
    CIAOX11_TEST_INFO << "ConnectorR:\tInvoked synchronous call "
                        << "(GET_RW_ATTRIB) answer <" << interface_attrib << ">" << std::endl;

    if (interface_attrib != 115)
      {
        CIAOX11_TEST_ERROR << "ConnectorR:\tERROR: interface_attrib returned an unexpected "
          << "value: expected <115> - got <" << interface_attrib << ">."
          << std::endl;
      }
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[user_private_ops]

  /** Session component operations */
  void MyBaseEvent_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[configuration_complete]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[configuration_complete]
  }

  void MyBaseEvent_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[ccm_activate]
    this->start_publishing();
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[ccm_activate]
  }

  void MyBaseEvent_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[ccm_passivate]
    this->ticker_->cancel();
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[ccm_passivate]
  }

  void MyBaseEvent_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[ccm_remove]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[ccm_remove]
  }


  int16_t
  MyBaseEvent_exec_i::consumer_port_attrib ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i::consumer_port_attrib[getter]
    return 2;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i::consumer_port_attrib[getter]
  }

  void
  MyBaseEvent_exec_i::consumer_port_attrib (
      int16_t consumer_port_attrib)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i::consumer_port_attrib[setter]
    if (consumer_port_attrib != 4321)
    {
      CIAOX11_TEST_ERROR << "ConnectorR:\tERROR: consumer_port_attrib received an "
          << "unexpected value: expected <4321> - got <" << consumer_port_attrib << ">."
          << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i::consumer_port_attrib[setter]
  }

  int16_t
  MyBaseEvent_exec_i::conn_attrib ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i::conn_attrib[getter]
    return 1;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i::conn_attrib[getter]
  }

  void
  MyBaseEvent_exec_i::conn_attrib (
      int16_t conn_attrib)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i::conn_attrib[setter]
    if (conn_attrib != 4321)
    {
      CIAOX11_TEST_ERROR << "ConnectorR:\tERROR: conn_attrib received an "
          << "unexpected value: expected <4321> - got <" << conn_attrib << ">."
          << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i::conn_attrib[setter]
  }

  /// Operations from Components::SessionComponent
  void
  MyBaseEvent_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[set_session_context]
    this->context_ = IDL::traits<Hello::CCM_MyBaseEvent_Context>::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl[user_namespace_end_impl]

} // namespace Hello_MyBaseEvent_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_MyBaseEvent_Impl[factory]
extern "C" void
create_Hello_MyBaseEvent_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <Hello_MyBaseEvent_Impl::MyBaseEvent_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : Hello_MyBaseEvent_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : gen_test_connr_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
