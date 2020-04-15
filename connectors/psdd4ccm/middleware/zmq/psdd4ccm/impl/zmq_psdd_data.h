// -*- C++ -*-
/**
 * @file    zmq_psdd_data.h
 * @author  Martin Corino
 *
 * @brief   ZMQ Message Data for PSDD base
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef ZMQ_PSDD_DATA_H_
#define ZMQ_PSDD_DATA_H_

#include "psdd4ccm/idl/psdd4ccm_baseC.h"

#include "psdd4ccm/impl/zmq_psdd_stub_export.h"

#include "ace/CDR_Stream.h"

namespace PSDD
{
  namespace ZMQ
  {
    enum class EByteOrder : int32_t
    {
      eBigEndian = ACE_CDR::BYTE_ORDER_BIG_ENDIAN,
      eLittleEndian = ACE_CDR::BYTE_ORDER_LITTLE_ENDIAN
    };

    class ZMQ_PSDD_STUB_Export PSDataOut
      : public ::CCM_PSDD::PSData
    {
    public:
      virtual
      ~PSDataOut () = default;

      virtual void
      set_byte_order (EByteOrder) = 0;

      virtual ACE_OutputCDR&
      key_out () = 0;

      virtual ACE_OutputCDR&
      data_out () = 0;

    protected:
      PSDataOut () = default;
    };

    class ZMQ_PSDD_STUB_Export PSDataIn
      : public ::CCM_PSDD::PSData
    {
    public:
      virtual
      ~PSDataIn () = default;

      virtual void
      set_byte_order (EByteOrder) = 0;

      virtual ACE_InputCDR&
      key_in () = 0;

      virtual ACE_InputCDR&
      data_in () = 0;

    protected:
      PSDataIn () = default;
    };
  }
}

#endif
