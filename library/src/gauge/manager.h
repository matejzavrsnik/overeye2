#pragma once

#include "factory.h"
#include "configuration.h"
#include <vector>
#include <memory>

class QGridLayout;

namespace gauges
{

class representation;

class manager
{

private:

   std::vector<representation> m_gauges;
   QGridLayout* m_grid;

public:

   explicit manager (QGridLayout* grid);

   void
   add (
      representation gauge
   );

};

}
