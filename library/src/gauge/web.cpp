//
// Created by matej on 22/03/2021.
//


#include "web.h"
#include <string/replace.h>

namespace gauges
{

const std::wstring_view g_style_placeholder = L"{style}";

const std::wstring_view g_content_placeholder = L"{content}";



   web::web (
      std::wstring_view style,
      std::wstring_view content
   ) :
      m_style(style),
      m_page_template(
         std::wstring(L"<!DOCTYPE html><html><head><meta charset=\"utf-8\"><style>") + std::wstring(g_style_placeholder)
            + std::wstring(L"</style></head><body>") + std::wstring(g_content_placeholder)
            + std::wstring(L"</body></html>")
      ),
      m_page_content(content)
   {
      setObjectName(QString::fromStdString("gauge" + std::to_string(unique.id())));
   }

   void
   web::display ()
   {
      m_page_template = render_template(m_page_template, m_page_content);
      m_last_rendered_page = render(m_page_template);
      set_content(m_last_rendered_page);
   }


   // customisation point for additional rendering by derived classes
   std::wstring
   web::render (std::wstring page_template)
   {
      return page_template;
   }


   // render basic html to be used with anything
   // can't be done in dtor because we might want to change stylesheet after control is created
   std::wstring
   web::render_template (
      std::wstring page_template,
      std::wstring_view content
   )
   {
      mzlib::string_replace(page_template, g_style_placeholder, m_style);
      mzlib::string_replace(page_template, g_content_placeholder, content);
      return page_template;
   }


}

