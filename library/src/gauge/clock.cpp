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
   const parameters& page_parameters
) :
   webport(style, {})
{
   // set default parameters
   m_parameters.set(webport::tags::content(), html(), false); // take over content from users
   m_parameters.set(tags::format(), L"ddd MMMM d yyyy hh:mm:ss", true, L"Format");
   m_parameters.set(tags::location(), L"current", true, L"Location");

   // then apply user setting on top
   for (const auto& page_parameter : page_parameters)
   {
      m_parameters.set( // todo: only if it is a user setting
         page_parameter.get_tag(), page_parameter.get_value(), true, page_parameter.get_name()
      );
   }

   using namespace std::chrono_literals;
   set_content_refresh_period(1000ms);
}


std::wstring
clock::render (
   const std::wstring& page_template,
   const parameters& page_parameters
)
{
   auto page = webport::render(page_template, page_parameters);

   auto format = QString::fromStdWString(m_parameters.get(tags::format())->get_value());
   auto location = QString::fromStdWString(m_parameters.get(tags::location())->get_value());

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

