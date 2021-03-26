#pragma once

#include "gauge.h"
#include "configuration.h"
#include <string>

namespace gauges
{

// webport webport
// usable on its own, but intended for further specialisation
class webport : public gauge
{

private:

   std::unique_ptr<::webport> m_qt_gauge;
   const std::wstring m_page_template;
   std::wstring m_last_rendered_page;

   void
   set_html (std::wstring_view html);

   void
   update_settings (const gauges::parameters& parameters);

public:

   webport (
      const std::wstring& style,
      const parameters& page_parameters
   );

   void
   display () override;

   ::webport*
   graphical_representation() override;

protected:

   parameters m_parameters;

   static std::wstring
   render (
      const std::wstring& page_template,
      const parameters& page_parameters
   );

   void
   set_parameter (
      const std::wstring& tag,
      const std::wstring& value,
      bool user_setting,
      const std::wstring& friendly_name
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
