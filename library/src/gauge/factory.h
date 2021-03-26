#pragma once

#include "gauge.h"
#include <memory>

namespace library { struct settings; }

namespace gauges
{

struct configuration;

std::unique_ptr<gauges::gauge>
gauge_factory (
   const configuration& gc,
   const library::settings& set
);

}
