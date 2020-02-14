// -*- C++ -*-
/**
 * @file    dds_content_filtered_topic.h
 * @author  Marcel Smit
 *
 * @brief   Wrapper facade for DDS
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDSX11_IMPL_CONTENT_FILTERED_TOPIC_H_
#define DDSX11_IMPL_CONTENT_FILTERED_TOPIC_H_

#include "dds/dds_export.h"
#include "dds/dds_native_entity_t.h"
#include "idl/dds_dcpsC.h"
#include "dds/dds_proxy_traits_t.h"

#if !defined (DDSX11_HAS_VENDOR_TYPEDEFS)
namespace DDS_Native {
  namespace DDS {
    class ContentFilteredTopic;
  }
}
#endif /* DDSX11_HAS_VENDOR_TYPEDEFS */

namespace DDSX11
{
  class DDSX11_IMPL_Export DDS_ContentFilteredTopic_proxy final
    : public virtual IDL::traits< ::DDS::ContentFilteredTopic>::base_type
    , public virtual NativeEntityBase_T<DDS_Native::DDS::ContentFilteredTopic>
  {
  public:
    /// Constructor
    explicit DDS_ContentFilteredTopic_proxy (
      DDS_Native::DDS::ContentFilteredTopic * cft);

    /// Destructor
    virtual ~DDS_ContentFilteredTopic_proxy () = default;

    virtual std::string
    get_filter_expression () override;

    virtual ::DDS::ReturnCode_t
    get_expression_parameters (
      ::DDS::StringSeq & expression_parameters) override;

    virtual ::DDS::ReturnCode_t
    set_expression_parameters (
      const ::DDS::StringSeq & expression_parameters) override;

    virtual IDL::traits< ::DDS::Topic >::ref_type
    get_related_topic () override;

    virtual std::string get_type_name () override;

    virtual std::string get_name () override;

    virtual IDL::traits< ::DDS::DomainParticipant >::ref_type
    get_participant () override;

  private:
    DDS_ContentFilteredTopic_proxy() = delete;
    DDS_ContentFilteredTopic_proxy(const DDS_ContentFilteredTopic_proxy&) = delete;
    DDS_ContentFilteredTopic_proxy(DDS_ContentFilteredTopic_proxy&&) = delete;
    DDS_ContentFilteredTopic_proxy& operator=(const DDS_ContentFilteredTopic_proxy&) = delete;
    DDS_ContentFilteredTopic_proxy& operator=(DDS_ContentFilteredTopic_proxy&&) = delete;
  };

  typedef entity_traits< ::DDS::ContentFilteredTopic, DDS_ContentFilteredTopic_proxy, DDS_Native::DDS::ContentFilteredTopic >
    cft_trait;

} /* DDS_X11 */

#endif /* DDSX11_IMPL_CONTENT_FILTERED_TOPIC_H_ */
