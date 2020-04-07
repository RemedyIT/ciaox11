// -*- C++ -*-
/**
 * @file    psdd4ccm_middleware_t.h
 * @author  Martin Corino
 *
 * @brief   Definitions for middleware specific implementations
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
#ifndef PSDD4CCM_MIDDLEWARE_T_H_
#define PSDD4CCM_MIDDLEWARE_T_H_

#include "psdd4ccm/idl/ccm_psddC.h"
#include "psdd4ccm/impl/psdd/psdd_publisher_t.h"
#include "psdd4ccm/impl/psdd/psdd_subscriber_t.h"

namespace CIAOX11
{
  namespace PSDD
  {
    namespace MWUtils
    {
      /* Provides for creation of middleware extended entities.
       */
      template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
      typename IDL::traits< ::PSDD::Publisher_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>>::ref_type
      create_publisher ();

      template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
      typename IDL::traits< ::PSDD::Subscriber_T<CCM_TYPE, TOPIC_TYPE, TOPIC_SEQ_TYPE>>::ref_type
      create_subscriber ();

      template <typename CCM_TYPE>
      std::shared_ptr<typename CCM_TYPE::service_helper_type>
      create_service_helper (
          IDL::traits< ::Components::SessionContext>::ref_type,
          bool publish,
          bool subscribe);
    }
  }
}

#include "psdd4ccm/impl/psdd4ccm_middleware_t.cpp"

#endif /* PSDD4CCM_MIDDLEWARE_T_H_ */
