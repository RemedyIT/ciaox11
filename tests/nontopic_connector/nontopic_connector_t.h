/**
 * @file    nontopic_connector_t.h
 * @author  Marijke Hengstmengel
 *
 * @brief   CIAOX11 templated connector templates
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#ifndef NT_CONNECTOR_T
#define NT_CONNECTOR_T


template <typename CCM_TYPE,
          typename T,
          typename U,
          typename Tseq,
          typename Useq>
class NT_Connector_T
: public virtual CCM_TYPE::base_type
{
public:
   NT_Connector_T () = default;
   virtual ~NT_Connector_T ();

   void set_session_context (IDL::traits<Components::SessionContext>::ref_type ctx) override;

   void configuration_complete () override;
   void ccm_remove () override;
   void ccm_activate () override;
   void ccm_passivate () override;

private:
   NT_Connector_T(const NT_Connector_T&) = delete;
   NT_Connector_T(NT_Connector_T&&) = delete;
   NT_Connector_T& operator=(const NT_Connector_T&) = delete;
   NT_Connector_T& operator=(NT_Connector_T&&) = delete;
};


template <typename CCM_TYPE,
          typename T,
          typename U,
          typename Tseq,
          typename Useq>
class NT2_Connector_T
: public virtual CCM_TYPE::base_type
{
public:
   NT2_Connector_T ();
   virtual ~NT2_Connector_T ();

   typename IDL::traits<typename CCM_TYPE::write_port_traits::foo2_type>::ref_type
   get_write_port_foo2 ()  override;

   typename CCM_TYPE::write_port_traits::port_attrib_type write_port_port_attrib()  override;
   void write_port_port_attrib(const typename CCM_TYPE::write_port_traits::port_attrib_type& _v)  override;

   int16_t conn_attrib() override;
   void conn_attrib(int16_t _v) override;

   typename CCM_TYPE::NT2_attrib_type NT2_attrib() override;
   void NT2_attrib(const typename CCM_TYPE::NT2_attrib_type& _v) override;

   void set_session_context (IDL::traits<Components::SessionContext>::ref_type ctx) override;

   void configuration_complete () override;
   void ccm_remove () override;
   void ccm_activate () override;
   void ccm_passivate () override;

private:
   NT2_Connector_T(const NT2_Connector_T&) = delete;
   NT2_Connector_T(NT2_Connector_T&&) = delete;
   NT2_Connector_T& operator=(const NT2_Connector_T&) = delete;
   NT2_Connector_T& operator=(NT2_Connector_T&&) = delete;
};

template <typename CCM_TYPE,
          typename T,
          typename U,
          typename Tseq,
          typename Useq>
class NT3_Connector_T
: public virtual NT2_Connector_T<CCM_TYPE, T, U, Tseq, Useq>
{
public:
  NT3_Connector_T () = default;
  virtual ~NT3_Connector_T () = default;
  typename CCM_TYPE::NT3_attrib_type NT3_attrib() override;
  void NT3_attrib(const typename CCM_TYPE::NT3_attrib_type& _v) override;

  typename IDL::traits<typename CCM_TYPE::foo3_type>::ref_type
  get_foo3 ()  override;

  typename IDL::traits<typename CCM_TYPE::write_port_traits::foo2_type>::ref_type
  get_foo5_foo2 ()  override;

  typename CCM_TYPE::foo5_traits::port_attrib_type foo5_port_attrib() override;
  void foo5_port_attrib(const typename CCM_TYPE::foo5_traits::port_attrib_type& _v)  override;

private:
  // Should be able to store a reference to a base type
  typename IDL::traits<typename CCM_TYPE::write_port_traits::foo2_type>::ref_type write_foo2_type_ref {};
  typename IDL::traits<typename CCM_TYPE::write_port_traits::foo3_type>::ref_type write_foo3_type_ref {};
  typename IDL::traits<typename CCM_TYPE::foo3_type>::ref_type foo3_type_ref {};
  typename IDL::traits<typename CCM_TYPE::foo_type>::ref_type foo_type_ref {};
  // Should be able to use attributes traits from the base and from our type
  typename CCM_TYPE::NT2_attrib_type NT2_attrib_ {};
  typename CCM_TYPE::NT3_attrib_type NT3_attrib_ {};

  NT3_Connector_T(const NT3_Connector_T&) = delete;
  NT3_Connector_T(NT3_Connector_T&&) = delete;
  NT3_Connector_T& operator=(const NT3_Connector_T&) = delete;
  NT3_Connector_T& operator=(NT3_Connector_T&&) = delete;
};

#include "nontopic_connector_t.cpp"

#endif
