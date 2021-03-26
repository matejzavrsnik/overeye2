#pragma once

#include "../qt/gauge.h"
#include "../gauge/parameters.h"

namespace gauges
{

// base class for all gauges
// gauges::base is sort of a sibling of qt::gauge
// two audiences: as an interface for gauge for the rest of the logic and a containment for qt widget that displays it.
// the intention was to split qt(ui) code from my(logic) code as much as possible, but they still need to communicate.
// guideline: think of trying to replace qt in the future; ideally the changes for gauges would be done in this class only.
// why is "general" not base class? Not all gauges will be web based.
class base
{
public:

   virtual void
   display () = 0;

   ::gauge*
   qt ();

protected:

   explicit base ();

   mzlib::unique m_unique;
   parameters m_parameters;

   void
   set_html (std::wstring_view html);

private:

   std::unique_ptr<::gauge> m_qt_gauge;

   void
   update_settings (const gauges::parameters& parameters);


};

}

