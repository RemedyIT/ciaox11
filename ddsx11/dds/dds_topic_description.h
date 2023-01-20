// -*- C++ -*-
/**
 * @file    dds_topic_description.h
 * @author  Marcel Smit
 *
 * @brief   Wrapper facade for DDS
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDSX11_IMPL_TOPIC_DESCRIPTION_H_
#define DDSX11_IMPL_TOPIC_DESCRIPTION_H_

#include "dds/dds_export.h"
#include "dds/dds_native_entity_t.h"
#include "idl/dds_dcpsC.h"
#include "dds/dds_proxy_traits_t.h"

#if !defined (DDSX11_HAS_VENDOR_TYPEDEFS)
namespace DDS_Native {
  namespace DDS {
    class TopicDescription;
  }
}
#endif /* DDSX11_HAS_VENDOR_TYPEDEFS */

namespace DDSX11
{
  class DDSX11_IMPL_Export DDS_TopicDescription_proxy final
    : public virtual IDL::traits<::DDS::TopicDescription>::base_type
    , public virtual NativeEntityBase_T<DDS_Native::DDS::TopicDescription>
  {
  public:
    /// Constructor
    explicit DDS_TopicDescription_proxy (DDS_Native::DDS::TopicDescription * rc);

    /// Destructor
    ~DDS_TopicDescription_proxy () override = default;

    std::string get_type_name () override;

    std::string get_name () override;

    IDL::traits<::DDS::DomainParticipant>::ref_type get_participant () override;

  private:

    DDS_TopicDescription_proxy() = delete;
    DDS_TopicDescription_proxy(const DDS_TopicDescription_proxy&) = delete;
    DDS_TopicDescription_proxy(DDS_TopicDescription_proxy&&) = delete;
    DDS_TopicDescription_proxy& operator=(const DDS_TopicDescription_proxy&) = delete;
    DDS_TopicDescription_proxy& operator=(DDS_TopicDescription_proxy&&) = delete;
  };
}

#endif /* DDSX11_IMPL_TOPIC_DESCRIPTION_H_ */
