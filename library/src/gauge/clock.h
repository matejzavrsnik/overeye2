#pragma once

#include "webport.h"
#include "parameters.h"
#include <QDateTime>

namespace gauge
{

class clock : public webport
{

public:

   clock (std::shared_ptr<parameters> parameters);

private:

   QDateTime m_date_time;

   std::string
   render (
      const std::string& page_template,
      std::shared_ptr<parameters> page_parameters
   ) override;

public:

   class tags
   {
      friend class clock;

   private:

      const static std::string&
      clock ();

   public:

      const static std::string&
      timezone ();

      const static std::string&
      format ();

   };

};


}
