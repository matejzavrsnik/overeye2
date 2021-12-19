#pragma once

#include "basic_setting.h"
#include "extended_setting.h"
#include "i_user_parameters.h"

#include <string>
#include <vector>
#include <optional>

/**
 * @brief Interface to everything related to gauge parameters.
 * @details The audience for this i_gauge is the gauge itself and it needs access to everything about configuration.
 */
class i_gauge_parameters
{

public:

   virtual void
   set_or_add_user_setting (
      const std::wstring& tag,
      const std::wstring& value,
      const std::wstring& name
   ) = 0;

   virtual void
   set_or_add_internal_setting (
      const std::wstring& tag,
      const std::wstring& value
   ) = 0;

   virtual bool
   set(
      const std::wstring& tag,
      const std::wstring& value
   ) = 0;

   virtual std::optional<std::wstring>
   get_value(
      const std::wstring& tag
   ) = 0;

   virtual std::vector<gauge::basic_setting>
   get_all() = 0;

   virtual
   ~i_gauge_parameters () {}
};
