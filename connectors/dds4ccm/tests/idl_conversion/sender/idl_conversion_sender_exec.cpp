// -*- C++ -*-
/**
 * @file    idl_conversion_sender_exec.cpp
 * @author  Marcel Smit
 *
 * @brief   Sender component implementation of the IDL conversion test.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : idl_conversion_sender_impl.cpp[Header]

#include "idl_conversion_sender_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Sender_Impl[user_includes]
#include "dds4ccm/tests/common/dds4ccm_test_utils.h"
//@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Sender_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Sender_Impl[user_global_impl]
constexpr uint16_t keys () { return 10; }
//@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Sender_Impl[user_global_impl]

namespace IDL_Conversion_Test_Sender_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Sender_Impl[user_namespace_impl]
  class TT_Callback final
    : public IDL::traits<CCM_TT::TT_Handler>::base_type
  {
  public:
    TT_Callback (IDL::traits< ::IDL_Conversion_Test::CCM_Sender>::weak_ref_type component_executor,
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
    IDL::traits< ::IDL_Conversion_Test::CCM_Sender>::weak_ref_type component_executor_;
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
  //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Sender_Impl[user_namespace_impl]

  /**
   * Facet Executor Implementation Class : connector_status_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Sender_Impl::connector_status_exec_i[ctor]
  connector_status_exec_i::connector_status_exec_i (
      IDL::traits<IDL_Conversion_Test::CCM_Sender_Context>::ref_type context,
      IDL::traits<IDL_Conversion_Test::CCM_Sender>::weak_ref_type component_executor)
    : context_ (std::move (context))
    , component_executor_ (std::move(component_executor))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Sender_Impl::connector_status_exec_i[ctor]

  connector_status_exec_i::~connector_status_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Sender_Impl::connector_status_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Sender_Impl::connector_status_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Sender_Impl::connector_status_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Sender_Impl::connector_status_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Sender_Impl::connector_status_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Sender_Impl::connector_status_exec_i[user_private_ops]


  /** Operations and attributes from connector_status */

  void
  connector_status_exec_i::on_inconsistent_topic (
      IDL::traits< ::DDS::Topic>::ref_type the_topic,
      const ::DDS::InconsistentTopicStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Sender_Impl::connector_status_exec_i::on_inconsistent_topic[_the_topic_status]
    X11_UNUSED_ARG(the_topic);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Sender_Impl::connector_status_exec_i::on_inconsistent_topic[_the_topic_status]
  }

  void
  connector_status_exec_i::on_requested_incompatible_qos (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::RequestedIncompatibleQosStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Sender_Impl::connector_status_exec_i::on_requested_incompatible_qos[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Sender_Impl::connector_status_exec_i::on_requested_incompatible_qos[_the_reader_status]
  }

  void
  connector_status_exec_i::on_sample_rejected (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::SampleRejectedStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Sender_Impl::connector_status_exec_i::on_sample_rejected[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Sender_Impl::connector_status_exec_i::on_sample_rejected[_the_reader_status]
  }

  void
  connector_status_exec_i::on_offered_deadline_missed (
      IDL::traits< ::DDS::DataWriter>::ref_type the_writer,
      const ::DDS::OfferedDeadlineMissedStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Sender_Impl::connector_status_exec_i::on_offered_deadline_missed[_the_writer_status]
    X11_UNUSED_ARG(the_writer);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Sender_Impl::connector_status_exec_i::on_offered_deadline_missed[_the_writer_status]
  }

  void
  connector_status_exec_i::on_offered_incompatible_qos (
      IDL::traits< ::DDS::DataWriter>::ref_type the_writer,
      const ::DDS::OfferedIncompatibleQosStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Sender_Impl::connector_status_exec_i::on_offered_incompatible_qos[_the_writer_status]
    X11_UNUSED_ARG(the_writer);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Sender_Impl::connector_status_exec_i::on_offered_incompatible_qos[_the_writer_status]
  }

  void
  connector_status_exec_i::on_unexpected_status (
      IDL::traits< ::DDS::Entity>::ref_type the_entity,
      ::DDS::StatusKind status_kind)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Sender_Impl::connector_status_exec_i::on_unexpected_status[_the_entity_status_kind]
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
    //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Sender_Impl::connector_status_exec_i::on_unexpected_status[_the_entity_status_kind]
  }

  /**
   * Component Executor Implementation Class : Sender_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Sender_Impl::Sender_exec_i[ctor]
  Sender_exec_i::Sender_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Sender_Impl::Sender_exec_i[ctor]

  Sender_exec_i::~Sender_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Sender_Impl::Sender_exec_i[dtor]
    //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Sender_Impl::Sender_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Sender_Impl::Sender_exec_i[user_public_ops]
  void
  Sender_exec_i::check_status ()
  {
    IDL::traits< ::DDS::DataWriter>::ref_type writer_dds_entity =
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
    }  }


  void
  Sender_exec_i::start_publishing ()
  {
    if (!this->already_publishing_)
    {
      this->already_publishing_ = true;
      this->tm_activate_->cancel();

      this->tm_ = tt_s->schedule_repeated_trigger (
                        CORBA::make_reference<TT_Callback> (IDL::traits< IDL_Conversion_Test::CCM_Sender>::narrow (this->_lock()),false),
                        CCM_TT::TT_Duration (0, 1000000000 / this->rate_),
                        CCM_TT::TT_Duration (0, 1000000000 / this->rate_),
                        0);
    }
  }

  void
  Sender_exec_i::tick ()
  {
    try
    {
      if (this->last_iteration_ >= this->iterations ())
      {
        this->last_iteration_ = 0;
        if (++this->last_key_ > keys ())
        {
          this->stop ();
          return;
        }
      }
      ++this->last_iteration_;

      Example::B10 b10;
      b10.reserve (5);
      for (uint16_t i = 1; i < 6; ++i)
      {
        Example::B02 b02 (i*this->last_iteration_);
        b10.push_back (b02);
      }

      Example::B11 b11;
      for (uint16_t i = 1; i < IDL::traits< Example::B11 >::bound () + 1; ++i)
      {
        Example::B02 b02 ((i+1)*this->last_iteration_);
        b11.push_back (b02);
      }

      const Example::B12 b12 (15);
      const Example::B13 b13 (15);
      const Example::B12 b14 (15);

      Example::B15 b15 (10);
      for (uint16_t i = 0; i < 10; ++i)
      {
        b15[i] = i*this->last_iteration_;
      }

      Example::B16 b16;
      for (uint16_t x = 0; x < 4; ++x)
      {
        for (uint16_t y = 0; y < 5; ++y)
        {
          b16[x][y] = x*y*this->last_iteration_;
        }
      }


      Example::B32 b32;
      b32[0] = Example::B31 (3*this->last_iteration_);
      b32[1] = Example::B31 (4*this->last_iteration_);

      Example::B33 b33;
      for (uint16_t x = 0; x < 4; ++x)
      {
        for (uint16_t y = 0; y < 5; ++y)
        {
          b33[x][y] = Example::B31 (x*y*this->last_iteration_);
        }
      }

      Example::B34 b34;
      for (uint16_t x = 0; x < 6; ++x)
      {
        for (uint16_t y = 0; y < 7; ++y)
        {
          for (uint16_t z = 0; z < 8; ++z)
          {
            b34[x][y][z] = Example::B31 (x*y*z*this->last_iteration_);
          }
        }
      }

      Example::B40 b40;
      b40[0] = 2*this->last_iteration_;
      b40[1] = 3*this->last_iteration_;

      Example::B41 b41;
      for (uint16_t x = 0; x < 2; ++x)
      {
        for (uint16_t y = 0; y < 3; ++y)
        {
          b41[x][y] = (x+1)*(y+2)*this->last_iteration_;
        }
      }

      const Example::B42 b42 (b40);

      const std::array<int32_t, 4> arr {{5,4,3,2}};
      Example::B43 b43 (arr);

      const Example::B_50 b50 (
        "ITERATION_" + std::to_string (this->last_key_) +
        "_" + std::to_string (this->last_iteration_));

      std::string iter = std::to_string (this->last_iteration_);
      Example::B51 b51 (5-iter.length (), '*');
      b51 += iter;

      const Example::B52 b52 (this->last_iteration_^this->last_iteration_);

      const Example::B53 b53 (b32);

      const Example::B_54 b54 (b50);

      const Example::B55 b55 (b51);

      Example::B56 b56;
      for (uint16_t x = 0; x < 6; ++x)
      {
        for (uint16_t y = 0; y < 5; ++y)
        {
          b56[x][y] = std::to_string (x+y+this->last_iteration_);
        }
      }

      Example::B57 b57;
      for (uint16_t val = this->last_iteration_; val <  this->last_iteration_ + 100; ++val)
      {
        b57.push_back ("VALUE_"+std::to_string (val));
      }

      Example::B59 b59;
      for (uint16_t val = this->last_iteration_; val <  this->last_iteration_ + 100; ++val)
      {
        b59.push_back ("BOUNDED STRING VALUE_"+std::to_string (val));
      }

      Example::B60 b60;
      for (uint16_t val = this->last_iteration_; val <  this->last_iteration_ + 100; ++val)
      {
        b60.push_back ("BOUNDED STRING VALUE_"+std::to_string (val+33));
      }

      Example::B80 b80;
      b80.b_80_2 (Example::B70::B70_3);

      Example::B83 b83;
      b83.a ("B83 STRING A");
      b83.c ("B83 STRING C");
      b83.d ("B83 STRING D");
      Example::B81 b81;
      for (uint16_t val = this->last_iteration_; val <  this->last_iteration_ + 100; ++val)
      {
        b81.b("B81 STRING B VALUE_"+std::to_string (val));
        b81.c("B81 BOUNDED STRING C VALUE_"+std::to_string (val));
        b83.f().push_back (b81);
      }

      bool a_13 = (this->last_iteration_%2) == 1;

      std::string const key ("KEY_"+std::to_string (this->last_key_));
      Example::IDLConversionMessage msg (
          'A',                        // char
          L'A',                       // wchar
          this->last_iteration_ > 255 ? 255 : this->last_iteration_,      // octet
          -1*this->last_iteration_,   // short
          this->last_iteration_,      // ushort
          -2*this->last_iteration_,   // long
          2*this->last_iteration_,    // ulong
          -200*this->last_iteration_, // longlong
          200*this->last_iteration_,  // ulonglong
          this->last_iteration_,      // float
          this->last_iteration_,      // double
          this->last_iteration_,      // long double
          a_13,
          b10,
          b11,
          b12,
          b13,
          b14,
          b15,
          b16,
          b32,
          b33,
          b34,
          b40,
          b41,
          b42,
          b43,
          b50,
          b51,
          b52,
          b53,
          b54,
          b55,
          b56,
          b57,
          b59,
          b60,
          a_13 ? Example::B70::B70_1 : Example::B70::B70_2,
          b80,
          b83,
          key,
          this->last_iteration_);

      IDL::traits < Example::IDLConversionTestConnector::Writer>::ref_type writer =
        this->context_->get_connection_info_write_data ();

      writer->write_one (msg, ::DDS::HANDLE_NIL);

      DDS4CCM_TEST_DEBUG << "Written sample to DDS with key <" << key << "> and iteration <"
        << this->last_iteration_ << ">." << std::endl;
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
  //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Sender_Impl::Sender_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Sender_Impl::Sender_exec_i[user_private_ops]
  void
  Sender_exec_i::stop ()
  {
    this->tm_->cancel();
  }
  //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Sender_Impl::Sender_exec_i[user_private_ops]

  /** Session component operations */
  void Sender_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Sender_Impl::Sender_exec_i[configuration_complete]
    DDS4CCM_TEST_DEBUG << "Sender_exec_i::configuration_complete" << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Sender_Impl::Sender_exec_i[configuration_complete]
  }

  void Sender_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Sender_Impl::Sender_exec_i[ccm_activate]
    // Your code here
    //start status checker
    this->tt_s = this->context_->get_connection_tt_scheduler ();
    this->tm_activate_ = this->tt_s->schedule_repeated_trigger (
                              CORBA::make_reference<TT_Callback> (IDL::traits< IDL_Conversion_Test::CCM_Sender>::narrow (this->_lock()),true),
                              CCM_TT::TT_Duration (0, 1000000000),
                              CCM_TT::TT_Duration (0, 1000000000),
                              0);

    //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Sender_Impl::Sender_exec_i[ccm_activate]
  }

  void Sender_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Sender_Impl::Sender_exec_i[ccm_passivate]
    if (!this->tm_)
    {
      DDS4CCM_TEST_ERROR << "ERROR: Sender_exec_i::ccm_passivate - "
                            "Test did not start, because no DDS::PUBLICATION_MATCHED_STATUS was received."
                            << std::endl;
    }
    else
    {
      //if timer not already cancelled, do it now
      if (!this->tm_->is_canceled())
      {
        this->stop();
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
    //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Sender_Impl::Sender_exec_i[ccm_passivate]
  }

  void Sender_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Sender_Impl::Sender_exec_i[ccm_remove]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Sender_Impl::Sender_exec_i[ccm_remove]
  }

  IDL::traits< ::CCM_DDS::CCM_ConnectorStatusListener>::ref_type
  Sender_exec_i::get_connector_status ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Sender_Impl::Sender_exec_i[get_connector_status]
    if (!this->connector_status_)
      {
        this->connector_status_ =
          CORBA::make_reference <connector_status_exec_i>
            (this->context_, IDL::traits<IDL_Conversion_Test::CCM_Sender>::narrow (this->_lock()));

      }
    return this->connector_status_;
  //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Sender_Impl::Sender_exec_i[get_connector_status]
  }


  uint16_t
  Sender_exec_i::rate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Sender_Impl::Sender_exec_i::rate[getter]
    return this->rate_;
    //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Sender_Impl::Sender_exec_i::rate[getter]
  }

  void
  Sender_exec_i::rate (
      uint16_t rate)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Sender_Impl::Sender_exec_i::rate[setter]
    this->rate_ = rate;
    //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Sender_Impl::Sender_exec_i::rate[setter]
  }

  uint16_t
  Sender_exec_i::iterations ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Sender_Impl::Sender_exec_i::iterations[getter]
    return this->iterations_;
    //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Sender_Impl::Sender_exec_i::iterations[getter]
  }

  void
  Sender_exec_i::iterations (
      uint16_t iterations)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Sender_Impl::Sender_exec_i::iterations[setter]
    this->iterations_ = iterations;
    //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Sender_Impl::Sender_exec_i::iterations[setter]
  }

  /// Operations from Components::SessionComponent
  void
  Sender_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Sender_Impl::Sender_exec_i[set_session_context]
    this->context_ = IDL::traits<IDL_Conversion_Test::CCM_Sender_Context>::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Sender_Impl::Sender_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Sender_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Sender_Impl[user_namespace_end_impl]

} // namespace IDL_Conversion_Test_Sender_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Sender_Impl[factory]
extern "C" void
create_IDL_Conversion_Test_Sender_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <IDL_Conversion_Test_Sender_Impl::Sender_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Sender_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : idl_conversion_sender_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
