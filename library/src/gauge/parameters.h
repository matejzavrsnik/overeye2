#pragma once

#include <string>
#include <vector>
#include <optional>

namespace gauges
{

class parameter
{

public:

   //todo: I have configuration, information, and parameters. Need better names
   parameter (
      std::wstring  tag,
      std::wstring  value,
      bool user_setting,
      std::wstring  friendly_name
   );

   [[nodiscard]] const std::wstring&
   get_tag () const;

   [[nodiscard]] const std::wstring&
   get_value () const;

   void
   set_value (const std::wstring& v);

   [[nodiscard]] bool
   is_user_setting () const;

   void
   set_user_setting (bool v);

   [[nodiscard]] const std::wstring&
   get_name () const;

private:

   std::wstring m_tag;
   std::wstring m_value;
   bool m_user_setting;
   std::wstring m_name;
public:
   void
   set_name (const std::wstring& name);

};

class parameters
{
   std::vector<parameter> m_parameters;

   std::vector<parameter>::iterator
   find (const std::wstring& tag)
   {
      auto existing_parameter = std::find_if(
         m_parameters.begin(), m_parameters.end(), [&tag] (const parameter& p)
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

   parameter&
   find_or_add (const std::wstring& tag)
   {
      auto existing_parameter = find(tag);
      if (existing_parameter != m_parameters.end())
      {
         return *existing_parameter;
      }

      //todo: to allow ctor that only takes tag? It would make sense here
      parameter parameter{tag, L"", false, L""};
      m_parameters.push_back(parameter);
      return *m_parameters.rbegin();
   }

public:

   parameters ()
   = default;

   parameters (
      const std::initializer_list<parameter>& params
   )
   {
      for (
         const auto& param : params
         )
      {
         m_parameters.push_back(param);
      }
   }

   // sets tag value if exists, adds if it doesn't
   // two params are optional because two audiences: gauges setting these for themselves and user settings
   // perhaps an opportunity for refactor?
   void
   set (
      const std::wstring& tag,
      const std::wstring& value,
      const std::optional<bool> user_setting = std::nullopt,
      const std::optional<std::wstring>& name = std::nullopt
   )
   {
      parameter& param = find_or_add(tag);

      param.set_value(value);
      if (user_setting) param.set_user_setting(*user_setting);
      if (name) param.set_name(*name);
   }

   //todo: leaking implementation detail
   std::vector<parameter>::iterator
   begin ()
   {
      return m_parameters.begin();
   }

   std::vector<parameter>::iterator
   end ()
   {
      return m_parameters.end();
   }

   [[nodiscard]] std::vector<parameter>::const_iterator
   begin () const
   {
      return m_parameters.begin();
   }

   [[nodiscard]] std::vector<parameter>::const_iterator
   end () const
   {
      return m_parameters.end();
   }
};

}
