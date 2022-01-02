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
   gauge->logical->prepare_display();

   gauge->visual->window()->setGeometry(
      std::stoi(*gauge->parameters->get_value("x")),
      std::stoi(*gauge->parameters->get_value("y")),
      std::stoi(*gauge->parameters->get_value("width")),
      std::stoi(*gauge->parameters->get_value("height"))
   );

   gauge->visual->setParent(m_screen.get());

   m_gauges.push_back(std::move(gauge));
}

void
manager::show ()
{
   m_screen->show();
}

}
