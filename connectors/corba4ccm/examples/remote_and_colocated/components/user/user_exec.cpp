// -*- C++ -*-
/**
 * @file    user_exec.cpp
 * @author  Martin Corino
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : user_impl.cpp[Header]

#include "user_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_User_Impl[user_includes]
#include "ciaox11/testlib/ciaox11_testlog.h"
#include <iomanip>
//@@{__RIDL_REGEN_MARKER__} - END : Example_User_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_User_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : Example_User_Impl[user_global_impl]

namespace Example_User_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_User_Impl[user_namespace_impl]
  class TT_Callback final
    : public IDL::traits<CCM_TT::TT_Handler>::base_type
  {
  public:
    TT_Callback (
        std::string conn,
        IDL::traits<::Example::CCM_User_Context>::ref_type ctx)
      : connection_ (std::move(conn))
      , ciao_context_ (std::move(ctx))
    {}

    void
    on_trigger (
        IDL::traits<::CCM_TT::TT_Timer>::ref_type timer,
        const ::CCM_TT::TT_Duration& time,
        uint32_t round) override;

  private:
    std::string connection_;
    IDL::traits<::Example::CCM_User_Context>::ref_type ciao_context_;
  };

  void
  TT_Callback::on_trigger (
      IDL::traits<::CCM_TT::TT_Timer>::ref_type timer,
      const ::CCM_TT::TT_Duration& time,
      uint32_t round)
  {
    CIAOX11_TEST_INFO << "TT_Callback::on_trigger - timer[" << timer->id ()
                      << "] @ " << time.sec () << "."
                      << std::right << std::setfill('0') << std::setw(9)
                      << time.nanosec ()
                      << " #" << round
                      << " : " << this->connection_
                      << std::endl;

    CIAOX11_TEST_INFO << "Accessing run_my_foo receptacle" << std::endl;

    IDL::traits<::Example::Foo>::ref_type run_my_foo = this->ciao_context_->get_connection_run_my_foo ();
    if (run_my_foo)
    {
      run_my_foo->do_something ("Request from "+this->connection_+" User");
    }
    else
    {
      CIAOX11_TEST_ERROR << "Undefined run_my_foo receptacle!" << std::endl;
    }
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Example_User_Impl[user_namespace_impl]


  /**
   * Component Executor Implementation Class : User_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_User_Impl::User_exec_i[ctor]
  User_exec_i::User_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Example_User_Impl::User_exec_i[ctor]

  User_exec_i::~User_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_User_Impl::User_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Example_User_Impl::User_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_User_Impl::User_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Example_User_Impl::User_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_User_Impl::User_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Example_User_Impl::User_exec_i[user_private_ops]

  /** Session component operations */
  void User_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_User_Impl::User_exec_i[configuration_complete]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Example_User_Impl::User_exec_i[configuration_complete]
  }

  void User_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_User_Impl::User_exec_i[ccm_activate]
    this->context_->get_connection_tt_scheduler ()->schedule_trigger (
        CORBA::make_reference<TT_Callback> (this->connection (), this->context_),
        CCM_TT::TT_Duration (3, 0));

    CIAOX11_TEST_INFO << "Activated " << this->connection () << " User component." << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : Example_User_Impl::User_exec_i[ccm_activate]
  }

  void User_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_User_Impl::User_exec_i[ccm_passivate]
    CIAOX11_TEST_INFO << "Passivated " << this->connection () << " User component." << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : Example_User_Impl::User_exec_i[ccm_passivate]
  }

  void User_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_User_Impl::User_exec_i[ccm_remove]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Example_User_Impl::User_exec_i[ccm_remove]
  }


  std::string
  User_exec_i::connection ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_User_Impl::User_exec_i::connection[getter]
    return this->connection_;
    //@@{__RIDL_REGEN_MARKER__} - END : Example_User_Impl::User_exec_i::connection[getter]
  }

  void
  User_exec_i::connection (
      const std::string& connection)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_User_Impl::User_exec_i::connection[setter]
    this->connection_ = connection;
    //@@{__RIDL_REGEN_MARKER__} - END : Example_User_Impl::User_exec_i::connection[setter]
  }

  /// Operations from Components::SessionComponent
  void
  User_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_User_Impl::User_exec_i[set_session_context]
    this->context_ = IDL::traits<::Example::CCM_User_Context >::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : Example_User_Impl::User_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_User_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : Example_User_Impl[user_namespace_end_impl]

} // namespace Example_User_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_User_Impl[factory]
extern "C" void
create_Example_User_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <Example_User_Impl::User_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : Example_User_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : user_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
