#pragma once

#include "base.h"
#include <memory>

namespace library { struct settings; }

namespace gauges
{

struct configuration;

std::unique_ptr<base>
gauge_factory (
   const configuration& gc,
   const library::settings& set
);

}
