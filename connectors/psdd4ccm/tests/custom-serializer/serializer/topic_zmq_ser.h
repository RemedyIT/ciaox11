/**
 * @file    topic_zmq_ser.h
 * @author  Martin Corino
 *
 * @brief   Custom serializer for ZMQ Emitter topics.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef _TOPIC_ZMQ_SER_H_
#define _TOPIC_ZMQ_SER_H_

#include "topicPSEC.h"
#include "serializer_export.h"

namespace Emitter
{
  namespace Topic
  {
    class SERIALIZER_Export Custom_ZMQ_Serializer
      : public ::Test::TopicInterface::CCM_Serializer
    {
    public:
      Custom_ZMQ_Serializer () = default;
      ~Custom_ZMQ_Serializer () override = default;

      /// @copydoc topicPS.idl::LoRa::Topic::Serializer::setup_pack
      bool
      setup_pack (
          IDL::traits<::CCM_PSDD::PSData>::ref_type data) override;

      /// @copydoc topicPS.idl::LoRa::Topic::Serializer::pack_key
      bool
      pack_key (
          IDL::traits<::CCM_PSDD::PSData>::ref_type data,
          const ::Test::Topic& keyvalue) override;

      /// @copydoc topicPS.idl::LoRa::Topic::Serializer::pack_data
      bool
      pack_data (
          IDL::traits<::CCM_PSDD::PSData>::ref_type data,
          const ::Test::Topic& datum) override;

      /// @copydoc topicPS.idl::LoRa::Topic::Serializer::finalize_pack
      void
      finalize_pack (
          IDL::traits<::CCM_PSDD::PSData>::ref_type data) override;

      /// @copydoc topicPS.idl::LoRa::Topic::Serializer::setup_unpack
      bool
      setup_unpack (
          IDL::traits<::CCM_PSDD::PSData>::ref_type data) override;

      /// @copydoc topicPS.idl::LoRa::Topic::Serializer::unpack_key
      bool
      unpack_key (
          IDL::traits<::CCM_PSDD::PSData>::ref_type data,
          ::Test::Topic& keyvalue) override;

      /// @copydoc topicPS.idl::LoRa::Topic::Serializer::unpack_data
      bool
      unpack_data (
          IDL::traits<::CCM_PSDD::PSData>::ref_type data,
          ::Test::Topic& datum) override;

      /// @copydoc topicPS.idl::LoRa::Topic::Serializer::finalize_unpack
      void
      finalize_unpack (
          IDL::traits<::CCM_PSDD::PSData>::ref_type data) override;
    };
  }
}

extern "C" SERIALIZER_Export  void
create_Custom_Topic_ZMQ_Serializer (
  IDL::traits<CORBA::LocalObject>::ref_type&);

#endif
