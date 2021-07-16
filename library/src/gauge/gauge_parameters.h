#pragma once

#include "basic_setting.h"
#include "extended_setting.h"
#include "user_parameters.h"

#include <string>
#include <vector>
#include <optional>

// audience: gauge needs to control of everything about the settings
class gauge_parameters
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

};
