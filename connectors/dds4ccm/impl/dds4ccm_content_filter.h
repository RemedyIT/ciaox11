// -*- C++ -*-
/**
 * @file    dds4ccm_content_filter.h
 * @author  Marcel Smit
 *
 * @brief   Implementation of the DDS4CCM connector
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDS4CCM_CONTENT_FILTER_H_
#define DDS4CCM_CONTENT_FILTER_H_

#include "dds4ccm/idl/dds4ccm_baseC.h"
#include "dds4ccm/idl/dds4ccm_baseEC.h"
#include "dds4ccm/impl/dds4ccm_impl_export.h"

namespace CIAOX11
{
  namespace DDS4CCM
  {
    class DDS4CCM_IMPL_Export CCM_DDS_ContentFilterSetting_i
      : public virtual IDL::traits< CCM_DDS::CCM_ContentFilterSetting>::base_type
    {
    public:
      /// Constructor
      CCM_DDS_ContentFilterSetting_i () = default;

      /// Destructor
      ~CCM_DDS_ContentFilterSetting_i () override = default;

      void set_filter_parameters (const ::DDS::StringSeq &parameters) override;

      CCM_DDS::QueryFilter filter ();

      void filter (const CCM_DDS::QueryFilter &filter);

      IDL::traits< ::DDS::ContentFilteredTopic>::ref_type
      create_contentfilteredtopic (
        IDL::traits< ::DDS::Topic>::ref_type topic,
        IDL::traits< ::DDS::Subscriber>::ref_type subscriber);

      void delete_contentfilteredtopic (IDL::traits< ::DDS::Subscriber>::ref_type subscriber);

    private:
      CCM_DDS::QueryFilter filter_ {};
      IDL::traits< ::DDS::ContentFilteredTopic>::ref_type cft_ {};

      CCM_DDS_ContentFilterSetting_i(const CCM_DDS_ContentFilterSetting_i&) = delete;
      CCM_DDS_ContentFilterSetting_i(CCM_DDS_ContentFilterSetting_i&&) = delete;
      CCM_DDS_ContentFilterSetting_i& operator=(const CCM_DDS_ContentFilterSetting_i&) = delete;
      CCM_DDS_ContentFilterSetting_i& operator=(CCM_DDS_ContentFilterSetting_i&&) = delete;
    };
  }
}

#endif /* DDS4CCM_CONTENT_FILTER_H_ */
