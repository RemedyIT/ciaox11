// -*- C++ -*-
/**
 * @file    dds4ccm_content_filter.cpp
 * @author  Marcel Smit
 *
 * @brief   Implementation of the DDS4CCM connector
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
#include "dds4ccm/impl/dds4ccm_content_filter.h"
#include "dds4ccm/logger/dds4ccm_log.h"
#include "dds4ccm/impl/dds4ccm_utils.h"

namespace CIAOX11
{
  namespace DDS4CCM
  {
    ::CCM_DDS::QueryFilter
    CCM_DDS_ContentFilterSetting_i::filter ()
    {
      DDS4CCM_LOG_TRACE (
        "CCM_DDS_ContentFilterSetting_i::filter");

      return this->filter_;
    }

    void
    CCM_DDS_ContentFilterSetting_i::filter (
      const ::CCM_DDS::QueryFilter & filter)
    {
      DDS4CCM_LOG_TRACE ("CCM_DDS_ContentFilterSetting_i::filter");

      this->filter_ = filter;
      DDS4CCM_LOG_DEBUG ("CCM_DDS_ContentFilterSetting_i::filter - "
        << IDL::traits< ::CCM_DDS::QueryFilter >::write (filter));
    }

    IDL::traits< ::DDS::ContentFilteredTopic >::ref_type
    CCM_DDS_ContentFilterSetting_i::create_contentfilteredtopic (
      IDL::traits< ::DDS::Topic >::ref_type topic,
      IDL::traits< ::DDS::Subscriber >::ref_type subscriber)
    {
      DDS4CCM_LOG_TRACE (
        "CCM_DDS_ContentFilterSetting_i::create_contentfilteredtopic");

      IDL::traits< ::DDS::DomainParticipant >::ref_type dp =
        subscriber->get_participant ();
      if (!dp)
      {
        DDS4CCM_LOG_ERROR (
          "CCM_DDS_ContentFilterSetting_i::create_contentfilteredtopic: "
          "Unable to get DomainParticipant.");
        throw CORBA::INTERNAL ();
      }

      // Determine the name of the ContentFilteredTopic
      // A ContentFilteredTopic cannot have the same name as another Content-
      // FilteredTopic in the same DomainParticipant. Since a domain participant
      // can be shared, the name should be unique.
      // Using stringstream to avoid compiler issues.
      std::stringstream name;
      name << "DDS4CCMX11_CFT_" << this;

      this->cft_ =
        dp->create_contentfilteredtopic (
          name.str (),
          topic,
          this->filter_.expression (),
          this->filter_.parameters ());

      if (!this->cft_)
      {
        DDS4CCM_LOG_ERROR (
          "CCM_DDS_ContentFilterSetting_i::create_contentfilteredtopic: "
          "Error creating ContentFilteredTopic <"
          << name.str () << ">.");
        throw CORBA::INTERNAL ();
      }
      else
      {
        DDS4CCM_LOG_DEBUG (
          "CCM_DDS_ContentFilterSetting_i::create_contentfilteredtopic: "
          "successfully created ContentFilteredTopic <"
          << name.str () << ">.");
      }
      return this->cft_;
    }

    void
    CCM_DDS_ContentFilterSetting_i::delete_contentfilteredtopic (
      IDL::traits< ::DDS::Subscriber >::ref_type subscriber)
    {
      DDS4CCM_LOG_TRACE (
        "CCM_DDS_ContentFilterSetting_i::delete_contentfilteredtopic");

      IDL::traits< ::DDS::DomainParticipant >::ref_type dp =
        subscriber->get_participant ();

      if (dp && this->cft_)
      {
        std::string const name = this->cft_->get_name ();
        ::DDS::ReturnCode_t const retcode =
          dp->delete_contentfilteredtopic (this->cft_);

        if (retcode == ::DDS::RETCODE_OK)
        {
          DDS4CCM_LOG_DEBUG (
            "CCM_DDS_ContentFilterSetting_i::delete_contentfilteredtopic: "
            << "successfully deleted ContentFilteredTopic <"
            << name << ">.");
        }
        else
        {
          DDS4CCM_LOG_ERROR (
            "CCM_DDS_ContentFilterSetting_i::delete_contentfilteredtopic: "
            << "Error deleting ContentFilteredTopic <"
            << name << ">: <"
            << IDL::traits< ::DDS::ReturnCode_t >::write<retcode_formatter> (retcode)
            << ">.");
          throw CCM_DDS::InternalError (retcode, 0);
        }
      }
    }

    void
    CCM_DDS_ContentFilterSetting_i::set_filter_parameters (
      const ::DDS::StringSeq &parameters)
    {
      DDS4CCM_LOG_TRACE ("CCM_DDS_ContentFilterSetting_i::set_filter_parameters");

      if (!this->cft_ || this->filter_.expression ().empty ())
      {
        DDS4CCM_LOG_ERROR (
          "CCM_DDS_ContentFilterSetting_i::set_filter_parameters: "
          "Calling set_filter_parameters without having set a filter.");
        throw CCM_DDS::InternalError (::DDS::RETCODE_BAD_PARAMETER, 0);
      }

      ::DDS::ReturnCode_t const retcode =
        this->cft_->set_expression_parameters (parameters);
      if (retcode == ::DDS::RETCODE_OK)
      {
        DDS4CCM_LOG_DEBUG ("CCM_DDS_ContentFilterSetting_i::set_filter_parameters: "
          "successfully set parameters on ContentFilteredTopic.");
        this->filter_.parameters (parameters);
      }
      else
      {
        DDS4CCM_LOG_ERROR("CCM_DDS_ContentFilterSetting_i::set_filter_parameters: "
          << "Error setting filter parameters: <"
          << IDL::traits< ::DDS::ReturnCode_t >::write<retcode_formatter> (retcode)
          << ">.");

        throw CCM_DDS::InternalError (retcode, 0);
      }
    }
  }
}
