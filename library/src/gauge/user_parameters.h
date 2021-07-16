#pragma once

#include "basic_setting.h"
#include "extended_setting.h"

#include <string>
#include <vector>
#include <optional>

namespace gauge
{

// audience: visual control that needs to display settings and also set them according to user changes
class user_parameters
{

public:

   virtual std::optional<std::wstring>
   user_setting_get_name (
      const std::wstring& tag
   ) = 0;

   virtual bool
   user_setting_set (
      const gauge::basic_setting& setting
   ) = 0;

   virtual std::vector<gauge::basic_setting>
   user_setting_get_all () = 0;

};

}
