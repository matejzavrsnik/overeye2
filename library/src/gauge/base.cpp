#include "base.h"

namespace gauges
{

base::base () :
   m_qt_gauge(std::make_unique<::gauge>(m_parameters))
{
   m_qt_gauge->setObjectName(std::string("gauge") + std::to_string(m_unique.id()));
   m_qt_gauge->new_settings.connect(&base::update_settings, this);
}

::gauge*
base::qt ()
{
   return m_qt_gauge.get();
}

void
base::set_html (std::wstring_view html)
{
   m_qt_gauge->setHtml(html);
}

void
base::update_settings (const gauges::parameters& parameters)
{
   for (
      const auto& i : parameters
      )
   {
      m_parameters.set(i.get_tag(), i.get_value());
   }
   display();
}


}