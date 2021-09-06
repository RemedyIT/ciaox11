/**
 * @file   dpf_sdqwp.cpp
 * @author Johnny Willemsen <jwillemsen@remedy.nl>
 *
 * @brief  Test whether dpf->set_default_participant_qos_with_profile
 *         works as expected
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#include "shapetype_dds_typesupport.h"
#include <iostream>
#include <thread>
#include "tests/testlib/ddsx11_testlog.h"

static std::string const qos_profile { "shapes#ShapesProfile" };

int main (int, char *[])
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
        DDS::traits<DDS::DomainParticipantFactory>::get_instance ();

      retcode = dpf->set_default_participant_qos_with_profile(qos_profile);

      if (retcode != DDS::RETCODE_OK)
      {
        DDSX11_TEST_ERROR << "Failed to set default participant QoS from profile: "
                          << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
                          << std::endl;
        return 1;
      }

      DDS::traits<ShapeType>::domainparticipant_ref_type domain_participant =
        dpf->create_participant (
          domain_id_, DDS::PARTICIPANT_QOS_DEFAULT, nullptr, DDS::STATUS_MASK_NONE);

      retcode = DDS::traits<ShapeType>::register_type (domain_participant, "ShapeType");
      if (retcode != DDS::RETCODE_OK)
      {
        DDSX11_TEST_ERROR << "dpf_sdqwp: Failed to register type: "
                          << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
                          << std::endl;
        return 1;
      }

      DDS::traits<ShapeType>::topic_ref_type topic = domain_participant->create_topic (
        "Square", DDS::traits<ShapeType>::get_type_name (), DDS::TOPIC_QOS_DEFAULT, nullptr, DDS::STATUS_MASK_NONE);

      retcode = DDS::traits<ShapeType>::register_type (domain_participant, "ShapeType");
      if (retcode != DDS::RETCODE_OK)
      {
        DDSX11_TEST_ERROR << "Builtin: Error to register type: "
                          << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
                          << std::endl;
        return 1;
      }

      DDS::traits<ShapeType>::publisher_ref_type publisher =
        domain_participant->create_publisher (DDS::PUBLISHER_QOS_DEFAULT, nullptr, DDS::STATUS_MASK_NONE);
      if (!publisher)
      {
        DDSX11_TEST_ERROR << "dpf_sdqwp: Failed to create publisher." << std::endl;
        return 1;
      }

      DDS::traits<ShapeType>::datawriter_ref_type dw =
          publisher->create_datawriter(topic, DDS::DATAWRITER_QOS_DEFAULT, nullptr, DDS::STATUS_MASK_NONE);
      if (!dw)
      {
        DDSX11_TEST_ERROR << "dpf_sdqwp: Failed to create datawriter." << std::endl;
        return 1;
      }

      // Now delete the datawriter, this should work
      retcode = publisher->delete_datawriter (dw);
      if (retcode != DDS::RETCODE_OK)
      {
        DDSX11_TEST_ERROR << "dpf_sdqwp: Failed to delete datawriter: "
                          << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
                          << std::endl;
        return 1;
      }

      // Now delete the publisher
      retcode = domain_participant->delete_publisher (publisher);
      if (retcode != DDS::RETCODE_OK)
      {
        DDSX11_TEST_ERROR << "dpf_sdqwp: Failed to delete publisher: "
                          << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
                          << std::endl;
        return 1;
      }

      retcode = domain_participant->delete_topic (topic);
      if (retcode != DDS::RETCODE_OK)
      {
        DDSX11_TEST_ERROR << "dpf_sdqwp: Failed to delete topic from domain participant: "
                          << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
                          << std::endl;
        return 1;
      }

      retcode = dpf->delete_participant(domain_participant);
      if (retcode != DDS::RETCODE_OK)
      {
        DDSX11_TEST_ERROR << "Builtin: Failed to delete domain participant from domain participant factory: "
                          << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
                          << std::endl;
        return 1;
      }

      retcode = dpf->finalize_instance ();
      dpf = nullptr;
      if (retcode != ::DDS::RETCODE_OK)
      {
        DDSX11_TEST_ERROR << "Builtin: Failed to finalize the domain participant factory: "
                          << IDL::traits< ::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
                          << std::endl;
        return 1;
      }
    }
  catch (const std::exception& e)
    {
      DDSX11_TEST_ERROR << "exception caught: " << e << std::endl;
      return 1;
    }

  return retcode == DDS::RETCODE_OK ? 0 : 1;
}

