// -*- C++ -*-
/**
 * @file    dds_data_writer.h
 * @author  Marcel Smit
 *
 * @brief   Placeholder for the type specific native DataWriter. This is
 *          there in order to be able to create a generic conversion trait.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
#ifndef DDSX11_IMPL_DATA_WRITER_H_
#define DDSX11_IMPL_DATA_WRITER_H_

#include "dds/dds_proxy_traits_t.h"
#include "dds/dds_common.h"

#if !defined (DDSX11_HAS_VENDOR_TYPEDEFS)
namespace DDS_Native {
  namespace DDS {
    class DataWriter;
  }
}
#endif /* DDSX11_HAS_VENDOR_TYPEDEFS */

namespace DDSX11
{
  class DDS_DataWriter_proxy
    : public virtual IDL::traits< ::DDS::DataWriter>::base_type
  {
  public:
    DDS_DataWriter_proxy () = default;
    virtual ~DDS_DataWriter_proxy () = default;

    virtual DDS_Native::DDS::DataWriter *
    get_native_entity () = 0;

  private:
    DDS_DataWriter_proxy(const DDS_DataWriter_proxy&) = delete;
    DDS_DataWriter_proxy(DDS_DataWriter_proxy&&) = delete;
    DDS_DataWriter_proxy& operator=(const DDS_DataWriter_proxy&) = delete;
    DDS_DataWriter_proxy& operator=(DDS_DataWriter_proxy&&) = delete;
  };

  typedef entity_traits< ::DDS::DataWriter, DDS_DataWriter_proxy, DDS_Native::DDS::DataWriter >
    data_writer_trait;
}

#endif /* DDSX11_IMPL_DATA_WRITER_H_ */
