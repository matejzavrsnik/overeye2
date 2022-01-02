#include "parameters.h"

namespace gauge
{

   void
   parameters::set_or_add_user_setting (
      const std::string& tag,
      const std::string& value,
      const std::string& nice_name
   )
   {
      m_settings[tag] = value;
      m_nice_names[tag] = nice_name;
   }

   void
   parameters::set_or_add_internal_setting (
      const std::string& tag,
      const std::string& value
   )
   {
      m_settings[tag] = value;
      m_nice_names.erase(tag);
   }

   bool
   parameters::set(
      const std::string& tag,
      const std::string& value
   )
   {
      auto existing_setting = m_settings.find(tag);
      if (existing_setting != m_settings.end())
      {
         existing_setting->second = value;
         return true;
      }

      return false;
   }

   bool
   parameters::user_setting_set (
      const std::string& tag,
      const std::string& value
   )
   {
      if (m_nice_names.find(tag) != m_nice_names.end())
         return false; // not a user setting

      auto it_setting = m_settings.find(tag);
      if (it_setting == m_settings.end())
         return false; // no such setting at all

      it_setting->second = value;
      return true;
   }

   std::optional<std::string>
   parameters::get_value (const std::string& tag)
   {
      auto it_setting = m_settings.find(tag);
      if (it_setting != m_settings.end())
      {
         return it_setting->second;
      }
      return std::nullopt;
   }

   std::optional<std::string>
   parameters::user_setting_get_name (
      const std::string& tag
   )
   {
      auto it_setting = m_nice_names.find(tag);
      if (it_setting != m_nice_names.end())
      {
         return it_setting->second;
      }
      return std::nullopt;
   }

   std::map<std::string, std::string>
   parameters::user_setting_get_all ()
   {
      std::map<std::string, std::string> settings;
      for (const auto& [tag, _] : m_nice_names)
         settings[tag] = m_settings[tag];
      return settings;
   }

}
