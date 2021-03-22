//
// Created by matej on 22/03/2021.
//

#ifndef OPROJECT_OVEREYE_WEB_H
#define OPROJECT_OVEREYE_WEB_H

#include "gauge.h"
#include <string>

namespace gauges
{

// generic web gauge
class web : public gauge
{

private:

   std::wstring_view m_style;
   std::wstring m_page_template;
   std::wstring m_page_content;
   std::wstring m_last_rendered_page;

public:

   web (
      std::wstring_view style,
      std::wstring_view content
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
      std::wstring_view content
   );

};

}

#endif //OPROJECT_OVEREYE_WEB_H
