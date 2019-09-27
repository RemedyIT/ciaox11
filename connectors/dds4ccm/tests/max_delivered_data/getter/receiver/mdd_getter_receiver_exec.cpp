// -*- C++ -*-
/**
 * @file    mdd_getter_receiver_exec.cpp
 * @author  Marcel Smit
 *
 * @brief   Receiver component for the max delivered data test for the getter
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : mdd_getter_receiver_impl.cpp[Header]

#include "mdd_getter_receiver_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : MDD_Getter_Test_Receiver_Impl[user_includes]
#include "dds4ccm/tests/common/common_test_utils.h"
//@@{__RIDL_REGEN_MARKER__} - END : MDD_Getter_Test_Receiver_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : MDD_Getter_Test_Receiver_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : MDD_Getter_Test_Receiver_Impl[user_global_impl]

namespace MDD_Getter_Test_Receiver_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : MDD_Getter_Test_Receiver_Impl[user_namespace_impl]
  class TT_Callback final
     : public IDL::traits<CCM_TT::TT_Handler>::base_type
   {
   public:
     TT_Callback (IDL::traits< ::MDD_Getter_Test::CCM_Receiver_Context>::ref_type ctx)
          : ciao_context_ (ctx)
     {}

     virtual
     void
     on_trigger (
         IDL::traits< ::CCM_TT::TT_Timer>::ref_type timer,
         const ::CCM_TT::TT_Duration& time,
         uint32_t round) override;

   private:
       std::string connection_;
       IDL::traits< ::MDD_Getter_Test::CCM_Receiver_Context>::ref_type ciao_context_;
   };

   void
   TT_Callback::on_trigger (
       IDL::traits< ::CCM_TT::TT_Timer>::ref_type timer,
       const ::CCM_TT::TT_Duration&,
       uint32_t)
   {
     try
     {
       if (DDS4CCM_TEST_UTILS::check_last (
         this->ciao_context_->get_connection_info_get_data (), 2, 1))
       {
         timer->cancel ();
         IDL::traits< CommonTestConnector::Getter >::ref_type getter =
           this->ciao_context_->get_connection_info_get_fresh_data ();
         getter->max_delivered_data (2);

         CommonTestMessageSeq messages;
         CCM_DDS::ReadInfoSeq readinfos;
         getter->get_many (messages, readinfos);

         if (messages.size () != 2)
         {
           DDS4CCM_TEST_ERROR << "ERROR: Receiver_exec_i::tick - "
             << "Unexpected number of samples received. Expected <2> - got <"
             << messages.size () << ">." << std::endl;
         }
         else
         {
           DDS4CCM_TEST_DEBUG << "OK: Receiver_exec_i::TT_Callback::on_trigger  - "
             << "Expected number of samples received <"
             << messages.size () << ">." << std::endl;
         }
       }
     }
     catch_dds4ccm_test_ex(ex, "Receiver_exec_i::TT_Callback::on_trigger ")
   }
  //@@{__RIDL_REGEN_MARKER__} - END : MDD_Getter_Test_Receiver_Impl[user_namespace_impl]

  /**
   * Facet Executor Implementation Class : info_get_status_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : MDD_Getter_Test_Receiver_Impl::info_get_status_exec_i[ctor]
  info_get_status_exec_i::info_get_status_exec_i (
    IDL::traits<MDD_Getter_Test::CCM_Receiver_Context>::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : MDD_Getter_Test_Receiver_Impl::info_get_status_exec_i[ctor]

  info_get_status_exec_i::~info_get_status_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : MDD_Getter_Test_Receiver_Impl::info_get_status_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : MDD_Getter_Test_Receiver_Impl::info_get_status_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : MDD_Getter_Test_Receiver_Impl::info_get_status_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : MDD_Getter_Test_Receiver_Impl::info_get_status_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : MDD_Getter_Test_Receiver_Impl::info_get_status_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : MDD_Getter_Test_Receiver_Impl::info_get_status_exec_i[user_private_ops]


  /** Operations and attributes from info_get_status */

  void
  info_get_status_exec_i::on_requested_deadline_missed (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::RequestedDeadlineMissedStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : MDD_Getter_Test_Receiver_Impl::info_get_status_exec_i::on_requested_deadline_missed[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : MDD_Getter_Test_Receiver_Impl::info_get_status_exec_i::on_requested_deadline_missed[_the_reader_status]
  }

  void
  info_get_status_exec_i::on_sample_lost (
      IDL::traits< ::DDS::DataReader>::ref_type the_reader,
      const ::DDS::SampleLostStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : MDD_Getter_Test_Receiver_Impl::info_get_status_exec_i::on_sample_lost[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : MDD_Getter_Test_Receiver_Impl::info_get_status_exec_i::on_sample_lost[_the_reader_status]
  }

  /**
   * Component Executor Implementation Class : Receiver_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : MDD_Getter_Test_Receiver_Impl::Receiver_exec_i[ctor]
  Receiver_exec_i::Receiver_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : MDD_Getter_Test_Receiver_Impl::Receiver_exec_i[ctor]

  Receiver_exec_i::~Receiver_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : MDD_Getter_Test_Receiver_Impl::Receiver_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : MDD_Getter_Test_Receiver_Impl::Receiver_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : MDD_Getter_Test_Receiver_Impl::Receiver_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : MDD_Getter_Test_Receiver_Impl::Receiver_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : MDD_Getter_Test_Receiver_Impl::Receiver_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : MDD_Getter_Test_Receiver_Impl::Receiver_exec_i[user_private_ops]

  /** Session component operations */
  void Receiver_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : MDD_Getter_Test_Receiver_Impl::Receiver_exec_i[configuration_complete]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : MDD_Getter_Test_Receiver_Impl::Receiver_exec_i[configuration_complete]
  }

  void Receiver_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : MDD_Getter_Test_Receiver_Impl::Receiver_exec_i[ccm_activate]
    IDL::traits<CCM_TT::TT_Scheduler>::ref_type tt_s = this->context_->get_connection_tt_scheduler ();

    tt_s->schedule_repeated_trigger (
            CORBA::make_reference<TT_Callback> (this->context_),
            CCM_TT::TT_Duration (3, 0),
            CCM_TT::TT_Duration (1, 0),
            0);
    //@@{__RIDL_REGEN_MARKER__} - END : MDD_Getter_Test_Receiver_Impl::Receiver_exec_i[ccm_activate]
  }

  void Receiver_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : MDD_Getter_Test_Receiver_Impl::Receiver_exec_i[ccm_passivate]
    //@@{__RIDL_REGEN_MARKER__} - END : MDD_Getter_Test_Receiver_Impl::Receiver_exec_i[ccm_passivate]
  }

  void Receiver_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : MDD_Getter_Test_Receiver_Impl::Receiver_exec_i[ccm_remove]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : MDD_Getter_Test_Receiver_Impl::Receiver_exec_i[ccm_remove]
  }

  IDL::traits< ::CCM_DDS::CCM_PortStatusListener >::ref_type
  Receiver_exec_i::get_info_get_status ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : MDD_Getter_Test_Receiver_Impl::Receiver_exec_i[get_info_get_status]
  if (!this->info_get_status_)
  {
    this->info_get_status_ = CORBA::make_reference <info_get_status_exec_i> (this->context_);
  }
  return this->info_get_status_;
  //@@{__RIDL_REGEN_MARKER__} - END : MDD_Getter_Test_Receiver_Impl::Receiver_exec_i[get_info_get_status]
  }

  /// Operations from Components::SessionComponent
  void
  Receiver_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : MDD_Getter_Test_Receiver_Impl::Receiver_exec_i[set_session_context]
    this->context_ = IDL::traits<MDD_Getter_Test::CCM_Receiver_Context>::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : MDD_Getter_Test_Receiver_Impl::Receiver_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : MDD_Getter_Test_Receiver_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : MDD_Getter_Test_Receiver_Impl[user_namespace_end_impl]

} // namespace MDD_Getter_Test_Receiver_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : MDD_Getter_Test_Receiver_Impl[factory]
extern "C" void
create_MDD_Getter_Test_Receiver_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <MDD_Getter_Test_Receiver_Impl::Receiver_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : MDD_Getter_Test_Receiver_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : mdd_getter_receiver_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
