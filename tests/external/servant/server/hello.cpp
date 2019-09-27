/**
 * @file    hello.cpp
 * @author  Martin Corino
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
#include "testlib/taox11_testlog.h"
#include "hello.h"

#include <sstream>

Hello::Hello (IDL::traits<CORBA::ORB>::ref_type orb)
  : orb_ (orb)
{
}

Hello::~Hello()
{
  TAOX11_TEST_INFO << "Hello::~Hello()" << std::endl;
}

std::string
Hello::get_string (int32_t answer)
{
  TAOX11_TEST_INFO << "Hello::get_string(" << answer << ")" << std::endl;
  std::ostringstream os;
  os << "Hello there! The answer = " << (answer * this->value_) << ".";
  return os.str ();
}

int16_t
Hello::interface_attrib ()
{
  return this->value_;
}

void
Hello::interface_attrib (int16_t _v)
{
  TAOX11_TEST_INFO << "Hello::interface_attrib(" << _v << ")" << std::endl;
  this->value_ = _v;
}

void
Hello::shutdown ()
{
  this->orb_->shutdown (false);
}
