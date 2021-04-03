#pragma once

#include "factory.h"
#include "configuration.h"
#include <vector>
#include <memory>

#include "clock.h"
#include "representation.h"

class QGridLayout;

namespace gauge
{

class representation;

class manager
{

private:

   std::vector<std::unique_ptr<representation>> m_gauges;
   QGridLayout* m_grid;

public:

   explicit manager (QGridLayout* grid);

   void
   add (
   std::unique_ptr<representation> gauge
   );

};

}
