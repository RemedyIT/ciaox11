// -*- C++ -*-
/**
 * @file    rg_late_bind_sender_exec.cpp
 * @author  Marcel Smit
 *
 * @brief   Sender component implementation of the late binded topic test.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : rg_late_bind_sender_impl.cpp[Header]

#include "rg_late_bind_sender_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Sender_Impl[user_includes]
#include "dds4ccm/logger/dds4ccm_testlog.h"
#include "dds4ccm/tests/common/common_test_utils.h"
//@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Sender_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Sender_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Sender_Impl[user_global_impl]

namespace RG_LateBinding_Sender_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Sender_Impl[user_namespace_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Sender_Impl[user_namespace_impl]

  /**
   * Facet Executor Implementation Class : start_writing_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Sender_Impl::start_writing_exec_i[ctor]
  start_writing_exec_i::start_writing_exec_i (
      IDL::traits<RG_LateBinding::CCM_Sender_Context>::ref_type context,
      IDL::traits<RG_LateBinding::CCM_Sender>::weak_ref_type component_executor)
    : context_ (std::move (context))
    , component_executor_ (std::move(component_executor))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Sender_Impl::start_writing_exec_i[ctor]

  start_writing_exec_i::~start_writing_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Sender_Impl::start_writing_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Sender_Impl::start_writing_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Sender_Impl::start_writing_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Sender_Impl::start_writing_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Sender_Impl::start_writing_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Sender_Impl::start_writing_exec_i[user_private_ops]


  /** Operations and attributes from start_writing */

  void
  start_writing_exec_i::start_write ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Sender_Impl::start_writing_exec_i::start_write[void]
    auto cex = IDL::traits<Sender_exec_i>::narrow (this->component_executor_.lock ());
    if (cex)
      cex->switch_context ();
    else
    {
      DDS4CCM_TEST_ERROR << "start_writing_exec_i::start_write - "
        "ERROR: failed to lock component executor" << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Sender_Impl::start_writing_exec_i::start_write[void]
  }

  /**
   * Component Executor Implementation Class : Sender_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Sender_Impl::Sender_exec_i[ctor]
  Sender_exec_i::Sender_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Sender_Impl::Sender_exec_i[ctor]

  Sender_exec_i::~Sender_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Sender_Impl::Sender_exec_i[dtor]
    //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Sender_Impl::Sender_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Sender_Impl::Sender_exec_i[user_public_ops]
  void
  Sender_exec_i::notify ()
  {
    if (!this->first_run_)
    {
      this->reset_topic_name ("SecondLateBindingTopic");
    }

    try
    {
      IDL::traits< ::CommonTestConnector::Writer >::ref_type writer =
        this->context_->get_connection_info_write_data ();
      DDS4CCM_TEST_DEBUG << "Sender_exec_i::notify - Samples: " << std::endl;
      for (uint16_t key = 1; key < this->keys_ + 1; ++key)
      {
        CommonTestMessage sample;
        sample.key ("KEY_" + std::to_string (key));

        for (uint16_t iter = 1; iter < this->iterations_ + 1; ++iter)
          {
            sample.iteration (iter);
            writer->write_one (sample, ::DDS::HANDLE_NIL);
            DDS4CCM_TEST_DEBUG << '\t' << sample << std::endl;
          }
      }
      IDL::traits< ReaderStarter >::ref_type starter =
        this->context_->get_connection_reader_start ();
      DDS4CCM_TEST_DEBUG << "Sender_exec_i::notify  - "
        << "Inform the receiver that all samples were written."
        << std::endl;
      starter->set_reader_properties (this->keys (), this->iterations ());
      starter->start_read ();
    }
    catch (const ::CCM_DDS::NonChangeable &)
    {
      DDS4CCM_TEST_DEBUG << "Sender_exec_i::notify - "
        << "ERROR: Caught NonChangeable exception." << std::endl;
    }
    catch (const CORBA::Exception &ex)
    {
      DDS4CCM_TEST_DEBUG << "Sender_exec_i::notify - "
        << "ERROR: Caught CORBA exception: " << ex << std::endl;
    }
    catch (...)
    {
      DDS4CCM_TEST_ERROR << "Sender_exec_i::notify - "
        << "ERROR: Unexpected and unknown exception caught." << std::endl;
    }
    this->first_run_ = false;
  }

  void
  Sender_exec_i::switch_context ()
  {
    // Can be invoked more than once.
    IDL::traits<CCM_TT::TT_Scheduler>::ref_type tt_s = this->context_->get_connection_tt_scheduler ();

    if (this->tm_)
    {
      this->tm_->cancel ();
      this->tm_.reset ();
    }
    this->tm_ = tt_s->schedule_trigger (
                       CORBA::make_reference<ContextSwitch> (IDL::traits< RG_LateBinding::CCM_Sender>::narrow (this->_lock())),
                       CCM_TT::TT_Duration (0, 0));
  }

  void
  Sender_exec_i::reset_topic_name (std::string const &topic_name)
  {
    try
    {
      DDS4CCM_TEST_DEBUG << "Sender_exec_i::reset_topic_name - "
        << "Setting topic name to '" << topic_name <<"'." << std::endl;
      IDL::traits< ::CommonTestConnector::Writer >::ref_type writer =
        this->context_->get_connection_info_write_data ();
      IDL::traits< ::CORBA::Object >::ref_type cmp = writer->_get_component ();
      if (!cmp)
      {
        DDS4CCM_TEST_ERROR << "Sender_exec_i::reset_topic_name - "
          "ERROR: Unable to get component interface." << std::endl;
        return;
      }
      IDL::traits< ::CommonTestConnector::CCM_DDS_Event >::ref_type conn =
        IDL::traits< ::CommonTestConnector::CCM_DDS_Event >::narrow (cmp);
      if (!conn)
      {
        DDS4CCM_TEST_ERROR << "ERROR: Sender_exec_i::reset_topic_name - "
          "Unable to narrow connector interface." << std::endl;
        return;
      }

      conn->topic_name (topic_name);
    }
    catch (const ::CCM_DDS::NonChangeable &)
    {
      DDS4CCM_TEST_ERROR << "Sender_exec_i::reset_topic_name - "
        "ERROR: Caught NonChangeable exception." << std::endl;
    }
  }
  //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Sender_Impl::Sender_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Sender_Impl::Sender_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Sender_Impl::Sender_exec_i[user_private_ops]

  /** Session component operations */
  void Sender_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Sender_Impl::Sender_exec_i[configuration_complete]
    DDS4CCM_TEST_DEBUG << "Sender_exec_i::configuration_complete" << std::endl;
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Sender_Impl::Sender_exec_i[configuration_complete]
  }

  void Sender_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Sender_Impl::Sender_exec_i[ccm_activate]
    this->switch_context ();
    //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Sender_Impl::Sender_exec_i[ccm_activate]
  }

  void Sender_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Sender_Impl::Sender_exec_i[ccm_passivate]
    // Should be able to set to topic to an empty string.
    this->reset_topic_name ("");
    if (this->tm_)
    {
      this->tm_->cancel ();
      this->tm_.reset ();
    }
    //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Sender_Impl::Sender_exec_i[ccm_passivate]
  }

  void Sender_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Sender_Impl::Sender_exec_i[ccm_remove]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Sender_Impl::Sender_exec_i[ccm_remove]
  }

  IDL::traits< CCM_WriterStarter >::ref_type
  Sender_exec_i::get_start_writing ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Sender_Impl::Sender_exec_i[get_start_writing]
  if (!this->start_writing_)
  {
    this->start_writing_ =
      CORBA::make_reference <start_writing_exec_i> (
        this->context_, IDL::traits<RG_LateBinding::CCM_Sender>::narrow (this->_lock()));
  }
  return this->start_writing_;
  //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Sender_Impl::Sender_exec_i[get_start_writing]
  }


  uint16_t
  Sender_exec_i::iterations ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Sender_Impl::Sender_exec_i::iterations[getter]
    return this->iterations_;
    //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Sender_Impl::Sender_exec_i::iterations[getter]
  }

  void
  Sender_exec_i::iterations (
      uint16_t iterations)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Sender_Impl::Sender_exec_i::iterations[setter]
    this->iterations_ = iterations;
    //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Sender_Impl::Sender_exec_i::iterations[setter]
  }

  uint16_t
  Sender_exec_i::keys ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Sender_Impl::Sender_exec_i::keys[getter]
    return this->keys_;
    //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Sender_Impl::Sender_exec_i::keys[getter]
  }

  void
  Sender_exec_i::keys (
      uint16_t keys)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Sender_Impl::Sender_exec_i::keys[setter]
    this->keys_ = keys;
    //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Sender_Impl::Sender_exec_i::keys[setter]
  }

  /// Operations from Components::SessionComponent
  void
  Sender_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Sender_Impl::Sender_exec_i[set_session_context]
    this->context_ = IDL::traits<RG_LateBinding::CCM_Sender_Context>::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Sender_Impl::Sender_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Sender_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Sender_Impl[user_namespace_end_impl]

} // namespace RG_LateBinding_Sender_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Sender_Impl[factory]
extern "C" void
create_RG_LateBinding_Sender_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <RG_LateBinding_Sender_Impl::Sender_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Sender_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : rg_late_bind_sender_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
