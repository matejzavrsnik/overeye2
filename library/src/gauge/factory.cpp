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

      visual->new_settings.connect(&gauge::webport::receive_new_settings, logical.get());
      logical->content_ready.connect(&gui::webport::setHtml, visual.get());

      return std::make_optional<representation>(std::move(unique), std::move(logical), std::move(visual), gc.location);
   }
   case gauge::type::twitter:
   {
      auto logical = std::make_unique<gauge::twitter>(set.gauge_stylesheet, gc.parameters);
      auto visual = std::make_unique<gui::webport>(gc.parameters);
      visual->setObjectName(std::string("twitter") + std::to_string(unique.id()));

      visual->new_settings.connect(&gauge::twitter::receive_new_settings, logical.get());
      logical->content_ready.connect(&gui::webport::setHtml, visual.get());

      return std::make_optional<representation>(std::move(unique), std::move(logical), std::move(visual), gc.location);
   }
   case gauge::type::clock:
   {

      auto visual = std::make_unique<gui::webport>(gc.parameters);
      auto logical = std::make_unique<gauge::clock>(set.gauge_stylesheet, gc.parameters, visual.get()); //todo: move one line up again
      visual->setObjectName(std::string("clock") + std::to_string(unique.id()));

      visual->new_settings.connect(&gauge::clock::receive_new_settings, logical.get());
      logical->content_ready.connect(&gui::webport::setHtml, visual.get());
      visual->request_new_content.connect(&gauge::clock::new_content_requested, logical.get());

      return std::make_optional<representation>(std::move(unique), std::move(logical), std::move(visual), gc.location);
   }
   }
   return std::nullopt; // should never happen (tm)
}

}