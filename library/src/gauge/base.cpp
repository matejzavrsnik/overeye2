//
// Created by matej on 22/03/2021.
//

#include "base.h"
#include <memory>

namespace gauges
{

base::base (QWidget* parent) :
   m_info(std::make_shared<information>()),
   m_qt_gauge(std::make_unique<::gauge>(parent))
{
   m_info->id = m_unique.id();
   m_qt_gauge->m_info = m_info;
   m_qt_gauge->setObjectName(std::string("gauge") + std::to_string(m_unique.id()));
   m_qt_gauge->new_settings.connect(&base::update_settings, this);
}

::gauge* base::qt()
{
   return m_qt_gauge.get();
}

void base::set_html(std::wstring_view html)
{
   m_qt_gauge->setHtml(html);
}

void base::update_settings(const gauges::information& info)
{
   for(const auto& i : info.parameters)
   {
      m_page_parameters.set(i.get_tag(), i.get_value());
   }
   display();
}


}