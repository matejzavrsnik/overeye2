#pragma once

#include "gauge.h"
#include "configuration.h"
#include <string>

namespace gauges
{

// webport gauge
// usable on its own, but also intended for further specialisation
class webport : public gauge
{

public:

   webport (
      const std::wstring& style,
      const parameters& page_parameters
   );

   sigslot::signal<const std::wstring&> content_ready;

   void
   display () override;

   void
   receive_new_settings (const gauges::parameters& parameters);

protected:

   parameters m_parameters;

   static std::wstring
   render (
      const std::wstring& page_template,
      const parameters& page_parameters
   );

public:

   class tags
   {
      friend class webport;

   private:

      const static std::wstring&
      genesis ();

   public:

      const static std::wstring&
      style ();

      const static std::wstring&
      content ();

   };

};

}
