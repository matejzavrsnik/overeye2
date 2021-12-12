#pragma once

#include "../gauge/configuration.h"

#include <string_view>
#include <vector>

namespace logic
{

struct settings
{
   std::wstring dialog_stylesheet;
   std::wstring gauge_stylesheet;
   std::vector<gauge::configuration> gauge_configurations;
};

}