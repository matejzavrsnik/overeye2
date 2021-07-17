#pragma once

#include "../gui/webport.h"
#include "parameters.h"

namespace gauge
{

// base class for all gauge
// audience: an i_gauge for webport for the rest of the logic + what's common, ie unique member.
// Q: Why is "webport" not base class? A: Not all gauge will be web based.
class i_gauge
{

public:

   virtual void
   display () = 0;

protected:

   explicit i_gauge () = default;

};

}

