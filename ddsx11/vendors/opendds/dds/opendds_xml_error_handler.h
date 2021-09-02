/**
 * @file    opendds_xml_error_handler.h
 * @author  Johnny Willemsen
 *
 * @brief  DDSX11 version  error handler for Xerces
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef DDSX11_XML_ERROR_HANDLER_H
#define DDSX11_XML_ERROR_HANDLER_H

#pragma once

#include "dds/dds_export.h"
#include <ace/XML_Utils/XML_Error_Handler.h>

namespace DDSX11
{
  /**
    * @class DDSX11_XML_Error_Hander
    *
    * @brief DDSX11 error handler for XERCES
    *
    */
  class DDSX11_IMPL_Export DDSX11_XML_Error_Handler final
#if ACE_VERSION_CODE <= 0x70003
    : public xercesc::ErrorHandler
#else
    : public XML::XML_Error_Handler
#endif
  {
  public:
    DDSX11_XML_Error_Handler () = default;
    ~DDSX11_XML_Error_Handler () override = default;

    void warning(const xercesc::SAXParseException& toCatch) override;
    void error(const xercesc::SAXParseException& toCatch) override;
    void fatalError(const xercesc::SAXParseException& toCatch) override;
#if ACE_VERSION_CODE <= 0x70003
    void resetErrors() override;
    bool getErrors () const;
#endif
  private :
    DDSX11_XML_Error_Handler (const DDSX11_XML_Error_Handler&) = delete;
    DDSX11_XML_Error_Handler& operator= (const DDSX11_XML_Error_Handler&) = delete;
    DDSX11_XML_Error_Handler (DDSX11_XML_Error_Handler&&) = delete;
    DDSX11_XML_Error_Handler& operator= (DDSX11_XML_Error_Handler&&) = delete;
#if ACE_VERSION_CODE <= 0x70003
    bool errors_ {};
#endif
  };
}

#endif /* DDSX11_XML_ERROR_HANDLER_H */
