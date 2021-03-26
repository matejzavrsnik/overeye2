#pragma once

#include "gauge/configuration.h"

#include <string_view>
#include <vector>

namespace library
{

struct settings
{
   std::wstring dialog_stylesheet;
   std::wstring gauge_stylesheet;
   std::vector<gauges::configuration> gauge_configurations;
};

}
