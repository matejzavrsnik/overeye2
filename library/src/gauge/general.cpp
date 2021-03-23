//
// Created by matej on 22/03/2021.
//


#include "general.h"
#include <string/replace.h>

namespace gauges
{

const std::wstring_view g_style_placeholder = L"{style}";

const std::wstring_view g_content_placeholder = L"{content}";



   general::general (
      std::wstring_view style,
      parameters parameters
   ) :
      m_style(style),
      m_page_template(
         std::wstring(L"<!DOCTYPE html><html><head><meta charset=\"utf-8\"><style>") + std::wstring(g_style_placeholder)
            + std::wstring(L"</style></head><body>") + std::wstring(g_content_placeholder)
            + std::wstring(L"</body></html>")
      ),
      m_page_parameters(parameters)
   {
   }

   void
   general::display ()
   {
      m_page_template = render_template(m_page_template, m_page_parameters);
      m_last_rendered_page = render(m_page_template);
      set_html(m_last_rendered_page);
   }


   // customisation point for additional rendering by derived classes
   std::wstring
   general::render (std::wstring page_template)
   {
      return page_template;
   }


   // render basic html to be used with anything
   // can't be done in dtor because we might want to change stylesheet after control is created
   std::wstring
   general::render_template (
      std::wstring page_template,
      parameters parameters
   )
   {
      mzlib::string_replace(page_template, g_style_placeholder, m_style);
      for(const auto& parameter : parameters)
         mzlib::string_replace(page_template, parameter.first, parameter.second);
      return page_template;
   }


}

