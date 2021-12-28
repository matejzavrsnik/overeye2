#pragma once

#include "../gauge/factory.h"
#include "../gauge/configuration.h"
#include <vector>
#include <memory>

#include "../gauge/clock.h"
#include "representation.h"
#include "../gui/screen.h"

class QGridLayout;

namespace gauge
{

class representation;

class manager
{

private:

   std::vector<std::unique_ptr<representation>> m_gauges;
   std::unique_ptr<gui::screen> m_screen;

public:

   explicit manager (std::unique_ptr<gui::screen> screen);

   void
   add (
   std::unique_ptr<representation> gauge
   );

   void
   show ();

};

}
