#pragma once

#include "webport.h"
#include "i_gauge_parameters.h"

namespace gauge
{

class twitter : public webport
{

public:

   twitter (
      const std::string& style,
      std::shared_ptr<i_gauge_parameters> user_settings
   );

   class tags
   {
   public:

      const static std::string&
      handle ();

   };

};


}
