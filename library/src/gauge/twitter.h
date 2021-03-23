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

private:

   parameters m_twitter_parameters;

public:

   twitter (
      std::wstring_view style,
      parameters parameters
   );

protected:

   // customisation point for additional rendering by derived classes
   virtual std::wstring
   render (std::wstring page_template) override;
};



}

#endif //OPROJECT_OVEREYE_TWITTER_H
