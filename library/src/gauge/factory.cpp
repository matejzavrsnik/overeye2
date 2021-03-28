
#include "factory.h"

#include "types.h"
#include "webport.h"
#include "twitter.h"
#include "clock.h"
#include "representation.h"
#include "../settings.h"



namespace gauge
{



std::optional<representation>
gauge_factory (
   const configuration& gc,
   const library::settings& set
)
{
   mzlib::unique unique;
   switch (gc.type)
   {
   case gauge::type::webport:
   {

      auto logical = std::make_unique<gauge::webport>(set.gauge_stylesheet, gc.parameters);
      auto visual = std::make_unique<gui::webport>(gc.parameters);
      visual->setObjectName(std::string("webport") + std::to_string(unique.id()));

      visual->send_user_changes.connect(&gauge::webport::receive_user_changes, logical.get());
      logical->send_content.connect(&gui::webport::receive_content, visual.get());

      return std::make_optional<representation>(std::move(unique), std::move(logical), std::move(visual), gc.location);
   }
   case gauge::type::twitter:
   {
      auto logical = std::make_unique<gauge::twitter>(set.gauge_stylesheet, gc.parameters);
      auto visual = std::make_unique<gui::webport>(gc.parameters);
      visual->setObjectName(std::string("twitter") + std::to_string(unique.id()));

      visual->send_user_changes.connect(&gauge::twitter::receive_user_changes, logical.get());
      logical->send_content.connect(&gui::webport::receive_content, visual.get());

      return std::make_optional<representation>(std::move(unique), std::move(logical), std::move(visual), gc.location);
   }
   case gauge::type::clock:
   {
      auto logical = std::make_unique<gauge::clock>(set.gauge_stylesheet, gc.parameters);
      auto visual = std::make_unique<gui::webport>(gc.parameters);
      visual->setObjectName(std::string("clock") + std::to_string(unique.id()));

      visual->send_user_changes.connect(&gauge::clock::receive_user_changes, logical.get());
      visual->request_content.connect(&gauge::clock::receive_request_content, logical.get());
      logical->send_content.connect(&gui::webport::receive_content, visual.get());
      logical->request_content_refresh.connect(&gui::webport::receive_content_refresh_request, visual.get());

      return std::make_optional<representation>(std::move(unique), std::move(logical), std::move(visual), gc.location);
   }
   }
   return std::nullopt; // should never happen (tm)
}

}