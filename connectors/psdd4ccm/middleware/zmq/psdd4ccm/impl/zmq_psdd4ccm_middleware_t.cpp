// -*- C++ -*-
/**
 * @file    zmq_psdd4ccm_middleware_t.cpp
 * @author  Martin Corino
 *
 * @brief   Switch for middleware specific implementations
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef ZMQ_PSDD4CCM_MIDDLEWARE_T_CPP_
#define ZMQ_PSDD4CCM_MIDDLEWARE_T_CPP_

#include "psdd4ccm/impl/zmq_psdd_publisher_t.h"
#include "psdd4ccm/impl/zmq_psdd_subscriber_t.h"
#include "zmq_psdd_service_helper.h"

namespace CIAOX11
{
  namespace PSDD
  {
    namespace MWUtils
    {
      /* Provides for creation of middleware extended entities.
       */
      template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
      typename IDL::traits<::PSDD::Publisher_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>>::ref_type
      create_publisher ()
      {
        return CORBA::make_reference< ::PSDD::ZMQ::Publisher_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE> > ();
      }

      template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
      typename IDL::traits<::PSDD::Subscriber_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>>::ref_type
      create_subscriber ()
      {
        return CORBA::make_reference< ::PSDD::ZMQ::Subscriber_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE> > ();
      }

      template <typename CCM_TYPE>
      std::shared_ptr<typename CCM_TYPE::service_helper_type>
      create_service_helper (
          IDL::traits<::Components::SessionContext>::ref_type ctx,
          bool publish,
          bool subscribe)
      {
        try
        {
          std::shared_ptr<typename CCM_TYPE::service_helper_type> svhlp =
              std::make_shared< ::PSDD::ZMQ::ServiceHelper> ();
          svhlp->initialize (ctx, publish, subscribe);
          return svhlp;
        }
        catch (const std::bad_alloc&)
        {
          return {};
        }
      }
    }
  }
}

#endif
