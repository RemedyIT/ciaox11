// -*- C++ -*-
/**
 * @file    rg_late_bind_receiver_exec.cpp
 * @author  Marcel Smit
 *
 * @brief   Receiver component implementation of the late binded topic test.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : rg_late_bind_receiver_impl.cpp[Header]

#include "rg_late_bind_receiver_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Receiver_Impl[user_includes]
#include "dds4ccm/tests/common/common_test_utils.h"
#include "commonSEEC.h"
//@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Receiver_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Receiver_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Receiver_Impl[user_global_impl]

namespace RG_LateBinding_Receiver_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Receiver_Impl[user_namespace_impl]
  class TT_Callback final
  : public IDL::traits<CCM_TT::TT_Handler>::base_type
  {
  public:
    explicit TT_Callback (IDL::traits< ::RG_LateBinding::CCM_Receiver>::weak_ref_type component_executor)
            : component_executor_(component_executor)
    {}

    void
    on_trigger (
      IDL::traits< ::CCM_TT::TT_Timer>::ref_type timer,
      const ::CCM_TT::TT_Duration& time,
      uint32_t round) override;

  private:
    IDL::traits< ::RG_LateBinding::CCM_Receiver>::weak_ref_type component_executor_;
 };

   void
   TT_Callback::on_trigger (
     IDL::traits< ::CCM_TT::TT_Timer>::ref_type timer,
     const ::CCM_TT::TT_Duration& time,
     uint32_t round)
   {
     X11_UNUSED_ARG(time);
     X11_UNUSED_ARG(round);
     X11_UNUSED_ARG(timer);
     auto cex = IDL::traits<Receiver_exec_i>::narrow (this->component_executor_.lock ());
     if (cex)
     {
       cex->tick();
     }
  }
  //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Receiver_Impl[user_namespace_impl]

  /**
   * Facet Executor Implementation Class : info_get_status_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Receiver_Impl::info_get_status_exec_i[ctor]
  info_get_status_exec_i::info_get_status_exec_i (
    IDL::traits<RG_LateBinding::CCM_Receiver_Context>::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Receiver_Impl::info_get_status_exec_i[ctor]

  info_get_status_exec_i::~info_get_status_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Receiver_Impl::info_get_status_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Receiver_Impl::info_get_status_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Receiver_Impl::info_get_status_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Receiver_Impl::info_get_status_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Receiver_Impl::info_get_status_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Receiver_Impl::info_get_status_exec_i[user_private_ops]


  /** Operations and attributes from info_get_status */

  void
  info_get_status_exec_i::on_requested_deadline_missed (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::RequestedDeadlineMissedStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Receiver_Impl::info_get_status_exec_i::on_requested_deadline_missed[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Receiver_Impl::info_get_status_exec_i::on_requested_deadline_missed[_the_reader_status]
  }

  void
  info_get_status_exec_i::on_sample_lost (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::SampleLostStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Receiver_Impl::info_get_status_exec_i::on_sample_lost[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Receiver_Impl::info_get_status_exec_i::on_sample_lost[_the_reader_status]
  }
  /**
   * Facet Executor Implementation Class : start_reading_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Receiver_Impl::start_reading_exec_i[ctor]
  start_reading_exec_i::start_reading_exec_i (
      IDL::traits<RG_LateBinding::CCM_Receiver_Context>::ref_type context,
      IDL::traits<RG_LateBinding::CCM_Receiver>::weak_ref_type component_executor)
    : context_ (std::move (context))
    , component_executor_ (std::move(component_executor))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Receiver_Impl::start_reading_exec_i[ctor]

  start_reading_exec_i::~start_reading_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Receiver_Impl::start_reading_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Receiver_Impl::start_reading_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Receiver_Impl::start_reading_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Receiver_Impl::start_reading_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Receiver_Impl::start_reading_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Receiver_Impl::start_reading_exec_i[user_private_ops]


  /** Operations and attributes from start_reading */

  void
  start_reading_exec_i::start_read ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Receiver_Impl::start_reading_exec_i::start_read[void]
    auto cex = IDL::traits<Receiver_exec_i>::narrow (this->component_executor_.lock ());
    if (cex)
      cex->start ();
    else
    {
      DDS4CCM_TEST_ERROR << "start_reading_exec_i::start_read - "
        "ERROR: failed to lock component executor" << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Receiver_Impl::start_reading_exec_i::start_read[void]
  }

  void
  start_reading_exec_i::start_new_run (
      uint16_t run)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Receiver_Impl::start_reading_exec_i::start_new_run[_run]
    X11_UNUSED_ARG(run);
    //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Receiver_Impl::start_reading_exec_i::start_new_run[_run]
  }

  void
  start_reading_exec_i::set_reader_properties (
      uint16_t nr_keys,
      uint16_t nr_iterations)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Receiver_Impl::start_reading_exec_i::set_reader_properties[_nr_keys_nr_iterations]
    auto cex = IDL::traits<Receiver_exec_i>::narrow (this->component_executor_.lock ());
    if (cex)
      cex->set_reader_properties (nr_keys, nr_iterations);
    else
    {
      DDS4CCM_TEST_ERROR << "start_reading_exec_i::set_reader_properties - "
        "ERROR: failed to lock component executor" << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Receiver_Impl::start_reading_exec_i::set_reader_properties[_nr_keys_nr_iterations]
  }

  /**
   * Component Executor Implementation Class : Receiver_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Receiver_Impl::Receiver_exec_i[ctor]
  Receiver_exec_i::Receiver_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Receiver_Impl::Receiver_exec_i[ctor]

  Receiver_exec_i::~Receiver_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Receiver_Impl::Receiver_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Receiver_Impl::Receiver_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Receiver_Impl::Receiver_exec_i[user_public_ops]
  void
  Receiver_exec_i::tick ()
  {
    if (DDS4CCM_TEST_UTILS::check_last (
      this->context_->get_connection_info_get_data (),
      this->keys_,
      this->iterations_))
    {
      this->start_read ();
    }
  }

  void
  Receiver_exec_i::start ()
  {
    if (this->first_run_)
    {
      this->test_exception ();
    }
    this->set_topic_name ();

    IDL::traits<CCM_TT::TT_Scheduler>::ref_type tt_s = this->context_->get_connection_tt_scheduler ();

    this->tm_ = tt_s->schedule_repeated_trigger (
                       CORBA::make_reference<TT_Callback> (IDL::traits< RG_LateBinding::CCM_Receiver>::narrow (this->_lock())),
                       CCM_TT::TT_Duration (1, 0),
                       CCM_TT::TT_Duration (1, 0),
                       0);
  }

  void
  Receiver_exec_i::set_reader_properties (
    uint16_t keys, uint16_t iterations)
  {
    DDS4CCM_TEST_DEBUG << "Receiver_exec_i::set_reader_properties - "
      << "new reader properties: keys <" << keys << "> - iterations <"
      << iterations << ">." << std::endl;
    this->keys_ = keys;
    this->iterations_ = iterations;
  }


  //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Receiver_Impl::Receiver_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Receiver_Impl::Receiver_exec_i[user_private_ops]
  void
  Receiver_exec_i::start_read ()
  {
    if (this->tm_)
    {
      this->tm_->cancel ();
    }

    // The same topic name could be set again without
    // any issues.
    this->set_topic_name ();

    this->start_getting ();
    this->start_reading ();

    // switch to the second topic
    if (this->first_run_)
    {
      this->inform_sender ();
      this->first_run_ = false;
    }
  }

  void
  Receiver_exec_i::inform_sender ()
  {
    try
    {
      IDL::traits< WriterStarter>::ref_type starter =
        this->context_->get_connection_writer_start ();
      starter->start_write ();
    }
    catch_dds4ccm_test_ex(ex, "Receiver_exec_i::inform_sender")
  }

  void
  Receiver_exec_i::check_samples (
    const std::string &test,
    const CommonTestMessageSeq &samples,
    uint16_t expected)
  {
    bool error = samples.size () != expected;
    if (test == "get")
    {
      error = samples.size () < expected;
    }
    else
    {
      // it could be that sample were read in the last-sample-checker.
      // Therefor the getter does not represent the correct number of
      // samples in DDS. The reader does since it does read all samples.
      this->samples_read_ += samples.size ();
    }

    if (error)
    {
      DDS4CCM_TEST_ERROR << "Receiver_exec_i::check_samples - "
        << "ERROR: Unexpected number of " << test << " samples received: "
        << "expected <";
      if (test == "get")
      {
        DDS4CCM_TEST_ERROR << "at least ";
      }
      DDS4CCM_TEST_ERROR << expected << "> - received <"
        << samples.size () << ">." << std::endl;
    }
    else
    {
      DDS4CCM_TEST_DEBUG << "Receiver_exec_i::check_samples - "
        << "(" << test << ") samples found: <" << samples.size () << ">."
        << " Samples: " << std::endl;
    }
    for (const CommonTestMessage &msg : samples)
    {
      DDS4CCM_TEST_DEBUG << '\t' << msg << std::endl;
    }
  }

  /**
   * The DDS4CCM connector is not initialized yet. Reading samples on an
   * invalid datareader reference will result in a INV_OBJREF exception.
   */
  void
  Receiver_exec_i::test_exception ()
  {
    try
    {
      IDL::traits< ::CommonTestConnector::Reader>::ref_type reader =
        this->context_->get_connection_info_get_data ();
      if (!reader)
      {
        DDS4CCM_TEST_ERROR << "Receiver_exec_i::test_exception - "
          "ERROR: Unable to get reader interface from the context." << std::endl;
        return;
      }

      ::CCM_DDS::ReadInfo readinfo;
      CommonTestMessage sample ("KEY_1", 0);

      reader->read_one_last (sample, readinfo, ::DDS::HANDLE_NIL);

      DDS4CCM_TEST_ERROR << "Receiver_exec_i::test_exception - "
        "ERROR: No exception caught before topic name has been set" << std::endl;
    }
    catch (const ::CORBA::INV_OBJREF &)
    {
      DDS4CCM_TEST_DEBUG << "Receiver_exec_i::test_exception - "
        "Expected INV_OBJREF thrown." << std::endl;
    }
    catch_dds4ccm_test_ex(ex, "Receiver_exec_i::test_exception")
  }

  void
  Receiver_exec_i::start_reading ()
  {
    DDS4CCM_TEST_DEBUG << "Receiver_exec_i::start_reading - "
      "Start reading." << std::endl;
    IDL::traits< ::CommonTestConnector::Reader>::ref_type reader =
      this->context_->get_connection_info_get_data ();
    try
    {
      CommonTestMessageSeq samples;
      ::CCM_DDS::ReadInfoSeq readinfo;
      reader->read_all (samples, readinfo);
      this->check_samples ("read", samples, this->iterations_ * this->keys_);
    }
    catch_dds4ccm_test_ex(ex, "Receiver_exec_i::start_reading")
  }

  void
  Receiver_exec_i::start_getting ()
  {
    try
    {
      IDL::traits< ::CommonTestConnector::Getter>::ref_type getter =
        this->context_->get_connection_info_get_fresh_data ();
      if (!getter)
      {
        DDS4CCM_TEST_ERROR << "Receiver_exec_i::start_getting - "
          "ERROR: Unable to get writer interface from the CIAO context." << std::endl;
        return;
      }
      getter->time_out (DDS::Duration_t (1, 0));

      CommonTestMessageSeq samples;
      ::CCM_DDS::ReadInfoSeq readinfos;
      getter->get_many (samples, readinfos);
      this->check_samples ("get", samples, 1);
    }
    catch_dds4ccm_test_ex(ex, "Receiver_exec_i::start_getting")
  }

  void
  Receiver_exec_i::set_topic_name ()
  {
    try
    {
      std::string const topic_name (this->first_run_ ? "FirstLateBindingTopic" : "SecondLateBindingTopic");

      DDS4CCM_TEST_DEBUG << "Receiver_exec_i::set_topic_name - "
        << "Setting topic name to <" << topic_name << ">." << std::endl;
      IDL::traits< ::CommonTestConnector::Getter>::ref_type getter =
        this->context_->get_connection_info_get_fresh_data ();
      IDL::traits< ::CORBA::Object>::ref_type cmp = getter->_get_component ();
      if (!cmp)
      {
        DDS4CCM_TEST_ERROR << "Receiver_exec_i::set_topic_name - "
          "ERROR: Unable to get component interface." << std::endl;
        return;
      }
      IDL::traits< ::CommonTestConnector::CCM_DDS_Event>::ref_type conn =
        IDL::traits< ::CommonTestConnector::CCM_DDS_Event >::narrow (cmp);
      if (!conn)
      {
        DDS4CCM_TEST_ERROR << "ERROR: Receiver_exec_i::set_topic_name - "
          "Unable to narrow connector interface." << std::endl;
        return;
      }

      conn->topic_name (topic_name);
    }
    catch (const ::CCM_DDS::NonChangeable &)
    {
      DDS4CCM_TEST_ERROR << "Receiver_exec_i::set_topic_name - "
        "ERROR: Caught NonChangeable exception." << std::endl;
    }
    catch_dds4ccm_test_ex(ex, "Receiver_exec_i::set_topic_name")
  }
  //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Receiver_Impl::Receiver_exec_i[user_private_ops]

  /** Session component operations */
  void Receiver_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Receiver_Impl::Receiver_exec_i[configuration_complete]
    DDS4CCM_TEST_DEBUG << "Receiver_exec_i::configuration_complete" << std::endl;
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Receiver_Impl::Receiver_exec_i[configuration_complete]
  }

  void Receiver_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Receiver_Impl::Receiver_exec_i[ccm_activate]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Receiver_Impl::Receiver_exec_i[ccm_activate]
  }

  void Receiver_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Receiver_Impl::Receiver_exec_i[ccm_passivate]
    if (!this->tm_)
    {
      DDS4CCM_TEST_ERROR << "ERROR: Receiver_exec_i::ccm_passivate - "
                            "Test did call start."
                         << std::endl;
    }
    else
    {
      if (!this->tm_->is_canceled())
      {
        this->tm_->cancel();
      }
    }
    if (this->samples_read_ == 0)
    {
      DDS4CCM_TEST_ERROR << "Receiver_exec_i::ccm_passivate - "
        << "ERROR: No samples were read from DDS." << std::endl;
    }
    else
    {
      DDS4CCM_TEST_DEBUG << "Receiver_exec_i::ccm_passivate - "
        << "<" << this->samples_read_ << "> samples were read from DDS." << std::endl;
    }
    if (this->samples_read_ != (2 * this->keys_ * this->iterations_))
    {
      DDS4CCM_TEST_ERROR << "Receiver_exec_i::ccm_passivate - "
        << "ERROR: unexpected number of samples read from DDS: expected <"
        << 2 * this->keys_ * this->iterations_ << "> - read <" << this->samples_read_
        << ">." << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Receiver_Impl::Receiver_exec_i[ccm_passivate]
  }

  void Receiver_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Receiver_Impl::Receiver_exec_i[ccm_remove]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Receiver_Impl::Receiver_exec_i[ccm_remove]
  }

  IDL::traits< ::CCM_DDS::CCM_PortStatusListener>::ref_type
  Receiver_exec_i::get_info_get_status ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Receiver_Impl::Receiver_exec_i[get_info_get_status]
  if (!this->info_get_status_)
  {
    this->info_get_status_ = CORBA::make_reference <info_get_status_exec_i> (this->context_);
  }
  return this->info_get_status_;
  //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Receiver_Impl::Receiver_exec_i[get_info_get_status]
  }

  IDL::traits< CCM_ReaderStarter>::ref_type
  Receiver_exec_i::get_start_reading ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Receiver_Impl::Receiver_exec_i[get_start_reading]
  if (!this->start_reading_)
  {
    this->start_reading_ = CORBA::make_reference <start_reading_exec_i> (
      this->context_, IDL::traits<RG_LateBinding::CCM_Receiver>::narrow (this->_lock ()));
  }
  return this->start_reading_;
  //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Receiver_Impl::Receiver_exec_i[get_start_reading]
  }

  /// Operations from Components::SessionComponent
  void
  Receiver_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Receiver_Impl::Receiver_exec_i[set_session_context]
    this->context_ = IDL::traits<RG_LateBinding::CCM_Receiver_Context>::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Receiver_Impl::Receiver_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Receiver_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Receiver_Impl[user_namespace_end_impl]

} // namespace RG_LateBinding_Receiver_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : RG_LateBinding_Receiver_Impl[factory]
extern "C" void
create_RG_LateBinding_Receiver_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <RG_LateBinding_Receiver_Impl::Receiver_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : RG_LateBinding_Receiver_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : rg_late_bind_receiver_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
