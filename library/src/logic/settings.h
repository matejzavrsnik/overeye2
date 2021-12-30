#pragma once

#include "../gauge/configuration.h"

#include <string_view>
#include <vector>

namespace logic
{

struct settings
{
   std::string dialog_stylesheet;
   std::string gauge_stylesheet;
   std::vector<gauge::configuration> gauge_configurations;
};

}