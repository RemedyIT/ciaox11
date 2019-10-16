// -*- C++ -*-
/**
 * @file    union_receiver_exec.cpp
 * @author  Marcel Smit
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : union_receiver_impl.cpp[Header]

#include "union_receiver_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Receiver_Impl[user_includes]
#include "dds4ccm/tests/common/dds4ccm_test_utils.h"
//@@{__RIDL_REGEN_MARKER__} - END : Uni_Receiver_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Receiver_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : Uni_Receiver_Impl[user_global_impl]

namespace Uni_Receiver_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Receiver_Impl[user_namespace_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : Uni_Receiver_Impl[user_namespace_impl]

  /**
   * Facet Executor Implementation Class : info_out_data_listener_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Receiver_Impl::info_out_data_listener_exec_i[ctor]
  info_out_data_listener_exec_i::info_out_data_listener_exec_i (
    IDL::traits< ::Uni::CCM_Receiver_Context >::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Uni_Receiver_Impl::info_out_data_listener_exec_i[ctor]

  info_out_data_listener_exec_i::~info_out_data_listener_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Receiver_Impl::info_out_data_listener_exec_i[dtor]
    if (!this->handled_assignment_a_)
    {
      DDS4CCM_TEST_ERROR << "ERROR: info_out_data_listener_exec_i::~info_out_data_listener_exec_i - "
        << "Assignment A was not handled by the receiver." << std::endl;
    }
    if (!this->handled_assignment_b_)
    {
      DDS4CCM_TEST_ERROR << "ERROR: info_out_data_listener_exec_i::~info_out_data_listener_exec_i - "
        << "Assignment B was not handled by the receiver." << std::endl;
    }
    if (!this->handled_assignment_c_)
    {
      DDS4CCM_TEST_ERROR << "ERROR: info_out_data_listener_exec_i::~info_out_data_listener_exec_i - "
        << "Assignment C was not handled by the receiver." << std::endl;
    }
    if (!this->handled_assignment_d_)
    {
      DDS4CCM_TEST_ERROR << "ERROR: info_out_data_listener_exec_i::~info_out_data_listener_exec_i - "
        << "Assignment D was not handled by the receiver." << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : Uni_Receiver_Impl::info_out_data_listener_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Receiver_Impl::info_out_data_listener_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Uni_Receiver_Impl::info_out_data_listener_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Receiver_Impl::info_out_data_listener_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Uni_Receiver_Impl::info_out_data_listener_exec_i[user_private_ops]


  /** Operations and attributes from info_out_data_listener */

  void
  info_out_data_listener_exec_i::on_one_data (
      const ::Uni::UnionMessage& datum,
      const ::CCM_DDS::ReadInfo& info)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Receiver_Impl::info_out_data_listener_exec_i::on_one_data[_datum_info]
    X11_UNUSED_ARG(info);

    DDS4CCM_TEST_DEBUG << "info_out_data_listener_exec_i::on_one_data - "
      << "New sample " << datum << std::endl;

    switch (datum.a ())
    {
      case Uni::Assignment::A:
        this->handle_assignment_a (datum);
        break;
      case Uni::Assignment::B:
        this->handle_assignment_b (datum);
        break;
      case Uni::Assignment::C:
        this->handle_assignment_c (datum);
        break;
      case Uni::Assignment::D:
        this->handle_assignment_d (datum);
        break;
      default:
      case Uni::Assignment::NONE:
        break;
    }


    //@@{__RIDL_REGEN_MARKER__} - END : Uni_Receiver_Impl::info_out_data_listener_exec_i::on_one_data[_datum_info]
  }

  void
  info_out_data_listener_exec_i::on_many_data (
      const ::Uni::UnionMessageSeq& data,
      const ::CCM_DDS::ReadInfoSeq& infos)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Receiver_Impl::info_out_data_listener_exec_i::on_many_data[_data_infos]
    X11_UNUSED_ARG(data);
    X11_UNUSED_ARG(infos);
    DDS4CCM_TEST_ERROR << "ERROR: info_out_data_listener_exec_i::on_many_data - "
      << "unexpected invocation" << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : Uni_Receiver_Impl::info_out_data_listener_exec_i::on_many_data[_data_infos]
  }
  /**
   * Facet Executor Implementation Class : info_out_status_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Receiver_Impl::info_out_status_exec_i[ctor]
  info_out_status_exec_i::info_out_status_exec_i (
    IDL::traits< ::Uni::CCM_Receiver_Context >::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Uni_Receiver_Impl::info_out_status_exec_i[ctor]

  info_out_status_exec_i::~info_out_status_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Receiver_Impl::info_out_status_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Uni_Receiver_Impl::info_out_status_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Receiver_Impl::info_out_status_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Uni_Receiver_Impl::info_out_status_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Receiver_Impl::info_out_status_exec_i[user_private_ops]
  void
  info_out_data_listener_exec_i::handle_assignment_a (const Uni::UnionMessage& msg)
  {
    this->handled_assignment_a_ = true;
    // Empty, uninitialized union
    try
    {
      // default
      if (msg.b_03 ().b_03_d () != 0)
      {
        DDS4CCM_TEST_ERROR << "ERROR: info_out_aata_listener_exec_i::handle_assignment_a <b_03>  - "
          << "unexpected value for the default member detected. Expected <0> - got <"
          << msg.b_03 ().b_03_d () << ">." << std::endl;
      }
    }
    catch (const CORBA::BAD_PARAM&)
    {
      DDS4CCM_TEST_ERROR << "ERROR: info_out_data_listener_exec_i::handle_assignment_a - "
        << "Caught unexpected BAD_PARAM exception whilst examining <b_03>." << std::endl;
    }

    try
    {
      if (msg.d ()._d () != Uni::DataType::dtLong)
      {
        DDS4CCM_TEST_ERROR << "ERROR: info_out_data_listener_exec_i::handle_assignment_a <d> - "
          << "unexpected value for the discriminator detected. Expected <Uni::DataType::dtLong> "
          << "- got <" << msg.d ()._d () << ">." << std::endl;
      }
    }
    catch (const CORBA::BAD_PARAM&)
    {
      DDS4CCM_TEST_ERROR << "ERROR: info_out_data_listener_exec_i::handle_assignment_a - "
        << "Caught unexpected BAD_PARAM exception whilst examining <d>." << std::endl;
    }
  }

  void
  info_out_data_listener_exec_i::handle_assignment_b (const Uni::UnionMessage& msg)
  {
    this->handled_assignment_b_ = true;

    // Initialized default
    try
    {
      // default
      if (msg.b_03 ().b_03_d () != 5)
      {
        DDS4CCM_TEST_ERROR << "ERROR: info_out_aata_listener_exec_i::handle_assignment_b <b_03>  - "
          << "unexpected value for the default member detected. Expected <5> - got <"
          << msg.b_03 ().b_03_d () << ">." << std::endl;
      }
    }
    catch (const CORBA::BAD_PARAM&)
    {
      DDS4CCM_TEST_ERROR << "ERROR: info_out_data_listener_exec_i::handle_assignment_b - "
        << "Caught unexpected BAD_PARAM exception whilst examining the default member of "
        << "<b_03>." << std::endl;
    }

    try
    {
      if (msg.d ()._d () != Uni::DataType::dtLong)
      {
        DDS4CCM_TEST_ERROR << "ERROR: info_out_data_listener_exec_i::handle_assignment_b <d> - "
          << "unexpected value for the discriminator detected. Expected <Uni::DataType::dtLong> "
          << "- got <" << msg.d ()._d () << ">." << std::endl;
      }
      if (msg.d ().longData () != 5)
      {
        DDS4CCM_TEST_ERROR << "ERROR: info_out_aata_listener_exec_i::handle_assignment_b <d>  - "
          << "unexpected value for longData detected. Expected <5> - got <"
          << msg.d ().longData () << ">." << std::endl;
      }
    }
    catch (const CORBA::BAD_PARAM&)
    {
      DDS4CCM_TEST_ERROR << "ERROR: info_out_data_listener_exec_i::handle_assignment_b - "
        << "Caught unexpected BAD_PARAM exception whilst examining <d>." << std::endl;
    }
  }

  void
  info_out_data_listener_exec_i::handle_assignment_c (const Uni::UnionMessage& msg)
  {
    this->handled_assignment_c_ = true;
    // first member of b_03
    try
    {
      if (msg.b_03 ()._d () != 0)
      {
        DDS4CCM_TEST_ERROR << "ERROR: info_out_data_listener_exec_i::handle_assignment_c <b_03>  - "
          << "unexpected value for the discriminator detected. Expected <0> - got <"
          << msg.b_03 ()._d () << ">." << std::endl;
      }

      if (msg.b_03 ().b_03_1 ().b01_1 () != 5)
      {
        DDS4CCM_TEST_ERROR << "ERROR: info_out_data_listener_exec_i::handle_assignment_c <b_03>  - "
          << "unexpected value for the first member detected. Expected <5> - got <"
          << msg.b_03 ().b_03_1 ().b01_1 () << ">." << std::endl;
      }
    }
    catch (const CORBA::BAD_PARAM&)
    {
      DDS4CCM_TEST_ERROR << "ERROR: info_out_data_listener_exec_i::handle_assignment_c - "
        << "Caught unexpected BAD_PARAM exception whilst examining <b_03>." << std::endl;
    }

    // first member of d
    try
    {
      if (msg.d ()._d () != Uni::DataType::dtLong)
      {
        DDS4CCM_TEST_ERROR << "ERROR: info_out_data_listener_exec_i::handle_assignment_c <d>  - "
          << "unexpected value for the discriminator detected. Expected <Uni::DataType::dtLong> - got <"
          << msg.d ()._d () << ">." << std::endl;
      }

      if (msg.d ().longData () != 5)
      {
        DDS4CCM_TEST_ERROR << "ERROR: info_out_data_listener_exec_i::handle_assignment_c <d> - "
          << "unexpected value for the first member detected. Expected <5> - got <"
          << msg.d ().longData () << ">." << std::endl;
      }
    }
    catch (const CORBA::BAD_PARAM&)
    {
      DDS4CCM_TEST_ERROR << "ERROR: info_out_data_listener_exec_i::handle_assignment_c - "
        << "Caught unexpected BAD_PARAM exception whilst examining <d>." << std::endl;
    }
  }

  void
  info_out_data_listener_exec_i::handle_assignment_d (const Uni::UnionMessage& msg)
  {
    this->handled_assignment_d_ = true;

    // last member of b_03
    try
    {
      if (msg.b_03 ()._d () != 4)
      {
        DDS4CCM_TEST_ERROR << "ERROR: info_out_data_listener_exec_i::handle_assignment_d <b_03>  - "
          << "unexpected value for the discriminator detected. Expected <4> - got <"
          << msg.b_03 ()._d () << ">." << std::endl;
      }

      if (msg.b_03 ().b_03_5 () != "XX")
      {
        DDS4CCM_TEST_ERROR << "ERROR: info_out_data_listener_exec_i::handle_assignment_d <b_03>  - "
          << "unexpected value for the last member detected. Expected <5> - got <"
          << msg.b_03 ().b_03_5 () << ">." << std::endl;
      }
    }
    catch (const CORBA::BAD_PARAM&)
    {
      DDS4CCM_TEST_ERROR << "ERROR: info_out_data_listener_exec_i::handle_assignment_d - "
        << "Caught unexpected BAD_PARAM exception whilst examining <b_03>." << std::endl;
    }

    // last member of d
    try
    {
      if (msg.d ()._d () != Uni::DataType::dtGlobal)
      {
        DDS4CCM_TEST_ERROR << "ERROR: info_out_data_listener_exec_i::handle_assignment_d <d>  - "
          << "unexpected value for the discriminator detected. Expected <Uni::DataType::dtGlobal> - got <"
          << msg.d ()._d () << ">." << std::endl;
      }

      if (msg.d ().globalData ().x () != 4)
      {
        DDS4CCM_TEST_ERROR << "ERROR: info_out_data_listener_exec_i::handle_assignment_d <d> - "
          << "unexpected value for the last member detected. Expected <5> - got <"
          << msg.d ().globalData ().x () << ">." << std::endl;
      }
    }
    catch (const CORBA::BAD_PARAM&)
    {
      DDS4CCM_TEST_ERROR << "ERROR: info_out_data_listener_exec_i::handle_assignment_d - "
        << "Caught unexpected BAD_PARAM exception whilst examining <d>." << std::endl;
    }
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Uni_Receiver_Impl::info_out_status_exec_i[user_private_ops]


  /** Operations and attributes from info_out_status */

  void
  info_out_status_exec_i::on_requested_deadline_missed (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::RequestedDeadlineMissedStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Receiver_Impl::info_out_status_exec_i::on_requested_deadline_missed[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : Uni_Receiver_Impl::info_out_status_exec_i::on_requested_deadline_missed[_the_reader_status]
  }

  void
  info_out_status_exec_i::on_sample_lost (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::SampleLostStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Receiver_Impl::info_out_status_exec_i::on_sample_lost[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : Uni_Receiver_Impl::info_out_status_exec_i::on_sample_lost[_the_reader_status]
  }

  /**
   * Component Executor Implementation Class : Receiver_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Receiver_Impl::Receiver_exec_i[ctor]
  Receiver_exec_i::Receiver_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Uni_Receiver_Impl::Receiver_exec_i[ctor]

  Receiver_exec_i::~Receiver_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Receiver_Impl::Receiver_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Uni_Receiver_Impl::Receiver_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Receiver_Impl::Receiver_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Uni_Receiver_Impl::Receiver_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Receiver_Impl::Receiver_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Uni_Receiver_Impl::Receiver_exec_i[user_private_ops]

  /** Session component operations */
  void Receiver_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Receiver_Impl::Receiver_exec_i[configuration_complete]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Uni_Receiver_Impl::Receiver_exec_i[configuration_complete]
  }

  void Receiver_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Receiver_Impl::Receiver_exec_i[ccm_activate]
    IDL::traits< ::CCM_DDS::DataListenerControl >::ref_type lc =
      this->context_->get_connection_info_out_data_control ();
    lc->mode (::CCM_DDS::ListenerMode::ONE_BY_ONE);
    //@@{__RIDL_REGEN_MARKER__} - END : Uni_Receiver_Impl::Receiver_exec_i[ccm_activate]
  }

  void Receiver_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Receiver_Impl::Receiver_exec_i[ccm_passivate]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Uni_Receiver_Impl::Receiver_exec_i[ccm_passivate]
  }

  void Receiver_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Receiver_Impl::Receiver_exec_i[ccm_remove]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Uni_Receiver_Impl::Receiver_exec_i[ccm_remove]
  }

  IDL::traits< ::Uni::UnionConnector::CCM_Listener >::ref_type
  Receiver_exec_i::get_info_out_data_listener ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Receiver_Impl::Receiver_exec_i[get_info_out_data_listener]
    if (!this->info_out_data_listener_)
    {
      this->info_out_data_listener_ = CORBA::make_reference <info_out_data_listener_exec_i> (this->context_);
    }
    return this->info_out_data_listener_;
  //@@{__RIDL_REGEN_MARKER__} - END : Uni_Receiver_Impl::Receiver_exec_i[get_info_out_data_listener]
  }

  IDL::traits< ::CCM_DDS::CCM_PortStatusListener >::ref_type
  Receiver_exec_i::get_info_out_status ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Receiver_Impl::Receiver_exec_i[get_info_out_status]
    if (!this->info_out_status_)
    {
      this->info_out_status_ = CORBA::make_reference <info_out_status_exec_i> (this->context_);
    }
    return this->info_out_status_;
  //@@{__RIDL_REGEN_MARKER__} - END : Uni_Receiver_Impl::Receiver_exec_i[get_info_out_status]
  }

  /// Operations from Components::SessionComponent
  void
  Receiver_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Receiver_Impl::Receiver_exec_i[set_session_context]
    this->context_ = IDL::traits< ::Uni::CCM_Receiver_Context >::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : Uni_Receiver_Impl::Receiver_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Receiver_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : Uni_Receiver_Impl[user_namespace_end_impl]

} // namespace Uni_Receiver_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Uni_Receiver_Impl[factory]
extern "C" void
create_Uni_Receiver_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <Uni_Receiver_Impl::Receiver_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : Uni_Receiver_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : union_receiver_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
