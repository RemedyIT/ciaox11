// -*- C++ -*-
/**
 * @file    psdd_publisher_t.h
 * @author  Martin Corino
 *
 * @brief   PSDD publisher template
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef PSDD_PUBLISHER_T_H
#define PSDD_PUBLISHER_T_H

namespace PSDD
{
  template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
  class Publisher_T
    : public CCM_TYPE::supplier_traits::data_type
  {
  public:
    ~Publisher_T () override = default;

    typedef typename CCM_TYPE::service_helper_type service_helper_type;

    virtual void
    initialize (
        const std::string &topic_name,
        std::shared_ptr<service_helper_type> svhlp) = 0;

    virtual void shutdown () = 0;
  };
};

#endif
