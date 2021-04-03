#pragma once

#include "basic_setting.h"

namespace gauge
{

// atom of parameters
class extended_setting //todo: separate file
{

private:

   basic_setting m_basic_setting;
   bool m_user_setting;
   std::wstring m_name;

public:

   //todo: I have configuration, information, and parameters. Need better names
   extended_setting (
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

}