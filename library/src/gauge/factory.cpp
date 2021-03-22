//
// Created by matej on 22/03/2021.
//

#include "factory.h"

#include "types.h"
#include "web.h"
#include "twitter.h"
#include "configuration.h"
#include "../settings.h"

#include <memory>

namespace gauges
{

std::unique_ptr <::gauge>
gauge_factory (
   const configuration& gc,
   const library::settings& set
)
{
   switch (gc.type)
   {
   case gauges::type::generic:
      return std::make_unique<gauges::web>(set.gauge_stylesheet, gc.content);
   case gauges::type::twitter:
      return std::make_unique<gauges::twitter>(set.gauge_stylesheet, gc.content);
   }
   return nullptr; // should never happen (tm)
}

}