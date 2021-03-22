//
// Created by matej on 22/03/2021.
//

#include "gauge_factory.h"

#include "gauge_types.h"
#include "gauge_web.h"
#include "gauge_twitter.h"
#include "gauge_configuration.h"
#include "settings.h"

#include <memory>

namespace library
{

std::unique_ptr <::gauge>
gauge_factory (
   const gauge_configuration& gc,
   const settings& set
)
{
   switch (gc.type)
   {
   case gauge_type::generic:
      return std::make_unique<gauge_web>(set.gauge_stylesheet, gc.content);
   case gauge_type::twitter:
      return std::make_unique<gauge_twitter>(set.gauge_stylesheet, gc.content);
   }
   return nullptr; // should never happen (tm)
}

}