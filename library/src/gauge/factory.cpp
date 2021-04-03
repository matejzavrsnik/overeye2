#include "factory.h"

#include "types.h"
#include "webport.h"
#include "twitter.h"
#include "clock.h"
#include "representation.h"
#include "../settings.h"


namespace gauge
{


std::unique_ptr<representation>
gauge_factory (
   const configuration& gc,
   const library::settings& set
)
{
   mzlib::unique unique;
   auto r = std::make_unique<representation>();

   switch (gc.type)
   {
   case gauge::type::webport:
   {
      auto logical = std::make_unique<gauge::webport>(set.gauge_stylesheet, r->parameters);
      auto visual = std::make_unique<gui::webport>(gc.parameters);
      visual->setObjectName(std::string("webport") + std::to_string(unique.id()));

      for(auto setting : gc.parameters)
         r->parameters->user_setting_set(setting); //todo: make it so that order doesn't matter that much

      visual->send_user_setting.connect(&gauge::clock::receive_user_setting, logical.get());
      visual->request_content.connect(&gauge::clock::receive_request_content, logical.get());
      logical->send_content.connect(&gui::webport::receive_content, visual.get());
      logical->request_content_refresh.connect(&gui::webport::receive_content_refresh_request, visual.get());

      r->unique = std::move(unique);
      r->logical = std::move(logical);
      r->visual = std::move(visual);
      r->location = gc.location;

      return r;
   }
   case gauge::type::twitter:
   {
      auto logical = std::make_unique<gauge::twitter>(set.gauge_stylesheet, r->parameters);
      auto visual = std::make_unique<gui::webport>(gc.parameters);
      visual->setObjectName(std::string("twitter") + std::to_string(unique.id()));

      for(auto setting : gc.parameters)
         r->parameters->user_setting_set(setting); //todo: make it so that order doesn't matter that much

      visual->send_user_setting.connect(&gauge::clock::receive_user_setting, logical.get());
      visual->request_content.connect(&gauge::clock::receive_request_content, logical.get());
      logical->send_content.connect(&gui::webport::receive_content, visual.get());
      logical->request_content_refresh.connect(&gui::webport::receive_content_refresh_request, visual.get());

      r->unique = std::move(unique);
      r->logical = std::move(logical);
      r->visual = std::move(visual);
      r->location = gc.location;

      return r;
   }
   case gauge::type::clock:
   {
      auto logical = std::make_unique<gauge::clock>(set.gauge_stylesheet, r->parameters);
      auto visual = std::make_unique<gui::webport>(gc.parameters);
      visual->setObjectName(std::string("clock") + std::to_string(unique.id()));

      for(auto setting : gc.parameters)
         r->parameters->user_setting_set(setting); //todo: make it so that order doesn't matter that much

      visual->send_user_setting.connect(&gauge::clock::receive_user_setting, logical.get());
      visual->request_content.connect(&gauge::clock::receive_request_content, logical.get());
      logical->send_content.connect(&gui::webport::receive_content, visual.get());
      logical->request_content_refresh.connect(&gui::webport::receive_content_refresh_request, visual.get());

      r->unique = std::move(unique);
      r->logical = std::move(logical);
      r->visual = std::move(visual);
      r->location = gc.location;

      return r;
   }
   }
   throw std::exception{}; // todo: make my own
}

}