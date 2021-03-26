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
)
{
   m_parameters.set(tags::genesis(), html(), false);
   m_parameters.set(tags::style(), style, false);
   for (
      const auto& page_parameter : page_parameters
      )
   {
      m_parameters.set(page_parameter.get_tag(), page_parameter.get_value(), true, page_parameter.get_name());
   }
}

void
webport::display ()
{
   auto rendered_content = render(tags::genesis(), m_parameters);
   content_ready(rendered_content);
}

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

void
webport::receive_new_settings (const gauges::parameters& parameters)
{
   for (
      const auto& i : parameters
      )
   {
      m_parameters.set(i.get_tag(), i.get_value());
   }
   display();
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
