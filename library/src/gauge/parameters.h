#pragma once

#include "basic_setting.h"
#include "extended_setting.h"
#include "user_parameters.h"
#include "gauge_parameters.h"

#include <string>
#include <vector>
#include <optional>

namespace gauge
{

// two interfaces for two audiences
class parameters : public user_parameters, public gauge_parameters
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
