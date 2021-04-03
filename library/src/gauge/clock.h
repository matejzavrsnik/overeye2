#pragma once

#include "webport.h"
#include <QDateTime>

namespace gauge
{

class clock : public webport
{

public:

   clock (
      const std::wstring& style,
      std::shared_ptr<gauge_settings> user_settings
   );

private:

   QDateTime m_date_time;

   std::wstring
   render (
      const std::wstring& page_template,
      std::shared_ptr<gauge::gauge_settings> page_parameters
   ) override;

public:

   class tags
   {
      friend class clock;

   private:

      const static std::wstring&
      clock ();

   public:

      const static std::wstring&
      location ();

      const static std::wstring&
      format ();

   };

};


}
