#pragma once

#include "i_gauge.h"
#include "configuration.h"
#include "i_gauge_parameters.h"

#include <tools/metronome.h>

#include <string>

namespace gauge
{

// webport gauge
// usable on its own, but also intended for further specialisation
class webport : public i_gauge
{

public:

   webport (
      const std::string& style,
      std::shared_ptr<i_gauge_parameters> settings
   );

   virtual ~webport();

   sigslot::signal<const std::string&> send_content;
   sigslot::signal<> request_refresh;

   void
   apply_user_settings(std::map<std::string, basic_setting> settings);

   void
   display () override;

protected:

   std::shared_ptr<i_gauge_parameters> m_settings;

   virtual std::string
   render (
      const std::string& page_template,
      std::shared_ptr<i_gauge_parameters> page_parameters
   );

   void
   set_content_refresh_period (
      std::chrono::milliseconds period
   );

private:

   mzlib::metronome<sigslot::signal<>> m_timer;

   void
   tick ();

public:

   class tags
   {
      friend class webport;

   private:

      const static std::string&
      genesis (); //todo: too complicated for no reason

   public:

      const static std::string&
      style ();

      const static std::string&
      content ();

   };

};

}
