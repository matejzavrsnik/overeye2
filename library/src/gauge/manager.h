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

   std::vector<representation> m_gauges;
   QGridLayout* m_grid;

public:

   explicit manager (QGridLayout* grid);

   void
   add (
      representation gauge
   );

   std::future<void> f;
   void test()
   {
      f = std::async(std::launch::async, [this](){
         using namespace std::chrono_literals;
         std::this_thread::sleep_for(5000ms);
         dynamic_cast<gauge::clock*>(m_gauges[0].logical.get())->tick();
      });
   }

   void tick()
   {

   }

};

}
