#include "factory.h"

#include "types.h"
#include "webport.h"
#include "twitter.h"
#include "representation.h"
#include "../settings.h"

namespace gauges
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
   case gauges::type::webport:
   {

      auto logical = std::make_unique<gauges::webport>(set.gauge_stylesheet, gc.parameters);
      auto visual = std::make_unique<gui::webport>(gc.parameters);
      visual->setObjectName(std::string("webport") + std::to_string(unique.id()));

      visual->new_settings.connect(&gauges::webport::receive_new_settings, logical.get());
      logical->content_ready.connect(&gui::webport::setHtml, visual.get());

      return std::make_optional<representation>({std::move(unique), std::move(logical), std::move(visual)});
   }
   case gauges::type::twitter:
   {
      auto logical = std::make_unique<gauges::twitter>(set.gauge_stylesheet, gc.parameters);
      auto visual = std::make_unique<gui::webport>(gc.parameters);
      visual->setObjectName(std::string("twitter") + std::to_string(unique.id()));

      visual->new_settings.connect(&gauges::twitter::receive_new_settings, logical.get());
      logical->content_ready.connect(&gui::webport::setHtml, visual.get());

      return std::make_optional<representation>({std::move(unique), std::move(logical), std::move(visual)});
   }
   }
   return std::nullopt; // should never happen (tm)
}

}