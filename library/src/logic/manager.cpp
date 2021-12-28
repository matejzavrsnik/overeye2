#include "manager.h"
#include "representation.h"
#include <QGridLayout>

namespace gauge
{

manager::manager (std::unique_ptr<gui::screen> screen) :
   m_screen(std::move(screen))
{
}

void
manager::add (
   std::unique_ptr<representation> gauge
)
{
   gauge->logical->display();

   gauge->visual->window()->setGeometry(gauge->location.x, gauge->location.y, gauge->location.w, gauge->location.h);
   gauge->visual->setParent(m_screen.get());

   m_gauges.push_back(std::move(gauge));
}

void
manager::show ()
{
   m_screen->show();
}

}
