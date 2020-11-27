/**
 * @file   receiver.cpp
 * @author Marcel Smit <msmit@remedy.nl>
 *
 * @brief  Shapes Subscriber example using the IDL to C++11
 *         language mapping
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#include "shapetype_dds_typesupport.h"
#include <thread>
#include "tests/testlib/ddsx11_testlog.h"

int16_t received_ {};
static std::string const qos_profile { "shapes#ShapesProfile" };

class ShapeTypeListener final :
  public DDS::traits<ShapeType>::datareaderlistener_type
{
public:
  void
  on_requested_deadline_missed (
    DDS::traits<ShapeType>::datareader_ref_type the_reader,
    const DDS::RequestedDeadlineMissedStatus& status) override;

  void
  on_requested_incompatible_qos (
    DDS::traits<ShapeType>::datareader_ref_type the_reader,
    const DDS::RequestedIncompatibleQosStatus& status) override;

  void
  on_sample_rejected (
    DDS::traits<ShapeType>::datareader_ref_type the_reader,
    const DDS::SampleRejectedStatus& status) override;

  void
  on_liveliness_changed (
    DDS::traits<ShapeType>::datareader_ref_type the_reader,
    const DDS::LivelinessChangedStatus& status) override;

  void
  on_subscription_matched (
      DDS::traits<ShapeType>::datareader_ref_type the_reader,
      const DDS::SubscriptionMatchedStatus& status) override;

  void
  on_sample_lost (
      DDS::traits<ShapeType>::datareader_ref_type the_reader,
      const DDS::SampleLostStatus& status) override;

  void
  on_data_available (
    DDS::traits<ShapeType>::datareader_ref_type the_reader) override;
};

int main (int argc, char *argv[])
{
  DDS::ReturnCode_t retcode { DDS::RETCODE_OK };

  try
    {
      const char * domain = std::getenv ("DDS4CCM_DEFAULT_DOMAIN_ID");
      ::DDS::DomainId_t domain_id_ {};
      if (domain)
      {
        domain_id_ = std::atoi (domain);
      }

      DDS::traits<ShapeType>::domainparticipantfactory_ref_type dpf =
        DDS::traits<DDS::DomainParticipantFactory >::get_instance ();
      DDS::traits<ShapeType>::domainparticipant_ref_type domain_participant =
        dpf->create_participant_with_profile (
          domain_id_, qos_profile, nullptr, DDS::STATUS_MASK_NONE);

      retcode = DDS::traits<ShapeType>::register_type (domain_participant, "ShapeType");
      if (retcode != DDS::RETCODE_OK)
      {
        DDSX11_TEST_ERROR << "receiver: Failed to register type: "
                          << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
                          << std::endl;
        return 1;
      }

      DDS::traits<ShapeType>::topic_ref_type topic = domain_participant->create_topic_with_profile (
        "Square", DDS::traits<ShapeType>::get_type_name (), qos_profile, nullptr, DDS::STATUS_MASK_NONE);

      DDS::traits<ShapeType>::subscriber_ref_type subscriber =
        domain_participant->create_subscriber (DDS::SUBSCRIBER_QOS_DEFAULT, nullptr, DDS::STATUS_MASK_NONE);

      if (topic && subscriber)
      {
        CORBA::object_traits<DDS::DataReader>::ref_type dr {};
        DDS::traits<ShapeType>::datareaderlistener_ref_type listener =
          DDS::make_reference<ShapeTypeListener>();
        if (listener)
        {
          dr = subscriber->create_datareader_with_profile (topic, qos_profile, listener, DDS::DATA_AVAILABLE_STATUS);

          if (!dr)
          {
            DDSX11_TEST_ERROR << "receiver: Error in creating datareader!" << std::endl;
          }
        }
        else
        {
          DDSX11_TEST_ERROR << "receiver: No listener created!" << std::endl;
        }

        std::string sleep_time { "10" };
        if (argc > 1)
        {
          sleep_time = argv[1];
        }
        DDSX11_TEST_DEBUG << "Waiting " << sleep_time << " seconds in order to receive "
          << "all samples." << std::endl;
        std::this_thread::sleep_for (std::chrono::seconds (std::stoi (sleep_time)));
        DDSX11_TEST_DEBUG << "Received " << received_ << ". Closing..." << std::endl;
        if (received_ == 0)
          DDSX11_TEST_ERROR << "ERROR: No samples received." << std::endl;

        if (dr)
        {
          retcode = subscriber->delete_datareader (dr);
          dr = nullptr;
          if (retcode != DDS::RETCODE_OK)
          {
            DDSX11_TEST_ERROR << "receiver: Failed to delete datareader from subscriber."
                              << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
                              << std::endl;
            return 1;
          }
        }
        retcode = domain_participant->delete_subscriber (subscriber);
        subscriber = nullptr;
        if (retcode != DDS::RETCODE_OK)
        {
          DDSX11_TEST_ERROR << "receiver: Failed to delete subscriber from domain participant." << std::endl
                            << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
                            << std::endl;
          return 1;
        }
        retcode = domain_participant->delete_topic (topic);
        topic = nullptr;
        if (retcode != DDS::RETCODE_OK)
        {
          DDSX11_TEST_ERROR << "receiver: Failed to delete topic from domain participant"
                            << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
                            << std::endl;
          return 1;
        }
      }
      else
      {
        DDSX11_TEST_ERROR << "receiver: Either Topic or Subscriber is null." << std::endl;
        retcode = DDS::RETCODE_ERROR;
      }

      retcode = dpf->delete_participant(domain_participant);
      domain_participant = nullptr;
      if (retcode != DDS::RETCODE_OK)
      {
        DDSX11_TEST_ERROR << "receiver: Failed to delete domain participant from domain participant factory: "
                          << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
                          << std::endl;
        return 1;
      }
      retcode = dpf->finalize_instance ();
      dpf = nullptr;
      if (retcode != ::DDS::RETCODE_OK)
      {
        DDSX11_TEST_ERROR << "receiver: Failed to finalize the domain participant factory: "
                          << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
                          << std::endl;
        return 1;
      }
    }
  catch (const std::exception& e)
    {
      DDSX11_TEST_ERROR << "receiver: exception caught: " << e.what ()
                        << std::endl;
      return 1;
    }

  return retcode == DDS::RETCODE_OK ? 0 : 1;
}

void
ShapeTypeListener::on_requested_deadline_missed (
  DDS::traits<ShapeType>::datareader_ref_type ,
  const DDS::RequestedDeadlineMissedStatus& )
{
  DDSX11_TEST_DEBUG << "ShapeTypeListener::on_requested_deadline_missed received"
                    << std::endl;
}

void
ShapeTypeListener::on_requested_incompatible_qos (
  DDS::traits<ShapeType>::datareader_ref_type ,
  const DDS::RequestedIncompatibleQosStatus& )
{
  DDSX11_TEST_DEBUG << "ShapeTypeListener::on_requested_incompatible_qos received"
                    << std::endl;
}

void
ShapeTypeListener::on_sample_rejected (
  DDS::traits<ShapeType>::datareader_ref_type ,
  const DDS::SampleRejectedStatus& )
{
  DDSX11_TEST_DEBUG << "ShapeTypeListener::on_sample_rejected received"
                    << std::endl;
}

void
ShapeTypeListener::on_liveliness_changed (
  DDS::traits<ShapeType>::datareader_ref_type ,
  const DDS::LivelinessChangedStatus& )
{
  DDSX11_TEST_DEBUG << "ShapeTypeListener::on_liveliness_changed received"
                    << std::endl;
}

void
ShapeTypeListener::on_subscription_matched (
  DDS::traits<ShapeType>::datareader_ref_type ,
  const DDS::SubscriptionMatchedStatus& )
{
  DDSX11_TEST_DEBUG << "ShapeTypeListener::on_subscription_matched received"
                    << std::endl;
}

void
ShapeTypeListener::on_sample_lost (
  DDS::traits<ShapeType>::datareader_ref_type ,
  const DDS::SampleLostStatus& )
{
  DDSX11_TEST_DEBUG << "ShapeTypeListener::on_sample_lost received"
                    << std::endl;
}

void
ShapeTypeListener::on_data_available (
  DDS::traits<ShapeType>::datareader_ref_type the_reader)
{
  DDSX11_TEST_DEBUG << "ShapeTypeListener::on_data_available" << std::endl;
  DDS::traits<ShapeType>::typed_datareader_ref_type rd =
    DDS::traits<ShapeType>::narrow (the_reader);

  ShapeType shape;
  DDS::SampleInfo info;
  for(;;)
  {
    DDS::ReturnCode_t const retcode = rd->take_next_sample(shape, info);
    if (retcode == DDS::RETCODE_NO_DATA)
    {
      /* No more samples */
      break;
    }
    else if (retcode != DDS::RETCODE_OK)
    {
      DDSX11_TEST_ERROR << "receiver: Unable to take data from data reader, error "
                        << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
                        << std::endl;
      break;
    }
    else if (info.valid_data ())
    {
      DDSX11_TEST_DEBUG << "Received <" << ++received_ << ">: " << shape << std::endl;
    }
  }
}

