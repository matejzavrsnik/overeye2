//
// Created by matej on 23/03/2021.
//

//todo: at some point do pragma once on all of these and change the setting in clion for new files
#ifndef OPROJECT_OVEREYE_PARAMETERS_H
#define OPROJECT_OVEREYE_PARAMETERS_H

#include <string>
#include <vector>

namespace gauges
{

class parameter
{

public:

   //todo: I have configuration, information, and parameters. Need better names
   parameter (
      const std::wstring& tag,
      const std::wstring& value,
      bool user_setting,
      const std::wstring& friendly_name
   );

   [[nodiscard]] const std::wstring&
   get_tag () const;

   [[nodiscard]] const std::wstring&
   get_value () const;

   void set_value(const std::wstring& v);

   [[nodiscard]] bool
   is_user_setting () const;

   void set_user_setting(bool v);

   const std::wstring&
   get_friendly_name () const;

private:

   std::wstring m_tag;
   std::wstring m_value;
   bool m_user_setting;
   std::wstring m_friendly_name;

};

using parameters = std::vector<parameter>;

}

#endif //OPROJECT_OVEREYE_PARAMETERS_H
