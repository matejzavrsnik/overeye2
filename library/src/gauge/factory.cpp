#include "factory.h"

#include "types.h"
#include "general.h"
#include "twitter.h"
#include "../settings.h"

namespace gauges
{

std::unique_ptr<gauges::gauge>
gauge_factory (
   const configuration& gc,
   const library::settings& set
)
{
   switch (gc.type)
   {
   case gauges::type::general:return std::make_unique<gauges::general>(set.gauge_stylesheet, gc.parameters);
   case gauges::type::twitter:return std::make_unique<gauges::twitter>(set.gauge_stylesheet, gc.parameters);
   }
   return nullptr; // should never happen (tm)
}

}