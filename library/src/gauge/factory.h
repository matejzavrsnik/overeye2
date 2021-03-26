#pragma once

#include "gauge.h"
#include <memory>

namespace library { struct settings; }

namespace gauges
{

struct configuration;
struct representation;

std::optional<representation>
gauge_factory (
   const configuration& gc,
   const library::settings& set
);

}
