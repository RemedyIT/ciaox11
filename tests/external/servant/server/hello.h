/**
 * @file    hello.h
 * @author  Martin Corino
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#ifndef HELLO_H
#define HELLO_H
#include /**/ "ace/pre.h"

#include "helloS.h"

/// Implement the Test::Hello interface
class Hello
  : public virtual CORBA::servant_traits<Test::Hello>::base_type
{
public:
  /// Constructor
  Hello (IDL::traits<CORBA::ORB>::ref_type orb);
  virtual ~Hello ();

  virtual
  std::string
  get_string (
      int32_t answer) override;

  virtual
  int16_t
  interface_attrib () override;

  virtual
  void
  interface_attrib (
      int16_t _v) override;

  virtual
  void
  shutdown () override;

private:
  /// Use an ORB reference to convert strings to objects and shutdown
  /// the application.
  IDL::traits<CORBA::ORB>::ref_type orb_;
  int16_t value_ {};
};

#include /**/ "ace/post.h"
#endif /* HELLO_H */
