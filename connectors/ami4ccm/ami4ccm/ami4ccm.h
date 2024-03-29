/**
 * @file    ami4ccm.h
 * @author  Marijke Hengstmengel
 *
 * @brief Header file AMI4CCM ExceptionHolder
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#ifndef CIAO_AMI4CCM_H
#define CIAO_AMI4CCM_H

#include "connectors/ami4ccm/ami4ccm/ami4ccmC.h"
#include "tao/x11/object.h"
#include "tao/x11/portable_server/portableserver.h"
#include "tao/x11/messaging/messaging.h"
#include "ccm/session/ccm_sessioncontextC.h"
#include "connectors/ami4ccm/ami4ccm/ami4ccm_impl_export.h"

namespace CCM_AMI
{
  class AMI4CCM_IMPL_Export ExceptionHolder_i final
  : public virtual IDL::traits<::CCM_AMI::ExceptionHolder>::base_type
  {
  public:
    explicit ExceptionHolder_i (IDL::traits<::Messaging::ExceptionHolder>::ref_type excep_holder);

    ~ExceptionHolder_i () override = default;

    /// Rethrow the original exception
    void raise_exception () override;

  private:
    IDL::traits<::Messaging::ExceptionHolder>::ref_type holder_;

    ExceptionHolder_i() = delete;
    ExceptionHolder_i(const ExceptionHolder_i&) = delete;
    ExceptionHolder_i(ExceptionHolder_i&&) = delete;
    ExceptionHolder_i& operator=(const ExceptionHolder_i&) = delete;
    ExceptionHolder_i& operator=(ExceptionHolder_i&&) = delete;
  };

  /// Helper method for AMI4CCM connectors
  AMI4CCM_IMPL_Export
  IDL::traits<PortableServer::POA>::ref_type
  get_ami_POA (IDL::traits<Components::SessionContext>::ref_type context);
}

#endif /* CIAO_AMI4CCM_H */
