/**
 * @file    server.cpp
 * @author  Martin Corino
 *
 * @brief   CORBA C++11 server application
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */

#include "hello.h"
#include "testlib/taox11_testlog.h"
#include "orbsvcs/orbsvcs/naming_server/CosNamingC.h"
#include "ace/Get_Opt.h"

#include <sstream>
#include <fstream>

uint16_t port_ {30001};
std::string name_ {"HelloServant"};
std::string ior_file_ {"server.ior"};

bool
parse_args (int argc, ACE_TCHAR *argv[])
{
  ACE_Get_Opt get_opts (argc, argv, ACE_TEXT("o:p:n:h"),
                        1,
                        0,
                        ACE_Get_Opt::RETURN_IN_ORDER);
  int c;

  while ((c = get_opts ()) != -1)
    switch (c)
      {
      case 'p':
        port_ = std::atoi (get_opts.opt_arg ());
        break;

      case 'n':
        name_ = get_opts.opt_arg ();
        break;

      case 'o':
        ior_file_ = get_opts.opt_arg ();
        break;

      case 'h':
        TAOX11_TEST_ERROR << "usage: -o <ior file> -p <port> -n <servant name>"
              << std::endl;
        return false;

      case '?':
      {
        // skip to next argv entry
        for (int aix = get_opts.opt_ind (); get_opts.opt_ind () == aix ;) get_opts ();
        break;
      }
      default:
        break;
      }
  // Indicates successful parsing of the command line
  return true;
}

int
main(int argc, ACE_TCHAR *argv[])
{
  try
    {
      if (!parse_args (argc, argv))
        return 1;

      // create ORB arguments
      int orb_argc = argc + 2;  // make room for 2 more args
      std::unique_ptr<const char*[]> orb_argv = std::make_unique<const char*[]> (orb_argc);
      // copy all current args
      for (int i=0; i<argc ;++i)
      {
        orb_argv.get ()[i] = argv[i];
      }
      // add listen endpoint args
      orb_argv.get ()[argc] = "-ORBListenEndpoints";
      std::ostringstream os;
      os << "iiop://:"<< port_;
      std::string listen_endpoint = os.str ();
      orb_argv.get ()[argc+1] = listen_endpoint.c_str ();

      // initialize ORB
      IDL::traits<CORBA::ORB>::ref_type _orb =
          CORBA::ORB_init (orb_argc, const_cast<char**> (orb_argv.get ()));

      if (_orb == nullptr)
        {
          TAOX11_TEST_ERROR
            << "ERROR: CORBA::ORB_init (argc, argv) returned null ORB."
            << std::endl;
          return 1;
        }

      IDL::traits<CORBA::Object>::ref_type obj =
        _orb->resolve_initial_references ("RootPOA");

      if (!obj)
        {
          TAOX11_TEST_ERROR
            << "ERROR: resolve_initial_references (\"RootPOA\") returned null reference." << std::endl;
          return 1;
        }

      TAOX11_TEST_INFO << "retrieved RootPOA object reference" << std::endl;

      IDL::traits<PortableServer::POA>::ref_type root_poa =
        IDL::traits<PortableServer::POA>::narrow (obj);

      if (!root_poa)
        {
          TAOX11_TEST_ERROR
            << "ERROR: IDL::traits<PortableServer::POA>::narrow (obj) returned null object."
            << std::endl;
          return 1;
        }

      TAOX11_TEST_INFO << "narrowed POA interface" << std::endl;

      IDL::traits<PortableServer::POAManager>::ref_type poaman =
        root_poa->the_POAManager ();

      if (!poaman)
        {
          TAOX11_TEST_ERROR
            << "ERROR: root_poa->the_POAManager () returned null object."
            << std::endl;
          return 1;
        }

      CORBA::servant_traits<Test::Hello>::ref_type hello_impl =
        CORBA::make_reference<Hello> (_orb);

      TAOX11_TEST_INFO << "created Hello servant" << std::endl;

      PortableServer::ObjectId id = root_poa->activate_object (hello_impl);

      TAOX11_TEST_INFO << "activated Hello servant" << std::endl;

      IDL::traits<CORBA::Object>::ref_type hello_obj =
        root_poa->id_to_reference (id);

      if (hello_obj == nullptr)
        {
          TAOX11_TEST_ERROR
            << "ERROR: root_poa->id_to_reference (id) returned null reference."
            << std::endl;
          return 1;
        }

      IDL::traits<Test::Hello>::ref_type hello =
        IDL::traits<Test::Hello>::narrow (hello_obj);

      if (hello == nullptr)
        {
          TAOX11_TEST_ERROR
            << "ERROR: IDL::traits<Test::Hello>::narrow (hello_obj) returned null reference."
            << std::endl;
          return 1;
        }

      std::string ior = _orb->object_to_string (hello);

      TAOX11_TEST_INFO << "Resolving NameService"
        << std::endl;
      IDL::traits<CORBA::Object>::ref_type ins_obj =
          _orb->resolve_initial_references("NameService");
      if (ins_obj)
      {
        IDL::traits<CosNaming::NamingContext>::ref_type nc =
            IDL::traits<CosNaming::NamingContext>::narrow (ins_obj);
        if (nc)
        {
          // Binding deployment manager IOR to DeploymentNC
          TAOX11_TEST_INFO << "Registering servant in NC as \"" <<
                              name_ << "\"." << std::endl;
          CosNaming::Name cname;
          cname.push_back (CosNaming::NameComponent (name_, ""));
          nc->rebind (cname, hello);
        }
        else
        {
          TAOX11_TEST_ERROR << "Narrow to NamingContext returned nil."
            << std::endl ;
          return 1;
        }
      }
      else
      {
        TAOX11_TEST_ERROR << "NameService resolved to nil."
          << std::endl ;
        return 1;
      }

      // Output the IOR to the <ior_file_>
      std::ofstream fos(ior_file_);
      if (!fos)
      {
        TAOX11_TEST_ERROR << "ERROR: failed to open file '" << ior_file_ << "'" << std::endl;
        return 1;
      }
      fos << ior;
      fos.close ();

      poaman->activate ();

      TAOX11_TEST_INFO << "starting event loop" << std::endl;

      _orb->run ();

      TAOX11_TEST_INFO << "event loop finished" << std::endl;

      root_poa->destroy (true, true);

      _orb->destroy ();
    }
  catch (const std::exception& e)
    {
      TAOX11_TEST_ERROR << "exception caught: " << e.what () << std::endl;
      return 1;
    }

  return 0;
}
