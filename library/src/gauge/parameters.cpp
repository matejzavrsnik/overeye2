#include "parameters.h"

namespace gauge
{

   std::vector<extended_setting>::iterator
   parameters::find (const std::wstring& tag)
   {
      auto existing_parameter = std::find_if(
         m_parameters.begin(), m_parameters.end(), [&tag] (const extended_setting& p)
         {
            return p.get_tag() == tag;
         }
      );

      if (existing_parameter != m_parameters.end())
      {
         return existing_parameter;
      }

      return m_parameters.end();
   }

   extended_setting&
   parameters::find_or_add (const std::wstring& tag)
   {
      auto existing_parameter = find(tag);
      if (existing_parameter != m_parameters.end())
      {
         return *existing_parameter;
      }

      //todo: to allow ctor that only takes tag? It would make sense here
      extended_setting parameter{tag, L"", false, L""};
      m_parameters.push_back(parameter);
      return *m_parameters.rbegin();
   }

   void
   parameters::set_or_add_user_setting (
      const std::wstring& tag,
      const std::wstring& value,
      const std::wstring& name
   )
   {
      extended_setting& param = find_or_add(tag);

      param.set_value(value);
      param.set_user_setting(true);
      param.set_name(name);
   }

   void
   parameters::set_or_add_internal_setting (
      const std::wstring& tag,
      const std::wstring& value
   )
   {
      extended_setting& param = find_or_add(tag);

      param.set_value(value);
      param.set_user_setting(false);
   }

bool
parameters::set(
   const std::wstring& tag,
   const std::wstring& value
)
{
   auto existing_parameter = find(tag);
   if (existing_parameter != m_parameters.end())
   {
      existing_parameter->set_value(value);
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
      auto parameter = find(setting.tag);
      if (parameter == m_parameters.end())
         return false;
      if (!parameter->is_user_setting())
         return false;
      parameter->set_value(setting.value);
      return true;
   }

   std::optional<std::wstring>
   parameters::get_value (const std::wstring& tag)
   {
      auto existing_parameter = find(tag);
      if (existing_parameter != m_parameters.end())
      {
         return existing_parameter->get_value();
      }
      return std::nullopt;
   }

   std::optional<std::wstring>
   parameters::user_setting_get_name (
      const std::wstring& tag
   )
   {
      auto existing_parameter = find(tag);
      if (existing_parameter != m_parameters.end() && existing_parameter->is_user_setting())
      {
         return existing_parameter->get_name();
      }
      return std::nullopt;
   }

   std::vector<basic_setting>
   parameters::user_setting_get_all ()
   {
      std::vector<basic_setting> s;
      for (auto param : m_parameters)
         if (param.is_user_setting())
            s.push_back({param.get_tag(), param.get_value()});
      return s;
   }

   std::vector<basic_setting>
   parameters::get_all ()
   {
      std::vector<basic_setting> s;
      for (auto param : m_parameters)
         s.push_back({param.get_tag(), param.get_value()});
      return s;
   }

}
