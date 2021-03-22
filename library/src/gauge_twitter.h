//
// Created by matej on 22/03/2021.
//

#ifndef OPROJECT_OVEREYE_GAUGE_TWITTER_H
#define OPROJECT_OVEREYE_GAUGE_TWITTER_H

#include "gauge_web.h"

namespace library
{

class gauge_twitter : public library::gauge_web
{

private:

   std::wstring_view m_twitter_handle;

public:

   gauge_twitter (
      std::wstring_view style,
      std::wstring_view twitter_handle
   );

protected:

   // customisation point for additional rendering by derived classes
   virtual std::wstring
   render (std::wstring page_template) override;
};



}

#endif //OPROJECT_OVEREYE_GAUGE_TWITTER_H
