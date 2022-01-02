#include "factory.h"

#include "types.h"
#include "webport.h"
#include "twitter.h"
#include "clock.h"
#include "../logic/representation.h"
#include "../logic/settings.h"
#include "parameters.h"


namespace gauge
{

std::unique_ptr<gauge::webport>
instantiate_webport (
   gauge::type type,
   std::shared_ptr<parameters> parameters
)
{
   switch(type)
   {
   case gauge::type::webport:
      return std::make_unique<gauge::webport>(parameters);
   case gauge::type::clock:
      return std::make_unique<gauge::clock>(parameters);
   case gauge::type::twitter:
      return std::make_unique<gauge::twitter>(parameters);
   }

   throw std::exception{}; // todo: make my own
}

std::unique_ptr<representation>
webport_gauge_factory (
   gauge::type type,
   const configuration& gauge_configuration,
   const std::string& stylesheet
)
{
   auto gauge_representation = std::make_unique<representation>();

   // Create parameters shared between logical and visual parts of the gauge
   auto parameters = std::make_shared<gauge::parameters>(gauge_configuration.settings);
   parameters->set(webport::tags::style(), stylesheet);

   // Instantiate and apply custom settings
   auto logical = instantiate_webport(type, parameters);
   auto visual = std::make_unique<gui::webport>(parameters);
   visual->setObjectName(std::string("webport") + std::to_string(gauge_representation->unique.id()));

   // Connect signals and slots
   visual->request_content.connect(&gauge::webport::display, logical.get());
   visual->signal_settings_changed.connect(&gauge::webport::display, logical.get());
   logical->send_content.connect(&gui::webport::receive_content, visual.get());
   logical->request_refresh.connect(&gui::webport::receive_request_refresh, visual.get());

   // Assemble into representation object
   gauge_representation->logical = std::move(logical);
   gauge_representation->visual = std::move(visual);
   gauge_representation->location = gauge_configuration.location;
   gauge_representation->parameters = parameters;

   return gauge_representation;
}

std::unique_ptr<representation>
gauge_factory (
   const configuration& gc,
   const std::string& gauge_stylesheet
)
{
   switch(gc.type)
   {
   case gauge::type::webport:
   case gauge::type::clock:
   case gauge::type::twitter:
      return webport_gauge_factory(gc.type, gc, gauge_stylesheet);
   }

   throw std::exception{}; // todo: make my own
}

}