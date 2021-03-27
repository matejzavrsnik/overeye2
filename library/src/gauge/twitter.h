#pragma once

#include "webport.h"

namespace gauge
{

class twitter : public webport
{

public:

   twitter (
      const std::wstring& style,
      const parameters& page_parameters
   );

   class tags
   {
   public:

      const static std::wstring&
      handle ();

   };

};


}
