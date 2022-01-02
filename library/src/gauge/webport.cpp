#include "webport.h"
#include "parameters.h"
#include "string/get_substring.h"
#include <string/replace.h>

namespace
{
const std::string&
webport_embedded_html ()
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
   std::shared_ptr<parameters> settings
) :
   m_settings(settings)
{
   // setup settings expected for this gauge
   m_settings->set(tags::genesis(), webport_embedded_html());
   m_settings->set(tags::style(), style);
   m_settings->set(tags::content(), "");

   m_settings->make_user_facing(tags::content(), "Content");

   m_timer.tick.connect(&webport::tick, this);
}

webport::~webport()
{
   m_timer.tick.disconnect_all();
}

void
webport::apply_user_settings(std::map<std::string, std::string> settings)
{
   for(const auto& [tag, value] : settings)
      m_settings->set_value(tag, value);
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
   std::shared_ptr<parameters> page_parameters
)
{
   std::string page = page_template;

   std::string variable_in_page;
   int occurrence = 0;
   while(variable_in_page = mzlib::get_substring_between(page, "{", "}", occurrence), variable_in_page != "")
   {
      auto placeholder = "{" + variable_in_page + "}";
      std::optional<std::string> content = page_parameters->get_value(placeholder);
      if (content.has_value())
      {
         mzlib::string_replace(page, placeholder, content.value());
      }
      else
         ++occurrence;
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
