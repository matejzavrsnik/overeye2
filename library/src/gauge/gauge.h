#pragma once

#include "../qt/gauge.h"
#include "../gauge/parameters.h"

namespace gauges
{

// base class for all gauges
// audience: an interface for gauge for the rest of the logic + what's common, ie unique member.
// Q: Why is "webport" not base class? A: Not all gauges will be web based.
class gauge
{

public:

   virtual void
   display () = 0;

   virtual ::gauge*
   graphical_representation() = 0;

protected:

   explicit gauge () = default;

   mzlib::unique m_unique;
   
};

}

