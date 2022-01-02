#pragma once

#include <string>

namespace gauge
{

// atom of settings
class extended_setting
{

private:

   std::string m_value;

public:

   extended_setting () = default;

   //todo: I have configuration, information, and settings. Need better names
   extended_setting (std::string value);

   [[nodiscard]] const std::string&
   get_value () const;

   void
   set_value (const std::string& v);

};

}