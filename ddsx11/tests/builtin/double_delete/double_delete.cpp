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
#include "logger/ddsx11_log.h"

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
          domain_id_, DDS::PARTICIPANT_QOS_DEFAULT, nullptr, 0);

      retcode = DDS::traits<ShapeType>::register_type (domain_participant, "ShapeType");
      if (retcode != DDS::RETCODE_OK)
      {
        DDSX11_IMPL_LOG_PANIC ("Receiver: Failed to register type.");
        return 1;
      }

      DDS::traits<ShapeType>::topic_ref_type topic = domain_participant->create_topic (
        "Square", DDS::traits<ShapeType>::get_type_name (), DDS::TOPIC_QOS_DEFAULT, nullptr, 0);

      retcode = DDS::traits<ShapeType>::register_type (domain_participant, "ShapeType");
      if (retcode != DDS::RETCODE_OK)
      {
        DDSX11_IMPL_LOG_PANIC ("Builtin: Error to register type.");
        return 1;
      }

      DDS::Duration_t const zero {0, 0};
      DDS::traits<ShapeType>::topic_ref_type topic2 = domain_participant->find_topic ("Square", zero);

      retcode = domain_participant->delete_topic (topic2);
      if (retcode != DDS::RETCODE_OK)
      {
        DDSX11_IMPL_LOG_PANIC ("Receiver: Failed to delete topic2 from domain participant.");
        return 1;
      }

      retcode = domain_participant->delete_topic (topic);
      if (retcode != DDS::RETCODE_OK)
      {
        DDSX11_IMPL_LOG_PANIC ("Receiver: Failed to delete topic from domain participant.");
        return 1;
      }

      // Try to delete the topic the second time, this should return a RETCODE_BAD_PARAMETER
      retcode = domain_participant->delete_topic (topic);
      topic = nullptr;
      if (retcode != DDS::RETCODE_BAD_PARAMETER)
      {
        DDSX11_IMPL_LOG_PANIC ("Receiver: Second delete topic didn't return correct return code.");
        return 1;
      }

      retcode = dpf->delete_participant(domain_participant);
      if (retcode != DDS::RETCODE_OK)
      {
        DDSX11_IMPL_LOG_PANIC ("Builtin: Failed to delete domain participant from domain participant factory.");
        return 1;
      }

      retcode = dpf->delete_participant(domain_participant);
      domain_participant = nullptr;
      if (retcode != DDS::RETCODE_BAD_PARAMETER)
      {
        DDSX11_IMPL_LOG_PANIC ("Receiver: Second delete domain participant didn't return correct return code.");
        return 1;
      }

      retcode = dpf->finalize_instance ();
      dpf = nullptr;
      if (retcode != ::DDS::RETCODE_OK)
      {
        DDSX11_IMPL_LOG_PANIC ("Builtin: Failed to finalize the domain participant factory.");
        return 1;
      }
    }
  catch (const std::exception& e)
    {
      DDSX11_IMPL_LOG_PANIC ("exception caught: " << e.what ());
      return 1;
    }

  return retcode == DDS::RETCODE_OK ? 0 : 1;
}

