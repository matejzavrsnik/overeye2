#pragma once

#include "webport.h"

namespace gauge
{

class twitter : public webport
{

public:

   twitter (
      const std::wstring& style,
      const std::vector<user_setting>& user_settings
   );

   class tags
   {
   public:

      const static std::wstring&
      handle ();

   };

};


}
