#pragma once

#include "settings.h"

namespace logic
{

settings
load_settings ();

void
save_settings (
   const settings& set );

}

