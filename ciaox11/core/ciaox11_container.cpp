/**
 * @file    ciaox11_container.cpp
 * @author  Martin Corino
 *
 * @brief   Base class for CIAOX11 container implementation(s).
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#include "ciaox11/core/ciaox11_container.h"

namespace CIAOX11
{
    Container::Container (std::string name)
     : name_ (name)
    {
      this->service_registry_ = CORBA::make_reference<CIAOX11::Service_Registry_i> ();
    }

    Container::~Container ()
    {}
}
