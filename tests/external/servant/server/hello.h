/**
 * @file    hello.h
 * @author  Martin Corino
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#ifndef HELLO_H
#define HELLO_H

#include "helloS.h"

/// Implement the Test::Hello interface
class Hello
  : public virtual CORBA::servant_traits<Test::Hello>::base_type
{
public:
  /// Constructor
  Hello (IDL::traits<CORBA::ORB>::ref_type orb);
  virtual ~Hello ();

  std::string get_string (int32_t answer) override;

  int16_t interface_attrib () override;

  void interface_attrib (int16_t _v) override;

  void shutdown () override;

private:
  /// Use an ORB reference to convert strings to objects and shutdown
  /// the application.
  IDL::traits<CORBA::ORB>::ref_type orb_;
  int16_t value_ {};
};

#endif /* HELLO_H */
