#pragma once

#include <string>
#include <vector>
#include <optional>
#include <map>

namespace gauge
{

/**
 * @brief A collection of gauges parameters.
 */
class parameters
{

private:

   // A collection of all settings for the gauge in tag / value mapping
   std::map<std::string /*tag*/, std::string /*value*/> m_settings;

   // Settings that are user facing in config dialog need nice names to
   // present to user. This is a map between settings tags and nice names.
   // At the same time, membership in this collection implies a user facing
   // setting.
   std::map<std::string /*tag*/, std::string /*nice name*/> m_nice_names;

public:

   parameters () = default;
   virtual ~parameters () = default;

   void
   set_or_add_user_setting (
      const std::string& tag,
      const std::string& value,
      const std::string& name
   );

   void
   set_or_add_internal_setting(
      const std::string& tag,
      const std::string& value
   );

   bool
   set_value(
      const std::string& tag,
      const std::string& value
   );

   bool
   user_setting_set (
      const std::string& tag,
      const std::string& value
   );

   std::optional<std::string>
   get_value(const std::string &tag);

   std::optional<std::string>
   user_setting_get_name (
      const std::string& tag
   );

   std::map<std::string, std::string>
   user_setting_get_all();

};

}
