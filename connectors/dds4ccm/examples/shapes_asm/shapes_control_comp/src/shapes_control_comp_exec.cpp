// -*- C++ -*-
/**
 * @file    shapes_control_comp_exec.cpp
 * @author  Johnny Willemsen
 *
 * @brief   Shapes control component
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : shapes_control_comp_impl.cpp[Header]

#include "shapes_control_comp_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Control_comp_Impl[user_includes]
#include "ciaox11/testlib/ciaox11_testlog.h"
//@@{__RIDL_REGEN_MARKER__} - END : Shapes_Control_comp_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Control_comp_Impl[user_global_impl]
#define MIN_SIZE 5
//@@{__RIDL_REGEN_MARKER__} - END : Shapes_Control_comp_Impl[user_global_impl]

namespace Shapes_Control_comp_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Control_comp_Impl[user_namespace_impl]
  class TT_Callback final
         : public IDL::traits<CCM_TT::TT_Handler>::base_type
  {
  public:
    TT_Callback (IDL::traits< ::Shapes::CCM_Control_comp>::weak_ref_type component_executor)
    : component_executor_(component_executor)
    {}

    virtual
    void
    on_trigger (
       IDL::traits< ::CCM_TT::TT_Timer>::ref_type,
       const ::CCM_TT::TT_Duration&,
       uint32_t round);

   private:
     IDL::traits< ::Shapes::CCM_Control_comp>::weak_ref_type component_executor_;
  };

  void
  TT_Callback::on_trigger (
     IDL::traits< ::CCM_TT::TT_Timer>::ref_type,
     const ::CCM_TT::TT_Duration&,
     uint32_t)
  {
    auto cex = IDL::traits<Control_comp_exec_i>::narrow (this->component_executor_.lock ());
    if (cex)
    {
      cex->tick();
    }
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Control_comp_Impl[user_namespace_impl]


  /**
   * Component Executor Implementation Class : Control_comp_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Control_comp_Impl::Control_comp_exec_i[ctor]
  Control_comp_exec_i::Control_comp_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Control_comp_Impl::Control_comp_exec_i[ctor]

  Control_comp_exec_i::~Control_comp_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Control_comp_Impl::Control_comp_exec_i[dtor]
    //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Control_comp_Impl::Control_comp_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Control_comp_Impl::Control_comp_exec_i[user_public_ops]
  void
  Control_comp_exec_i::tick ()
  {
    if (this->x_increasing_)
    {
      ++this->current_x_;
      this->x_increasing_ = this->current_x_ + 1 <= this->max_x_;
    }
    else
    {
      --this->current_x_;
      this->x_increasing_ = this->current_x_ - 1 < 0;
    }
    if (this->y_increasing_)
    {
      ++this->current_y_;
      this->y_increasing_ = this->current_y_ + 1 <= this->max_y_;
    }
    else
    {
      --this->current_y_;
      this->y_increasing_ = this->current_y_ - 1 < 0;
    }
    if (resize_shape ())
    {
      if (this->size_increasing_)
      {
        ++this->current_size_;
        this->size_increasing_ = this->current_size_ + 1 <= this->max_size_;
      }
      else
      {
        if (this->current_size_ == MIN_SIZE)
        {
          this->size_increasing_ = true;
        }
        else
        {
          --this->current_size_;
          this->size_increasing_ = this->current_size_ - 1 < 0;
        }
      }
    }

    CIAOX11_TEST_DEBUG << "Updating Shape" << std::endl;
    IDL::traits< ::Shapes::Control_obj>::ref_type control =
      this->context_->get_connection_control ();

    if (!control)
    {
      CIAOX11_TEST_ERROR
          << "Control_comp_exec_i::tick: "
          << "Control connection is null" << std::endl;
      return;
    }
    if (control->setSize (this->current_size_) == ::Shapes::ReturnStatus::RETURN_ERROR)
      {
        CIAOX11_TEST_ERROR
          << "Control_comp_exec_i::tick: "
          << "Error setting shapes size" << std::endl;
      }
    else
      {
        CIAOX11_TEST_DEBUG
          << "Control_comp_exec_i::tick: "
          << "Size set to <" << this->current_size_ << ">" << std::endl;
      }
    if (control->setLocation (this->current_x_,
                              this->current_y_) == ::Shapes::ReturnStatus::RETURN_ERROR)
      {
        CIAOX11_TEST_ERROR
          << "Control_comp_exec_i::tick: "
          << "Error setting shapes location" << std::endl;
      }
    else
      {
        CIAOX11_TEST_DEBUG
          << "Control_comp_exec_i::tick: "
          << "Location set to <" << this->current_x_ << "><"
          << this->current_y_ << ">" << std::endl;
      }
   }
  //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Control_comp_Impl::Control_comp_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Control_comp_Impl::Control_comp_exec_i[user_private_ops]
  //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Control_comp_Impl::Control_comp_exec_i[user_private_ops]

  /** Session component operations */
  void Control_comp_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Control_comp_Impl::Control_comp_exec_i[configuration_complete]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Control_comp_Impl::Control_comp_exec_i[configuration_complete]
  }

  void Control_comp_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Control_comp_Impl::Control_comp_exec_i[ccm_activate]
    IDL::traits<CCM_TT::TT_Scheduler>::ref_type tt_s = this->context_->get_connection_tt_scheduler ();
    this->tm_= tt_s->schedule_repeated_trigger (
                           CORBA::make_reference<TT_Callback> (IDL::traits< Shapes::CCM_Control_comp>::narrow (this->_lock())),
                           CCM_TT::TT_Duration (1,0),
                           CCM_TT::TT_Duration (0,1000000000 / this->rate_),
                           0);

    //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Control_comp_Impl::Control_comp_exec_i[ccm_activate]
  }

  void Control_comp_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Control_comp_Impl::Control_comp_exec_i[ccm_passivate]
    if (!this->tm_)
    {
      CIAOX11_TEST_ERROR << "ERROR: Control_comp_exec_i::ccm_passivate - "
                            "Test did not start."
                         << std::endl;
    }
    else
    {
      if (!this->tm_->is_canceled())
      {
        this->tm_->cancel();
      }
    }
    //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Control_comp_Impl::Control_comp_exec_i[ccm_passivate]
  }

  void Control_comp_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Control_comp_Impl::Control_comp_exec_i[ccm_remove]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Control_comp_Impl::Control_comp_exec_i[ccm_remove]
  }


  uint32_t
  Control_comp_exec_i::rate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Control_comp_Impl::Control_comp_exec_i::rate[getter]
    return this->rate_;
    //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Control_comp_Impl::Control_comp_exec_i::rate[getter]
  }

  void
  Control_comp_exec_i::rate (
      uint32_t rate)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Control_comp_Impl::Control_comp_exec_i::rate[setter]
    this->rate_ = rate;
    //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Control_comp_Impl::Control_comp_exec_i::rate[setter]
  }

  uint16_t
  Control_comp_exec_i::max_x ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Control_comp_Impl::Control_comp_exec_i::max_x[getter]
    return this->max_x_;
    //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Control_comp_Impl::Control_comp_exec_i::max_x[getter]
  }

  void
  Control_comp_exec_i::max_x (
      uint16_t max_x)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Control_comp_Impl::Control_comp_exec_i::max_x[setter]
    this->max_x_ = max_x;
    //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Control_comp_Impl::Control_comp_exec_i::max_x[setter]
  }

  uint16_t
  Control_comp_exec_i::max_y ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Control_comp_Impl::Control_comp_exec_i::max_y[getter]
    return this->max_y_;
    //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Control_comp_Impl::Control_comp_exec_i::max_y[getter]
  }

  void
  Control_comp_exec_i::max_y (
      uint16_t max_y)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Control_comp_Impl::Control_comp_exec_i::max_y[setter]
    this->max_y_ = max_y;
    //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Control_comp_Impl::Control_comp_exec_i::max_y[setter]
  }

  uint16_t
  Control_comp_exec_i::max_size ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Control_comp_Impl::Control_comp_exec_i::max_size[getter]
    return this->max_size_;
    //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Control_comp_Impl::Control_comp_exec_i::max_size[getter]
  }

  void
  Control_comp_exec_i::max_size (
      uint16_t max_size)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Control_comp_Impl::Control_comp_exec_i::max_size[setter]
    this->max_size_ = max_size;
    this->current_size_ = max_size;
    //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Control_comp_Impl::Control_comp_exec_i::max_size[setter]
  }

  bool
  Control_comp_exec_i::resize_shape ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Control_comp_Impl::Control_comp_exec_i::resize_shape[getter]
    return this->resize_shape_;
    //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Control_comp_Impl::Control_comp_exec_i::resize_shape[getter]
  }

  void
  Control_comp_exec_i::resize_shape (
      bool resize_shape)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Control_comp_Impl::Control_comp_exec_i::resize_shape[setter]
    this->resize_shape_ = resize_shape;
    //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Control_comp_Impl::Control_comp_exec_i::resize_shape[setter]
  }

  /// Operations from Components::SessionComponent
  void
  Control_comp_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Control_comp_Impl::Control_comp_exec_i[set_session_context]
    this->context_ = IDL::traits<Shapes::CCM_Control_comp_Context>::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Control_comp_Impl::Control_comp_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Control_comp_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : Shapes_Control_comp_Impl[user_namespace_end_impl]

} // namespace Shapes_Control_comp_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Shapes_Control_comp_Impl[factory]
extern "C" void
create_Shapes_Control_comp_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <Shapes_Control_comp_Impl::Control_comp_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : Shapes_Control_comp_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : shapes_control_comp_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-
