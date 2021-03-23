//
// Created by matej on 23/03/2021.
//

#ifndef OPROJECT_OVEREYE_PARAMETERS_H
#define OPROJECT_OVEREYE_PARAMETERS_H

#include <string>
#include <vector>

namespace gauges
{

struct parameter
{
   std::wstring tag;
   std::wstring replacement;
   bool user_setting;
};

using parameters = std::vector<parameter>;

}

#endif //OPROJECT_OVEREYE_PARAMETERS_H
