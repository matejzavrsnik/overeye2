//
// Created by matej on 22/03/2021.
//

#ifndef OPROJECT_OVEREYE_GAUGE_FACTORY_H
#define OPROJECT_OVEREYE_GAUGE_FACTORY_H

#include "gauge.h"
#include <memory>

class gauge;

namespace library
{

struct gauge_configuration;
struct settings;

std::unique_ptr <gauge>
gauge_factory (
   const gauge_configuration& gc,
   const settings& set
);

}

#endif //OPROJECT_OVEREYE_GAUGE_FACTORY_H
