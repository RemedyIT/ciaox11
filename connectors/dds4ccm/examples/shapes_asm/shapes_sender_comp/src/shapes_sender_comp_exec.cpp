// -*- C++ -*-
/**
 * @file    shapes_sender_comp_exec.cpp
 * @author  Johnny Willemsen
 *
 * @brief   Shapes sender executor
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : shapes_sender_comp_impl.cpp[Header]

#include "shapes_sender_comp_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Sender_comp_Impl[user_includes]
#include "ciaox11/testlib/ciaox11_testlog.h"
//@@{__RIDL_REGEN_MARKER__} - END : Shapes_Sender_comp_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Sender_comp_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : Shapes_Sender_comp_Impl[user_global_impl]

namespace Shapes_Sender_comp_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Sender_comp_Impl[user_namespace_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Sender_comp_Impl[user_namespace_impl]

  /**
   * Facet Executor Implementation Class : control_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Sender_comp_Impl::control_exec_i[ctor]
  control_exec_i::control_exec_i (
    IDL::traits<Shapes::CCM_Sender_comp_Context>::ref_type context,
    IDL::traits<Shapes::CCM_Sender_comp>::weak_ref_type component_executor)
    : context_ (std::move (context))
    , component_executor_ (std::move(component_executor))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Sender_comp_Impl::control_exec_i[ctor]

  control_exec_i::~control_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Sender_comp_Impl::control_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Sender_comp_Impl::control_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Sender_comp_Impl::control_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Sender_comp_Impl::control_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Sender_comp_Impl::control_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Sender_comp_Impl::control_exec_i[user_private_ops]


  /** Operations and attributes from control */

  ::Shapes::ReturnStatus
  control_exec_i::setSize (
      uint16_t size)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Sender_comp_Impl::control_exec_i::setSize[_size]
    ::Shapes::ReturnStatus status = ::Shapes::ReturnStatus::RETURN_ERROR;
    auto cex = IDL::traits<Sender_comp_exec_i>::narrow (this->component_executor_.lock ());
    if (cex)
      status = cex->setSize (size);
    else
    {
      CIAOX11_TEST_ERROR << "control_exec_i::setSize - "
        "ERROR: failed to lock component executor" << std::endl;
    }
    return status;
    //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Sender_comp_Impl::control_exec_i::setSize[_size]
  }

  ::Shapes::ReturnStatus
  control_exec_i::setLocation (
      uint16_t x,
      uint16_t y)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Sender_comp_Impl::control_exec_i::setLocation[_x_y]
    ::Shapes::ReturnStatus status = ::Shapes::ReturnStatus::RETURN_ERROR;
    auto cex = IDL::traits<Sender_comp_exec_i>::narrow (this->component_executor_.lock ());
    if (cex)
      status = cex->setLocation (x, y);
    else
    {
      CIAOX11_TEST_ERROR << "control_exec_i::setLocation - "
        "ERROR: failed to lock component executor" << std::endl;
    }
    return status;
    //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Sender_comp_Impl::control_exec_i::setLocation[_x_y]
  }

  /**
   * Component Executor Implementation Class : Sender_comp_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Sender_comp_Impl::Sender_comp_exec_i[ctor]
  Sender_comp_exec_i::Sender_comp_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Sender_comp_Impl::Sender_comp_exec_i[ctor]

  Sender_comp_exec_i::~Sender_comp_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Sender_comp_Impl::Sender_comp_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Sender_comp_Impl::Sender_comp_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Sender_comp_Impl::Sender_comp_exec_i[user_public_ops]
  ::Shapes::ReturnStatus
  Sender_comp_exec_i::setSize (uint16_t size)
  {
    this->square_.shapesize(size);
    return this->update_square ();
  }

  ::Shapes::ReturnStatus
  Sender_comp_exec_i::setLocation (uint16_t x, uint16_t y)
   {
    this->square_.x(x);
    this->square_.y(y);
    return this->update_square ();
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Sender_comp_Impl::Sender_comp_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Sender_comp_Impl::Sender_comp_exec_i[user_private_ops]
  ::Shapes::ReturnStatus
  Sender_comp_exec_i::update_square ()
  {
    Shapes::ReturnStatus retval { Shapes::ReturnStatus::RETURN_OK };
    try
      {
        if (this->instance_handle_ != ::DDS::HANDLE_NIL)
          {
            IDL::traits< ::ShapeTypeInterface::Writer>::ref_type writer =
              this->context_->get_connection_info_write_data ();

            writer->write_one (this->square_, this->instance_handle_);

            CIAOX11_TEST_DEBUG
              << "Updated "
              << IDL::traits< ShapeType>::write (this->square_)
              << std::endl;
          }
      }
    catch (const CCM_DDS::NonExistent& )
      {
        retval = Shapes::ReturnStatus::RETURN_ERROR;
        CIAOX11_TEST_ERROR
          << "NonExistent Error while writing "
          << IDL::traits< ShapeType>::write (this->square_) << std::endl;
      }
    catch (const CCM_DDS::InternalError& ex)
      {
        retval = Shapes::ReturnStatus::RETURN_ERROR;
        CIAOX11_TEST_ERROR
          << "Internal Error while writing "
          << IDL::traits< ShapeType>::write (this->square_)
          << ": " << ex << std::endl;
      }
    return retval;
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Sender_comp_Impl::Sender_comp_exec_i[user_private_ops]

  /** Session component operations */
  void Sender_comp_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Sender_comp_Impl::Sender_comp_exec_i[configuration_complete]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Sender_comp_Impl::Sender_comp_exec_i[configuration_complete]
  }

  void Sender_comp_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Sender_comp_Impl::Sender_comp_exec_i[ccm_activate]
    try
      {
        IDL::traits < ::ShapeTypeInterface::Writer>::ref_type writer =
          this->context_->get_connection_info_write_data ();

        this->instance_handle_ = writer->register_instance (this->square_);

        CIAOX11_TEST_DEBUG
          << "Registered shape " << IDL::traits< ShapeType>::write (this->square_) << std::endl;
      }
    catch (const CCM_DDS::AlreadyCreated& )
      {
        CIAOX11_TEST_ERROR
          << "AlreadyCreated Error while creating "
          << IDL::traits< ShapeType>::write (this->square_) << std::endl;
      }
    catch (const CCM_DDS::InternalError& ex)
      {
        CIAOX11_TEST_ERROR
          << "Internal Error while creating "
          << IDL::traits< ShapeType>::write (this->square_)
          << ": " << ex << std::endl;
      }
    //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Sender_comp_Impl::Sender_comp_exec_i[ccm_activate]
  }

  void Sender_comp_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Sender_comp_Impl::Sender_comp_exec_i[ccm_passivate]
    try
      {
        IDL::traits< ShapeTypeInterface::Writer>::ref_type writer =
          this->context_->get_connection_info_write_data ();

        writer->unregister_instance (this->square_,
                                     this->instance_handle_);

        this->instance_handle_ = ::DDS::HANDLE_NIL;

        CIAOX11_TEST_DEBUG
          << "Unregistered shape " << IDL::traits< ShapeType>::write (this->square_) << std::endl;
      }
    catch (const CCM_DDS::NonExistent& )
      {
        CIAOX11_TEST_ERROR <<
         IDL::traits< ShapeType>::write (this->square_)  << " not deleted." << std::endl;
      }
    catch (const CCM_DDS::InternalError& ex)
      {
        CIAOX11_TEST_ERROR
          << "Internal Error while deleting "
          << IDL::traits< ShapeType>::write (this->square_)
          << ": " << ex << std::endl;
      }
    //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Sender_comp_Impl::Sender_comp_exec_i[ccm_passivate]
  }

  void Sender_comp_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Sender_comp_Impl::Sender_comp_exec_i[ccm_remove]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Sender_comp_Impl::Sender_comp_exec_i[ccm_remove]
  }

  IDL::traits< ::Shapes::CCM_Control_obj >::ref_type
  Sender_comp_exec_i::get_control ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Sender_comp_Impl::Sender_comp_exec_i[get_control]
  if (!this->control_)
  {
    this->control_ =
      CORBA::make_reference <control_exec_i>
        (this->context_, IDL::traits<Shapes::CCM_Sender_comp>::narrow (this->_lock()));
  }
  return this->control_;
  //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Sender_comp_Impl::Sender_comp_exec_i[get_control]
  }

  /// Operations from Components::SessionComponent
  void
  Sender_comp_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Sender_comp_Impl::Sender_comp_exec_i[set_session_context]
    this->context_ = IDL::traits<Shapes::CCM_Sender_comp_Context>::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Sender_comp_Impl::Sender_comp_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Sender_comp_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Sender_comp_Impl[user_namespace_end_impl]

} // namespace Shapes_Sender_comp_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Sender_comp_Impl[factory]
extern "C" void
create_Shapes_Sender_comp_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <Shapes_Sender_comp_Impl::Sender_comp_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : Shapes_Sender_comp_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : shapes_sender_comp_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
