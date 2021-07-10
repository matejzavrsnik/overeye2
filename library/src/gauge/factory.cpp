#include "factory.h"

#include "types.h"
#include "webport.h"
#include "twitter.h"
#include "clock.h"
#include "representation.h"
#include "../settings.h"


namespace gauge
{

std::unique_ptr<gauge::webport>
instantiate_webport(
   gauge::type type,
   std::wstring stylesheet,
   std::shared_ptr<gauge_settings> settings
)
{
   switch(type)
   {
   case gauge::type::webport:
      return std::make_unique<gauge::webport>(stylesheet, settings);
   case gauge::type::clock:
      return std::make_unique<gauge::clock>(stylesheet, settings);
   case gauge::type::twitter:
      return std::make_unique<gauge::twitter>(stylesheet, settings);
   }

   throw std::exception{}; // todo: make my own
}

std::unique_ptr<representation>
webport_gauge_factory(
   gauge::type type,
   const std::vector<gauge::basic_setting>& settings,
   const configuration& gc,
   const std::wstring& stylesheet
)
{
   auto gauge_representation = std::make_unique<representation>();

   // Instantiate and apply custom settings
   auto logical = instantiate_webport(type, stylesheet, gauge_representation->parameters);
   logical->apply_user_settings(settings);
   auto visual = std::make_unique<gui::webport>(gauge_representation->parameters);
   visual->setObjectName(std::string("webport") + std::to_string(gauge_representation->unique.id()));

   // Connect signals and slots
   visual->request_content.connect(&gauge::webport::display, logical.get());
   visual->signal_settings_changed.connect(&gauge::webport::display, logical.get());
   logical->send_content.connect(&gui::webport::receive_content, visual.get());
   logical->request_refresh.connect(&gui::webport::receive_request_refresh, visual.get());

   // Assemble into representation object
   gauge_representation->logical = std::move(logical);
   gauge_representation->visual = std::move(visual);
   gauge_representation->location = gc.location;

   return gauge_representation;
}

std::unique_ptr<representation>
gauge_factory (
   const configuration& gc,
   const std::wstring& gauge_stylesheet
)
{
   switch(gc.type)
   {
   case gauge::type::webport:
   case gauge::type::clock:
   case gauge::type::twitter:
      return webport_gauge_factory(gc.type, gc.settings, gc, gauge_stylesheet);
   }

   throw std::exception{}; // todo: make my own
}

}