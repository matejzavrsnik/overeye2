//
// Created by matej on 22/03/2021.
//

#ifndef OPROJECT_OVEREYE_TWITTER_H
#define OPROJECT_OVEREYE_TWITTER_H

#include "general.h"

namespace gauges
{

class twitter : public general
{

public:

   twitter (
      std::wstring style,
      const cparameters& page_parameters);

   class tags
   {
      friend class twitter;

   public:

      const static std::wstring& handle();

   };

};



}

#endif //OPROJECT_OVEREYE_TWITTER_H
