// -*- C++ -*-
/**
 * @file    zmq_psdd_data_i.cpp
 * @author  Martin Corino
 *
 * @brief   ZMQ Message data for PSDD implementation
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#include "psdd4ccm/logger/psdd4ccm_log.h"

#include <stdexcept>
#include "zmq_psdd_data_i.h"

#include "ace/Malloc_Allocator.h"

namespace PSDD
{
 namespace ZMQ
 {
   /**
    * Custom key allocator for ZMQ keyframe CDR streams.
    * As ZMQ performs binary matching on subscription keys
    * we need zero-ed memory allocated for the CDR buffers
    * to keep keyframe data consistent.
    */
   class KeyAllocator : public ACE_New_Allocator
   {
   public:
     virtual void *malloc (size_t nbytes)
     {
       return this->calloc (nbytes);
     }
   };

   // static singleton allocator instance
   static KeyAllocator key_allocator__;

   static
   void
   free_msg_data (void* /*data*/, void* hint)
   {
     std::unique_ptr<ACE_OutputCDR> safe_ptr;
     safe_ptr.reset (static_cast<ACE_OutputCDR*> (hint));
   }

   PSDataOut_Impl::PSDataOut_Impl (bool msg_envelope)
    : use_msg_envelope_ (msg_envelope)
   {}

   ACE_OutputCDR&
   PSDataOut_Impl::key_out ()
   {
     return *this->key_os_;
   }

   ACE_OutputCDR&
   PSDataOut_Impl::data_out ()
   {
     return *(this->use_msg_envelope_ ? this->data_os_ : this->key_os_);
   }

   void
   PSDataOut_Impl::start_message ()
   {
     try
     {
       this->key_os_ = std::make_unique<ACE_OutputCDR> (
               (size_t)0,
               ACE_CDR_BYTE_ORDER,
               &key_allocator__);
       if (this->use_msg_envelope_)
       {
         this->data_os_ = std::make_unique<ACE_OutputCDR> (
                 (size_t)0);
       }
     }
     catch (const std::bad_alloc&)
     {
       throw ::CCM_PSDD::InternalError (
           "PSDataOut_Impl::start_message",
           "NO_MEMORY");
     }
   }

   void
   PSDataOut_Impl::set_byte_order (EByteOrder bo)
   {
     if (ACE_CDR_BYTE_ORDER != static_cast<int> (bo))
     {
       this->key_os_->reset_byte_order (static_cast<int> (bo));
       this->data_os_->reset_byte_order (static_cast<int> (bo));
     }
   }

   void
   PSDataOut_Impl::finish_message (zmq_msg_t* keyframe, SafeMsg& skeyframe,
                                   zmq_msg_t* dataframe, SafeMsg& sdataframe)
   {
     PSDD4CCM_LOG_DEBUG (
       "PSDataOut_Impl::finish_message" <<
       " - storing keyframe data");
     this->consolidate_message_frame (*this->key_os_);
     this->finish_message_frame (
         this->key_os_.get (), keyframe);
     // safeguard initialized message
     skeyframe.reset (keyframe);
     // release resources
     this->key_os_.release (); // ZMQ will free later

     if (this->use_msg_envelope_)
     {
       this->consolidate_message_frame (*this->data_os_);

       PSDD4CCM_LOG_DEBUG (
         "PSDataOut_Impl::finish_message" <<
         " - data length=" << this->data_os_->length ());

       // only initialize dataframe if there is actually something serialized
       if (this->data_os_->length () > 0)
       {
         PSDD4CCM_LOG_DEBUG (
           "PSDataOut_Impl::finish_message" <<
           " - storing dataframe data");
         this->finish_message_frame (
             this->data_os_.get (), dataframe);
         // safeguard initialized message
         sdataframe.reset (dataframe);
         // release resources
         this->data_os_.release (); // ZMQ will free later
       }
     }
   }

   void
   PSDataOut_Impl::consolidate_message_frame (
       ACE_OutputCDR& os)
   {
     if (os.consolidate () != 0)
     {
       PSDD4CCM_LOG_PANIC (
         "PSDataOut_Impl::consolidate_message_frame" <<
         " - failed to consolidate output stream");

       throw ::CCM_PSDD::InternalError (
           "PSDataOut_Impl::consolidate_message_frame",
           "NO_MEMORY");
     }
   }

   void
   PSDataOut_Impl::finish_message_frame (
       ACE_OutputCDR* os,
       zmq_msg_t* msgframe)
   {
     const ACE_Message_Block *os_mb =
             os->begin ();
     void* data = const_cast<char*> (os_mb->rd_ptr ());
     size_t datalen = os_mb->length ();

     PSDD4CCM_LOG_DEBUG (
       "PSDataOut_Impl::finish_message_frame" <<
       " - data=" << data << " datalen=" << datalen);
     PSDD4CCM_LOG_DEBUG (
       "PSDataOut_Impl::finish_message_frame" <<
       " | "  <<
       x11_logger::hexdump ((char*)data, (uint32_t)datalen));

     if (::zmq_msg_init_data (msgframe,
                              data,
                              datalen,
                              free_msg_data,
                              os) != 0)
     {
       PSDD4CCM_LOG_PANIC (
         "PSDataOut_Impl::finish_message_frame" <<
         " - failed to initialize ZMQ message [" <<
         ::zmq_strerror (::zmq_errno ()) << "]");

       throw ::CCM_PSDD::InternalError (
           "PSDataOut_Impl::finish_message_frame",
           "NO_MEMORY");
     }
   }

   PSDataIn_Impl::PSDataIn_Impl (bool msg_envelope)
    : use_msg_envelope_ (msg_envelope)
   {
   }

   PSDataIn_Impl::~PSDataIn_Impl ()
   {
   }

   ACE_InputCDR&
   PSDataIn_Impl::key_in ()
   {
     return *this->is_key_;
   }

   ACE_InputCDR&
   PSDataIn_Impl::data_in ()
   {
     return *(this->use_msg_envelope_ ? this->is_data_ : this->is_key_);
   }

   void
   PSDataIn_Impl::start_message (zmq_msg_t* key, zmq_msg_t* data)
   {
     PSDD4CCM_LOG_DEBUG (
       "PSDataIn_Impl::start_message" <<
       " - reading keyframe data | "  <<
       x11_logger::hexdump (
           static_cast<char*> (::zmq_msg_data (key)),
           (uint32_t)::zmq_msg_size (key)));
     // initialize data streams
     size_t framelen = ::zmq_msg_size (key);
     try
     {
       // Create message block for the msg frame.  Ensure that it is
       // aligned.
       ACE_Message_Block mb (ACE_CDR::MAX_ALIGNMENT + framelen);
       ACE_CDR::mb_align (&mb);

       // copy the message frame
       mb.copy (static_cast<char*> (::zmq_msg_data (key)),
                framelen);

       // create CDR input stream from message block
       this->is_key_ =
           std::make_unique<ACE_InputCDR> (
               &mb);
     }
     catch (const std::bad_alloc&)
     {
       throw ::CCM_PSDD::InternalError (
           "PSDataIn_Impl::start_message",
           "NO_MEMORY");
     }

     PSDD4CCM_LOG_DEBUG (
       "PSDataIn_Impl::start_message" <<
       " - data read | " <<
       x11_logger::hexdump (
           static_cast<char*> (this->is_key_->rd_ptr()),
           (uint32_t)this->is_key_->length ()));

     if (this->use_msg_envelope_ && data)
     {
       PSDD4CCM_LOG_DEBUG (
         "PSDataIn_Impl::start_message" <<
         "- reading dataframe data | "  <<
         x11_logger::hexdump (
             static_cast<char*> (::zmq_msg_data (data)),
             (uint32_t)::zmq_msg_size (data)));
       size_t framelen = ::zmq_msg_size (data);
       try
       {
         // Create message block for the msg frame.  Ensure that it is
         // aligned.
         ACE_Message_Block mb (ACE_CDR::MAX_ALIGNMENT + framelen);
         ACE_CDR::mb_align (&mb);

         // copy the message frame
         mb.copy (static_cast<char*> (::zmq_msg_data (data)),
                  framelen);

         // create CDR input stream from message block
         this->is_data_ =
             std::make_unique<ACE_InputCDR> (
                 &mb);
       }
       catch (const std::bad_alloc&)
       {
         throw ::CCM_PSDD::InternalError (
             "PSDataIn_Impl::start_message",
             "NO_MEMORY");
       }

       PSDD4CCM_LOG_DEBUG (
         "PSDataIn_Impl::start_message" <<
         " - data read | " <<
         x11_logger::hexdump (
             static_cast<char*> (this->is_data_->rd_ptr ()),
             (uint32_t)this->is_data_->length ()));
     }
   }

   void
   PSDataIn_Impl::set_byte_order (EByteOrder bo)
   {
     if (ACE_CDR_BYTE_ORDER != static_cast<int> (bo))
     {
       this->is_key_->reset_byte_order (static_cast<int> (bo));
       this->is_data_->reset_byte_order (static_cast<int> (bo));
     }
   }
 }
}
