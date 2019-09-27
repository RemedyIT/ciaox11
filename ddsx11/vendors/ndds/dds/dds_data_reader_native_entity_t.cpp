// -*- C++ -*-
/**
 * @file    dds_data_reader_native_entity_t.cpp
 * @author  Martin Corino
 *
 * @brief   Vendor specific part of wrapper facade for DDS
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */

namespace DDSX11
{
  template <typename NATIVE_TYPED_READER, typename TYPED_READER_TYPE, typename TOPIC_TYPE, typename SEQ_TYPE, typename NATIVE_SEQ_TYPE>
  DataReader_T <NATIVE_TYPED_READER, TYPED_READER_TYPE, TOPIC_TYPE, SEQ_TYPE, NATIVE_SEQ_TYPE>::DataReader_T (
    DDS_Native::DDS::DataReader * dr) :
      native_entity_(NATIVE_TYPED_READER::narrow (dr))
  {
    DDSX11_LOG_TRACE ("DDSX11::DataReader_T::DataReader_T");
  }
}
