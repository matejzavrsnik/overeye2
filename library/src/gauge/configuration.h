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
   std::map<std::string, std::string> settings;
   int id;
};

}
