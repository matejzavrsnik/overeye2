#pragma once

#include "webport.h"

namespace gauge
{

class twitter : public webport
{

public:

   twitter (
      const std::wstring& style,
      std::shared_ptr<interface_gauge_settings> user_settings
   );

   class tags
   {
   public:

      const static std::wstring&
      handle ();

   };

};


}
