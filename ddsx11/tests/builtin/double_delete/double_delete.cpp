/**
 * @file   double_delete.cpp
 * @author Johnny Willemsen <jwillemsen@remedy.nl>
 *
 * @brief  Test whether multiple delete calls trigger the correct
 *         exception
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#include "shapetype_dds_typesupport.h"
#include <iostream>
#include <thread>
#include "tests/testlib/ddsx11_testlog.h"

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
      DDS::traits<ShapeType>::domainparticipant_ref_type domain_participant =
        dpf->create_participant (
          domain_id_, DDS::PARTICIPANT_QOS_DEFAULT, nullptr, DDS::STATUS_MASK_NONE);

      retcode = DDS::traits<ShapeType>::register_type (domain_participant, "ShapeType");
      if (retcode != DDS::RETCODE_OK)
      {
        DDSX11_TEST_ERROR << "double_delete: Failed to register type: "
                          << IDL::traits<::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
                          << std::endl;
        return 1;
      }

      DDS::traits<ShapeType>::topic_ref_type topic = domain_participant->create_topic (
        "Square", DDS::traits<ShapeType>::get_type_name (), DDS::TOPIC_QOS_DEFAULT, nullptr, DDS::STATUS_MASK_NONE);

      retcode = DDS::traits<ShapeType>::register_type (domain_participant, "ShapeType");
      if (retcode != DDS::RETCODE_OK)
      {
        DDSX11_TEST_ERROR << "Builtin: Error to register type: "
                          << IDL::traits<::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
                          << std::endl;
        return 1;
      }

      DDS::traits<ShapeType>::publisher_ref_type publisher =
        domain_participant->create_publisher (DDS::PUBLISHER_QOS_DEFAULT, nullptr, DDS::STATUS_MASK_NONE);
      if (!publisher)
      {
        DDSX11_TEST_ERROR << "double_delete: Failed to create publisher." << std::endl;
        return 1;
      }

      DDS::traits<ShapeType>::datawriter_ref_type dw =
          publisher->create_datawriter(topic, DDS::DATAWRITER_QOS_DEFAULT, nullptr, DDS::STATUS_MASK_NONE);
      if (!dw)
      {
        DDSX11_TEST_ERROR << "double_delete: Failed to create datawriter." << std::endl;
        return 1;
      }

      DDS::Duration_t const zero {0, 0};
      DDS::traits<ShapeType>::topic_ref_type topic2 = domain_participant->find_topic ("Square", zero);
      if (!topic2)
      {
        DDSX11_TEST_ERROR << "double_delete: Failed to use find_topic Square." << std::endl;
        return 1;
      }

      // topic2 and topic should have the same instance handles
      DDSX11_TEST_DEBUG << "Checking instance handles of topic and topic2" << std::endl;
      if (topic2->get_instance_handle () != topic->get_instance_handle ())
      {
        DDSX11_TEST_ERROR << "double_delete: topic and topic2 should have the same instance handles "
                          << topic2->get_instance_handle () << ":"
                          << topic->get_instance_handle ()
                          << std::endl;
        return 1;
      }

      DDSX11_TEST_DEBUG << "Deleting topic2" << std::endl;
      retcode = domain_participant->delete_topic (topic2);
      if (retcode != DDS::RETCODE_OK)
      {
        DDSX11_TEST_ERROR << "double_delete: Failed to delete topic2 from domain participant: "
                          << IDL::traits<::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
                          << std::endl;
        return 1;
      }

      // Try to delete the publisher when it still has a datawriter, this should fail
      retcode = domain_participant->delete_publisher (publisher);
      if (retcode == DDS::RETCODE_OK)
      {
        DDSX11_TEST_ERROR << "double_delete: Deleting publisher should fail: "
                          << IDL::traits<::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
                          << std::endl;
        return 1;
      }

      // Now delete the datawriter, this should work
      retcode = publisher->delete_datawriter (dw);
      if (retcode != DDS::RETCODE_OK)
      {
        DDSX11_TEST_ERROR << "double_delete: Failed to delete datawriter: "
                          << IDL::traits<::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
                          << std::endl;
        return 1;
      }

      // Try to delete the datawriter a second time, this should fail
      retcode = publisher->delete_datawriter (dw);
      dw = nullptr;
      if (retcode != DDS::RETCODE_BAD_PARAMETER)
      {
        DDSX11_TEST_ERROR << "double_delete: Deleting the datawriter the second time should fail: "
                          << IDL::traits<::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
                          << std::endl;
        return 1;
      }

      // Now delete the publisher after the datawriter has been deleted, it should
      // now work
      retcode = domain_participant->delete_publisher (publisher);
      if (retcode != DDS::RETCODE_OK)
      {
        DDSX11_TEST_ERROR << "double_delete: Failed to delete publisher: "
                          << IDL::traits<::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
                          << std::endl;
        return 1;
      }

      // And try to delete the publisher another time, this should fail
      retcode = domain_participant->delete_publisher (publisher);
      publisher = nullptr;
      if (retcode != DDS::RETCODE_BAD_PARAMETER)
      {
        DDSX11_TEST_ERROR << "double_delete: Deleting the publisher the second time should fail: "
                          << IDL::traits<::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
                          << std::endl;
        return 1;
      }

      retcode = domain_participant->delete_topic (topic);
      if (retcode != DDS::RETCODE_OK)
      {
        DDSX11_TEST_ERROR << "double_delete: Failed to delete topic from domain participant: "
                          << IDL::traits<::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
                          << std::endl;
        return 1;
      }

      // Try to delete the topic the second time, this should return a RETCODE_BAD_PARAMETER
      retcode = domain_participant->delete_topic (topic);
      topic = nullptr;
      if (retcode != DDS::RETCODE_BAD_PARAMETER)
      {
        DDSX11_TEST_ERROR << "double_delete: Second delete topic didn't return correct return code: "
                          << IDL::traits<::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
                          << std::endl;
        return 1;
      }

      retcode = dpf->delete_participant(domain_participant);
      if (retcode != DDS::RETCODE_OK)
      {
        DDSX11_TEST_ERROR << "Builtin: Failed to delete domain participant from domain participant factory: "
                          << IDL::traits<::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
                          << std::endl;
        return 1;
      }

      retcode = dpf->delete_participant(domain_participant);
      domain_participant = nullptr;
      if (retcode != DDS::RETCODE_BAD_PARAMETER)
      {
        DDSX11_TEST_ERROR << "double_delete: Second delete domain participant didn't return correct return code: "
                          << IDL::traits<::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
                          << std::endl;
        return 1;
      }

      retcode = dpf->finalize_instance ();
      dpf = nullptr;
      if (retcode != ::DDS::RETCODE_OK)
      {
        DDSX11_TEST_ERROR << "Builtin: Failed to finalize the domain participant factory: "
                          << IDL::traits<::DDS::ReturnCode_t>::write<retcode_formatter> (retcode)
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

