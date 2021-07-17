#include "webport.h"
#include "i_gauge_parameters.h"
#include <string/replace.h>

namespace
{
const std::wstring&
twitter_embedded_html ()
{
   static const std::wstring html = LR"(
   <!DOCTYPE html>
   <html>
     <head>
       <meta charset="utf-8">
       <style>{style}</style>
     </head>
     <body>{content}</body>
   </twitter_embedded_html>
   )";
   return html;
}
}

namespace gauge
{

webport::webport (
   const std::wstring& style,
   std::shared_ptr<i_gauge_parameters> settings
) :
   m_settings(settings)
{
   // setup settings expected for this gauge
   m_settings->set_or_add_internal_setting(tags::genesis(), twitter_embedded_html());
   m_settings->set_or_add_internal_setting(tags::style(), style);
   m_settings->set_or_add_user_setting(tags::content(), L"", L"Content");

   m_timer.tick.connect(&webport::tick, this);
}

webport::~webport()
{
   m_timer.tick.disconnect_all();
}

void
webport::apply_user_settings(std::vector<gauge::basic_setting> settings)
{
   for(auto setting : settings)
      m_settings->set(setting.tag, setting.value);
}

void
webport::display ()
{
   auto rendered_content = render(tags::genesis(), m_settings);
   send_content(rendered_content);
}

std::wstring
webport::render (
   const std::wstring& page_template,
   std::shared_ptr<i_gauge_parameters> page_parameters
)
{
   std::wstring page = page_template;
   for (const auto& parameter : page_parameters->get_all())
   {
      mzlib::string_replace(page, parameter.tag, parameter.value);
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
   request_refresh();
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
