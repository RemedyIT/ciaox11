/**
 * @file   sender.cpp
 * @author Johnny Willemsen <jwillemsen@remedy.nl>
 *
 * @brief  Shapes DataWriter example using the IDL to C++11
 *         language mapping
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#include "shapetype_dds_typesupport.h"
#include <thread>
#include "tests/testlib/ddsx11_testlog.h"

static std::string const qos_profile { "shapes#ShapesProfile" };

int main (int , char *[])
{
  DDS::ReturnCode_t retcode = DDS::RETCODE_OK;

  try
    {
      const char * domain = std::getenv ("DDS4CCM_DEFAULT_DOMAIN_ID");
      ::DDS::DomainId_t domain_id_ {};
      if (domain)
      {
        domain_id_ = std::atoi (domain);
      }

      DDS::traits<ShapeType>::domainparticipantfactory_ref_type dpf =
        DDS::traits<DDS::DomainParticipantFactory>::get_instance ();

      DDS::traits<ShapeType>::domainparticipant_ref_type domain_participant =
        dpf->create_participant_with_profile (
            domain_id_, qos_profile, nullptr, DDS::STATUS_MASK_NONE);

      retcode = DDS::traits<ShapeType>::register_type (domain_participant, "ShapeType");
      if (retcode != DDS::RETCODE_OK)
      {
        DDSX11_TEST_ERROR << "sender: Failed to register type: "
                          << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
                          << std::endl;
        return 1;
      }

      DDS::traits<ShapeType>::topic_ref_type topic = domain_participant->create_topic_with_profile (
        "Square", DDS::traits<ShapeType>::get_type_name (), qos_profile, nullptr, DDS::STATUS_MASK_NONE);

      DDS::traits<ShapeType>::publisher_ref_type publisher =
        domain_participant->create_publisher_with_profile (qos_profile, nullptr, DDS::STATUS_MASK_NONE);

      if (publisher && topic)
      {
        DDS::traits<ShapeType>::datawriter_ref_type dw =
          publisher->create_datawriter_with_profile (topic, qos_profile, nullptr, DDS::STATUS_MASK_NONE);

        DDS::traits<ShapeType>::typed_datawriter_ref_type shape_dw =
          DDS::traits<ShapeType>::narrow (dw);

        if (shape_dw)
        {
          // Wait for discovery
          int32_t count {};
          int32_t maxPollPeriods { 30 };
          while (count < maxPollPeriods)
          {
            DDS::PublicationMatchedStatus status;
            DDS::ReturnCode_t const ret_pm = dw->get_publication_matched_status(status);
            DDSX11_TEST_DEBUG << "sender: PublicationMatchedStatus: status is " << status << ", return_code is "
                              << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (ret_pm) << std::endl;
            if (status.total_count() == 1)
            {
              DDSX11_TEST_DEBUG << "sender: PublicationMatchedStatus status has been received"
                                << std::endl;

              break;
            }
            ++count;
            std::this_thread::sleep_for (std::chrono::milliseconds (500));
          }

          if (count == maxPollPeriods)
          {
            DDSX11_TEST_DEBUG << "sender: PublicationMatchedStatus status isn't received on time, so it is possible that not "
                                 "all written samples are going to be received." << std::endl;
          }

          ShapeType square {"GREEN", 10, 10, 25};

          DDS::InstanceHandle_t instance_handle =
            shape_dw->register_instance (square);

          for (uint32_t i = 0; i < 100; ++i)
          {
            shape_dw->write (square, instance_handle);
            DDSX11_TEST_DEBUG << "sender: Written sample " << square << std::endl;
            ++square.x(); ++square.y();
            std::this_thread::sleep_for (std::chrono::milliseconds (10));
          }

          DDSX11_TEST_DEBUG << "sender: Written 100 samples. Last sample: "
                            << square
                            << std::endl;

          shape_dw->unregister_instance (square, instance_handle);

          retcode = publisher->delete_datawriter (shape_dw);
          shape_dw = nullptr;
          if (retcode != DDS::RETCODE_OK)
          {
            DDSX11_TEST_ERROR << "sender: Failed to delete datawriter from publisher: "
                              << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
                              << std::endl;
            return 1;
          }
        }
        else
        {
          DDSX11_TEST_ERROR << "Sender: Typed datawriter is null." << std::endl;
          retcode = DDS::RETCODE_ERROR;
        }

        retcode = domain_participant->delete_publisher (publisher);
        publisher = nullptr;
        if (retcode != DDS::RETCODE_OK)
        {
          DDSX11_TEST_ERROR << "sender: Failed to delete publisher from domain participant"
                            << std::endl;
          return 1;
        }
        retcode = domain_participant->delete_topic (topic);
        topic = nullptr;
        if (retcode != DDS::RETCODE_OK)
        {
          DDSX11_TEST_ERROR << "sender: Failed to delete topic from domain participant"
                            << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
                            << std::endl;
          return 1;
        }
      }
      else
      {
        DDSX11_TEST_ERROR << "sender: Either Topic or Publisher is null"
                          << std::endl;
        retcode = DDS::RETCODE_ERROR;
      }

      retcode = dpf->delete_participant(domain_participant);
      domain_participant = nullptr;
      if (retcode != DDS::RETCODE_OK)
      {
        DDSX11_TEST_ERROR << "sender: Failed to delete domain participant from domain participant factory: "
                          << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
                          << std::endl;
        return 1;
      }
      retcode = dpf->finalize_instance ();
      dpf = nullptr;
      if (retcode != ::DDS::RETCODE_OK)
      {
        DDSX11_TEST_ERROR << "sender: Failed to finalize the domain participant factory: "
                          << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
                          << std::endl;
        return 1;
      }
    }
  catch (const std::exception& e)
    {
      DDSX11_TEST_ERROR << "sender: exception caught: " << e << std::endl;
      return 1;
    }

  return retcode == DDS::RETCODE_OK ? 0 : 1;
}
