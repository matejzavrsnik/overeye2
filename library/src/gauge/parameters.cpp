#include "parameters.h"

namespace gauge
{

   std::vector<extended_setting>::iterator
   parameters::find (const std::wstring& tag)
   {
      auto existing_setting = std::find_if(
         m_settings.begin(), m_settings.end(), [&tag] (const extended_setting& p)
         {
            return p.get_tag() == tag;
         }
      );

      if (existing_setting != m_settings.end())
      {
         return existing_setting;
      }

      return m_settings.end();
   }

   extended_setting&
   parameters::find_or_add (const std::wstring& tag)
   {
      auto existing_setting = find(tag);
      if (existing_setting != m_settings.end())
      {
         return *existing_setting;
      }

      //todo: to allow ctor that only takes tag? It would make sense here
      extended_setting setting{tag, L"", false, L""};
      m_settings.push_back(setting);
      return *m_settings.rbegin();
   }

   void
   parameters::set_or_add_user_setting (
      const std::wstring& tag,
      const std::wstring& value,
      const std::wstring& name
   )
   {
      extended_setting& setting = find_or_add(tag);

      setting.set_value(value);
      setting.set_user_setting(true);
      setting.set_name(name);
   }

   void
   parameters::set_or_add_internal_setting (
      const std::wstring& tag,
      const std::wstring& value
   )
   {
      extended_setting& setting = find_or_add(tag);

      setting.set_value(value);
      setting.set_user_setting(false);
   }

bool
parameters::set(
   const std::wstring& tag,
   const std::wstring& value
)
{
   auto existing_setting = find(tag);
   if (existing_setting != m_settings.end())
   {
      existing_setting->set_value(value);
      return true;
   }

   return false;
}

   // sets tag value if exists and is available as user basic_setting
   bool
   parameters::user_setting_set (
      const basic_setting& setting
   )
   {
      auto it_setting = find(setting.tag);
      if (it_setting == m_settings.end())
         return false;
      if (!it_setting->is_user_setting())
         return false;
      it_setting->set_value(setting.value);
      return true;
   }

   std::optional<std::wstring>
   parameters::get_value (const std::wstring& tag)
   {
      auto it_setting = find(tag);
      if (it_setting != m_settings.end())
      {
         return it_setting->get_value();
      }
      return std::nullopt;
   }

   std::optional<std::wstring>
   parameters::user_setting_get_name (
      const std::wstring& tag
   )
   {
      auto it_setting = find(tag);
      if (it_setting != m_settings.end() && it_setting->is_user_setting())
      {
         return it_setting->get_name();
      }
      return std::nullopt;
   }

   std::vector<basic_setting>
   parameters::user_setting_get_all ()
   {
      std::vector<basic_setting> settings;
      for (auto setting : m_settings)
         if (setting.is_user_setting())
            settings.push_back({setting.get_tag(), setting.get_value()});
      return settings;
   }

   std::vector<basic_setting>
   parameters::get_all ()
   {
      std::vector<basic_setting> settings;
      for (auto setting : m_settings)
         settings.push_back({setting.get_tag(), setting.get_value()});
      return settings;
   }

}
