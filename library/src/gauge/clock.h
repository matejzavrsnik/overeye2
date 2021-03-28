#pragma once

#include "webport.h"
#include <QDateTime>
#include <QTimer>

#include <future>

template<typename Signal>
class mytimer
{

public:

   Signal tick;

   void start(std::chrono::milliseconds period)
   {
      m_stop = false;
      _ = std::async(std::launch::async, &mytimer::runner, this, period);
   }

   void stop()
   {
      m_stop = true;
   }

   ~mytimer()
   {
      stop();
   }

private:

   bool m_stop;
   std::future<void> _; // future needs to outlive scope of std::async otherwise dtor will block

   void runner(std::chrono::milliseconds period)
   {
      while(!m_stop)
      {
         std::this_thread::sleep_for(period);
         tick();
      }
   }
};

namespace gauge
{



class clock : public webport
{

public:

   clock (
      const std::wstring& style,
      const parameters& page_parameters
   );

   void
   tick ();



   void
   receive_request_content()
   {
      display ();
   }

private:

   QDateTime m_date_time;

   mytimer<sigslot::signal<>> m_timer;



   std::wstring
   render (
      const std::wstring& page_template,
      const parameters& page_parameters
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
