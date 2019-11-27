/**
 * @file   builtin.cpp
 * @author Johnny Willemsen <jwillemsen@remedy.nl>
 *
 * @brief  Shapes built in DDS example using the IDL to C++11
 *         language mapping
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#include "shapetype_dds_typesupport.h"
#include <iostream>
#include <thread>

// X11_FUZZ: disable check_cout_cerr
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
        DDS::traits< DDS::DomainParticipantFactory >::get_instance ();
      DDS::traits<ShapeType>::domainparticipant_ref_type domain_participant =
        dpf->create_participant_with_profile (
          domain_id_, qos_profile, nullptr, 0);

      // Try to lookup a domain participant for a domain for which
      // we haven't created a domain participant, this should return a
      // nil object reference
      DDS::traits<ShapeType>::domainparticipant_ref_type invalid_domain =
        dpf->lookup_participant (domain_id_ + 1);
      if (!invalid_domain)
      {
        std::cout << "Builtin: Correctly returned no domain participant" << std::endl;
      }
      else
      {
        std::cerr << "Builtin: Error, got a domain participant for invalid domain" << std::endl;
      }

      // Now retrieve a domain participant for our domain, this should succeed
      DDS::traits<ShapeType>::domainparticipant_ref_type domain_participant2 =
        dpf->lookup_participant (domain_id_);
      if (domain_participant2)
      {
        std::cout << "Builtin: Correctly returned domain participant " << std::endl;
      }
      else
      {
        std::cerr << "Builtin: Error, got no domain participant for valid domain" << std::endl;
      }
      domain_participant2 = nullptr;

      retcode = DDS::traits<ShapeType>::register_type (domain_participant, "ShapeType");
      if (retcode != DDS::RETCODE_OK)
      {
        std::cerr << "Builtin: Error to register type." << std::endl;
        return 1;
      }

      DDS::traits<ShapeType>::subscriber_ref_type subscriber =
        domain_participant->get_builtin_subscriber ();

      if (!subscriber)
      {
        std::cerr << "ERROR: Unable to get the builtin subscriber!" << std::endl;
        retcode = DDS::RETCODE_ERROR;
      }

      DDS::traits<ShapeType>::subscriber_ref_type subscriber2 =
        domain_participant->get_builtin_subscriber ();

      if (!subscriber2)
      {
        std::cerr << "ERROR: Unable to get the builtin subscriber for the second time!" << std::endl;
        retcode = DDS::RETCODE_ERROR;
      }

      retcode = dpf->delete_participant(domain_participant);
      domain_participant = nullptr;
      if (retcode != DDS::RETCODE_OK)
      {
        std::cerr << "Builtin: Failed to delete domain participant from domain participant factory." << std::endl;
        return 1;
      }
      retcode = dpf->finalize_instance ();
      dpf = nullptr;
      if (retcode != ::DDS::RETCODE_OK)
      {
        std::cerr << "Builtin: Failed to finalize the domain participant factory." << std::endl;
        return 1;
      }
    }
  catch (const std::exception& e)
    {
      std::cerr << "exception caught: " << e.what () << std::endl;
      return 1;
    }

  return retcode == DDS::RETCODE_OK ? 0 : 1;
}

