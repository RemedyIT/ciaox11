/**
 * @file    psdd_traits.h
 * @author  Martin Corino
 *
 * @brief   ZMQ Middleware specific include for the PSDD traits.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef PSDD4CCM_TRAITS_H_
#define PSDD4CCM_TRAITS_H_

#include <type_traits>

# include "psdd4ccm/impl/zmq_psdd_traits.h"

namespace PSDD
{
  // import middleware specific classes
  using ::PSDD::ZMQ::PSDataIn;
  using ::PSDD::ZMQ::PSDataOut;
}

#endif /* PSDD4CCM_TRAITS_H_ */
