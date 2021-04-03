#pragma once

#include "types.h"
#include "location.h"
#include "parameters.h"
#include <string_view>

namespace gauge
{

struct configuration
{
   gauge::type type = gauge::type::webport;
   gauge::location location;
   std::vector<gauge::setting> parameters;
};

}
