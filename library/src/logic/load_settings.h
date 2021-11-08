#pragma once

#include "settings.h"

namespace logic
{

settings
load_settings (
   std::optional<std::wstring> default_json,
   std::optional<std::wstring> settings_filename
   );

void
save_settings (
   settings set );

}

