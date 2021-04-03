#pragma once

#include "basic_setting.h"
#include "extended_setting.h"

#include <string>
#include <vector>
#include <optional>

namespace gauge
{

// audience: visual control that needs to display settings and also set them according to user changes
class visual_settings
{

public:

   virtual std::optional<std::wstring>
   user_setting_get_name (
      const std::wstring& tag
   ) = 0;

   virtual bool
   user_setting_set (
      const basic_setting& setting
   ) = 0;

   virtual std::vector<basic_setting>
   user_setting_get_all() = 0;

};

// audience: gauge needs to control of everything about the settings
class gauge_settings
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

   virtual bool
   set(
      const std::wstring& tag,
      const std::wstring& value
   ) = 0;

   virtual std::optional<std::wstring>
   get_value(
      const std::wstring& tag
   ) = 0;

   virtual std::vector<basic_setting>
   get_all() = 0;

};

// two interfaces for two audiences
class parameters : public visual_settings, public gauge_settings
{

public:

   parameters () = default;

private:

   std::vector<extended_setting> m_settings;

   std::vector<extended_setting>::iterator
   find (const std::wstring& tag);

   extended_setting&
   find_or_add (const std::wstring& tag);

   void
   set_or_add_user_setting (
      const std::wstring& tag,
      const std::wstring& value,
      const std::wstring& name
   ) override;

   void
   set_or_add_internal_setting(
      const std::wstring& tag,
      const std::wstring& value
   ) override;

   bool
   set(
      const std::wstring& tag,
      const std::wstring& value
   ) override;

   // sets tag value if exists and is available as user basic_setting
   bool
   user_setting_set (
      const basic_setting& setting
   ) override;

   std::optional<std::wstring>
   get_value(const std::wstring &tag) override;

   std::optional<std::wstring>
   user_setting_get_name (
      const std::wstring& tag
   ) override;

   std::vector<basic_setting>
   user_setting_get_all() override;

   std::vector<basic_setting>
   get_all() override;

};

}
