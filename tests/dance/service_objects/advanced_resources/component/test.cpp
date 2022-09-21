// -*- C++ -*-
/**
 * @file    test.cpp
 * @author  Martin Corino
 *
 * @brief   DAnCEX11 ORB advanced_resources test
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#include "tao/ORB.h"
#include "tao/Resource_Factory.h"
#include "tao/Strategies/advanced_resource.h"
#include "ciaox11/testlib/ciaox11_testlog.h"

#include <string>

void do_test_orb_advanced_resources(const std::string& orbid)
{
  try
  {
    int argc = 0;
    CORBA::ORB_var orb = CORBA::ORB_init (argc, nullptr, orbid.c_str ());

    if (orb)
    {
      TAO_Resource_Factory* resfactory = orb->orb_core ()->resource_factory ();

      TAO_Advanced_Resource_Factory* adv_resfactory = dynamic_cast<TAO_Advanced_Resource_Factory*> (resfactory);

      if (adv_resfactory)
      {
        CIAOX11_TEST_INFO << "ORB Advanced_Resource_Factory correctly installed" << std::endl;

        if (adv_resfactory->purge_percentage () == 30)
        {
          CIAOX11_TEST_INFO << "ORB Advanced_Resource_Factory purge percentage correctly set to 30" << std::endl;
        }
        else
        {
          CIAOX11_TEST_ERROR << "ERROR: Resource factory purge percentage not updated correctly" << std::endl;
        }
      }
      else
      {
        CIAOX11_TEST_ERROR << "ERROR: Cannot retrieve ORB advanced resource factory" << std::endl;
      }
    }
    else
    {
      CIAOX11_TEST_ERROR << "ERROR: Cannot retrieve TAO ORB [" << orbid << "]" << std::endl;
    }
  }
  catch (const CORBA::Exception& ex)
  {
    ex._tao_print_exception("ERROR: Exception caught:", stderr);
  }
}
