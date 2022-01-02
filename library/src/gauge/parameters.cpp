#include "parameters.h"
#include "tools/get_if_exists.h"

namespace gauge
{
   parameters::parameters(
      const std::map<std::string, std::string>& settings
   ) :
      m_settings(settings)
   {
   }

   void
   parameters::set (
      const std::string& tag,
      const std::string& value
   )
   {
      m_settings[tag] = value;
   }

   bool
   parameters::make_user_facing (
      const std::string& tag,
      const std::string& nice_name
   )
   {
      // maintain invariant
      if (!mzlib::exists(tag, m_settings))
         return false; // can't make it user facing when it's not a setting

      m_nice_names[tag] = nice_name;
      return true;
   }

   void
   parameters::make_internal (
      const std::string& tag
   )
   {
      m_nice_names.erase(tag);
   }

   bool
   parameters::set_value(
      const std::string& tag,
      const std::string& value
   )
   {
      if (!mzlib::exists(tag, m_settings))
         return false;

      m_settings[tag] = value;
      return true;
   }

   std::optional<std::string>
   parameters::get_value (const std::string& tag)
   {
      return mzlib::get_if_exists(tag, m_settings);
   }

   std::optional<std::string>
   parameters::get_nice_name (
      const std::string& tag
   )
   {
      return mzlib::get_if_exists(tag, m_nice_names);
   }

   std::map<std::string, std::string>
   parameters::get_all_user_facing ()
   {
      std::map<std::string, std::string> settings;
      for (const auto& [tag, _] : m_nice_names)
         settings[tag] = m_settings[tag];
      return settings;
   }

}
