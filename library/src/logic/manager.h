#pragma once

#include "../gauge/factory.h"
#include "../gauge/configuration.h"
#include <vector>
#include <memory>

#include "../gauge/clock.h"
#include "representation.h"
#include "../gui/screen.h"
#include "../logic/settings.h"

namespace gauge
{

class manager
{

private:

   std::vector<std::unique_ptr<representation>> m_gauges;
   std::unique_ptr<gui::screen> m_screen;
   logic::settings m_settings;

   void
   add (
      std::unique_ptr<representation> gauge
   );

public:

   explicit manager (const logic::settings& settings);

   void
   show ();

   logic::settings
   collect_settings();

};

}
