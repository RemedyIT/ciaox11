/**
 * @file    psdd4ccm_dynamic_loader.h
 * @author Martin Corino
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 * Chamber of commerce Rotterdam nr.276339, The Netherlands
 */
#ifndef PSDD4CCM_DYNAMIC_LOADER_H
#define PSDD4CCM_DYNAMIC_LOADER_H

#include "ace/DLL.h"

#include "psdd4ccm/logger/psdd4ccm_log.h"

#include <string>
#include <memory>
#include <stdexcept>

namespace PSDD
{
  class DL_Module;

  template <typename T, typename ...Args>
  class DL_Method
  {
  public:
    DL_Method () = default;
    DL_Method (const DL_Method&) = default;
    DL_Method (DL_Method&&) = default;
    ~DL_Method () = default;

    explicit operator bool() const // never throws
    { return this->dl_entrypt_ == 0 ? false : true; }
    bool operator ==(std::nullptr_t) const // never throws
    { return this->dl_entrypt_ == 0 ? true : false; }
    bool operator !=(std::nullptr_t) const // never throws
    { return this->dl_entrypt_ == 0 ? false : true; }

    T
    operator () (
        Args ...args)
    {
      if (!(*this))
        throw std::runtime_error (
            "PSDD::DL_Method::call on nil entrypoint");

      typedef T (*method_type) (Args ...);

      method_type method_ptr =
          reinterpret_cast<method_type> (this->dl_entrypt_);

      return method_ptr (std::forward<Args> (args)...);
    }

  private:
    friend class DL_Module;

    DL_Method (std::shared_ptr<ACE_DLL> dlmod,
               ptrdiff_t entrypoint)
    : dl_module_ (dlmod)
    , dl_entrypt_ (entrypoint)
    {}

    std::shared_ptr<ACE_DLL> dl_module_ {};
    ptrdiff_t dl_entrypt_ {};
  };

  class DL_Module final
  {
  public:
    DL_Module (std::string artifact,
               uint32_t openmode = ACE_DEFAULT_SHLIB_MODE)
      : dl_artifact_ (artifact),
        dl_openmode_ (openmode)
    {}
    ~DL_Module () = default;

    template <typename T, typename ...Args>
    DL_Method<T, Args...>
    resolve (
        std::string& status,
        const std::string& entrypoint)
    {
      if (this->open_i (status))
      {
        ptrdiff_t mptr = this->resolve_i (
            entrypoint, status);
        if (mptr)
        {
          return DL_Method<T, Args...> (
              this->dl_module_, mptr);
        }
      }
      return {};
    }

  protected:
    bool
    open_i (
        std::string& status)
    {
      if (this->dl_artifact_.empty ())
      {
        status += "PSDD::DL_Module: " \
            "Cannot dynamically load module for empty artifact name.";
      }
      else
      {
        if (this->dl_module_)
        {
          if (this->dl_module_->get_handle () != ACE_SHLIB_INVALID_HANDLE)
            return true;
        }

        try
        {
          this->dl_module_ = std::make_shared<ACE_DLL> ();

          PSDD4CCM_LOG_DEBUG ("PSDD::DL_Module::open_i - " <<
                              "loading artifact <" << this->dl_artifact_ << ">");

          if (this->dl_module_->open(this->dl_artifact_.c_str (), this->dl_openmode_, false) == 0)
          {
            PSDD4CCM_LOG_DEBUG ("PSDD::DL_Module::open_i - " <<
                                "artifact successfully loaded");
            return true;
          }
          else
          {

            status += "PSDD::DL_Module: Dynamic load of artifact <";
            status += this->dl_artifact_;
            status += "> failed : ";
            status += this->dl_module_->error ();
          }
        }
        catch (const std::bad_alloc&)
        {
          PSDD4CCM_LOG_ERROR ("PSDD::DL_Module::open_i - " <<
                              "no memory");
        }
      }
      return false;
    }

    ptrdiff_t
    resolve_i (
        const std::string& entrypoint,
        std::string& status)
    {
      PSDD4CCM_LOG_DEBUG ("PSDD::DL_Module::resolve_i - " <<
                          "resolving entrypoint <" << entrypoint <<
                          "> in artifact <" << this->dl_artifact_ << ">");

      void *void_ptr = this->dl_module_->symbol (entrypoint.c_str ());
      ptrdiff_t tmp_ptr = reinterpret_cast <ptrdiff_t> (void_ptr);
      if (tmp_ptr == 0)
      {
        status += "PSDD::DL_Module: Failed to resolve entrypoint <";
        status += entrypoint;
        status += "> in artifact <";
        status += this->dl_artifact_;
        status += "> : ";
        status += this->dl_module_->error ();
      }
      else
      {
        PSDD4CCM_LOG_DEBUG ("PSDD::DL_Module::resolve_i - " <<
                            "successfully resolved entrypoint");
      }
      return tmp_ptr;
    }

  private:
    friend class DL_MethodBase;

    std::string dl_artifact_ {};
    uint32_t dl_openmode_ {};
    std::shared_ptr<ACE_DLL> dl_module_ {};
  };

} /* namespace PSDD */

#endif /* PSDD4CCM_DYNAMIC_LOADER_H */
