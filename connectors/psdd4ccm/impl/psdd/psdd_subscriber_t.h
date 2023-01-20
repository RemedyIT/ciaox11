// -*- C++ -*-
/**
 * @file    psdd_subscriber_t.h
 * @author  Martin Corino
 *
 * @brief   PSDD subscriber template
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef PSDD_SUBSCRIBER_T_H
#define PSDD_SUBSCRIBER_T_H

namespace PSDD
{
  template <typename CCM_TYPE, typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE>
  class Subscriber_T
    : public CCM_TYPE::consumer_traits::data_subscriber_type
  {
  public:
    ~Subscriber_T () override = default;

    typedef typename CCM_TYPE::event_strategy_type event_strategy_type;
    typedef typename CCM_TYPE::consumer_traits::data_type pull_consumer_data_type;
    typedef typename CCM_TYPE::consumer_traits::data_listener_type push_consumer_data_listener_type;
    typedef typename CCM_TYPE::service_helper_type service_helper_type;

    virtual void
    initialize (
        const std::string &topic_name,
        std::shared_ptr<service_helper_type> svhlp) = 0;

    virtual void
    shutdown () = 0;

    virtual typename IDL::traits<pull_consumer_data_type>::ref_type
    get_pull_consumer_data () = 0;

    virtual void
    activate_push_consumer_data_listener (
        const event_strategy_type&) = 0;

    virtual void
    dispatch_data_available (
        typename IDL::traits<push_consumer_data_listener_type>::ref_type dl) = 0;
  };
};

#endif
