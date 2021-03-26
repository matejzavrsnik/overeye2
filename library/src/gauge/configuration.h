#pragma once

#include "types.h"
#include "parameters.h"
#include <string_view>

namespace gauges
{

struct configuration
{
   gauges::type type = gauges::type::webport;
   int row{};
   int col{};
   int row_span{};
   int col_span{};
   gauges::parameters parameters;
};

}
