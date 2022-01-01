#include "parameters.h"

namespace gauge
{

   std::map<std::string, extended_setting>::iterator
   parameters::find (const std::string& tag)
   {
      return m_settings.find(tag);
   }

   extended_setting&
   parameters::find_or_add (const std::string& tag)
   {
      return m_settings[tag];
   }

   void
   parameters::set_or_add_user_setting (
      const std::string& tag,
      const std::string& value,
      const std::string& name
   )
   {
      extended_setting& setting = find_or_add(tag);

      setting.set_value(value);
      setting.set_user_setting(true);
      setting.set_name(name);
   }

   void
   parameters::set_or_add_internal_setting (
      const std::string& tag,
      const std::string& value
   )
   {
      extended_setting& setting = find_or_add(tag);

      setting.set_value(value);
      setting.set_user_setting(false);
   }

bool
parameters::set(
   const std::string& tag,
   const std::string& value
)
{
   auto existing_setting = find(tag);
   if (existing_setting != m_settings.end())
   {
      existing_setting->second.set_value(value);
      return true;
   }

   return false;
}

   // sets tag value if exists and is available as user basic_setting
   bool
   parameters::user_setting_set (
      const std::string& tag,
      const std::string& value
   )
   {
      auto it_setting = find(tag);
      if (it_setting == m_settings.end())
         return false;
      if (!it_setting->second.is_user_setting())
         return false;
      it_setting->second.set_value(value);
      return true;
   }

   std::optional<std::string>
   parameters::get_value (const std::string& tag)
   {
      auto it_setting = find(tag);
      if (it_setting != m_settings.end())
      {
         return it_setting->second.get_value();
      }
      return std::nullopt;
   }

   std::optional<std::string>
   parameters::user_setting_get_name (
      const std::string& tag
   )
   {
      auto it_setting = find(tag);
      if (it_setting != m_settings.end() && it_setting->second.is_user_setting())
      {
         return it_setting->second.get_name();
      }
      return std::nullopt;
   }

   std::map<std::string, std::string>
   parameters::user_setting_get_all ()
   {
      std::map<std::string, std::string> settings;
      for (auto setting : m_settings)
         if (setting.second.is_user_setting())
            settings[setting.first] = setting.second.get_value();
      return settings;
   }

}
