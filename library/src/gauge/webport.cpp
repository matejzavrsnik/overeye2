#include "webport.h"
#include "i_gauge_parameters.h"
#include <string/replace.h>

namespace
{
const std::string&
twitter_embedded_html ()
{
   static const std::string html = R"(
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
   const std::string& style,
   std::shared_ptr<i_gauge_parameters> settings
) :
   m_settings(settings)
{
   // setup settings expected for this gauge
   m_settings->set_or_add_internal_setting(tags::genesis(), twitter_embedded_html());
   m_settings->set_or_add_internal_setting(tags::style(), style);
   m_settings->set_or_add_user_setting(tags::content(), "", "Content");

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

std::string
webport::render (
   const std::string& page_template,
   std::shared_ptr<i_gauge_parameters> page_parameters
)
{
   std::string page = page_template;
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

const std::string&
webport::tags::genesis ()
{
   static const std::string tag{"{page_template}"};
   return tag;
}


const std::string&
webport::tags::style ()
{
   static const std::string tag{"{style}"};
   return tag;
}

const std::string&
webport::tags::content ()
{
   static const std::string tag{"{content}"};
   return tag;
}

}
