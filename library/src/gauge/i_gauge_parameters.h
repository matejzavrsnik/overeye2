#pragma once

#include <string>
#include <map>
#include <optional>

namespace gauge
{

/**
 * @brief Interface to everything related to gauge parameters.
 * @details The audience for this i_gauge is the gauge itself and it needs access to everything about configuration.
 */
class i_gauge_parameters
{

public:

   virtual void
   set_or_add_user_setting (
      const std::string& tag,
      const std::string& value,
      const std::string& name
   ) = 0;

   virtual void
   set_or_add_internal_setting (
      const std::string& tag,
      const std::string& value
   ) = 0;

   virtual bool
   set_value (
      const std::string& tag,
      const std::string& value
   ) = 0;

   virtual std::optional<std::string>
   get_value (
      const std::string& tag
   ) = 0;

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
   ~i_gauge_parameters () {}
};

}