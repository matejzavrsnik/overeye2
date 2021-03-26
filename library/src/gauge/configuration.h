#pragma once

#include "types.h"
#include "location.h"
#include "parameters.h"
#include <string_view>

namespace gauges
{

struct configuration
{
   gauges::type type = gauges::type::webport;
   gauges::location location;
   gauges::parameters parameters;
};

}
