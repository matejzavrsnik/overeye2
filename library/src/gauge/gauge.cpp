//
// Created by matej on 22/03/2021.
//

#include "gauge.h"
#include <memory>

namespace gauges
{

gauge::gauge (QWidget* parent) :
   m_qt_gauge(std::make_unique<::gauge>(parent))
{
   m_qt_gauge->setObjectName(std::string("gauge") + std::to_string(unique.id()));
}

::gauge* gauge::get_qt_object()
{
   return m_qt_gauge.get();
}

void gauge::set_html(std::wstring_view html)
{
   m_qt_gauge->setHtml(html);
}

}