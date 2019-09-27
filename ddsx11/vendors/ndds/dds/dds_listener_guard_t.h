// -*- C++ -*-
/**
 * @file    dds_listener_guard_t.h
 * @author  Johnny Willemsen
 *
 * @brief   Guard for make sure we cleanup the vendor set listener
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
#ifndef DDSX11_NDDS_LISTENER_GUARD_T_H_
#define DDSX11_NDDS_LISTENER_GUARD_T_H_

namespace DDSX11
{
  template <typename NATIVE_LISTENER_TYPE, typename X11_REF_TYPE>
  class DDSX11_Listener_Guard_T
  {
  public:
    DDSX11_Listener_Guard_T () = default;
    DDSX11_Listener_Guard_T (NATIVE_LISTENER_TYPE* drl) : listener_ (drl) { }
    ~DDSX11_Listener_Guard_T () = default;
    void operator= (NATIVE_LISTENER_TYPE* drl)
    {
      listener_.reset (drl);
    }
    NATIVE_LISTENER_TYPE* get ()
    {
      return listener_.get ();
    }
    void release ()
    {
      listener_.release ();
    }
  private:
    std::unique_ptr<NATIVE_LISTENER_TYPE> listener_;
    DDSX11_Listener_Guard_T(const DDSX11_Listener_Guard_T&) = delete;
    DDSX11_Listener_Guard_T(DDSX11_Listener_Guard_T&&) = delete;
    DDSX11_Listener_Guard_T& operator=(const DDSX11_Listener_Guard_T&) = delete;
    DDSX11_Listener_Guard_T& operator=(DDSX11_Listener_Guard_T&&) = delete;
  };
} // namespace DDSX11

#endif /* DDSX11_NDDS_LISTENER_GUARD_T_H_ */
