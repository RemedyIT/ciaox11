// -*- C++ -*-
/**
 * @file    dds_type_support.h
 * @author  Marcel Smit
 *
 * @brief   Registration of types and creation of type specific datareaders and
 *          datawriters.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDSX11_IMPL_TYPE_SUPPORT_H_
#define DDSX11_IMPL_TYPE_SUPPORT_H_

#include "dds/dds_export.h"
#include "dds/dds_common.h"
#include "dds/dds_data_writer_t.h"
#include "dds/dds_data_reader_t.h"
#include "dds/dds_traits.h"

#include "dds/dds_proxy_entity_manager.h"

#include <map>

namespace DDSX11
{
  class DDSX11_IMPL_Export DDS_TypeFactory_i
  {
  public:
    DDS_TypeFactory_i () = default;
    virtual ~DDS_TypeFactory_i ();

    virtual IDL::traits< ::DDS::DataWriter >::ref_type
    create_datawriter (DDS_Native::DDS::DataWriter* dw) = 0;

    virtual IDL::traits< ::DDS::DataReader >::ref_type
    create_datareader (DDS_Native::DDS::DataReader* dr) = 0;
  };

  /**
    * Helper class to administrate the type factory and how many times
    * it has been registered
    */
  class DDS_TypeFactory_i_ref
  {
    public:
      DDS_TypeFactory_i_ref (std::shared_ptr<DDS_TypeFactory_i> tf);
      ~DDS_TypeFactory_i_ref () = default;

      std::shared_ptr<DDS_TypeFactory_i> get_factory ();

      /**
        * Increments the reference count
        */
      uint32_t _inc_ref ();
      /**
        * Decrements the reference count
        */
      uint32_t _dec_ref ();

    private:
      uint32_t ref_count_ { 1 };
      std::shared_ptr<DDS_TypeFactory_i> tf_;
  };

  template <typename TOPIC_TYPE, typename TOPIC_SEQ_TYPE, typename NATIVE_SEQ_TYPE, typename NATIVE_DATAREADER_TYPE, typename NATIVE_DATAWRITER_TYPE>
  class DDS_TypeFactory_T final
    : public DDS_TypeFactory_i
  {
  public:
    virtual IDL::traits< ::DDS::DataWriter >::ref_type
    create_datawriter (DDS_Native::DDS::DataWriter *dw) override
    {
      typedef DDSX11::DataWriter_T<
          TOPIC_TYPE,
          NATIVE_DATAWRITER_TYPE,
          typename ::DDS::traits<TOPIC_TYPE>::datawriter_type>
        DataWriter_type;
      auto proxy = TAOX11_CORBA::make_reference<DataWriter_type>(dw);
      return proxy;
    }

    virtual IDL::traits< ::DDS::DataReader >::ref_type
    create_datareader (DDS_Native::DDS::DataReader *dr) override
    {
      typedef DDSX11::DataReader_T<
          NATIVE_DATAREADER_TYPE,
          typename ::DDS::traits<TOPIC_TYPE>::datareader_type,
          TOPIC_TYPE,
          TOPIC_SEQ_TYPE,
          NATIVE_SEQ_TYPE>
        DataReader_type;
      auto proxy = TAOX11_CORBA::make_reference<DataReader_type> (dr);
      return proxy;
    }
  };

  class DDSX11_IMPL_Export DDS_TypeSupport_i final
  {
  public:
    /**
      * Clears all internal maps, freeing the memory.
      */
    static void
    close ();

    /**
      * Registering a type-factory combination per DomainParticipant.
      * @retval false Insertions to one of the maps fails or if there's
      * already a factory for the given type registered.
      * @retval true This is the first time this type has been registered
      * and the caller can register the type to the DDS vendor
      */
    static bool
    register_type (
      IDL::traits< ::DDS::DomainParticipant >::ref_type dp,
      const std::string & type,
      const std::shared_ptr<DDS_TypeFactory_i> &factory);

    /**
      * Unregistering a type-factory combination for a specific
      * DomainParticipant. At the moment the type factory isn't used anymore
      * it is automatically destructed.
      * @retval false Unregistering the type factory failed or it is still in
      * use
      * @retval true Unregistering the type factory succeeded and the type is
      * not used anymore, the caller can unregister it from the DDS vendor
      */
    static bool
    unregister_type (
      IDL::traits< ::DDS::DomainParticipant >::ref_type dp,
      const std::string &type);

    /**
      * Create a type specific datawriter
      */
    static IDL::traits< ::DDS::DataWriter >::ref_type
    create_datawriter (
      IDL::traits< ::DDS::DomainParticipant >::ref_type dp,
      const std::string& type_name,
      DDS_Native::DDS::DataWriter* dw);
    /**
      * Create a type specific datareader
      */
    static IDL::traits< ::DDS::DataReader >::ref_type
    create_datareader (
      IDL::traits< ::DDS::DomainParticipant >::ref_type dp,
      const std::string& type_name,
      DDS_Native::DDS::DataReader* dr);

  private:
    DDS_TypeSupport_i () = default;
    ~DDS_TypeSupport_i () = default;

    /// Store for a specific DDS type a type factory var with its own refcount
    typedef std::map <
      std::string,
      std::unique_ptr<DDS_TypeFactory_i_ref>> typefactories;

    /// For each domain participant we store a map with type factories for the
    /// types that participant has
#if (DDSX11_NDDS==1)
    typedef ::DDS::octet_value instance_handle_type;
#else
    typedef int32_t instance_handle_type;
#endif
    typedef std::map<instance_handle_type, typefactories> participantfactories;

    static participantfactories participant_factories;

    /**
      * Searches for a TypeFactory, based on a type and DomainParticipant
      */
    static std::shared_ptr<DDS_TypeFactory_i> get_factory_i (
      IDL::traits< ::DDS::DomainParticipant >::ref_type dp,
      const std::string &type);
  };
}

#endif /* DDSX11_IMPL_TYPE_SUPPORT_H_ */
