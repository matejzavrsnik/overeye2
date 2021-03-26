#pragma once

#include "general.h"

namespace gauges
{

class twitter : public general
{

public:

   twitter (
      const std::wstring& style,
      const parameters& page_parameters
   );

   class tags
   {
      friend class twitter;

   public:

      const static std::wstring&
      handle ();

   };

};


}
