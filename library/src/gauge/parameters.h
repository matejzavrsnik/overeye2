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
   set (
      const std::string& tag,
      const std::string& value
   );

   bool
   make_user_facing (
      const std::string& tag,
      const std::string& nice_name
   );

   void
   make_internal (
      const std::string& tag
   );

   bool
   set_value(
      const std::string& tag,
      const std::string& value
   );

   std::optional<std::string>
   get_value(
      const std::string &tag
   );

   std::optional<std::string>
   get_nice_name (
      const std::string& tag
   );

   std::map<std::string, std::string>
   get_all_user_facing();

};

}
