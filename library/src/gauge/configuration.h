//
// Created by matej on 22/03/2021.
//

#ifndef OPROJECT_OVEREYE_CONFIGURATION_H
#define OPROJECT_OVEREYE_CONFIGURATION_H

#include "types.h"
#include <string_view>

namespace gauges
{

struct configuration
{
   gauges::type type;
   int row;
   int col;
   int row_span;
   int col_span;
   std::wstring_view content;
};

}

#endif //OPROJECT_OVEREYE_CONFIGURATION_H
