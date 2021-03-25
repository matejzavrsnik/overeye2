//
// Created by matej on 22/03/2021.
//

#ifndef OPROJECT_OVEREYE_GENERAL_H
#define OPROJECT_OVEREYE_GENERAL_H

#include "base.h"
#include "configuration.h"
#include <string>

namespace gauges
{

// general gauge
// usable on its own, but intended for further specialisation
class general : public base
{

private:

   const std::wstring m_page_template;
   std::wstring m_last_rendered_page;


public:

   general (
      std::wstring style,
      const cparameters& page_parameters
      );

   void
   display () override;

protected:

   std::wstring
   render (const std::wstring& page_template, const cparameters& page_parameters);

   void set_parameter(const std::wstring& tag, const std::wstring& value, bool user_setting, const std::wstring& friendly_name);

public:

   class tags
   {
      friend class general;
   private:

      const static std::wstring& genesis();

   public:

      const static std::wstring& style();
      const static std::wstring& content();

   };

};

}

#endif //OPROJECT_OVEREYE_GENERAL_H
