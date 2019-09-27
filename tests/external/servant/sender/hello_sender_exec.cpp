// -*- C++ -*-
/**
 * @file    hello_sender_exec.cpp
 * @author  Martin Corino
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : hello_sender_impl.cpp[Header]

#include "hello_sender_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl[user_includes]
#include <thread>
#include "ciaox11/testlib/ciaox11_testlog.h"
//@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl[user_global_impl]

namespace Test_Sender_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl[user_namespace_impl]
  //============================================================
  // Worker thread for synchronous invocations for Hello
  //============================================================
  hello_generator::hello_generator ()
  {
  }
  void
  hello_generator::set_context(
     IDL::traits<Test::CCM_Sender_Context>::ref_type context)
  {
    this->ciao_context_ = context;
  }

  int hello_generator::svc ()
  {
    std::this_thread::sleep_for (std::chrono::seconds (3));
    CIAOX11_TEST_INFO << "Sender:\t->get_connection_sender_port_hello_uses " << std::endl;
    IDL::traits<Test::Hello>::ref_type my_hello_ =
        this->ciao_context_->get_connection_sender_port_hello_uses ();
    if (!my_hello_)
    {
      CIAOX11_TEST_INFO << "Sender:\t->get_connection_sender_port_hello_uses "
                        << "returns null" << std::endl;
    }
    try {
      //run synch call
      std::string answer =
          my_hello_->get_string(13);
      CIAOX11_TEST_INFO << "Sender:\tsynch hello(13) -> " << answer << std::endl;
    }
    catch (const CORBA::Exception& ex) {
      CIAOX11_TEST_ERROR << "ERROR: Sender:\tsynch hello unexpected exception : " << ex
                       << std::endl;
      this->errors_ = true;
    }
    try {
      my_hello_->interface_attrib (3);
      int16_t ret  = my_hello_->interface_attrib ();
      CIAOX11_TEST_INFO << "Sender:\tsynch interface_attrib -> " << ret << std::endl;
    }
    catch (const CORBA::Exception& ex) {
      CIAOX11_TEST_ERROR << "ERROR: Sender:\tsynch interface_attrib unexpected exception : " << ex
                       << std::endl;
      this->errors_ = true;
    }
    try {
      //run synch call
      std::string answer =
          my_hello_->get_string(13);
      CIAOX11_TEST_INFO << "Sender:\tsynch hello(13) -> " << answer << std::endl;
    }
    catch (const CORBA::Exception& ex) {
      CIAOX11_TEST_ERROR << "ERROR: Sender:\tsynch hello unexpected exception : " << ex
                       << std::endl;
      this->errors_ = true;
    }

    return 0;
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl[user_namespace_impl]


  /**
   * Component Executor Implementation Class : Sender_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::Sender_exec_i[ctor]
  Sender_exec_i::Sender_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::Sender_exec_i[ctor]

  Sender_exec_i::~Sender_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::Sender_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::Sender_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::Sender_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::Sender_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::Sender_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::Sender_exec_i[user_private_ops]

  /** Session component operations */
  void Sender_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::Sender_exec_i[configuration_complete]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::Sender_exec_i[configuration_complete]
  }

  void Sender_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::Sender_exec_i[ccm_activate]
    CIAOX11_TEST_INFO << "Sender_exec_i::ccm_activate." << std::endl;

    this->hello_gen_.set_context(this->context_);
    this->hello_gen_.activate (THR_NEW_LWP | THR_JOINABLE, 1);
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::Sender_exec_i[ccm_activate]
  }

  void Sender_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::Sender_exec_i[ccm_passivate]
    CIAOX11_TEST_INFO << "Sender_exec_i::ccm_passivate." << std::endl;

    this->hello_gen_.wait (); // wait for generator task to finish
    if (this->hello_gen_.errors ())
    {
      CIAOX11_TEST_ERROR << "Sender_exec_i::ccm_passivate - errors encountered during execution" << std::endl;
    }
    // shutdown server
    IDL::traits<Test::Hello>::ref_type my_hello_ =
        this->context_->get_connection_sender_port_hello_uses ();
    if (!my_hello_)
    {
      CIAOX11_TEST_INFO << "Sender_exec_i::ccm_passivate:\t->get_connection_sender_port_hello_uses "
                        << "returns null" << std::endl;
    }
    else
    {
      my_hello_->shutdown ();
    }
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::Sender_exec_i[ccm_passivate]
  }

  void Sender_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::Sender_exec_i[ccm_remove]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::Sender_exec_i[ccm_remove]
  }

  /// Operations from Components::SessionComponent
  void
  Sender_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl::Sender_exec_i[set_session_context]
    this->context_ = IDL::traits<Test::CCM_Sender_Context>::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl::Sender_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl[user_namespace_end_impl]

} // namespace Test_Sender_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Test_Sender_Impl[factory]
extern "C" void
create_Test_Sender_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <Test_Sender_Impl::Sender_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : Test_Sender_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : hello_sender_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
