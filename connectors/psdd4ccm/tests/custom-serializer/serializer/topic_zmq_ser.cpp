/**
 * @file    topic_zmq_ser.cpp
 * @author  Martin Corino
 *
 * @brief   Custom serializer for ZMQ Emitter topics.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */

#include "topic_zmq_ser.h"

#include "psdd4ccm/middleware/zmq/psdd4ccm/impl/zmq_psdd_data.h"
#include "psdd4ccm/logger/psdd4ccm_log.h"

#include "ace/Truncate.h"

using namespace CIAOX11;

extern "C" void
create_Custom_Topic_ZMQ_Serializer (
  IDL::traits<CORBA::LocalObject>::ref_type& obj)
{
  obj = CORBA::make_reference<Emitter::Topic::Custom_ZMQ_Serializer> ();
}

namespace Emitter
{
  namespace Topic
  {
    bool
    Custom_ZMQ_Serializer::setup_pack (
        IDL::traits< ::CCM_PSDD::PSData>::ref_type /*data*/)
    {
      // leave endianness to default setting (native byte order)
      // as we only transmit single byte (char) streams
      return true;
    }

    bool
    Custom_ZMQ_Serializer::pack_key (
        IDL::traits< ::CCM_PSDD::PSData>::ref_type data,
        const ::Test::Topic& keyvalue)
    {
      IDL::traits<::PSDD::ZMQ::PSDataOut>::ref_type zmq_data =
          IDL::traits<::PSDD::ZMQ::PSDataOut>::narrow (data);
      if (zmq_data)
      {
        // subscribers need key packing for filtered subscriptions
        // do not use the streaming operator (<<) since we only want
        // character data in the stream no integer for the string size
        zmq_data->key_out ().write_char_array (
            keyvalue.key ().c_str (),
            ACE_Utils::truncate_cast<ACE_CDR::ULong> (keyvalue.key ().size ()));
        return true;
      }
      return false;
    }

    bool
    Custom_ZMQ_Serializer::pack_data (
        IDL::traits< ::CCM_PSDD::PSData>::ref_type,
        const ::Test::Topic&)
    {
      // this custom serializer is for subscribers only
      // end so should never have to pack data
      return false;
    }

    void
    Custom_ZMQ_Serializer::finalize_pack (
        IDL::traits< ::CCM_PSDD::PSData>::ref_type /*data*/)
    {
      // noop
    }

    bool
    Custom_ZMQ_Serializer::setup_unpack (
        IDL::traits< ::CCM_PSDD::PSData>::ref_type /*data*/)
    {
      // leave endianness to default setting (native byte order)
      // as we only transmit single byte (char) streams
      return true;
    }

    bool
    Custom_ZMQ_Serializer::unpack_key (
        IDL::traits< ::CCM_PSDD::PSData>::ref_type /*data*/,
        ::Test::Topic& /*keyvalue*/)
    {
      // we use single frame serialization/transmission
      // so key and data streams are identical
      // we'll handle full unpacking in #unpack_data
      return true;
    }

    bool
    Custom_ZMQ_Serializer::unpack_data (
        IDL::traits< ::CCM_PSDD::PSData>::ref_type data,
        ::Test::Topic& datum)
    {
      PSDD4CCM_LOG_TRACE ("Custom_ZMQ_Serializer::unpack_data");
      IDL::traits< ::PSDD::ZMQ::PSDataIn>::ref_type zmq_data =
          IDL::traits< ::PSDD::ZMQ::PSDataIn>::narrow (data);
      if (zmq_data)
      {
        PSDD4CCM_LOG_DEBUG ("Custom_ZMQ_Serializer::unpack_data" <<
                            " - ");
        std::string msg;
        msg.append (zmq_data->data_in ().rd_ptr (), zmq_data->data_in ().length ());
        PSDD4CCM_LOG_DEBUG ("Custom_ZMQ_Serializer::unpack_data" <<
                            " - msg=" << msg);
        std::string::size_type pos, off;
        if ((pos = msg.find (':')) != std::string::npos)
        {
          datum.key (msg.substr(0, pos));
          off = pos+1;
          if ((pos = msg.find (':', off)) != std::string::npos)
          {
            datum.device (std::stoul (msg.substr (off, pos)));
            off = pos+1;
            if ((pos = msg.find (':', off)) != std::string::npos)
            {
              datum.msgid (std::stoul (msg.substr (off, pos)));
              off = pos+1;
              if ((msg[off] == 'T' || msg[off] == 'F') && msg[off+1] == ':')
              {
                datum.status (msg[off] == 'T');
                off = off+2;
                datum.value (std::stod (msg.substr(off)));
                return true;
              }
            }
          }
        }
      }

      return false;
    }

    void
    Custom_ZMQ_Serializer::finalize_unpack (
        IDL::traits< ::CCM_PSDD::PSData>::ref_type /*data*/)
    {
      // noop
    }
  }
}
