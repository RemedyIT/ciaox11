/**
 * @file   ciaox11_exf_util.cpp
 * @author Martin Corino
 *
 * @brief Utility methods for the Axcioma execution framework.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#include "exf/deployment/core/ciaox11_exf_util.h"

#include <locale>
#include <sstream>
#include "exf/deployment/logger/log.h"

namespace CIAOX11
{
  namespace ExF
  {
    namespace Util
    {
      static const uint32_t sec_ns = 1000000000u;
      static const uint32_t sec_us = 1000000u;
      static const uint32_t sec_ms = 1000u;
      static const uint32_t usec_ns = 1000u;
      static const uint32_t msec_us = 1000u;

      static ExF::DeadlineType
      exf_string_to_deadline_type (const std::string& type)
      {
        if (type == ExF::SCHEDULING_DEADLINE_EXPIRE)
        {
          return ExF::DeadlineType::DLT_EXPIRE;
        }
        if (type == ExF::SCHEDULING_DEADLINE_SOFT)
        {
          return ExF::DeadlineType::DLT_SOFT;
        }
        if (type == ExF::SCHEDULING_DEADLINE_HARD)
        {
          return ExF::DeadlineType::DLT_HARD;
        }
        CIAOX11_EXF_LOG_ERROR ("ExF::Util::exf_string_to_deadline_type - " <<
                           "unknown deadline type '" << type << "'");
        return ExF::DeadlineType::DLT_NONE;
      }

      static ACE_Time_Value
      exf_string_to_deadline_time (const std::string& time_spec)
      {
        std::string time { time_spec };
        std::string units { "ns" };
        std::string::size_type pos { 0 };
        for (; pos < time.size () && std::isdigit (time[pos], std::locale ()) ;++pos);
        if (pos < time.size ())
        {
          units = time.substr (pos);
          time = time.substr(0, pos);
        }
        uint32_t number;
        std::istringstream is (time);
        is >> std::dec >> number;
        time_t sec {};
        suseconds_t usec {};
        if (units == "ns")
        {
          if (number >= sec_ns)
          {
            sec = number / sec_ns;
            number %= sec_ns;
          }
          usec = number / usec_ns;
        }
        else if (units == "us")
        {
          if (number >= sec_us)
          {
            sec = number / sec_us;
            number %= sec_us;
          }
          usec = number;
        }
        else if (units == "ms")
        {
          if (number >= sec_ms)
          {
            sec = number / sec_ms;
            number %= sec_ms;
          }
          usec = number * msec_us;
        }
        else if (units == "s")
        {
          sec = number;
        }
        else if (units == "m")
        {
          sec = number * 60;
        }
        else if (units == "h")
        {
          sec = number * 60 * 60;
        }
        return ACE_Time_Value (sec, usec);
      }

      bool get_exf_defaults (
          const Components::ConfigValues& config,
          ExF::Priority& prio,
          ExF::Deadline& deadline)
      {
        bool rc = false;
        for (const Components::ConfigValue& cval : config)
        {
          if (cval.name () == ExF::SCHEDULING_PRIORITY)
          {
            if (!(cval.value () >>= prio))
            {
              CIAOX11_EXF_LOG_ERROR ("ExF::Util::get_exf_defaults - " <<
                                 "failed to extract " << ExF::SCHEDULING_PRIORITY);
            }
            else
            {
              CIAOX11_EXF_LOG_DEBUG ("ExF::Util::get_exf_defaults - " <<
                                 "found " << ExF::SCHEDULING_PRIORITY <<
                                 " : " << prio);

              rc = true;
            }
          }
          else if (cval.name () == ExF::SCHEDULING_DEADLINE_TYPE)
          {
            std::string type;
            if (!(cval.value () >>= type))
            {
              CIAOX11_EXF_LOG_ERROR ("ExF::Util::get_exf_defaults - " <<
                                 "failed to extract " << ExF::SCHEDULING_DEADLINE_TYPE);
            }
            else
            {
              CIAOX11_EXF_LOG_DEBUG ("ExF::Util::get_exf_defaults - " <<
                                 "found " << ExF::SCHEDULING_DEADLINE_TYPE <<
                                 " : " << type);

              deadline.deadline_type_ = exf_string_to_deadline_type (type);
              rc = true;
            }
          }
          else if (cval.name () == ExF::SCHEDULING_DEADLINE_TIME)
          {
            std::string time;
            if (!(cval.value () >>= time))
            {
              CIAOX11_EXF_LOG_ERROR ("ExF::Util::get_exf_defaults - " <<
                                 "failed to extract " << ExF::SCHEDULING_DEADLINE_TIME);
            }
            else
            {
              CIAOX11_EXF_LOG_DEBUG ("ExF::Util::get_exf_defaults - " <<
                                 "found " << ExF::SCHEDULING_DEADLINE_TIME <<
                                 " : " << time);

              deadline.deadline_time_ = exf_string_to_deadline_time (time);
              rc = true;
            }
          }
        }
        return rc;
      }

      void get_exf_settings (
          const Components::ConfigValues& config,
          const std::string& event,
          ExF::Priority& prio,
          ExF::Deadline& deadline)
      {
        for (const Components::ConfigValue& cval : config)
        {
          if ( cval.name () == (ExF::SCHEDULING_PRIORITY + "." + event))
          {
            if (!(cval.value () >>= prio))
            {
              CIAOX11_EXF_LOG_ERROR ("ExF::Util::get_exf_settings - " <<
                                 "failed to extract " << ExF::SCHEDULING_PRIORITY <<
                                 " for " << event);
            }
            else
            {
              CIAOX11_EXF_LOG_DEBUG ("ExF::Util::get_exf_settings - " <<
                                 "found " << ExF::SCHEDULING_PRIORITY <<
                                 " for " << event << " : " << prio);
            }
          }
          else if ( cval.name () == (ExF::SCHEDULING_DEADLINE_TYPE + "." + event))
          {
            std::string type;
            if (!(cval.value () >>= type))
            {
              CIAOX11_EXF_LOG_ERROR ("ExF::Util::get_exf_settings - " <<
                                 "failed to extract " << ExF::SCHEDULING_DEADLINE_TYPE <<
                                 " for " << event);
            }
            else
            {
              CIAOX11_EXF_LOG_DEBUG ("ExF::Util::get_exf_settings - " <<
                                 "found " << ExF::SCHEDULING_DEADLINE_TYPE <<
                                 " for " << event << " : " << type);

              deadline.deadline_type_ = exf_string_to_deadline_type (type);
            }
          }
          else if ( cval.name () == (ExF::SCHEDULING_DEADLINE_TIME + "." + event))
          {
            std::string time;
            if (!(cval.value () >>= time))
            {
              CIAOX11_EXF_LOG_ERROR ("ExF::Util::get_exf_settings - " <<
                                 "failed to extract " << ExF::SCHEDULING_DEADLINE_TIME <<
                                 " for " << event);
            }
            else
            {
              CIAOX11_EXF_LOG_DEBUG ("ExF::Util::get_exf_settings - " <<
                                 "found " << ExF::SCHEDULING_DEADLINE_TIME <<
                                 " for " << event << " : " << time);

              deadline.deadline_time_ = exf_string_to_deadline_time (time);
            }
          }
        }
      }
    }
  }
};
