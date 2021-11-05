#include "clock.h"
#include "i_gauge_parameters.h"
#include <string/replace.h>
#include <QTimeZone>

namespace
{

const std::wstring&
twitter_embedded_html ()
{
   static const std::wstring html = LR"(
   {timezone}
   <h3>{clock}<h3>
   )";
   return html;
}

}

namespace gauge
{


clock::clock (
   const std::wstring& style,
   std::shared_ptr<i_gauge_parameters> user_settings
) :
   webport(style, user_settings)
{
   // setup settings expected for this gauge
   m_settings->set_or_add_internal_setting(webport::tags::content(), twitter_embedded_html()); // taking over {content} tag from user
   m_settings->set_or_add_user_setting(tags::format(), L"ddd MMMM d yyyy hh:mm:ss", L"Format");
   m_settings->set_or_add_user_setting(tags::timezone(), L"current", L"Location");

   using namespace std::chrono_literals;
   set_content_refresh_period(1000ms);
}


std::wstring
clock::render (
   const std::wstring& page_template,
   std::shared_ptr<i_gauge_parameters> page_parameters
)
{
   auto page = webport::render(page_template, page_parameters);

   auto format = QString::fromStdWString(m_settings->get_value(tags::format()).value_or(L""));
   auto location = QString::fromStdWString(m_settings->get_value(tags::timezone()).value_or(L""));

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
   auto clock = m_date_time.currentDateTime().toTimeZone(timeZone).toString(format).toStdWString();
   mzlib::string_replace(page, tags::clock(), clock);

   return page;
}

const std::wstring&
clock::tags::timezone ()
{
   static const std::wstring tag{L"{timezone}"};
   return tag;
}

const std::wstring&
clock::tags::clock ()
{
   static const std::wstring tag{L"{clock}"};
   return tag;
}

const std::wstring&
clock::tags::format ()
{
   static const std::wstring tag{L"{format}"};
   return tag;
}

}

