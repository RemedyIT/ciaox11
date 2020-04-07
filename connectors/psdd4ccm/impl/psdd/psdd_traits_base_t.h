/**
 * @file    psdd_traits_base_t.h
 * @author  Martin Corino
 *
 * @brief   Base PSDD traits for the topic type
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
#ifndef PSDD4CCM_TRAITS_BASE_H_
#define PSDD4CCM_TRAITS_BASE_H_

#include <type_traits>

namespace PSDD
{
  /**
   * Base struct for conversions
   */
  //@{
  template <typename DATA_TYPE>
  struct common_traits
  {
    typedef DATA_TYPE value_type;
  };

  template <typename DATA_TYPE>
  struct traits
    : public common_traits<DATA_TYPE>
  {
  };
  //@}

} // namespace PSDD

#endif /* PSDD4CCM_TRAITS_BASE_H_ */
