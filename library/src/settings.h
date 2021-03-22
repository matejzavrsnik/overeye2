//
// Created by matej on 22/03/2021.
//

#ifndef OPROJECT_OVEREYE_SETTINGS_H
#define OPROJECT_OVEREYE_SETTINGS_H

#include "gauge/configuration.h"

#include <string_view>
#include <vector>

namespace library
{

struct settings
{
   std::wstring_view dialog_stylesheet;
   std::wstring_view gauge_stylesheet;
   std::vector <gauges::configuration> gauge_configurations;
};

}

#endif //OPROJECT_OVEREYE_SETTINGS_H
