/**
 * @file    client.cpp
 * @author  Marcel Smit
 *
 * @brief   IDL2 client to test whether the component has been deregistered.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#include "orbsvcs/orbsvcs/naming_server/CosNamingC.h"
#include "testlib/taox11_testlog.h"
#include "ace/Get_Opt.h"

std::string ior = "file://ns.ior";
bool check_deregistration = false;

bool
parse_args (int argc, ACE_TCHAR *argv[])
{
  ACE_Get_Opt get_opts (argc, argv, ACE_TEXT("dk:"));
  int c;

  while ((c = get_opts ()) != -1)
    switch (c)
      {
      case 'd':
        check_deregistration = true;
        break;

      case 'k':
        ior = get_opts.opt_arg ();
        break;

      case '?':
      default:
        TAOX11_TEST_ERROR << "usage: -k <ior>"
              << std::endl;
        return false;
      }
  // Indicates successful parsing of the command line
  return true;
}

int
main (int argc, ACE_TCHAR *argv[])
{
  TAOX11_TEST_DEBUG << "Starting IDL2 client" << std::endl;

  try
  {
      // Initialize orb
      IDL::traits<CORBA::ORB>::ref_type orb = CORBA::ORB_init(argc, argv);

      if (!parse_args (argc, argv))
        return 1;

      // Find the Naming Service
      IDL::traits<CORBA::Object>::ref_type obj = orb->string_to_object (ior);

      if (obj == nullptr)
      {
        TAOX11_TEST_ERROR << "ERROR: string_to_object(<ior>) returned null reference."
          << std::endl;
        return 1;
      }

      IDL::traits<CosNaming::NamingContextExt>::ref_type nc = IDL::traits<CosNaming::NamingContextExt>::narrow (obj);

      if (!nc)
      {
        TAOX11_TEST_ERROR << "ERROR: Narrow returned null object."
            << std::endl;
        return 1;
      }

      try
      {
          TAOX11_TEST_DEBUG << "Resolving deployed component" << std::endl;

          // retrieve deployed component
          if (!nc->resolve_str ("TestComp"))
          {
            // this should never happen
            TAOX11_TEST_ERROR << "ERROR: Unable to resolve deployed component"
              << std::endl;
          }
      }
      catch (CORBA::Exception const &ex)
      {
          if (check_deregistration)
            TAOX11_TEST_DEBUG << "Unable to resolve deployed component : "
              << ex << std::endl;
          else
            TAOX11_TEST_ERROR << "Unable to resolve deployed component : "
              << ex << std::endl;
      }
  }
  catch (CORBA::Exception const &ex)
  {
      TAOX11_TEST_DEBUG << "ERROR while running the test: "
        << ex << std::endl;
      return 1;
  }

  TAOX11_TEST_DEBUG << "Succesfully finished IDL2 client" << std::endl;
  return 0;
}
