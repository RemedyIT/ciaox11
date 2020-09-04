/**
 * @file   log_backend.cpp
 * @author Johnny Willemsen
 *
 * @brief  A logging backend which puts ACE logging messages onto DDS
 *
 * Only use DDSX11 logging in this backend, that logging can't be enabled already
 * because this logger will call DDSX11, enabling DDSX11 logging will lead to
 * recursive logging calls.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#include "log_backend.h"
#include "ace/Env_Value_T.h"
#include "ace/Log_Msg.h"
#include "ace/Log_Record.h"
#include "ace/Get_Opt.h"
#include <iostream>
#include "logger/ddsx11_log.h"

namespace DAnCE
{
  ddsx11_log_backend::~ddsx11_log_backend (void)
  {
    DDSX11_LOG_TRACE ("ddsx11_log_backend::~ddsx11_log_backend");

    // Fallback close, should normally already be done by fini()
    (void) this->close ();
  }

  int
  ddsx11_log_backend::init (int argc, ACE_TCHAR **argv)
  {
    DDSX11_LOG_TRACE ("ddsx11_log_backend::init");

    ACE_Get_Opt opts (argc, argv, ACE_TEXT ("t:d:q:n:"), 0, 0, ACE_Get_Opt::RETURN_IN_ORDER);
    opts.long_option (ACE_TEXT ("topic"), 't', ACE_Get_Opt::ARG_REQUIRED);
    opts.long_option (ACE_TEXT ("domain"), 'd', ACE_Get_Opt::ARG_REQUIRED);
    opts.long_option (ACE_TEXT ("qosprofile"), 'q', ACE_Get_Opt::ARG_REQUIRED);
    opts.long_option (ACE_TEXT ("node-name"), 'n', ACE_Get_Opt::ARG_REQUIRED);

    int c {};

    while ((c = opts ()) != -1)
      {
        switch (c)
          {
          case 't':
            this->topic_name_ = opts.opt_arg ();
            break;

          case 'd':
            this->domain_ = std::atoi (opts.opt_arg ());
            break;

          case 'q':
            this->qos_profile_ = opts.opt_arg ();
            break;

          case 'n':
            this->node_ = opts.opt_arg ();
            break;

          default:
            DDSX11_IMPL_LOG_ERROR("Unknown option for ddsx11_log_backend" << opts.last_option ());
          }
      }

    return this->open (ACE_TEXT (""));
  }

  int
  ddsx11_log_backend::fini (void)
  {
    DDSX11_LOG_TRACE ("ddsx11_log_backend::fini");

    // We are instructed to shutdown, first step is to put the old logger
    // backend back so that we don't get log messages from our own
    // shutdown
    ACE_Log_Msg::msg_backend (old_log_msg_backend_);

    this->close ();

    return 0;
  }

  int
  ddsx11_log_backend::info (ACE_TCHAR **, size_t) const
  {
    DDSX11_LOG_TRACE ("ddsx11_log_backend::info");

    return 0;
  }

  void
  ddsx11_log_backend::get_configuration ()
  {
    DDSX11_LOG_TRACE ("ddsx11_log_backend::get_configuration");

    const char* env_domain = std::getenv ("DNCX11_DDS_LOG_DOMAIN");
    if (env_domain)
      {
        this->domain_ = std::atoi (env_domain);
        DDSX11_IMPL_LOG_DEBUG ("ddsx11_log_backend::get_configuration - domain set to " << this->domain_);
      }

    const char* env_topic = std::getenv ("DNCX11_DDS_LOG_TOPIC");
    if (env_topic)
      {
        this->topic_name_ = env_topic;
        DDSX11_IMPL_LOG_DEBUG ("ddsx11_log_backend::get_configuration - topic set to " << this->topic_name_);
      }

    const char* env_node = std::getenv ("DNCX11_DDS_NODE_NAME");
    if (env_topic)
      {
        this->node_ = env_node;
        DDSX11_IMPL_LOG_DEBUG ("ddsx11_log_backend::get_configuration - node name set to " << this->node_);
      }

    const char* env_qos_profile = std::getenv ("DNCX11_DDS_QOS_PROFILE");
    if (env_topic)
      {
        this->qos_profile_ = env_qos_profile;
        DDSX11_IMPL_LOG_DEBUG ("ddsx11_log_backend::get_configuration - QoS profile set to " << this->qos_profile_);
      }
  }

  bool
  ddsx11_log_backend::configure_dds (void)
  {
    DDSX11_LOG_TRACE ("ddsx11_log_backend::configure_dds");

    DDS::traits<DnCX11::Log_Record>::domainparticipantfactory_ref_type dpf =
      DDS::traits<DDS::DomainParticipantFactory>::get_instance ();

    // Check if we have a qos_profile passed, if so, let us use that
    if (this->qos_profile_.empty ())
      {
        this->participant_ =
          dpf->create_participant (
            this->domain_,
            DDS::PARTICIPANT_QOS_DEFAULT,
            nullptr,
            0);
      }
    else
      {
        this->participant_ =
          dpf->create_participant_with_profile (
            this->domain_,
            this->qos_profile_,
            nullptr,
            0);
      }

    if (!this->participant_)
      {
        DDSX11_IMPL_LOG_ERROR ("ddsx11_log_backend::open - Failed to create participant");
        return false;
      }

    DDS::ReturnCode_t retval =
      DDS::traits<DnCX11::Log_Record>::register_type (
        this->participant_,
        DDS::traits<DnCX11::Log_Record>::get_type_name ());

    if (retval != DDS::RETCODE_OK)
      {
        DDSX11_IMPL_LOG_ERROR ("ddsx11_log_backend::open - Failed to register type");
        (void) this->close ();
        return false;
      }

    DDS::TopicQos tqos;
    retval = participant_->get_default_topic_qos (tqos);
    if (retval != DDS::RETCODE_OK)
      {
        DDSX11_IMPL_LOG_ERROR ("ddsx11_log_backend::open - Failed to retrieve default topic QoS");
        (void) this->close ();
        return false;
      }

    this->topic_ =
      this->participant_->create_topic (
        this->topic_name_,
        DDS::traits<DnCX11::Log_Record>::get_type_name (),
        tqos,
        nullptr,
        0);

    if (!this->topic_)
      {
        DDSX11_IMPL_LOG_ERROR ("ddsx11_log_backend::open - Failed to create topic");
        this->close ();
        return false;
      }

    DDS::PublisherQos pubqos;
    retval = participant_->get_default_publisher_qos (pubqos);
    if (retval != DDS::RETCODE_OK)
      {
        DDSX11_IMPL_LOG_ERROR ("ddsx11_log_backend::open - Failed to retrieve default publisher QoS");
        (void) this->close ();
        return false;
      }

    this->publisher_ =
      this->participant_->create_publisher (
        pubqos,
        nullptr,
        0);

    if (!this->publisher_)
      {
        DDSX11_IMPL_LOG_ERROR ("ddsx11_log_backend::open - Failed to create publisher");
        this->close ();
        return false;
      }

    DDS::DataWriterQos writerqos;
    retval = publisher_->get_default_datawriter_qos (writerqos);
    if (retval != DDS::RETCODE_OK)
      {
        DDSX11_IMPL_LOG_ERROR ("ddsx11_log_backend::open - Failed to retrieve default datawriter QoS");
        (void) this->close ();
        return false;
      }

    this->datawriter_ =
      this->publisher_->create_datawriter (
        this->topic_,
        writerqos,
        nullptr,
        0);

    if (!this->datawriter_)
      {
        DDSX11_IMPL_LOG_ERROR ("ddsx11_log_backend::open - Failed to create the datawriter");
        this->close ();
        return false;
      }

    this->log_record_writer_ =
      DDS::traits<DnCX11::Log_Record>::narrow (this->datawriter_);

    if (!this->log_record_writer_)
      {
        DDSX11_IMPL_LOG_ERROR ("ddsx11_log_backend::open - Failed to narrow the typed datawriter");
        this->close ();
        return false;
      }

    return true;
  }

  int
  ddsx11_log_backend::open (const ACE_TCHAR *)
  {
    DDSX11_LOG_TRACE ("ddsx11_log_backend::open");

    // Check our environment
    this->get_configuration ();

    if (!this->configure_dds ())
      {
        DDSX11_IMPL_LOG_ERROR ("ddsx11_log_backend::open - unable to create DDS entities");
        return -1;
      }

    // Install ourselves as ACE Logging backend
    old_log_msg_backend_ = ACE_Log_Msg::msg_backend (this);

    return 0;
  }

  int
  ddsx11_log_backend::reset (void)
  {
    DDSX11_LOG_TRACE ("ddsx11_log_backend::reset");

    return this->close ();
  }

  int
  ddsx11_log_backend::close (void)
  {
    DDSX11_LOG_TRACE ("ddsx11_log_backend::close");

    if (datawriter_)
      {
        DDS::ReturnCode_t const retval =
          publisher_->delete_datawriter (datawriter_);

        if (retval != DDS::RETCODE_OK)
          {
            DDSX11_IMPL_LOG_ERROR ("log_server - Unable to delete datawriter <"
              << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retval)
              << ">.");
          }
        datawriter_ = nullptr;
        log_record_writer_ = nullptr;
      }

    if (publisher_)
      {
        DDS::ReturnCode_t const retval =
          participant_->delete_publisher (publisher_);

        if (retval != DDS::RETCODE_OK)
          {
            DDSX11_IMPL_LOG_ERROR ("log_server - Unable to delete publisher <"
              << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retval)
              << ">.");
          }
        publisher_ = nullptr;
      }

    if (topic_)
      {
        DDS::ReturnCode_t const retval =
          participant_->delete_topic (topic_);

        if (retval != DDS::RETCODE_OK)
          {
            DDSX11_IMPL_LOG_ERROR ("log_server - Unable to delete topic <"
              << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retval)
              << ">.");
          }
        topic_ = nullptr;
      }

    if (this->participant_)
      {
        DDS::traits<DnCX11::Log_Record>::domainparticipantfactory_ref_type dpf =
          DDS::traits<DDS::DomainParticipantFactory>::get_instance ();

        DDS::ReturnCode_t retval =
          dpf->delete_participant (this->participant_);

        if (retval != DDS::RETCODE_OK)
          {
            DDSX11_IMPL_LOG_ERROR ("ddsx11_log_backend::close - Unable to delete participant <"
              << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retval)
              << ">.");
          }

        this->participant_ = nullptr;

        retval = dpf->finalize_instance ();

        if (retval != DDS::RETCODE_OK)
          {
            DDSX11_IMPL_LOG_ERROR ("ddsx11_log_backend::close - Unable to finalize participant factory <"
              << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retval)
              << ">.");
          }
      }

    return 0;
  }

  ssize_t
  ddsx11_log_backend::log (ACE_Log_Record  &log_record)
  {
    // Construct a Log_Record to publish on DDS only when it isn't a DDSX11 log message (which would
    // trigger recursive logging
    std::string message = ACE_TEXT_ALWAYS_CHAR (log_record.msg_data ());
    if (message.find("DDSX11") ==  std::string::npos)
      {
        DnCX11::Log_Record instance { this->node_, log_record.pid(), 0, std::move(message) };

        DDS::ReturnCode_t const retval =
          this->log_record_writer_->write (instance, DDS::HANDLE_NIL);

        if (retval != DDS::RETCODE_OK)
          {
            DDSX11_IMPL_LOG_ERROR ("Unable to write log record to DDS");
            return 0;
          }
      }

    return log_record.msg_data_len ();
  }

  ACE_FACTORY_DEFINE (DNCX11_LOG_BACKEND, ddsx11_log_backend);
}

