// -*- C++ -*-
/**
 * @file    dds_data_reader.h
 * @author  Marcel Smit
 *
 * @brief   Placeholder for the type specific native DataReader. This is
 *          there in order to be able to create a generic conversion trait.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDSX11_IMPL_DATA_READER_H_
#define DDSX11_IMPL_DATA_READER_H_

#include "dds/dds_proxy_traits_t.h"

#if !defined (DDSX11_HAS_VENDOR_TYPEDEFS)
namespace DDS_Native {
  namespace DDS {
    class DataReader;
  }
#endif /* DDSX11_HAS_VENDOR_TYPEDEFS */

namespace DDSX11
{
  class DDS_DataReader_proxy
    : public virtual IDL::traits< ::DDS::DataReader>::base_type
  {
  public:
    DDS_DataReader_proxy () = default;
    virtual ~DDS_DataReader_proxy () = default;

    virtual DDS_Native::DDS::DataReader *get_native_entity () = 0;
    virtual void clear_native_entity () = 0;

  private:
    DDS_DataReader_proxy(const DDS_DataReader_proxy&) = delete;
    DDS_DataReader_proxy(DDS_DataReader_proxy&&) = delete;
    DDS_DataReader_proxy& operator=(const DDS_DataReader_proxy&) = delete;
    DDS_DataReader_proxy& operator=(DDS_DataReader_proxy&&) = delete;
  };

  typedef entity_traits< ::DDS::DataReader, DDS_DataReader_proxy, DDS_Native::DDS::DataReader>
    data_reader_trait;
}

#endif /* DDSX11_IMPL_DATA_READER_H_ */
