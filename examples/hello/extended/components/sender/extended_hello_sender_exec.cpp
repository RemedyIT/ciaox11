// -*- C++ -*-
/**
 * @file    extended_hello_sender_exec.cpp
 * @author  Johnny Willemsen
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : extended_hello_sender_impl.cpp[Header]

#include "extended_hello_sender_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl[user_includes]
#include <thread>
#include "ciaox11/testlib/ciaox11_testlog.h"
//@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl[user_global_impl]

namespace Hello_Sender_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl[user_namespace_impl]
  void
  foo_generator::set_context(
    IDL::traits<Hello::CCM_Sender_Context>::ref_type context)
  {
    this->context_ = IDL::traits<Hello::CCM_Sender_Context>::narrow (std::move(context));
  }


  int foo_generator::svc()
  {
    std::this_thread::sleep_for (std::chrono::seconds (3));
    IDL::traits<Hello::MyFoo>::ref_type my_foo =
      this->context_->get_connection_run_my_foo ();

    if (my_foo)
    {
      std::string out_str;
      for (int i = 0; i < 5; ++i)
      {
        std::string const result = my_foo->foo (
          "Do something for FOO <" + std::to_string (i) + ">", out_str);

        CIAOX11_TEST_INFO << "Sender - foo_generator - Invoked \"foo\" : "
                          << "result <" << result << "> - answer <" << out_str << ">"
                          << std::endl;
      }

      try
      {
        // Test exception
        std::string const noop = my_foo->foo ("throw", out_str);
        CIAOX11_TEST_ERROR << "ERROR: Sender - foo_generator - "
          << "No exception whilst calling \"foo\" with \"throw\" returning "
          << noop
          << std::endl;
      }
      catch (Hello::Ball const &ex)
      {
        CIAOX11_TEST_INFO << "Sender - foo_generator - "
          << "Caught expected exception: " << ex << std::endl;
      }

      try
      {
        // Test getter/setter of attributes.
        my_foo->foo_attrib (15);
        if (my_foo->foo_attrib () != 15)
        {
          CIAOX11_TEST_ERROR << "ERROR: Sender - foo_generator - "
            "Unexpected value of foo_attrib. Expected <15> - got <"
            << my_foo->foo_attrib () << ">." << std::endl;
        }
      }
      catch (...)
      {
        CIAOX11_TEST_ERROR << "ERROR: Sender - foo_generator - "
          "Unexpted exception caught." << std::endl;
      }

      try
      {
        // Test getraises exception.
        my_foo->foo_excep (15);
        uint16_t f = my_foo->foo_excep ();
        CIAOX11_TEST_ERROR << "ERROR: Sender - foo_generator - "
          "No exception whilst getting foo_excep: got <"
          << f << ">." << std::endl;
      }
      catch (Hello::Ball const &ex)
      {
        if (ex.error () == "Getraises Exception")
        {
          CIAOX11_TEST_INFO << "Sender - foo_generator (getraises) - "
            "Correct exception and message received." << std::endl;
        }
        else
        {
          CIAOX11_TEST_INFO << "Sender - foo_generator - "
            "Correct exception caught with an unexcepted message. Expected <"
            << "Getraises Exception> - got <" << ex.error () << ">" << std::endl;
        }
      }
      catch (...)
      {
        CIAOX11_TEST_ERROR << "ERROR: Sender - foo_generator (getraises) - "
          "Unexpted exception caught." << std::endl;
      }

      try
      {
        // Test setraises exception.
        my_foo->foo_excep (1);
        CIAOX11_TEST_ERROR << "ERROR: Sender - foo_generator - "
          "No exception whilst setting foo_excep." << std::endl;
      }
      catch (Hello::Ball const &ex)
      {
        if (ex.error () == "Setraises Exception")
        {
          CIAOX11_TEST_INFO << "Sender - foo_generator (setraises) - "
            "Correct exception and message received." << std::endl;
        }
        else
        {
          CIAOX11_TEST_INFO << "Sender - foo_generator - "
            "Correct exception caught with an unexcepted message. Expected <"
            << "Setraises Exception> - got <" << ex.error () << ">" << std::endl;
        }
      }
      catch (...)
      {
        CIAOX11_TEST_ERROR << "ERROR: Sender - foo_generator (setraises) - "
          "Unexpted exception caught." << std::endl;
      }
    }
    else
    {
      CIAOX11_TEST_ERROR << "Sender - ERROR, not possible to connect "
                         << std::endl;
    }
    return 0;
  }

  void
  bar_generator::set_context(
    IDL::traits<Hello::CCM_Sender_Context>::ref_type context)
  {
    this->context_ = IDL::traits<Hello::CCM_Sender_Context>::narrow (std::move(context));
  }

  int
  bar_generator::svc ()
  {
    std::this_thread::sleep_for (std::chrono::seconds (3));
    IDL::traits<Hello::MyBar>::ref_type my_bar =
      this->context_->get_connection_run_my_bar ();
    if (my_bar)
    {
      std::string out_str;
      for (int i = 0; i < 5; ++i)
      {
        std::string result = my_bar->bar (
          "Do something for BAR <" + std::to_string (i) + ">", out_str);

        CIAOX11_TEST_INFO << "Sender - bar_generator - Invoked \"bar\" : "
                          << "result <" << result << "> - answer <" << out_str << ">"
                          << std::endl;
      }
      if (my_bar->ro_bar_attrib () != 15)
      {
        CIAOX11_TEST_ERROR << "ERROR: Sender - bar_generator - "
          << "Unexpected value whilst getting ro_bar_attrib. Expected <15> - got <"
          << my_bar->ro_bar_attrib () << ">." << std::endl;
      }
    }
    return 0;
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl[user_namespace_impl]


  /**
   * Component Executor Implementation Class : Sender_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i[ctor]
  Sender_exec_i::Sender_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[ctor]

  Sender_exec_i::~Sender_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[user_private_ops]

  /** Session component operations */
  void Sender_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i[configuration_complete]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[configuration_complete]
  }

  void Sender_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i[ccm_activate]
    this->foo_gen_.set_context(this->context_);
    this->foo_gen_.activate (THR_NEW_LWP | THR_JOINABLE, 1);
    this->bar_gen_.set_context(this->context_);
    this->bar_gen_.activate (THR_NEW_LWP | THR_JOINABLE, 1);
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[ccm_activate]
  }

  void Sender_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i[ccm_passivate]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[ccm_passivate]
  }

  void Sender_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i[ccm_remove]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[ccm_remove]
  }

  /// Operations from Components::SessionComponent
  void
  Sender_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i[set_session_context]
    this->context_ = IDL::traits<Hello::CCM_Sender_Context>::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl[user_namespace_end_impl]

} // namespace Hello_Sender_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl[factory]
extern "C" void
create_Hello_Sender_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <Hello_Sender_Impl::Sender_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : extended_hello_sender_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
