/**
 * @file    opendds_xml_error_handler.cpp
 * @author  Johnny Willemsen
 *
 * @brief  DDSX11 version  error handler for Xerces
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#include "dds/opendds_xml_error_handler.h"
#include <xercesc/util/XMLString.hpp>
#include <xercesc/dom/DOMLocator.hpp>
#include <xercesc/sax/SAXParseException.hpp>
#include "ace/XML_Utils/XercesString.h"
#include "ddsx11/logger/ddsx11_log.h"

namespace DDSX11
{
  void DDSX11_XML_Error_Handler::warning(const xercesc::SAXParseException& toCatch)
  {
    XML::XStr file(toCatch.getSystemId ());
    XML::XStr msg (toCatch.getMessage ());

    DDSX11_IMPL_LOG_DEBUG ("Warning: " << file << ':' << toCatch.getLineNumber ()
                      << ':' << toCatch.getColumnNumber () << " - "
                      << msg);
  }

  void DDSX11_XML_Error_Handler::error(const xercesc::SAXParseException& toCatch)
  {
    XML::XStr file (toCatch.getSystemId ());
    XML::XStr msg (toCatch.getMessage ());

    DDSX11_IMPL_LOG_ERROR ("Error: " << file << ':' << toCatch.getLineNumber ()
                      << ':' << toCatch.getColumnNumber () << " - "
                      << msg);

    this->errors_ = true;
  }

  void DDSX11_XML_Error_Handler::fatalError(const xercesc::SAXParseException& toCatch)
  {
    XML::XStr file (toCatch.getSystemId ());
    XML::XStr msg (toCatch.getMessage ());

    DDSX11_IMPL_LOG_PANIC ("Fatal Error: " << file << ':' << toCatch.getLineNumber ()
                  << ':' << toCatch.getColumnNumber () << " - "
                  << msg);

    this->errors_ = true;
  }

#if ACE_VERSION_CODE <= 0x70003
  void DDSX11_XML_Error_Handler::resetErrors()
  {
    this->errors_ = false;
  }

  bool DDSX11_XML_Error_Handler::getErrors () const
  {
    return this->errors_;
  }
#endif
}
