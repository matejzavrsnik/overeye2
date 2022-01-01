#pragma once

#include "extended_setting.h"

#include <string>
#include <vector>
#include <optional>
#include <map>

namespace gauge
{

/**
 * @brief Interface to gauge parameters that user is allowed to control.
 * @details The audience for this i_gauge is the dialog that displays gauge configuration to the user.
 */
class i_user_parameters
{

public:

   virtual std::optional<std::string>
   user_setting_get_name (
      const std::string& tag
   ) = 0;

   virtual bool
   user_setting_set (
      const std::string& tag,
      const std::string& value
   ) = 0;

   virtual std::map<std::string, std::string>
   user_setting_get_all () = 0;

   virtual
   ~i_user_parameters () {}

};

}
