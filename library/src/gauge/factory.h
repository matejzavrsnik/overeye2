//
// Created by matej on 22/03/2021.
//

#ifndef OPROJECT_OVEREYE_FACTORY_H
#define OPROJECT_OVEREYE_FACTORY_H

#include "../qt/gauge.h"
#include <memory>

class gauge;

namespace library
{
struct settings;
}

namespace gauges
{

struct configuration;

std::unique_ptr <gauge>
gauge_factory (
   const configuration& gc,
   const library::settings& set
);

}

#endif //OPROJECT_OVEREYE_FACTORY_H
