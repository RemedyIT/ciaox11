/**
 * @file   ciaox11_exf_amh_base.cpp
 * @author Martin Corino
 *
 * @brief Base class for ExF based AMH request handlers.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#include "exf/deployment/amh/ciaox11_exf_amh_base.h"

#include "tao/Messaging/AMH_Response_Handler.h"
#include "tao/Thread_Lane_Resources.h"
#include "tao/Buffer_Allocator_T.h"
#include "tao/TAO_Server_Request.h"
#include "tao/ORB_Core.h"

#include "tao/x11/objproxy.h"
#include "tao/x11/user_exception_proxy_out.h"
#include "exf/deployment/logger/log.h"

// X11_FUZZ: disable check_taox11_namespaces
// X11_FUZZ: disable check_new_delete

namespace CIAOX11
{
  namespace ExF
  {
    namespace Impl
    {
      class AMH_ResponseHandler
        : public TAO_AMH_Response_Handler
      {
      public:
        // make this accessible
        TAO_OutputCDR& tao_out ()
        { return this->_tao_out; }

        void init_reply ()
        { this->_tao_rh_init_reply (); }

        void send_reply ()
        { this->_tao_rh_send_reply (); }

        void send_exception (const TAO_CORBA::Exception& ex)
        { this->_tao_rh_send_exception (ex); }
      };

      struct ExceptionHolder
      {
        ExceptionHolder (TAO_CORBA::Exception* ex) : tao_ex_ (ex) {}
        ExceptionHolder (const ExceptionHolder&) = default;
        ExceptionHolder (ExceptionHolder&&) = default;
        ~ExceptionHolder () { delete tao_ex_; }
        TAO_CORBA::Exception* tao_ex_;
      };

      RequestHandler::RequestHandler ()
      {
      }

      RequestHandler::~RequestHandler ()
      {
        // just reset, do *not* delete; that is handled by proxy_ member
        this->rh_ptr_ = nullptr;
      }

      void
      RequestHandler::_exf_rh_init_handler (TAO_ServerRequest& srvreq)
      {
        CIAOX11_EXF_LOG_TRACE ("RequestHandler::_exf_rh_init_handler - " <<
                               "request for " << srvreq.operation ());

        if (nullptr == srvreq.incoming ())
        {
          CIAOX11_EXF_LOG_TRACE ("RequestHandler::_exf_rh_init_handler - " <<
                                 "colocated call");

          // cache for collocated call handling
          this->srv_request_ = &srvreq;
        }
        else
        {
          CIAOX11_EXF_LOG_TRACE ("RequestHandler::_exf_rh_init_handler - " <<
                                 "remote call");

          TAO_ORB_Core *orb_core =
              srvreq.orb ()->orb_core ();

          TAO_AMH_BUFFER_ALLOCATOR* amh_allocator =
            orb_core->lane_resources ().amh_response_handler_allocator ();

          TAO::TAO_Buffer_Allocator<
              ExF::Impl::AMH_ResponseHandler,
              TAO_AMH_BUFFER_ALLOCATOR
            > buffer_allocator (amh_allocator);

          ExF::Impl::AMH_ResponseHandler_ptr _tao_rh_ptr =
            buffer_allocator.allocate();

          if (!_tao_rh_ptr)
          {
            throw TAO_CORBA::NO_MEMORY ();
          }

          _tao_rh_ptr->init (srvreq, amh_allocator);

          // manage response handler reference
          try
          {
            this->proxy_ =
                std::make_unique<TAOX11_NAMESPACE::Object_proxy> (_tao_rh_ptr);
          }
          catch (const std::bad_alloc&)
          {
            throw TAO_CORBA::NO_MEMORY ();
          }
          // keep for fast access
          this->rh_ptr_ = _tao_rh_ptr;
        }
      }

      void
      RequestHandler::_exf_rh_init_reply ()
      {
        if (!this->srv_request_)
        {
          if (!this->rh_ptr_)
          {
            // this should NEVER happen
            throw TAOX11_CORBA::INV_OBJREF ();
          }
          this->rh_ptr_->init_reply ();
        }
      }

      void
      RequestHandler::_exf_rh_send_reply ()
      {
        if (this->srv_request_)
        {
          this->collocated_sem_.release ();
        }
        else
        {
          if (!this->rh_ptr_)
          {
            // this should NEVER happen
            throw TAOX11_CORBA::INV_OBJREF ();
          }
          this->rh_ptr_->send_reply ();
        }
      }

      void
      RequestHandler::_exf_rh_send_exception (const TAOX11_CORBA::Exception& ex)
      {
        try
        {
          try
          {
            ex._raise();
          }
          catch (const TAOX11_NAMESPACE::CORBA::UserException& _ex) {
            throw TAOX11_NAMESPACE::UserExceptionProxy::out (_ex);
          }
          catch (const TAOX11_NAMESPACE::CORBA::SystemException& _ex) {
            // reraise as TAO system exception
            _ex._raise_tao ();
          }
        }
        catch (const TAO_CORBA::Exception& tao_ex)
        {
          if (nullptr != this->srv_request_)
          {
            try
            {
              this->ex_ = std::make_unique<ExceptionHolder> (tao_ex._tao_duplicate ());
            }
            catch (const std::bad_alloc&)
            {
              CIAOX11_EXF_LOG_ERROR ("RequestHandler::_exf_rh_send_exception - " <<
                                     "no memory");
            }

            this->collocated_sem_.release ();
          }
          else
          {
            this->rh_ptr_->send_exception (tao_ex);
          }
        }
        catch (...)
        {
          if (nullptr != this->srv_request_)
          {
            try
            {
              this->ex_ = std::make_unique<ExceptionHolder> (new TAO_CORBA::INTERNAL ());
            }
            catch (const std::bad_alloc&)
            {
              CIAOX11_EXF_LOG_ERROR ("RequestHandler::_exf_rh_send_exception - " <<
                                     "no memory");
            }

            this->collocated_sem_.release ();
          }
          else
          {
            this->rh_ptr_->send_exception (TAO_CORBA::INTERNAL ());
          }
        }
      }

      TAO_OutputCDR&
      RequestHandler::_exf_rh_output ()
      {
        if (!this->rh_ptr_)
        {
          // this should NEVER happen
          throw TAOX11_CORBA::INV_OBJREF ();
        }
        return this->rh_ptr_->tao_out ();
      }

      TAO_Operation_Details const *
      RequestHandler::_exf_operation_details () const
      {
        if (!this->srv_request_)
        {
          return nullptr;
        }
        else
        {
          return this->srv_request_->operation_details ();
        }
      }

      void
      RequestHandler::_exf_wait_for_collocated_result ()
      {
        if (this->srv_request_)
        {
          this->collocated_sem_.acquire ();

          if (this->ex_)
          {
            this->ex_->tao_ex_->_raise ();
          }
        }
      }
    }
  }
}
