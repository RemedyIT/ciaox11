// -*- C++ -*-
/**
 * @file    dds4ccm_conf.h
 * @author  Marcel Smit
 *
 * @brief   DDS4CCM4CIAOX11 Configuration file
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDS4CCM_CONF_H_
#define DDS4CCM_CONF_H_

/**
 * CIAOX11_DDS4CCM_CONTEXT_SWITCH defines whether DDS4CCM
 * does use the ORB core reactor thread when a DDS callback
 * has been received.
 *
 * If this is defined to 1 DDS4CCM will pass the DDS callback to the
 * ORB Core Reactor thread which means a thread context switch
 *
 * If this is defined to 0 no context switch takes place and the DDS
 * callback is delivered to the user code on the DDS thread
 *
 * If the user doesn't explicitly choose a value we will default to 1
 */
#if !defined (CIAOX11_DDS4CCM_CONTEXT_SWITCH)
# define CIAOX11_DDS4CCM_CONTEXT_SWITCH 1
#endif /* CIAOX11_DDS4CCM_CONTEXT_SWITCH */

#if (CIAOX11_DDS4CCM_CONTEXT_SWITCH == 1) && !defined (ACE_HAS_REACTOR_NOTIFICATION_QUEUE)
# error For using the DDS4CCM context switch ACE_HAS_REACTOR_NOTIFICATION_QUEUE must be defined
#endif

/**
 * This include provides definitions that need to be implemented for each supported
 * vendor!
 */
#include "dds4ccm_vendor_t.h"

#endif /* DDS4CCM_CONF_H_ */
