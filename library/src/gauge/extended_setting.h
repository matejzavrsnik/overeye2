#pragma once

#include <string>

namespace gauge
{

// atom of settings
class extended_setting
{

private:

   std::string m_value;
   bool m_user_setting;
   std::string m_name;

public:

   extended_setting () = default;

   //todo: I have configuration, information, and settings. Need better names
   extended_setting (
      std::string value,
      bool user_setting,
      std::string friendly_name
   );

   [[nodiscard]] const std::string&
   get_value () const;

   void
   set_value (const std::string& v);

   [[nodiscard]] bool
   is_user_setting () const;

   void
   set_user_setting (bool v);

   [[nodiscard]] const std::string&
   get_name () const;

   void
   set_name (const std::string& name);

};

}