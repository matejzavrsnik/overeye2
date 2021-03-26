#pragma once

#include "interface.h"
#include <memory>

namespace library { struct settings; }

namespace gauge
{

struct configuration;
struct representation;

std::optional<representation>
gauge_factory (
   const configuration& gc,
   const library::settings& set
);

}
