#pragma once

#include <string>
#include <vector>
#include <optional>

namespace gauge
{

struct setting
{
   std::wstring tag;
   std::wstring value;
};

// audience: visual control that needs to display settings and also set them accordign to user changes
class interface_visual_control_settings
{
public:
   virtual std::optional<std::wstring>
   user_setting_get_value (
      const std::wstring& tag
   ) = 0;

   virtual std::optional<std::wstring>
   user_setting_get_name (
      const std::wstring& tag
   ) = 0;

   virtual bool
   user_setting_set (
      const setting& setting
   ) = 0;

   virtual std::vector<setting>
   user_setting_get_all() = 0;
};




// atom of parameters
class parameter //todo: separate file
{

private:

   std::wstring m_tag;
   std::wstring m_value;
   bool m_user_setting;
   std::wstring m_name;

public:

   //todo: I have configuration, information, and parameters. Need better names
   parameter (
      std::wstring tag,
      std::wstring value,
      bool user_setting,
      std::wstring friendly_name
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

   void
   set_name (const std::wstring& name);

};




// audience: gauge needs to control of everything about the parameters
class interface_gauge_settings : public interface_visual_control_settings
{
public:
   virtual void
   set_or_add_user_setting (
      const std::wstring& tag,
      const std::wstring& value,
      const std::wstring& name
   ) = 0;

   virtual void
   set_or_add_internal_setting (
      const std::wstring& tag,
      const std::wstring& value
   ) = 0;

   virtual std::optional<std::wstring>
   get_value(
      const std::wstring& tag
   ) = 0;

   virtual std::vector<setting> //todo: not "user setting" anymore is it
   get_all() = 0;
};







class parameters : public interface_gauge_settings //todo: implementation to cpp
{
private:
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

   parameters () = default;

private:

   void
   set_or_add_user_setting (
      const std::wstring& tag,
      const std::wstring& value,
      const std::wstring& name
   ) override
   {
      parameter& param = find_or_add(tag);

      param.set_value(value);
      param.set_user_setting(true);
      param.set_name(name);
   }

   void
   set_or_add_internal_setting(
      const std::wstring& tag,
      const std::wstring& value
   ) override
   {
      parameter& param = find_or_add(tag);

      param.set_value(value);
      param.set_user_setting(false);
   }

   // sets tag value if exists and is available as user setting
   bool
   user_setting_set (
      const setting& setting
   )
   {
      auto parameter = find(setting.tag);
      if(parameter == m_parameters.end()) return false;
      if(!parameter->is_user_setting()) return false;
      parameter->set_value(setting.value);
      return true;
   }

   std::optional<std::wstring>
   get_value(const std::wstring &tag) override
   {
      auto existing_parameter = find(tag);
      if (existing_parameter != m_parameters.end())
      {
         return existing_parameter->get_value();
      }
      return std::nullopt;
   }

   std::optional<std::wstring>
   user_setting_get_value (
      const std::wstring& tag
   )
   {
      auto existing_parameter = find(tag);
      if (existing_parameter != m_parameters.end() &&
         existing_parameter->is_user_setting())
      {
         return existing_parameter->get_value();
      }
      return std::nullopt;
   }

   std::optional<std::wstring>
   user_setting_get_name (
      const std::wstring& tag
   )
   {
      auto existing_parameter = find(tag);
      if (existing_parameter != m_parameters.end() &&
         existing_parameter->is_user_setting())
      {
         return existing_parameter->get_name();
      }
      return std::nullopt;
   }

   std::vector<setting>
   user_setting_get_all()
   {
      std::vector<setting> s;
      for(auto param : m_parameters)
         if(param.is_user_setting())
            s.push_back({param.get_tag(), param.get_value()});
      return s;
   }

   std::vector<setting>
   get_all() override
   {
      std::vector<setting> s;
      for(auto param : m_parameters)
         s.push_back({param.get_tag(), param.get_value()});
      return s;
   }

};

}
