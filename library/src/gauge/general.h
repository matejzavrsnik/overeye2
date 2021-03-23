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

   std::wstring_view m_style;
   std::wstring m_page_template;
   parameters m_page_parameters;
   std::wstring m_last_rendered_page;

public:

   general (
      std::wstring_view style,
      parameters parameters
   );

   void
   display () override;

protected:

   // customisation point for additional rendering by derived classes
   virtual std::wstring
   render (std::wstring page_template);

private:

   // render basic html to be used with anything
   // can't be done in dtor because we might want to change stylesheet after control is created
   std::wstring
   render_template (
      std::wstring page_template,
      parameters parameters
   );

};

}

#endif //OPROJECT_OVEREYE_GENERAL_H
