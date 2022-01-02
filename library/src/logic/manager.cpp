#include "manager.h"
#include "representation.h"
#include <QGridLayout>

namespace gauge
{

manager::manager (const logic::settings& settings) :
   m_settings(settings),
   m_screen(std::make_unique<gui::screen>())
{
   m_screen->setWindowState(Qt::WindowFullScreen);
   m_screen->setStyleSheet(QString::fromStdString(m_settings.dialog_stylesheet));

   for (auto& gauge_configuration: m_settings.gauge_configurations)
   {
      auto gauge_representation = gauge::gauge_factory(gauge_configuration, m_settings.gauge_stylesheet);
      gauge_configuration.id = gauge_representation->unique.id();
      add(std::move(gauge_representation));
   }
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

logic::settings
manager::collect_settings()
{
   auto& configs = m_settings.gauge_configurations;
   for(const auto& gauge : m_gauges)
   {
      auto it_gauge_config = std::find_if(
         configs.begin(), configs.end(),
         [&gauge](const configuration& config)
         {
            return config.id == gauge->unique.id();
         });

      for(const auto& [tag, value] : gauge->parameters->get_all_user_facing())
      {
         it_gauge_config->settings[tag] = value;
      }
   }
   return m_settings;
}

}
