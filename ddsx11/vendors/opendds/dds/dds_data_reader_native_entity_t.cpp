// -*- C++ -*-
/**
 * @file    dds_data_reader_native_entity_t.cpp
 * @author  Martin Corino
 *
 * @brief   Vendor specific part of wrapper facade for DDS
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

namespace DDSX11
{
  template <typename NATIVE_TYPED_READER, typename TYPED_READER_TYPE, typename TOPIC_TYPE, typename SEQ_TYPE, typename NATIVE_SEQ_TYPE>
  DataReader_T <NATIVE_TYPED_READER, TYPED_READER_TYPE, TOPIC_TYPE, SEQ_TYPE, NATIVE_SEQ_TYPE>::DataReader_T (
    DDS_Native::DDS::DataReader * dr) :
      native_entity_(NATIVE_TYPED_READER::_narrow (dr))
  {
    DDSX11_LOG_TRACE ("DataReader_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::DataReader_T");
  }

  template <typename NATIVE_TYPED_READER, typename TYPED_READER_TYPE, typename TOPIC_TYPE, typename SEQ_TYPE, typename NATIVE_SEQ_TYPE>
  DataReader_T <NATIVE_TYPED_READER, TYPED_READER_TYPE, TOPIC_TYPE, SEQ_TYPE, NATIVE_SEQ_TYPE>::~DataReader_T ()
  {
    DDSX11_LOG_TRACE ("DataReader_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::~DataReader_T");
    if (native_entity_)
    {
      native_entity_->_remove_ref ();
    }
  }

  template <typename NATIVE_TYPED_READER, typename TYPED_READER_TYPE, typename TOPIC_TYPE, typename SEQ_TYPE, typename NATIVE_SEQ_TYPE>
  void
  DataReader_T <NATIVE_TYPED_READER, TYPED_READER_TYPE, TOPIC_TYPE, SEQ_TYPE, NATIVE_SEQ_TYPE>::clear_native_entity ()
  {
    DDSX11_LOG_TRACE ("DataReader_T<" << ::DDS::traits<TOPIC_TYPE>::get_type_name() << ">::clear_native_entity");
    if (native_entity_)
    {
      native_entity_->_remove_ref ();
      native_entity_ = nullptr;
    }
  }
}
