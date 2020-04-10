// -*- C++ -*-
/**
 * @file    zmq_psdd_data_i.h
 * @author  Martin Corino
 *
 * @brief   ZMQ Message data for PSDD implementation
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef ZMQ_PSDD_DATA_I_H_
#define ZMQ_PSDD_DATA_I_H_

#include "psdd4ccm/impl/zmq_psdd_data.h"
#include "psdd4ccm/impl/zmq_safe_msg.h"
#include "psdd4ccm/impl/zmq_psdd_stub_export.h"

#include "ace/Message_Block.h"

#include <zmq.h>

#include <memory>
#include <vector>

namespace PSDD
{
 namespace ZMQ
 {
   class ZMQ_PSDD_STUB_Export PSDataOut_Impl
     : public PSDataOut
   {
   public:
     PSDataOut_Impl (bool msg_envelope);
     virtual ~PSDataOut_Impl () = default;

     void set_byte_order (EByteOrder) override;

     ACE_OutputCDR& key_out () override;

     ACE_OutputCDR& data_out () override;

     void start_message ();

     void finish_message (zmq_msg_t* keyframe, SafeMsg& skeyframe,
                          zmq_msg_t* dataframe, SafeMsg& sdataframe);

   private:
     void consolidate_message_frame (
         ACE_OutputCDR& os);
     void finish_message_frame (
         ACE_OutputCDR* os,
         zmq_msg_t* msgframe);

     bool use_msg_envelope_;
     std::unique_ptr<ACE_OutputCDR> key_os_ {};
     std::unique_ptr<ACE_OutputCDR> data_os_ {};
   };

   class ZMQ_PSDD_STUB_Export PSDataIn_Impl
     : public PSDataIn
   {
   public:
     PSDataIn_Impl (bool msg_envelope);
     virtual ~PSDataIn_Impl ();

     void set_byte_order (EByteOrder) override;

     ACE_InputCDR& key_in () override;

     ACE_InputCDR& data_in () override;

     void start_message (zmq_msg_t* key, zmq_msg_t* data = nullptr);

   private:
     bool use_msg_envelope_;
     std::unique_ptr<ACE_InputCDR> is_key_ {};
     std::unique_ptr<ACE_InputCDR> is_data_ {};
   };
 }
}

#endif
