// -*- C++ -*-
/**
 * @file    psdd4ccm_conf.h
 * @author  Martin Corino
 *
 * @brief   PSDD4CCM Configuration file
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
#ifndef PSDD4CCM_CONF_H_
#define PSDD4CCM_CONF_H_

/**
 * CIAOX11_PSDD4CCM_CONTEXT_SWITCH defines whether PSDD4CCM
 * uses the ORB core reactor thread when a PSDD4CCM callback
 * has been received.
 *
 * If this is defined to 1 PSDD4CCM will pass the middleware callbacks to the
 * ORB Core Reactor thread which means a thread context switch
 *
 * If this is defined to 0 no context switch takes place and the middleware
 * callback is delivered to the user code on the middleware thread
 *
 * If the user doesn't explicitly choose a value we will default to 1
 */
#if !defined (CIAOX11_PSDD4CCM_CONTEXT_SWITCH)
#  define CIAOX11_PSDD4CCM_CONTEXT_SWITCH 1
#  define ACE_HAS_REACTOR_NOTIFICATION_QUEUE
#endif /* CIAOX11_PSDD4CCM_CONTEXT_SWITCH */

#if (CIAOX11_PSDD4CCM_CONTEXT_SWITCH == 1) && !defined (ACE_HAS_REACTOR_NOTIFICATION_QUEUE)
#  error For using the PSDD4CCM context switch ACE_HAS_REACTOR_NOTIFICATION_QUEUE must be defined
#endif

/**
 * These includes provide definitions that need to be implemented for all supported
 * middleware!
 */
#include "psdd4ccm/impl/psdd4ccm_middleware_t.h"
#include "psdd4ccm/impl/psdd_service_helper.h"
#include "psdd4ccm/impl/psdd_traits.h"

#endif /* PSDD4CCM_CONF_H_ */
