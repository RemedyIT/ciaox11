// -*- C++ -*-
/**
 * @file    custom_example_sender_exec.cpp
 * @author  Marcel Smit
 *
 * @brief   Sender component implementation of the IDL example.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : custom_example_sender_impl.cpp[Header]

#include "custom_example_sender_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicPublisher_comp_Impl[user_includes]
#include "dds4ccm/logger/dds4ccm_testlog.h"
#include "dds4ccm/tests/common/dds4ccm_test_utils.h"
//@@{__RIDL_REGEN_MARKER__} - END : Example_BasicPublisher_comp_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicPublisher_comp_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : Example_BasicPublisher_comp_Impl[user_global_impl]

namespace Example_BasicPublisher_comp_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicPublisher_comp_Impl[user_namespace_impl]
  class TT_Callback final
  : public IDL::traits<CCM_TT::TT_Handler>::base_type
  {
  public:
    explicit TT_Callback (IDL::traits< ::Example::CCM_BasicPublisher_comp>::weak_ref_type component_executor)
    : component_executor_(component_executor)
     {}

    void
    on_trigger (
        IDL::traits< ::CCM_TT::TT_Timer>::ref_type timer,
        const ::CCM_TT::TT_Duration& time,
        uint32_t round) override;

  private:
    IDL::traits< ::Example::CCM_BasicPublisher_comp>::weak_ref_type component_executor_;
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
    auto cex = IDL::traits<BasicPublisher_comp_exec_i>::narrow (this->component_executor_.lock ());
    if (cex)
    {
      cex->tick();
    }
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicPublisher_comp_Impl[user_namespace_impl]

  /**
   * Facet Executor Implementation Class : CA1DataPub_CSL_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicPublisher_comp_Impl::CA1DataPub_CSL_exec_i[ctor]
  CA1DataPub_CSL_exec_i::CA1DataPub_CSL_exec_i (
    IDL::traits<Example::CCM_BasicPublisher_comp_Context>::ref_type context,
    IDL::traits<Example::CCM_BasicPublisher_comp>::weak_ref_type component_executor)
    : context_ (std::move (context))
    , component_executor_ (std::move(component_executor))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicPublisher_comp_Impl::CA1DataPub_CSL_exec_i[ctor]

  CA1DataPub_CSL_exec_i::~CA1DataPub_CSL_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicPublisher_comp_Impl::CA1DataPub_CSL_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicPublisher_comp_Impl::CA1DataPub_CSL_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicPublisher_comp_Impl::CA1DataPub_CSL_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicPublisher_comp_Impl::CA1DataPub_CSL_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicPublisher_comp_Impl::CA1DataPub_CSL_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicPublisher_comp_Impl::CA1DataPub_CSL_exec_i[user_private_ops]


  /** Operations and attributes from CA1DataPub_CSL */

  void
  CA1DataPub_CSL_exec_i::on_inconsistent_topic (
      IDL::traits< ::DDS::Topic>::ref_type the_topic,
      const ::DDS::InconsistentTopicStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicPublisher_comp_Impl::CA1DataPub_CSL_exec_i::on_inconsistent_topic[_the_topic_status]
    X11_UNUSED_ARG(the_topic);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicPublisher_comp_Impl::CA1DataPub_CSL_exec_i::on_inconsistent_topic[_the_topic_status]
  }

  void
  CA1DataPub_CSL_exec_i::on_requested_incompatible_qos (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::RequestedIncompatibleQosStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicPublisher_comp_Impl::CA1DataPub_CSL_exec_i::on_requested_incompatible_qos[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicPublisher_comp_Impl::CA1DataPub_CSL_exec_i::on_requested_incompatible_qos[_the_reader_status]
  }

  void
  CA1DataPub_CSL_exec_i::on_sample_rejected (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::SampleRejectedStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicPublisher_comp_Impl::CA1DataPub_CSL_exec_i::on_sample_rejected[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicPublisher_comp_Impl::CA1DataPub_CSL_exec_i::on_sample_rejected[_the_reader_status]
  }

  void
  CA1DataPub_CSL_exec_i::on_offered_deadline_missed (
      IDL::traits< ::DDS::DataWriter>::ref_type the_writer,
      const ::DDS::OfferedDeadlineMissedStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicPublisher_comp_Impl::CA1DataPub_CSL_exec_i::on_offered_deadline_missed[_the_writer_status]
    X11_UNUSED_ARG(the_writer);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicPublisher_comp_Impl::CA1DataPub_CSL_exec_i::on_offered_deadline_missed[_the_writer_status]
  }

  void
  CA1DataPub_CSL_exec_i::on_offered_incompatible_qos (
      IDL::traits< ::DDS::DataWriter>::ref_type the_writer,
      const ::DDS::OfferedIncompatibleQosStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicPublisher_comp_Impl::CA1DataPub_CSL_exec_i::on_offered_incompatible_qos[_the_writer_status]
    X11_UNUSED_ARG(the_writer);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicPublisher_comp_Impl::CA1DataPub_CSL_exec_i::on_offered_incompatible_qos[_the_writer_status]
  }

  void
  CA1DataPub_CSL_exec_i::on_unexpected_status (
      IDL::traits< ::DDS::Entity>::ref_type the_entity,
      ::DDS::StatusKind status_kind)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicPublisher_comp_Impl::CA1DataPub_CSL_exec_i::on_unexpected_status[_the_entity_status_kind]
    DDS4CCM_TEST_DEBUG << "connector_status_exec_i::on_unexpected_status status_kind <" << DDS::dds_write(status_kind) << ">" << std::endl;
    if (!this->started_)
    {
      // If not started yet and number of connected datareaders is as expected,
      // start publishing and set started_ to true, so start_publishing is invoked only once.
      if (DDS4CCM_TEST_UTILS::check_publication_matched_status (the_entity, status_kind, 1))
      {
        auto cex = IDL::traits< BasicPublisher_comp_exec_i>::narrow (this->component_executor_.lock ());
        if (cex)
        {
          this->started_ = true;
          cex->start_publishing ();
        }
        else
        {
          DDS4CCM_TEST_DEBUG << "connector_status_exec_i::on_unexpected_status - "
                            << "WARNING: failed to lock component executor" << std::endl;
        }
      }
    }
    //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicPublisher_comp_Impl::CA1DataPub_CSL_exec_i::on_unexpected_status[_the_entity_status_kind]
  }

  /**
   * Component Executor Implementation Class : BasicPublisher_comp_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicPublisher_comp_Impl::BasicPublisher_comp_exec_i[ctor]
  BasicPublisher_comp_exec_i::BasicPublisher_comp_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicPublisher_comp_Impl::BasicPublisher_comp_exec_i[ctor]

  BasicPublisher_comp_exec_i::~BasicPublisher_comp_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicPublisher_comp_Impl::BasicPublisher_comp_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicPublisher_comp_Impl::BasicPublisher_comp_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicPublisher_comp_Impl::BasicPublisher_comp_exec_i[user_public_ops]
  void
  BasicPublisher_comp_exec_i::start_publishing ()
  {
    IDL::traits<CCM_TT::TT_Scheduler>::ref_type tt_s = this->context_->get_connection_tt_scheduler ();

    this->tm_ = tt_s->schedule_repeated_trigger (
                      CORBA::make_reference<TT_Callback> (IDL::traits< Example::CCM_BasicPublisher_comp>::narrow (this->_lock())),
                      CCM_TT::TT_Duration (0, 1000000),
                      CCM_TT::TT_Duration (0, 1000000),
                      0);
  }

  void
  BasicPublisher_comp_exec_i::tick ()
  {
    try
    {
      IDL::traits< Example::CA1_conn::Writer>::ref_type writer =
        this->context_->get_connection_CA1DataPub_data ();

      if (this->count () == this->counter_)
      {
        this->stop_publishing ();
        return;
      }

      Example::NA4 hdr (
        this->counter_,
        this->counter_ + 100,
        this->counter_ + 1000,
        this->counter_ * 10,
        this->counter_ * 20,
        this->counter_ * 100,
        this->counter_ * 200);

      Example::NA5 na5 (this->counter_);

      Example::CA09 ca09 (na5.NA5_1 (), na5);

      Example::CA1_msg msg (hdr, ca09);

      writer->write_one (msg, ::DDS::HANDLE_NIL);

      ++this->counter_;

    }
    catch (const CORBA::Exception &ex)
    {
      DDS4CCM_TEST_ERROR << "ERROR: BasicPublisher_comp_exec_i::tick - "
        << "caught unexpected CORBA exception: "
        << ex << std::endl;
    }
    catch (const std::exception &ex)
    {
      DDS4CCM_TEST_ERROR << "ERROR: BasicPublisher_comp_exec_i::tick - "
        << "caught std::exception: "
        << ex.what() << std::endl;
    }
    catch (...)
    {
      DDS4CCM_TEST_ERROR << "ERROR: BasicPublisher_comp_exec_i::tick - "
        << "ERROR caught unexpected exception"
        << std::endl;
    }
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicPublisher_comp_Impl::BasicPublisher_comp_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicPublisher_comp_Impl::BasicPublisher_comp_exec_i[user_private_ops]
  void
  BasicPublisher_comp_exec_i::stop_publishing ()
  {
    if (this->tm_)
    {
      this->tm_->cancel();
      DDS4CCM_TEST_DEBUG << "BasicPublisher_comp_exec_i::stop_publishing : Timer canceled." << std::endl;
    }
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicPublisher_comp_Impl::BasicPublisher_comp_exec_i[user_private_ops]

  /** Session component operations */
  void BasicPublisher_comp_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicPublisher_comp_Impl::BasicPublisher_comp_exec_i[configuration_complete]
    DDS4CCM_TEST_DEBUG << "BasicPublisher_comp_exec_i::configuration_complete" << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicPublisher_comp_Impl::BasicPublisher_comp_exec_i[configuration_complete]
  }

  void BasicPublisher_comp_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicPublisher_comp_Impl::BasicPublisher_comp_exec_i[ccm_activate]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicPublisher_comp_Impl::BasicPublisher_comp_exec_i[ccm_activate]
  }

  void BasicPublisher_comp_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicPublisher_comp_Impl::BasicPublisher_comp_exec_i[ccm_passivate]
    if (this->tm_->rounds() < 1)
    {
      DDS4CCM_TEST_ERROR << "ERROR: BasicPublisher_comp_exec_i::ccm_passivate - "
        "Test did not start." << std::endl;
    }
    else
    {
      this->stop_publishing ();
      DDS4CCM_TEST_DEBUG << "BasicPublisher_comp_exec_i::ccm_passivate : <"
        << this->counter_ << "> samples have been written to DDS" << std::endl;
    }


    //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicPublisher_comp_Impl::BasicPublisher_comp_exec_i[ccm_passivate]
  }

  void BasicPublisher_comp_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicPublisher_comp_Impl::BasicPublisher_comp_exec_i[ccm_remove]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicPublisher_comp_Impl::BasicPublisher_comp_exec_i[ccm_remove]
  }

  IDL::traits< ::CCM_DDS::CCM_ConnectorStatusListener>::ref_type
  BasicPublisher_comp_exec_i::get_CA1DataPub_CSL ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicPublisher_comp_Impl::BasicPublisher_comp_exec_i[get_CA1DataPub_CSL]
    if (!this->CA1DataPub_CSL_)
      {
        this->CA1DataPub_CSL_ =
          CORBA::make_reference <CA1DataPub_CSL_exec_i> (
            this->context_, IDL::traits<Example::CCM_BasicPublisher_comp>::narrow (this->_lock()));
      }
    return this->CA1DataPub_CSL_;
  //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicPublisher_comp_Impl::BasicPublisher_comp_exec_i[get_CA1DataPub_CSL]
  }


  uint32_t
  BasicPublisher_comp_exec_i::count ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicPublisher_comp_Impl::BasicPublisher_comp_exec_i::count[getter]
    return this->count_;
    //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicPublisher_comp_Impl::BasicPublisher_comp_exec_i::count[getter]
  }

  void
  BasicPublisher_comp_exec_i::count (
      uint32_t count)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicPublisher_comp_Impl::BasicPublisher_comp_exec_i::count[setter]
    this->count_ = count;
    //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicPublisher_comp_Impl::BasicPublisher_comp_exec_i::count[setter]
  }

  /// Operations from Components::SessionComponent
  void
  BasicPublisher_comp_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicPublisher_comp_Impl::BasicPublisher_comp_exec_i[set_session_context]
    this->context_ = IDL::traits<Example::CCM_BasicPublisher_comp_Context>::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicPublisher_comp_Impl::BasicPublisher_comp_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicPublisher_comp_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicPublisher_comp_Impl[user_namespace_end_impl]

} // namespace Example_BasicPublisher_comp_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicPublisher_comp_Impl[factory]
extern "C" void
create_Example_BasicPublisher_comp_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <Example_BasicPublisher_comp_Impl::BasicPublisher_comp_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : Example_BasicPublisher_comp_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : custom_example_sender_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
