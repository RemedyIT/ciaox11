/**
 * @file   log_backend.h
 * @author Johnny Willemsen
 *
 * @brief  A logging backend which puts ACE logging messages onto DDS
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#ifndef DAnCE_LOG_BACKEND_H
#define DAnCE_LOG_BACKEND_H

#include "ace/Log_Msg_Backend.h"
#include "ace/Service_Object.h"

#include "log_backend_export.h"
#include "log_record_dds_typesupport.h"
#include <string>

namespace DAnCE
{
  /**
   * @class ddsx11_log_backend
   * @brief Provides a logging backend that transmits records over DDS/.
   */
  class DNCX11_LOG_BACKEND_Export ddsx11_log_backend :
    public virtual ACE_Log_Msg_Backend,
    public virtual ACE_Service_Object
  {
  public:
    ddsx11_log_backend () = default;

    ~ddsx11_log_backend () override;

    // Methods from ACE_Log_Msg_Backend
    int open (const ACE_TCHAR *logger_key) override;

    int reset () override;

    int close () override;

    ssize_t log (ACE_Log_Record  &log_record) override;

    // Methods from ACE_Service_Object
    int init (int argc, ACE_TCHAR **argv) override;

    int fini () override;

    int info (ACE_TCHAR **str, size_t len) const override;

  private:
    /// Helper method to check our supported environment
    /// variables
    void get_configuration ();

    /// Helper method to setup DDSX11
    /// @retval true Setup successful
    /// @retval false Setup failed
    bool configure_dds ();

    std::string topic_name_;
    std::string node_;
    std::string qos_profile_;

    DDS::DomainId_t domain_{};

    ACE_Log_Msg_Backend * old_log_msg_backend_ {};

    DDS::traits<DnCX11::Log_Record>::domainparticipant_ref_type participant_;
    DDS::traits<DnCX11::Log_Record>::topic_ref_type topic_;
    DDS::traits<DnCX11::Log_Record>::publisher_ref_type publisher_;
    DDS::traits<DnCX11::Log_Record>::datawriter_ref_type datawriter_;
    DDS::traits<DnCX11::Log_Record>::typed_datawriter_ref_type log_record_writer_;
  };

  ACE_FACTORY_DECLARE (DNCX11_LOG_BACKEND, ddsx11_log_backend);
}

#endif
