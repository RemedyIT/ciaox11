/**
 * @file    main.cpp
 * @author  Marcel Smit
 *
 * @brief   Testing type support and dp-re-use.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#include "tests/testlib/ddsx11_testlog.h"

# include "dds/dds_type_support.h"
# include "dds/dds_vendor_adapter.h"

class TestTypeFactory final :
  public ::DDSX11::DDS_TypeFactory_i
{
public:
  TestTypeFactory () = default;
  virtual ~TestTypeFactory() {}

  IDL::traits< ::DDS::DataWriter>::ref_type
  create_datawriter (
    ::DDS_Native::DDS::DataWriter* dw) override;

  IDL::traits< ::DDS::DataReader>::ref_type
  create_datareader (
    ::DDS_Native::DDS::DataReader* dr) override;
};

IDL::traits< ::DDS::DataWriter>::ref_type
TestTypeFactory::create_datawriter (
    ::DDS_Native::DDS::DataWriter*)
{
  return nullptr;
}

IDL::traits< ::DDS::DataReader>::ref_type
TestTypeFactory::create_datareader (
  ::DDS_Native::DDS::DataReader*)
{
  return nullptr;
}

int main (int , char **)
{
  int ret = 0;

  try
    {
      const char * domain = std::getenv ("DDS4CCM_DEFAULT_DOMAIN_ID");
      uint16_t domain_id = 0;

      if (domain)
      {
        domain_id = std::atoi (domain);
      }

      IDL::traits< ::DDS::DomainParticipantFactory>::ref_type pf =
        ::DDSX11::VendorUtils::init_dds ();

      ::DDS::DomainParticipantQos qos;
      IDL::traits< ::DDS::DomainParticipant>::ref_type dp1 =
        pf->create_participant (domain_id, qos, nullptr, ::DDS::STATUS_MASK_NONE);
      if (!dp1)
        {
          DDSX11_TEST_ERROR
            << "ERROR - Could not create DP1" << std::endl;
          ++ret;
        }

      IDL::traits< ::DDS::DomainParticipant>::ref_type dp2 =
        pf->create_participant (domain_id, qos, nullptr, ::DDS::STATUS_MASK_NONE);
      if (!dp2)
        {
          DDSX11_TEST_ERROR
            << "ERROR - Could not create DP2" << std::endl;
          ++ret;
        }

      std::string const type1 ("DataType1");
      std::string const type2 ("DataType2");
      std::string const type3 ("DataType3");

      std::shared_ptr<TestTypeFactory> f1 = std::make_shared<TestTypeFactory> ();
      std::shared_ptr<TestTypeFactory> f2 = std::make_shared<TestTypeFactory> ();
      std::shared_ptr<TestTypeFactory> f3 = std::make_shared<TestTypeFactory> ();

      /// Register type 1 with f1
      if (::DDSX11::DDS_TypeSupport_i::register_type (dp1, type1, f1))
        {
          DDSX11_TEST_DEBUG
            << "OK - Type <" << type1 << "> and Factory <" << f1
            << "> successfully registered for DP1" << std::endl;
        }
      else
        {
          DDSX11_TEST_ERROR
            << "ERROR - Type <" << type1 << "> and Factory <" << f1
            << "> could not be registered for DP1" << std::endl;
          ++ret;
        }
      /// DP1 should now contain one type-factory combination

      /// Register the same factory again, this should return false because
      /// the type was already there
      if (::DDSX11::DDS_TypeSupport_i::register_type (dp1, type1, f1))
        {
          DDSX11_TEST_ERROR
            << "ERROR - Type <" << type1 << "> and Factory <" << f1
            << "> are indicated to be a fresh DP1" << std::endl;
          ++ret;
        }
      else
        {
          DDSX11_TEST_DEBUG
            << "OK - Type <" << type1 << "> and Factory <" << f1
            << "> are not fresh for DP1" << std::endl;
        }
      /// DP1 should now contain one type-factory combination

      /// Register the same factory again but with another name
      if (::DDSX11::DDS_TypeSupport_i::register_type (dp1, type2, f1))
        {
          DDSX11_TEST_DEBUG
            << "OK - Type <" << type2 << "> and Factory <" << f1
            << "> successfully registered for DP1" << std::endl;
        }
      else
        {
          DDSX11_TEST_ERROR
            << "ERROR - Type <" << type2 << "> and Factory <" << f1
            << "> could not be registered for DP1" << std::endl;
          ++ret;
        }
      /// DP1 should now contain two type-factory combinations

      /// Register the same type with another factory
      if (::DDSX11::DDS_TypeSupport_i::register_type (dp1, type2, f2))
        {
          DDSX11_TEST_ERROR
            << "ERROR - Type <" << type2 << "> and Factory <" << f2
            << "> could be registered for DP1" << std::endl;
          ++ret;
        }
      else
        {
          DDSX11_TEST_DEBUG
            << "OK - Type <" << type2 << "> and Factory <" << f2
            << "> could not be registered for DP1" << std::endl;
        }
      /// DP1 should now contain two type-factory combinations

      /// Just register type 3 with f3
      if (::DDSX11::DDS_TypeSupport_i::register_type (dp1, type3, f3))
        {
          DDSX11_TEST_DEBUG
            << "OK - Type <" << type3 << "> and Factory <" << f3
            << "> successfully registered for DP1" << std::endl;
        }
      else
        {
          DDSX11_TEST_ERROR
            << "ERROR - Type <" << type3 << "> and Factory <" << f3
            << "> could be registered for DP1" << std::endl;
          ++ret;
        }
      /// DP1 should now contain three type-factory combinations

      /// Unregister an unused factory by using an unused domain participant
      if (::DDSX11::DDS_TypeSupport_i::unregister_type (dp2, type1))
        {
          DDSX11_TEST_ERROR
            << "ERROR - Unregistered type <" << type1 << "> for DP2 could be "
            << "unregistered." << std::endl;
          ++ret;
        }
      else
        {
          DDSX11_TEST_DEBUG
            << "OK - Unregistered type <" << type1 << "> for DP2 could not "
            << "be unregistered" << std::endl;
        }

      /// Unregister a registered type by using a used domain participant,
      /// the refcount drops to 1 making this return false
      if (::DDSX11::DDS_TypeSupport_i::unregister_type (dp1, type1))
        {
          DDSX11_TEST_ERROR
            << "ERROR - Registered type <" << type1 << "> for DP1 returns false "
            << std::endl;
          ++ret;
        }
      else
        {
          DDSX11_TEST_DEBUG
            << "OK - Registered type <" << type1 << "> for DP1 could "
            << "be unregistered and return false" << std::endl;
        }
      /// DP1 should now contain two type-factory combinations

      /// Unregister the same type and domain participant again, this
      /// should drop the refcount to zero and return true
      if (::DDSX11::DDS_TypeSupport_i::unregister_type (dp1, type1))
        {
          DDSX11_TEST_DEBUG
            << "OK - Unregistered type <" << type1 << "> for DP1 could "
            << "be unregistered" << std::endl;
        }
      else
        {
          DDSX11_TEST_ERROR
            << "ERROR - Unregistered type <" << type1 << "> for DP1 could not "
            << "be unregistered" << std::endl;
          ++ret;
        }
      /// DP1 should now contain two type-factory combinations

      /// Call Close on TypeSupport. This should remove the last remaining entries.
      ::DDSX11::DDS_TypeSupport_i::close();

      /// Unregister the type and domain participant which should be removed by 'close'
      if (::DDSX11::DDS_TypeSupport_i::unregister_type (dp1, type2))
        {
          DDSX11_TEST_ERROR
            << "ERROR - Deleted type <" << type2 << "> for DP1 could be "
            << "unregistered" << std::endl;
          ++ret;
        }
      else
        {
          DDSX11_TEST_DEBUG
            << "OK - Deleted type <" << type2 << "> for DP1 could not be "
            << "unregistered" << std::endl;
        }

      /// Unregister the type and domain participant which should be removed by 'close'
      if (::DDSX11::DDS_TypeSupport_i::unregister_type (dp1, type3))
        {
          DDSX11_TEST_ERROR
            << "ERROR - Deleted type <" << type3 << "> for DP1 could be "
            << "unregistered" << std::endl;
          ++ret;
        }
      else
        {
          DDSX11_TEST_DEBUG
            << "OK - Deleted type <" << type3 << "> for DP1 could not be "
            << "unregistered" << std::endl;
        }

      /// No need to remove f1, f2, and f3 since ::close will remove them.
      pf->delete_participant(dp1);
      pf->delete_participant(dp2);

      pf->finalize_instance ();
    }
  catch (const ::CORBA::Exception& e)
    {
      DDSX11_TEST_ERROR
        << "ACE_TMAIN - Caught unexpected CORBA exception : " << e << std::endl;
      return 1;
    }
  catch (...)
    {
      DDSX11_TEST_ERROR
         << "ACE_TMAIN - ERROR: Caught unexpected exception" << std::endl;
      return 1;
    }
  if (ret == 0)
    {
      DDSX11_TEST_DEBUG << "Test passed !" << std::endl;
    }
  else
    {
      DDSX11_TEST_ERROR << ret << " errors found during test !" << std::endl;
    }
  return ret;
}
