#include "clock.h"
#include <string/replace.h>
#include <QTimeZone>

namespace
{

const std::wstring&
html ()
{
   static const std::wstring html = LR"(
   {location}
   <h3>{clock}<h3>
   )";
   return html;
}

}

namespace gauge
{


clock::clock (
   const std::wstring& style,
   interface_gauge_settings& user_settings
) :
   webport(style, user_settings)
{
   // setup parameters expected for this gauge
   m_parameters.set_or_add(webport::tags::content(), html(), false); // taking over {content} tag from user
   m_parameters.set_or_add(tags::format(), L"ddd MMMM d yyyy hh:mm:ss", true, L"Format");
   m_parameters.set_or_add(tags::location(), L"current", true, L"Location");

   // configure with user settings
   //for (const auto& user_setting : user_settings)
   //{
   //   m_parameters.user_setting_set(user_setting);
   //}

   using namespace std::chrono_literals;
   set_content_refresh_period(1000ms);
}


std::wstring
clock::render (
   const std::wstring& page_template,
   interface_gauge_settings& page_parameters
)
{
   auto page = webport::render(page_template, page_parameters);

   auto format = QString::fromStdWString(m_parameters.get_value(tags::format()).value_or(L""));
   auto location = QString::fromStdWString(m_parameters.get_value(tags::location()).value_or(L""));

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
clock::tags::location ()
{
   static const std::wstring tag{L"{location}"};
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

