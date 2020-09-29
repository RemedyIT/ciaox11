/**
 * @file    nontopic_connector_t.cpp
 * @author  Marijke Hengstmengel
 *
 * @brief   CIAOX11 templated connector template
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#include "ciaox11/testlib/ciaox11_testlog.h"

template <typename CCM_TYPE,
          typename T,
          typename U,
          typename Tseq,
          typename Useq>
NT_Connector_T<CCM_TYPE, T, U, Tseq, Useq>::~NT_Connector_T ()
{
}

template <typename CCM_TYPE,
          typename T,
          typename U,
          typename Tseq,
          typename Useq>
void
NT_Connector_T<CCM_TYPE, T, U, Tseq, Useq>::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type /* ctx*/)
{
  CIAOX11_TEST_INFO << "NT_Connector_T::set_session_context" << std::endl;
}

template <typename CCM_TYPE,
          typename T,
          typename U,
          typename Tseq,
          typename Useq>
void
NT_Connector_T<CCM_TYPE, T, U, Tseq, Useq>::configuration_complete ()
{
  CIAOX11_TEST_INFO << "NT_Connector_T::configuration_complete" << std::endl;
}

template <typename CCM_TYPE,
          typename T,
          typename U,
          typename Tseq,
          typename Useq>
void
NT_Connector_T<CCM_TYPE, T, U, Tseq, Useq>::ccm_remove ()
{
  CIAOX11_TEST_INFO << "NT_Connector_T::ccm_remove" << std::endl;
}

template <typename CCM_TYPE,
          typename T,
          typename U,
          typename Tseq,
          typename Useq>
void
NT_Connector_T<CCM_TYPE, T, U, Tseq, Useq>::ccm_activate ()
{
  CIAOX11_TEST_INFO << "NT_Connector_T::ccm_activate" << std::endl;
}

template <typename CCM_TYPE,
          typename T,
          typename U,
          typename Tseq,
          typename Useq>
void
NT_Connector_T<CCM_TYPE, T, U, Tseq, Useq>::ccm_passivate ()
{
  CIAOX11_TEST_INFO << "NT_Connector_T::ccm_passivate" << std::endl;
}

template <typename CCM_TYPE,
          typename T,
          typename U,
          typename Tseq,
          typename Useq>
NT2_Connector_T<CCM_TYPE, T, U, Tseq, Useq>::NT2_Connector_T ()
{
}

template <typename CCM_TYPE,
          typename T,
          typename U,
          typename Tseq,
          typename Useq>
NT2_Connector_T<CCM_TYPE, T, U, Tseq, Useq>::~NT2_Connector_T ()
{
}

template <typename CCM_TYPE,
          typename T,
          typename U,
          typename Tseq,
          typename Useq>
typename IDL::traits<typename CCM_TYPE::write_port_traits::foo2_type>::ref_type
NT2_Connector_T<CCM_TYPE, T, U, Tseq, Useq>::get_write_port_foo2()
{
  return {};
}

template <typename CCM_TYPE,
          typename T,
          typename U,
          typename Tseq,
          typename Useq>
typename CCM_TYPE::write_port_traits::port_attrib_type
NT2_Connector_T<CCM_TYPE, T, U, Tseq, Useq>::write_port_port_attrib()
{
  return {};
}

template <typename CCM_TYPE,
          typename T,
          typename U,
          typename Tseq,
          typename Useq>
void
NT2_Connector_T<CCM_TYPE, T, U, Tseq, Useq>::write_port_port_attrib(
    const typename CCM_TYPE::write_port_traits::port_attrib_type& /*_v*/)
{
}

template <typename CCM_TYPE,
          typename T,
          typename U,
          typename Tseq,
          typename Useq>
int16_t
NT2_Connector_T<CCM_TYPE, T, U, Tseq, Useq>::conn_attrib()
{
  return {};
}

template <typename CCM_TYPE,
          typename T,
          typename U,
          typename Tseq,
          typename Useq>
void
NT2_Connector_T<CCM_TYPE, T, U, Tseq, Useq>::conn_attrib(int16_t /*_v*/)
{
}

template <typename CCM_TYPE,
          typename T,
          typename U,
          typename Tseq,
          typename Useq>
typename CCM_TYPE::NT2_attrib_type
NT2_Connector_T<CCM_TYPE, T, U, Tseq, Useq>::NT2_attrib()
{
  return {};
}

template <typename CCM_TYPE,
          typename T,
          typename U,
          typename Tseq,
          typename Useq>
void
NT2_Connector_T<CCM_TYPE, T, U, Tseq, Useq>::NT2_attrib(const typename CCM_TYPE::NT2_attrib_type& /*_v*/)
{
}

template <typename CCM_TYPE,
          typename T,
          typename U,
          typename Tseq,
          typename Useq>
void
NT2_Connector_T<CCM_TYPE, T, U, Tseq, Useq>::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type /* ctx*/)
{
  CIAOX11_TEST_INFO << "NT2_Connector_T::set_session_context" << std::endl;
}

template <typename CCM_TYPE,
          typename T,
          typename U,
          typename Tseq,
          typename Useq>
void
NT2_Connector_T<CCM_TYPE, T, U, Tseq, Useq>::configuration_complete ()
{
  CIAOX11_TEST_INFO << "NT2_Connector_T::configuration_complete" << std::endl;
}

template <typename CCM_TYPE,
          typename T,
          typename U,
          typename Tseq,
          typename Useq>
void
NT2_Connector_T<CCM_TYPE, T, U, Tseq, Useq>::ccm_remove ()
{
  CIAOX11_TEST_INFO << "NT2_Connector_T::ccm_remove" << std::endl;
}

