#include "webport.h"
#include <string/replace.h>

namespace
{
const std::wstring&
html ()
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

webport::webport (
   const std::wstring& style,
   const parameters& page_parameters
) :
   m_qt_gauge(std::make_unique<gui::webport>(m_parameters)),
   m_page_template(tags::genesis())
{
   // todo: create outside and leave logic completely free of representation?
   m_qt_gauge->setObjectName(std::string("webport") + std::to_string(m_unique.id()));
   m_qt_gauge->new_settings.connect(&webport::update_settings, this);

   set_parameter(tags::genesis(), html(), false, tags::genesis()); //todo: make it accept default
   set_parameter(tags::style(), style, false, tags::style());
   for (
      const auto& page_parameter : page_parameters
      )
   {
      set_parameter(page_parameter.get_tag(), page_parameter.get_value(), true, page_parameter.get_name());
   }
}

void
webport::display ()
{
   m_last_rendered_page = render(m_page_template, m_parameters);
   set_html(m_last_rendered_page);
}


// customisation point for additional rendering by derived classes
std::wstring
webport::render (
   const std::wstring& page_template,
   const parameters& page_parameters
)
{
   std::wstring page = page_template;
   for (
      const auto& parameter : page_parameters
      )
   {
      mzlib::string_replace(page, parameter.get_tag(), parameter.get_value());
   }
   return page;
}

gui::webport*
webport::graphical_representation()
{
   return m_qt_gauge.get();
}

void
webport::set_html (std::wstring_view html)
{
   m_qt_gauge->setHtml(html);
}

void
webport::update_settings (const gauges::parameters& parameters)
{
   for (
      const auto& i : parameters
      )
   {
      m_parameters.set(i.get_tag(), i.get_value());
   }
   display();
}

void
webport::set_parameter (
   const std::wstring& tag,
   const std::wstring& value,
   bool user_setting,
   const std::wstring& friendly_name
)
{
   m_parameters.set(tag, value, user_setting, friendly_name);
}

const std::wstring&
webport::tags::genesis ()
{
   static const std::wstring tag{L"{page_template}"};
   return tag;
}


const std::wstring&
webport::tags::style ()
{
   static const std::wstring tag{L"{style}"};
   return tag;
}

const std::wstring&
webport::tags::content ()
{
   static const std::wstring tag{L"{content}"};
   return tag;
}



}
