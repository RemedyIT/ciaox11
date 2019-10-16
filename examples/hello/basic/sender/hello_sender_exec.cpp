// -*- C++ -*-
/**
 * @file    hello_sender_exec.cpp
 * @author  Johnny Willemsen
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : hello_sender_impl.cpp[Header]

#include "hello_sender_exec.h"

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
        int32_t result = my_foo->foo (
          "Do something for foo <" + std::to_string (i) + ">", out_str);

        CIAOX11_TEST_INFO << "Sender - foo_generator - Invoked \"foo\" : "
                          << "result <" << result << "> - answer <" << out_str << ">"
                          << std::endl;

        int32_t answer;
        my_foo->hello (answer);

        CIAOX11_TEST_INFO << "Sender - foo_generator - Invoked \"hello\" : "
                          << "result <" << result << "> - answer <" << answer << ">"
                          << std::endl;

        try
        {
          // Test getraises exception.
          uint16_t f = my_foo->rw_attrib ();
          CIAOX11_TEST_INFO << "Sender - foo_generator - "
            "get rw_attrib returned <"
            << f << ">." << std::endl;
        }
        catch (Hello::InternalError const &)
        {
          CIAOX11_TEST_INFO << "Sender - foo_generator (getraises) - "
          "Correct exception and message received." << std::endl;
        }

        try
        {
          // Test setraises exception.
          my_foo->rw_attrib (15);
          CIAOX11_TEST_INFO << "Sender - foo_generator - "
            "set rw_attrib to 15." << std::endl;
        }
        catch (Hello::InternalError const &)
        {
          CIAOX11_TEST_INFO << "Sender - foo_generator (setraises) - "
              "Correct exception and message received." << std::endl;
        }

        try
        {
          int16_t x = my_foo->ro_attrib ();
          CIAOX11_TEST_INFO << "Sender - foo_generator - "
            "Get ro_attrib returned <" << x << ">" << std::endl;
        }
        catch (Hello::InternalError const &)
        {
          CIAOX11_TEST_INFO << "Sender - foo_generator (ro_atrib) - "
              "Correct exception and message received." << std::endl;
        }
      } // endfor
    }
    else
    {
      CIAOX11_TEST_ERROR << "Sender - ERROR, not possible to connect "
                         << std::endl;
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
//@@{__RIDL_REGEN_MARKER__} - BEGIN : hello_sender_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
