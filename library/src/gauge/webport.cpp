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

namespace gauge
{

webport::webport (
   const std::wstring& style,
   const std::vector<user_setting>& user_settings
)
{
   // setup parameters expected for this gauge
   m_parameters.set_or_add(tags::genesis(), html(), false);
   m_parameters.set_or_add(tags::style(), style, false);
   m_parameters.set_or_add(tags::content(), L"", true);

   // configure with user settings
   for (const auto& user_setting : user_settings)
   {
      m_parameters.set_user_setting(user_setting.tag, user_setting.value);
   }

   m_timer.tick.connect(&webport::tick, this);
}

webport::~webport()
{
   m_timer.tick.disconnect_all();
}

void
webport::display ()
{
   auto rendered_content = render(tags::genesis(), m_parameters);
   send_content(rendered_content);
}

std::wstring
webport::render (
   const std::wstring& page_template,
   const parameters& page_parameters
)
{
   std::wstring page = page_template;
   for (const auto& parameter : page_parameters)
   {
      mzlib::string_replace(page, parameter.get_tag(), parameter.get_value());
   }
   return page;
}

void
webport::set_content_refresh_period (
   std::chrono::milliseconds period
)
{
   m_timer.start(period);
}

void
webport::tick ()
{
   request_content_refresh();
}

void
webport::receive_user_setting (const gauge::user_setting& parameters)
{
   m_parameters.set_user_setting(parameters.tag, parameters.value);
   display();
}

void
webport::receive_request_content ()
{
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
