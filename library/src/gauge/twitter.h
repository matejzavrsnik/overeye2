#pragma once

#include "webport.h"
#include "parameters.h"

namespace gauge
{

class twitter : public webport
{

public:

   twitter (std::shared_ptr<parameters> parameters);

   class tags
   {
   public:

      const static std::string&
      handle ();

   };

};


}
