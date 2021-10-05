// -*- C++ -*-
/**
 * @file    dds_typefactory_t.h
 * @author  Johnny Willemsen
 *
 * @brief   Templated type factory for creating datareaders/datawriter
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDSX11_IMPL_TYPEFACTORY_T_H_
#define DDSX11_IMPL_TYPEFACTORY_T_H_

#include "dds/dds_data_writer_t.h"
#include "dds/dds_data_reader_t.h"

namespace DDSX11
{
  template <typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE, typename NATIVE_SEQ_TYPE, typename NATIVE_DATAREADER_TYPE, typename NATIVE_DATAWRITER_TYPE>
  class DDS_TypeFactory_T final
    : public DDS_TypeFactory_i
  {
  public:
    IDL::traits< ::DDS::DataWriter>::ref_type
    create_datawriter (DDS_Native::DDS::DataWriter *dw) override
    {
      using DataWriter_type = DDSX11::DataWriter_T<
          TOPIC_TYPE,
          NATIVE_DATAWRITER_TYPE,
          typename ::DDS::traits<TOPIC_TYPE>::datawriter_type>;
      auto proxy = TAOX11_CORBA::make_reference<DataWriter_type>(dw);
      return proxy;
    }

    IDL::traits< ::DDS::DataReader>::ref_type
    create_datareader (DDS_Native::DDS::DataReader *dr) override
    {
      using DataReader_type = DDSX11::DataReader_T<
          NATIVE_DATAREADER_TYPE,
          typename ::DDS::traits<TOPIC_TYPE>::datareader_type,
          TOPIC_TYPE,
          TOPIC_SEQ_TYPE,
          NATIVE_SEQ_TYPE>;
      auto proxy = TAOX11_CORBA::make_reference<DataReader_type> (dr);
      return proxy;
    }
  };
}

#endif /* DDSX11_IMPL_TYPEFACTORY_T_H_ */
