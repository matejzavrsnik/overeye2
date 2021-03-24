//
// Created by matej on 22/03/2021.
//


#include "general.h"
#include <string/replace.h>

namespace
{
   const std::wstring& html()
   {
      static const std::wstring html = LR"(
   <!DOCTYPE html>
   <html>
     <head>
       <meta charset="utf-8">
       <style>{style}</style>
     </head>
     <body>{content}</body>
   </html>
   )";
      return html;
   }
}

namespace gauges
{

   general::general (
      std::wstring style,
      const parameters& page_parameters)
      :
      m_page_template(tags::genesis())
   {
      set_parameter(tags::genesis(), html(), false, tags::genesis()); //todo: make it accept default
      set_parameter(tags::style(), style, false, tags::style());
      for(const auto& page_parameter : page_parameters)
         set_parameter(page_parameter.get_tag(), page_parameter.get_value(), true, page_parameter.get_friendly_name());
   }

   void
   general::display ()
   {
      //m_page_template = render_template(m_page_template, m_page_parameters);
      m_last_rendered_page = render(m_page_template, m_page_parameters);
      set_html(m_last_rendered_page);
   }


   // customisation point for additional rendering by derived classes
   std::wstring
   general::render (const std::wstring& page_template, const parameters& page_parameters)
   {
      std::wstring page = page_template;
      for(const auto& parameter : page_parameters)
         mzlib::string_replace(page, parameter.get_tag(), parameter.get_value());
      return page;
   }

   void general::set_parameter(const std::wstring& tag, const std::wstring& value, bool user_setting, const std::wstring& friendly_name)
   {
      auto existing_parameter = std::find_if(
         m_page_parameters.begin(), m_page_parameters.end(),
         [&tag](const parameter& p) {
            return p.get_tag() == tag;
         });
      if(existing_parameter != m_page_parameters.end())
      {
         existing_parameter->set_value(value);
         existing_parameter->set_user_setting(user_setting);
      }
      else
      {
         parameter parameter{tag, value, user_setting, friendly_name};
         m_page_parameters.push_back(parameter);
      }

      m_info->parameters = m_page_parameters; // copy for now, good enough
   }

   const parameters& general::get_parameters()
   {
      return m_page_parameters;
   }

   const std::wstring& general::tags::genesis()
   {
      static const std::wstring tag{L"{page_template}"};
      return tag;
   }




const std::wstring& general::tags::style()
{
   static const std::wstring tag{L"{style}"};
   return tag;
}

const std::wstring& general::tags::content()
{
   static const std::wstring tag{L"{content}"};
   return tag;
}


   // render basic html to be used with anything
   // can't be done in dtor because we might want to change stylesheet after control is created
   //std::wstring
   //general::render_template (
   //   std::wstring page_template,
   //   parameters parameters
   //)
   //{
   //   mzlib::string_replace(page_template, g_style_placeholder, m_style);
   //   for(const auto& parameter : parameters)
   //      mzlib::string_replace(page_template, parameter.first, parameter.second);
   //   return page_template;
   //}


}

