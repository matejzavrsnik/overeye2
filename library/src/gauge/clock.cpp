#include "clock.h"
#include "parameters.h"
#include <string/replace.h>
#include <QTimeZone>

namespace
{

const std::string&
clock_embedded_html ()
{
   static const std::string html = R"(
   {timezone}
   <h3>{clock}<h3>
   )";
   return html;
}

}

namespace gauge
{


clock::clock (
   const std::string& style,
   std::shared_ptr<parameters> user_settings
) :
   webport(style, user_settings)
{
   m_settings->set(webport::tags::content(), clock_embedded_html());

   m_settings->make_internal(webport::tags::content()); // taking over {content} tag from user
   m_settings->make_user_facing(tags::format(), "Format");
   m_settings->make_user_facing(tags::timezone(), "Location");

   using namespace std::chrono_literals;
   set_content_refresh_period(1000ms);
}


std::string
clock::render (
   const std::string& page_template,
   std::shared_ptr<parameters> page_parameters
)
{
   auto page = webport::render(page_template, page_parameters);

   auto format = QString::fromStdString(m_settings->get_value(tags::format()).value_or(""));
   auto location = QString::fromStdString(m_settings->get_value(tags::timezone()).value_or(""));

   //auto aaa = QTimeZone::availableTimeZoneIds();
   //std::vector<std::string> zones;
   //for(auto aa : aaa)
   //   zones.push_back(aa.toStdString());

   //Asia/Ulaanbaatar
   //Antarctica/Davis
   //Europe/London
   //Europe/Ljubljana
   //America/New_York
   //America/Monterrey

   QTimeZone timeZone(location.toUtf8());
   auto clock = m_date_time.currentDateTime().toTimeZone(timeZone).toString(format).toStdString();
   mzlib::string_replace(page, tags::clock(), clock);

   return page;
}

const std::string&
clock::tags::timezone ()
{
   static const std::string tag{"{timezone}"};
   return tag;
}

const std::string&
clock::tags::clock ()
{
   static const std::string tag{"{clock}"};
   return tag;
}

const std::string&
clock::tags::format ()
{
   static const std::string tag{"{format}"};
   return tag;
}

}

