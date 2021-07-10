#pragma once

#include "interface.h"
#include <memory>

namespace library { struct settings; }

namespace gauge
{

struct configuration;
struct representation;

std::unique_ptr<representation>
gauge_factory (
   const configuration& gc,
   const std::wstring& gauge_stylesheet
);

}