template <typename CCM_TYPE,
          typename T,
          typename U,
          typename Tseq,
          typename Useq>
void
NT2_Connector_T<CCM_TYPE, T, U, Tseq, Useq>::ccm_activate ()
{
  CIAOX11_TEST_INFO << "NT2_Connector_T::ccm_activate" << std::endl;
}

template <typename CCM_TYPE,
          typename T,
          typename U,
          typename Tseq,
          typename Useq>
void
NT2_Connector_T<CCM_TYPE, T, U, Tseq, Useq>::ccm_passivate ()
{
  CIAOX11_TEST_INFO << "NT2_Connector_T::ccm_passivate" << std::endl;
}

template <typename CCM_TYPE,
          typename T,
          typename U,
          typename Tseq,
          typename Useq>
void
NT3_Connector_T<CCM_TYPE, T, U, Tseq, Useq>::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type /* ctx*/)
{
  CIAOX11_TEST_INFO << "NT3_Connector_T::set_session_context" << std::endl;
}

template <typename CCM_TYPE,
          typename T,
          typename U,
          typename Tseq,
          typename Useq>
void
NT3_Connector_T<CCM_TYPE, T, U, Tseq, Useq>::configuration_complete ()
{
  CIAOX11_TEST_INFO << "NT3_Connector_T::configuration_complete" << std::endl;
}

template <typename CCM_TYPE,
          typename T,
          typename U,
          typename Tseq,
          typename Useq>
void
NT3_Connector_T<CCM_TYPE, T, U, Tseq, Useq>::ccm_remove ()
{
  CIAOX11_TEST_INFO << "NT3_Connector_T::ccm_remove" << std::endl;
}

template <typename CCM_TYPE,
          typename T,
          typename U,
          typename Tseq,
          typename Useq>
void
NT3_Connector_T<CCM_TYPE, T, U, Tseq, Useq>::ccm_activate ()
{
  CIAOX11_TEST_INFO << "NT3_Connector_T::ccm_activate" << std::endl;
}

template <typename CCM_TYPE,
          typename T,
          typename U,
          typename Tseq,
          typename Useq>
void
NT3_Connector_T<CCM_TYPE, T, U, Tseq, Useq>::ccm_passivate ()
{
  CIAOX11_TEST_INFO << "NT3_Connector_T::ccm_passivate" << std::endl;
}

template <typename CCM_TYPE,
          typename T,
          typename U,
          typename Tseq,
          typename Useq>
typename CCM_TYPE::NT3_attrib_type
NT3_Connector_T<CCM_TYPE, T, U, Tseq, Useq>::NT3_attrib()
{
  return {};
}

template <typename CCM_TYPE,
          typename T,
          typename U,
          typename Tseq,
          typename Useq>
void
NT3_Connector_T<CCM_TYPE, T, U, Tseq, Useq>::NT3_attrib(const typename CCM_TYPE::NT3_attrib_type& /*_v*/)
{
}

template <typename CCM_TYPE,
          typename T,
          typename U,
          typename Tseq,
          typename Useq>
typename IDL::traits<typename CCM_TYPE::foo3_type>::ref_type
NT3_Connector_T<CCM_TYPE, T, U, Tseq, Useq>::get_foo3()
{
  return {};
}

template <typename CCM_TYPE,
          typename T,
          typename U,
          typename Tseq,
          typename Useq>
typename IDL::traits<typename CCM_TYPE::write_port_traits::foo2_type>::ref_type
NT3_Connector_T<CCM_TYPE, T, U, Tseq, Useq>::get_foo5_foo2()
{
  return {};
}

template <typename CCM_TYPE,
          typename T,
          typename U,
          typename Tseq,
          typename Useq>
typename CCM_TYPE::foo5_traits::port_attrib_type
NT3_Connector_T<CCM_TYPE, T, U, Tseq, Useq>::foo5_port_attrib()
{
  return {};
}

template <typename CCM_TYPE,
          typename T,
          typename U,
          typename Tseq,
          typename Useq>
void
NT3_Connector_T<CCM_TYPE, T, U, Tseq, Useq>::foo5_port_attrib(
    const typename CCM_TYPE::foo5_traits::port_attrib_type& /*_v*/)
{
}

template <typename CCM_TYPE>
void
Bar_Connector_T<CCM_TYPE>::set_session_context (IDL::traits<Components::SessionContext>::ref_type /*ctx*/)
{
  CIAOX11_TEST_INFO << "Bar_Connector_T::set_session_context" << std::endl;
}

template <typename CCM_TYPE>
void
Bar_Connector_T<CCM_TYPE>::configuration_complete ()
{
  CIAOX11_TEST_INFO << "Bar_Connector_T::configuration_complete" << std::endl;
}

template <typename CCM_TYPE>
void
Bar_Connector_T<CCM_TYPE>::ccm_remove ()
{
  CIAOX11_TEST_INFO << "Bar_Connector_T::ccm_remove" << std::endl;
}

template <typename CCM_TYPE>
void
Bar_Connector_T<CCM_TYPE>::ccm_activate ()
{
  CIAOX11_TEST_INFO << "Bar_Connector_T::ccm_activate" << std::endl;
}

template <typename CCM_TYPE>
void
Bar_Connector_T<CCM_TYPE>::ccm_passivate ()
{
  CIAOX11_TEST_INFO << "Bar_Connector_T::ccm_passivate" << std::endl;
}

template <typename CCM_TYPE>
int16_t
Bar_Connector_T<CCM_TYPE>::foo ()
{
  return {};
}

template <typename CCM_TYPE>
void
Bar_Connector_T<CCM_TYPE>::foo (int16_t)
{
}
