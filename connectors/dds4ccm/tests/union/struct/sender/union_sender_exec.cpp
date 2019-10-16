// -*- C++ -*-
/**
 * @file    union_sender_exec.cpp
 * @author  Marcel Smit
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : union_sender_impl.cpp[Header]

#include "union_sender_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Sender_Impl[user_includes]
#include "dds4ccm/tests/common/dds4ccm_test_utils.h"
//@@{__RIDL_REGEN_MARKER__} - END : Uni_Sender_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Sender_Impl[user_global_impl]
// Your code here
//@@{__RIDL_REGEN_MARKER__} - END : Uni_Sender_Impl[user_global_impl]

namespace Uni_Sender_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Sender_Impl[user_namespace_impl]
  class TT_Callback final
  : public IDL::traits<CCM_TT::TT_Handler>::base_type
  {
  public:
    TT_Callback (IDL::traits< ::Uni::CCM_Sender>::weak_ref_type component_executor,
                 bool activate)
    : component_executor_(component_executor)
    , activate_(activate)
    {}

    virtual
    void
    on_trigger (
           IDL::traits< ::CCM_TT::TT_Timer>::ref_type timer,
           const ::CCM_TT::TT_Duration& time,
           uint32_t round) override;

  private:
    IDL::traits< ::Uni::CCM_Sender>::weak_ref_type component_executor_;
    bool const activate_;
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
    auto cex = IDL::traits<Sender_exec_i>::narrow (this->component_executor_.lock ());
    if (cex)
    {
      if (this->activate_)
        cex->check_status();
      else
       cex->tick();
    }
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Uni_Sender_Impl[user_namespace_impl]

  /**
   * Facet Executor Implementation Class : connector_status_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Sender_Impl::connector_status_exec_i[ctor]
  connector_status_exec_i::connector_status_exec_i (
    IDL::traits< ::Uni::CCM_Sender_Context >::ref_type context,
    IDL::traits< Uni::CCM_Sender>::weak_ref_type component_executor)
    : context_ (std::move (context))
    , component_executor_ (std::move(component_executor))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Uni_Sender_Impl::connector_status_exec_i[ctor]

  connector_status_exec_i::~connector_status_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Sender_Impl::connector_status_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Uni_Sender_Impl::connector_status_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Sender_Impl::connector_status_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Uni_Sender_Impl::connector_status_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Sender_Impl::connector_status_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Uni_Sender_Impl::connector_status_exec_i[user_private_ops]


  /** Operations and attributes from connector_status */

  void
  connector_status_exec_i::on_inconsistent_topic (
      IDL::traits< ::DDS::Topic>::ref_type the_topic,
      const ::DDS::InconsistentTopicStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Sender_Impl::connector_status_exec_i::on_inconsistent_topic[_the_topic_status]
    X11_UNUSED_ARG(the_topic);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : Uni_Sender_Impl::connector_status_exec_i::on_inconsistent_topic[_the_topic_status]
  }

  void
  connector_status_exec_i::on_requested_incompatible_qos (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::RequestedIncompatibleQosStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Sender_Impl::connector_status_exec_i::on_requested_incompatible_qos[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : Uni_Sender_Impl::connector_status_exec_i::on_requested_incompatible_qos[_the_reader_status]
  }

  void
  connector_status_exec_i::on_sample_rejected (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::SampleRejectedStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Sender_Impl::connector_status_exec_i::on_sample_rejected[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : Uni_Sender_Impl::connector_status_exec_i::on_sample_rejected[_the_reader_status]
  }

  void
  connector_status_exec_i::on_offered_deadline_missed (
      IDL::traits< ::DDS::DataWriter>::ref_type the_writer,
      const ::DDS::OfferedDeadlineMissedStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Sender_Impl::connector_status_exec_i::on_offered_deadline_missed[_the_writer_status]
    X11_UNUSED_ARG(the_writer);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : Uni_Sender_Impl::connector_status_exec_i::on_offered_deadline_missed[_the_writer_status]
  }

  void
  connector_status_exec_i::on_offered_incompatible_qos (
      IDL::traits< ::DDS::DataWriter>::ref_type the_writer,
      const ::DDS::OfferedIncompatibleQosStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Sender_Impl::connector_status_exec_i::on_offered_incompatible_qos[_the_writer_status]
    X11_UNUSED_ARG(the_writer);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : Uni_Sender_Impl::connector_status_exec_i::on_offered_incompatible_qos[_the_writer_status]
  }

  void
  connector_status_exec_i::on_unexpected_status (
      IDL::traits< ::DDS::Entity>::ref_type the_entity,
      ::DDS::StatusKind status_kind)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Sender_Impl::connector_status_exec_i::on_unexpected_status[_the_entity_status_kind]
    DDS4CCM_TEST_DEBUG << "connector_status_exec_i::on_unexpected_status status_kind: " << DDS::dds_write(status_kind) << std::endl;
    // dds4ccm/tests/updater/sender/updater_sender_exec.cpp for an explanation of the
    // started_ flag.
    if (!this->started_)
    {
      if (DDS4CCM_TEST_UTILS::check_publication_matched_status (the_entity, status_kind, 1))
      {
        auto cex = IDL::traits<Sender_exec_i>::narrow (this->component_executor_.lock ());
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
    //@@{__RIDL_REGEN_MARKER__} - END : Uni_Sender_Impl::connector_status_exec_i::on_unexpected_status[_the_entity_status_kind]
  }

  /**
   * Component Executor Implementation Class : Sender_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Sender_Impl::Sender_exec_i[ctor]
  Sender_exec_i::Sender_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Uni_Sender_Impl::Sender_exec_i[ctor]

  Sender_exec_i::~Sender_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Sender_Impl::Sender_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Uni_Sender_Impl::Sender_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Sender_Impl::Sender_exec_i[user_public_ops]
  void
  Sender_exec_i::check_status ()
  {
    IDL::traits< ::DDS::DataWriter >::ref_type writer_dds_entity =
      this->context_->get_connection_info_write_dds_entity ();
    if (writer_dds_entity)
    {
      ::DDS::PublicationMatchedStatus status {};
      ::DDS::ReturnCode_t const retcode = writer_dds_entity->get_publication_matched_status (status);

      if (retcode != ::DDS::RETCODE_OK)
      {
        DDS4CCM_TEST_ERROR <<"Sender_exec_i::check_status - "
          << "Error: Unable to get_publication_matched_status: <"
          << IDL::traits< ::DDS::ReturnCode_t >::write<retcode_formatter> (retcode)
          << ">." << std::endl;
      }
      else
      {
        DDS4CCM_TEST_DEBUG << "Sender_exec_i::check_status publication_matched current_count: "
                         << status.current_count() << std::endl;

        if (status.current_count() == 1)
        {
          DDS4CCM_TEST_DEBUG << "Sender_exec_i::check_status publication_matched received" << std::endl;
          this->tm_activate_->cancel();
          this->start_publishing();
        }
      }
    }
  }

  void
  Sender_exec_i::start_publishing ()
  {
    if (!this->already_publishing_)
    {
      this->already_publishing_ = true;

      this->tm_activate_->cancel();

      this->tm_ = tt_s->schedule_repeated_trigger (
                    CORBA::make_reference<TT_Callback> (IDL::traits< Uni::CCM_Sender>::narrow (this->_lock()),false),
                    CCM_TT::TT_Duration (1, 0),
                    CCM_TT::TT_Duration (1, 0),
                    0);
    }
  }

  void
  Sender_exec_i::tick ()
  {
    try
    {
      IDL::traits < Uni::UnionConnector::Writer >::ref_type writer =
        this->context_->get_connection_info_write_data ();

      Uni::Assignment assignment { Uni::Assignment::NONE };
      switch (this->last_assignment_)
      {
        case Uni::Assignment::NONE:
          assignment = Uni::Assignment::A;
          break;
        case Uni::Assignment::A:
          assignment = Uni::Assignment::B;
          break;
        case Uni::Assignment::B:
          assignment = Uni::Assignment::C;
          break;
        case Uni::Assignment::C:
          assignment = Uni::Assignment::D;
          break;
        case Uni::Assignment::D:
          this->stop ();
          break;
      }

      switch (assignment)
      {
        case Uni::Assignment::A:
          {
            // Assignment A
            ////////////////////////////////////////////
            // First assignment; empty, uninitialized unions
            Uni::Data dt_a;
            Uni::B03 b_a;

            Uni::UnionMessage msg_a { assignment, b_a, dt_a };

            writer->write_one (msg_a, ::DDS::HANDLE_NIL);
            DDS4CCM_TEST_DEBUG << "Written sample to DDS " << msg_a << std::endl;

            this->last_assignment_ = Uni::Assignment::A;
          }
          break;
        case Uni::Assignment::B:
          {
            // Assignment B
            ////////////////////////////////////////////
            Uni::Data dt_b;
            Uni::B03 b_b;

            // Set the defaults
            b_b.b_03_d (5);
            dt_b.longData (5);

            Uni::UnionMessage msg_b { assignment, b_b, dt_b };

            writer->write_one (msg_b, ::DDS::HANDLE_NIL);
            DDS4CCM_TEST_DEBUG << "Written sample to DDS " << msg_b << std::endl;

            this->last_assignment_ = Uni::Assignment::B;
          }
          break;
        case Uni::Assignment::C:
          {
            // Assignment C
            ////////////////////////////////////////////
            Uni::Data dt_c;
            Uni::B03 b_c;

            // Set the first item
            b_c.b_03_1 (Uni::B01 (5));
            dt_c.longData (5);

            Uni::UnionMessage msg_c { assignment, b_c, dt_c };

            writer->write_one (msg_c, ::DDS::HANDLE_NIL);
            DDS4CCM_TEST_DEBUG << "Written sample to DDS " << msg_c << std::endl;

            this->last_assignment_ = Uni::Assignment::C;
          }
          break;
        case Uni::Assignment::D:
          {
            // Assignment D
            ////////////////////////////////////////////
            Uni::Data dt_d;
            Uni::B03 b_d;

            // Set the last item
            b_d.b_03_5 ("XX");
            dt_d.globalData (Global (4));

            Uni::UnionMessage msg_d { assignment, b_d, dt_d };

            writer->write_one (msg_d, ::DDS::HANDLE_NIL);
            DDS4CCM_TEST_DEBUG << "Written sample to DDS " << msg_d << std::endl;

            this->last_assignment_ = Uni::Assignment::D;
          }
        case Uni::Assignment::NONE:
          break;
      }
    }
    catch (const CORBA::Exception &ex)
    {
      DDS4CCM_TEST_ERROR << "Sender_exec_i::tick: ERROR: "
        "caught CORBA exception: " << ex << std::endl;
    }
    catch (const std::exception &ex)
    {
      DDS4CCM_TEST_ERROR << "Sender_exec_i::tick: ERROR: "
        "caught std::exception: " << ex.what() << std::endl;
    }
    catch (...)
    {
      DDS4CCM_TEST_ERROR << "Sender_exec_i::tick: ERROR: "
        "caught unexpected exception" << std::endl;
    }
  }

  //@@{__RIDL_REGEN_MARKER__} - END : Uni_Sender_Impl::Sender_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Sender_Impl::Sender_exec_i[user_private_ops]
  void
  Sender_exec_i::stop ()
  {
    this->tm_->cancel();
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Uni_Sender_Impl::Sender_exec_i[user_private_ops]

  /** Session component operations */
  void Sender_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Sender_Impl::Sender_exec_i[configuration_complete]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Uni_Sender_Impl::Sender_exec_i[configuration_complete]
  }

  void Sender_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Sender_Impl::Sender_exec_i[ccm_activate]
    //start status checker
    this->tt_s = this->context_->get_connection_tt_scheduler ();
    this->tm_activate_ = this->tt_s->schedule_repeated_trigger (
                              CORBA::make_reference<TT_Callback> (IDL::traits< Uni::CCM_Sender>::narrow (this->_lock()),true),
                              CCM_TT::TT_Duration (0, 1000000000),
                              CCM_TT::TT_Duration (0, 1000000000),
                              0);
    //@@{__RIDL_REGEN_MARKER__} - END : Uni_Sender_Impl::Sender_exec_i[ccm_activate]
  }

  void Sender_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Sender_Impl::Sender_exec_i[ccm_passivate]
    if (!this->tm_)
    {
       DDS4CCM_TEST_ERROR << "ERROR: Sender_exec_i::ccm_passivate - "
                             "Test did not start, because no DDS::PUBLICATION_MATCHED_STATUS was received."
                          << std::endl;
    }
    else
    {
      if (!this->tm_->is_canceled())
      {
        this->tm_->cancel();
      }
      if (this->tm_->rounds() < 1)
      {
        DDS4CCM_TEST_ERROR << "ERROR: Sender_exec_i::ccm_passivate - "
                             "Timer of tests didn't tick." << std::endl;
      }
      else
      {
        DDS4CCM_TEST_DEBUG << "Sender_exec_i::ccm_passivate - "
                                  "Timer ticked " << this->tm_->rounds() << " times." << std::endl;
      }
    }
    //@@{__RIDL_REGEN_MARKER__} - END : Uni_Sender_Impl::Sender_exec_i[ccm_passivate]
  }

  void Sender_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Sender_Impl::Sender_exec_i[ccm_remove]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Uni_Sender_Impl::Sender_exec_i[ccm_remove]
  }

  IDL::traits< ::CCM_DDS::CCM_ConnectorStatusListener >::ref_type
  Sender_exec_i::get_connector_status ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Sender_Impl::Sender_exec_i[get_connector_status]
    if (!this->connector_status_)
    {
        this->connector_status_ =
          CORBA::make_reference <connector_status_exec_i>
            (this->context_, IDL::traits<Uni::CCM_Sender>::narrow (this->_lock()));
    }
    return this->connector_status_;
  //@@{__RIDL_REGEN_MARKER__} - END : Uni_Sender_Impl::Sender_exec_i[get_connector_status]
  }

  /// Operations from Components::SessionComponent
  void
  Sender_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Sender_Impl::Sender_exec_i[set_session_context]
    this->context_ = IDL::traits< ::Uni::CCM_Sender_Context >::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : Uni_Sender_Impl::Sender_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Sender_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : Uni_Sender_Impl[user_namespace_end_impl]

} // namespace Uni_Sender_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Sender_Impl[factory]
extern "C" void
create_Uni_Sender_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <Uni_Sender_Impl::Sender_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : Uni_Sender_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : union_sender_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
