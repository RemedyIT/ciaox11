// -*- C++ -*-
/**
 * @file    custom_example_receiver_exec.cpp
 * @author  Marcel Smit
 *
 * @brief   Receiver component implementation of the IDL example.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : custom_example_receiver_impl.cpp[Header]

#include "custom_example_receiver_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicSubscriber_comp_Impl[user_includes]
#include "dds4ccm/tests/common/dds4ccm_test_utils.h"
//@@{__RIDL_REGEN_MARKER__} - END : Example_BasicSubscriber_comp_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicSubscriber_comp_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : Example_BasicSubscriber_comp_Impl[user_global_impl]

namespace Example_BasicSubscriber_comp_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicSubscriber_comp_Impl[user_namespace_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicSubscriber_comp_Impl[user_namespace_impl]

  /**
   * Facet Executor Implementation Class : CA1DataSub_data_listener_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicSubscriber_comp_Impl::CA1DataSub_data_listener_exec_i[ctor]
  CA1DataSub_data_listener_exec_i::CA1DataSub_data_listener_exec_i (
    IDL::traits<Example::CCM_BasicSubscriber_comp_Context>::ref_type context,
    std::atomic_ulong &samples_received)
    : context_ (std::move (context))
    , samples_received_ (samples_received)
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicSubscriber_comp_Impl::CA1DataSub_data_listener_exec_i[ctor]

  CA1DataSub_data_listener_exec_i::~CA1DataSub_data_listener_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicSubscriber_comp_Impl::CA1DataSub_data_listener_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicSubscriber_comp_Impl::CA1DataSub_data_listener_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicSubscriber_comp_Impl::CA1DataSub_data_listener_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicSubscriber_comp_Impl::CA1DataSub_data_listener_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicSubscriber_comp_Impl::CA1DataSub_data_listener_exec_i[user_private_ops]
  void
  CA1DataSub_data_listener_exec_i::check_sample (const Example::CA1_msg &msg)
  {
    ++this->samples_received_;

    uint32_t counter = msg.hdr ().NA4_6 ();

    if (msg.hdr ().NA4_5 () != msg.hdr ().NA4_6 () + 100)
    {
      DDS4CCM_TEST_ERROR << "CA1DataSub_data_listener_exec_i::check_sample - "
        << "ERROR : Sample <" << counter << "> contains an unexpected value for "
        << "hdr.NA4_5 : expected<" << msg.hdr ().NA4_6 () + 100
        << "> - got <" << msg.hdr ().NA4_5 () << ">."
        << std::endl;
    }
    if (msg.hdr ().NA4_1 () != msg.hdr ().NA4_6 () + 1000)
    {
      DDS4CCM_TEST_ERROR << "CA1DataSub_data_listener_exec_i::check_sample - "
        << "ERROR : Sample <" << counter << "> contains an unexpected value for "
        << "hdr.NA4_1 : expected<" << msg.hdr ().NA4_6 () + 100
        << "> - got <" << msg.hdr ().NA4_1 () << ">."
        << std::endl;
    }
    if (msg.hdr ().NA4_4 () != msg.hdr ().NA4_6 () * 10)
    {
      DDS4CCM_TEST_ERROR << "CA1DataSub_data_listener_exec_i::check_sample - "
        << "ERROR : Sample <" << counter << "> contains an unexpected value for "
        << "hdr.NA4_4 : expected<" << msg.hdr ().NA4_6 () * 10
        << "> - got <" << msg.hdr ().NA4_4 () << ">."
        << std::endl;
    }
    if (msg.hdr ().NA4_2 () != msg.hdr ().NA4_6 () * 20)
    {
      DDS4CCM_TEST_ERROR << "CA1DataSub_data_listener_exec_i::check_sample - "
        << "ERROR : Sample <" << counter << "> contains an unexpected value for "
        << "hdr.NA4_2 : expected<" << msg.hdr ().NA4_6 () * 20
        << "> - got <" << msg.hdr ().NA4_2 () << ">."
        << std::endl;
    }
    if (msg.hdr ().NA4_3 () != msg.hdr ().NA4_6 () * 100)
    {
      DDS4CCM_TEST_ERROR << "CA1DataSub_data_listener_exec_i::check_sample - "
        << "ERROR : Sample <" << counter << "> contains an unexpected value for "
        << "hdr.NA4_3 : expected<" << msg.hdr ().NA4_6 () * 100
        << "> - got <" << msg.hdr ().NA4_3 () << ">."
        << std::endl;
    }
    if (msg.hdr ().NA4_7 () != msg.hdr ().NA4_6 () * 200)
    {
      DDS4CCM_TEST_ERROR << "CA1DataSub_data_listener_exec_i::check_sample - "
        << "ERROR : Sample <" << counter << "> contains an unexpected value for "
        << "hdr.NA4_7 : expected<" << msg.hdr ().NA4_6 () * 200
        << "> - got <" << msg.hdr ().NA4_7 () << ">."
        << std::endl;
    }


    if (msg.data ().CA09_1 ().NA5_1 () != msg.hdr ().NA4_6 ())
    {
      DDS4CCM_TEST_ERROR << "CA1DataSub_data_listener_exec_i::check_sample - "
        << "ERROR : Sample <" << counter << "> contains an unexpected value for "
        << "data.CA09_1.NA5_1 : expected<" << msg.hdr ().NA4_6 ()
        << "> - got <" << msg.data ().CA09_1 ().NA5_1 () << ">."
        << std::endl;
    }

    if (msg.data ().CA09_2 () != msg.data ().CA09_1 ().NA5_1 ())
    {
      DDS4CCM_TEST_ERROR << "CA1DataSub_data_listener_exec_i::check_sample - "
        << "ERROR : Sample <" << counter << "> contains an unexpected value for "
        << "data.CA09_2 : expected<" << msg.data ().CA09_1 ().NA5_1 ()
        << "> - got <" << msg.data ().CA09_2 () << ">."
        << std::endl;
    }
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicSubscriber_comp_Impl::CA1DataSub_data_listener_exec_i[user_private_ops]


  /** Operations and attributes from CA1DataSub_data_listener */

  void
  CA1DataSub_data_listener_exec_i::on_one_data (
      const ::Example::CA1_msg& datum,
      const ::CCM_DDS::ReadInfo& info)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicSubscriber_comp_Impl::CA1DataSub_data_listener_exec_i::on_one_data[_datum_info]
    X11_UNUSED_ARG(datum);
    X11_UNUSED_ARG(info);

    DDS4CCM_TEST_ERROR << "CA1DataSub_data_listener_exec_i::on_one_data - "
      "ERROR: Unexpected invocation of 'on_one_data'." << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicSubscriber_comp_Impl::CA1DataSub_data_listener_exec_i::on_one_data[_datum_info]
  }

  void
  CA1DataSub_data_listener_exec_i::on_many_data (
      const ::Example::CA1_msgSeq& data,
      const ::CCM_DDS::ReadInfoSeq& infos)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicSubscriber_comp_Impl::CA1DataSub_data_listener_exec_i::on_many_data[_data_infos]
    X11_UNUSED_ARG(infos);
    for (const Example::CA1_msg &msg : data)
    {
      this->check_sample (msg);
    }
    //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicSubscriber_comp_Impl::CA1DataSub_data_listener_exec_i::on_many_data[_data_infos]
  }
  /**
   * Facet Executor Implementation Class : CA1DataSub_status_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicSubscriber_comp_Impl::CA1DataSub_status_exec_i[ctor]
  CA1DataSub_status_exec_i::CA1DataSub_status_exec_i (
    IDL::traits<Example::CCM_BasicSubscriber_comp_Context>::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicSubscriber_comp_Impl::CA1DataSub_status_exec_i[ctor]

  CA1DataSub_status_exec_i::~CA1DataSub_status_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicSubscriber_comp_Impl::CA1DataSub_status_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicSubscriber_comp_Impl::CA1DataSub_status_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicSubscriber_comp_Impl::CA1DataSub_status_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicSubscriber_comp_Impl::CA1DataSub_status_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicSubscriber_comp_Impl::CA1DataSub_status_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicSubscriber_comp_Impl::CA1DataSub_status_exec_i[user_private_ops]


  /** Operations and attributes from CA1DataSub_status */

  void
  CA1DataSub_status_exec_i::on_requested_deadline_missed (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::RequestedDeadlineMissedStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicSubscriber_comp_Impl::CA1DataSub_status_exec_i::on_requested_deadline_missed[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicSubscriber_comp_Impl::CA1DataSub_status_exec_i::on_requested_deadline_missed[_the_reader_status]
  }

  void
  CA1DataSub_status_exec_i::on_sample_lost (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::SampleLostStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicSubscriber_comp_Impl::CA1DataSub_status_exec_i::on_sample_lost[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicSubscriber_comp_Impl::CA1DataSub_status_exec_i::on_sample_lost[_the_reader_status]
  }

  /**
   * Component Executor Implementation Class : BasicSubscriber_comp_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicSubscriber_comp_Impl::BasicSubscriber_comp_exec_i[ctor]
  BasicSubscriber_comp_exec_i::BasicSubscriber_comp_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicSubscriber_comp_Impl::BasicSubscriber_comp_exec_i[ctor]

  BasicSubscriber_comp_exec_i::~BasicSubscriber_comp_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicSubscriber_comp_Impl::BasicSubscriber_comp_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicSubscriber_comp_Impl::BasicSubscriber_comp_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicSubscriber_comp_Impl::BasicSubscriber_comp_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicSubscriber_comp_Impl::BasicSubscriber_comp_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicSubscriber_comp_Impl::BasicSubscriber_comp_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicSubscriber_comp_Impl::BasicSubscriber_comp_exec_i[user_private_ops]

  /** Session component operations */
  void BasicSubscriber_comp_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicSubscriber_comp_Impl::BasicSubscriber_comp_exec_i[configuration_complete]
    DDS4CCM_TEST_DEBUG << "BasicSubscriber_comp_exec_i::configuration_complete" << std::endl;
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicSubscriber_comp_Impl::BasicSubscriber_comp_exec_i[configuration_complete]
  }

  void BasicSubscriber_comp_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicSubscriber_comp_Impl::BasicSubscriber_comp_exec_i[ccm_activate]
    IDL::traits< ::CCM_DDS::DataListenerControl >::ref_type lc =
      this->context_->get_connection_CA1DataSub_data_control ();

    if (!lc)
    {
      DDS4CCM_TEST_ERROR << "Error:  Listener control receptacle is null!"
        << std::endl;
      throw ::CORBA::INTERNAL ();
    }
    lc->mode (::CCM_DDS::ListenerMode::MANY_BY_MANY);
    //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicSubscriber_comp_Impl::BasicSubscriber_comp_exec_i[ccm_activate]
  }

  void BasicSubscriber_comp_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicSubscriber_comp_Impl::BasicSubscriber_comp_exec_i[ccm_passivate]
    if (this->count () != this->samples_received_)
    {
      DDS4CCM_TEST_ERROR << "BasicSubscriber_comp_exec_i::ccm_passivate : ERROR "
        << "unexpected number of samples received. expected <" << this->count ()
        << "> - got <" << this->samples_received_ << ">." << std::endl;
    }
    else
    {
      DDS4CCM_TEST_DEBUG << "BasicSubscriber_comp_exec_i::ccm_passivate : <"
        << this->samples_received_ << "> samples have been received from DDS" << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicSubscriber_comp_Impl::BasicSubscriber_comp_exec_i[ccm_passivate]
  }

  void BasicSubscriber_comp_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicSubscriber_comp_Impl::BasicSubscriber_comp_exec_i[ccm_remove]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicSubscriber_comp_Impl::BasicSubscriber_comp_exec_i[ccm_remove]
  }

  IDL::traits< ::Example::CA1_conn::CCM_Listener >::ref_type
  BasicSubscriber_comp_exec_i::get_CA1DataSub_data_listener ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicSubscriber_comp_Impl::BasicSubscriber_comp_exec_i[get_CA1DataSub_data_listener]
    if (!this->CA1DataSub_data_listener_)
      {
        this->CA1DataSub_data_listener_ = CORBA::make_reference <CA1DataSub_data_listener_exec_i> (
          this->context_, this->samples_received_);
      }
    return this->CA1DataSub_data_listener_;
  //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicSubscriber_comp_Impl::BasicSubscriber_comp_exec_i[get_CA1DataSub_data_listener]
  }

  IDL::traits< ::CCM_DDS::CCM_PortStatusListener >::ref_type
  BasicSubscriber_comp_exec_i::get_CA1DataSub_status ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicSubscriber_comp_Impl::BasicSubscriber_comp_exec_i[get_CA1DataSub_status]
    if (!this->CA1DataSub_status_)
      {
        this->CA1DataSub_status_ = CORBA::make_reference <CA1DataSub_status_exec_i> (this->context_);
      }
    return this->CA1DataSub_status_;
  //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicSubscriber_comp_Impl::BasicSubscriber_comp_exec_i[get_CA1DataSub_status]
  }


  uint32_t
  BasicSubscriber_comp_exec_i::count ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicSubscriber_comp_Impl::BasicSubscriber_comp_exec_i::count[getter]
    return this->count_;
    //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicSubscriber_comp_Impl::BasicSubscriber_comp_exec_i::count[getter]
  }

  void
  BasicSubscriber_comp_exec_i::count (
      uint32_t count)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicSubscriber_comp_Impl::BasicSubscriber_comp_exec_i::count[setter]
    this->count_ = count;
    //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicSubscriber_comp_Impl::BasicSubscriber_comp_exec_i::count[setter]
  }

  /// Operations from Components::SessionComponent
  void
  BasicSubscriber_comp_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicSubscriber_comp_Impl::BasicSubscriber_comp_exec_i[set_session_context]
    this->context_ = IDL::traits<Example::CCM_BasicSubscriber_comp_Context>::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicSubscriber_comp_Impl::BasicSubscriber_comp_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicSubscriber_comp_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : Example_BasicSubscriber_comp_Impl[user_namespace_end_impl]

} // namespace Example_BasicSubscriber_comp_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Example_BasicSubscriber_comp_Impl[factory]
extern "C" void
create_Example_BasicSubscriber_comp_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <Example_BasicSubscriber_comp_Impl::BasicSubscriber_comp_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : Example_BasicSubscriber_comp_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : custom_example_receiver_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
