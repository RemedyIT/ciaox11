// -*- C++ -*-
/**
 * @file    dds_data_writer_native_entity_t.cpp
 * @author  Johnny Willemsen
 *
 * @brief   Vendor specific part of wrapper facade for DDS
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

namespace DDSX11
{
  template <typename TOPIC_TYPE, typename NATIVE_TYPED_WRITER, typename TYPED_WRITER_TYPE>
  DataWriter_T<TOPIC_TYPE, NATIVE_TYPED_WRITER, TYPED_WRITER_TYPE>::DataWriter_T (
    DDS_Native::DDS::DataWriter * dw) :
      native_entity_(NATIVE_TYPED_WRITER::narrow (dw))
  {
    DDSX11_LOG_TRACE ("DDSX11::DataWriter_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::DataWriter_T");
  }

  template <typename TOPIC_TYPE, typename NATIVE_TYPED_WRITER, typename TYPED_WRITER_TYPE>
  DataWriter_T<TOPIC_TYPE, NATIVE_TYPED_WRITER, TYPED_WRITER_TYPE>::~DataWriter_T ()
  {
    DDSX11_LOG_TRACE ("DDSX11::DataWriter_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::~DataWriter_T");
  }
}

