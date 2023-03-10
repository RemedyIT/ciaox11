/**
 * @file   ciaox11_exf_amh_base.h
 * @author Martin Corino
 *
 * @brief Base class for ExF based AMH request handlers.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef CIAOX11_EXF_AMH_BASE_H
#define CIAOX11_EXF_AMH_BASE_H

#include "tao/x11/object_fwd.h"

#include "ace/Semaphore.h"
#include "exf/deployment/amh/ciaox11_exf_amh_export.h"

// forward declare the TAO AMH response handler and Output CDR
TAO_BEGIN_VERSIONED_NAMESPACE_DECL

class TAO_ServerRequest;
class TAO_Operation_Details;
class TAO_OutputCDR;

TAO_END_VERSIONED_NAMESPACE_DECL

// X11_FUZZ: disable check_taox11_namespaces

namespace CIAOX11
{
  namespace ExF
  {
    namespace Impl
    {
      class AMH_ResponseHandler;
      typedef AMH_ResponseHandler* AMH_ResponseHandler_ptr;

      struct ExceptionHolder;

      class CIAOX11_EXF_AMH_Export RequestHandler
      {
      public:
        // cannot make it '= default;' as ExceptionHolder is still incomplete here
        RequestHandler ();
        virtual ~RequestHandler ();

        void send_exception (const TAOX11_CORBA::Exception& ex)
        { this->_exf_rh_send_exception (ex); }

        void _exf_wait_for_collocated_result ();

      protected:
        void _exf_rh_init_handler (TAO_ServerRequest&);

        void _exf_rh_init_reply ();

        void _exf_rh_send_reply ();

        void _exf_rh_send_exception (const TAOX11_CORBA::Exception&);

        TAO_OutputCDR& _exf_rh_output ();

        TAO_Operation_Details const * _exf_operation_details () const;

      private:
        TAOX11_NAMESPACE::Object_proxy_ref proxy_;
        AMH_ResponseHandler_ptr rh_ptr_ {};
        TAO_ServerRequest* srv_request_ {};
        ACE_Semaphore collocated_sem_ {0};
        std::unique_ptr<ExceptionHolder> ex_;
      };
    }
  }
}

// X11_FUZZ: enable check_taox11_namespaces

#endif
