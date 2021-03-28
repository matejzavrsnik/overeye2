#pragma once

#include "interface.h"
#include "configuration.h"
#include <string>

namespace gauge
{

// webport gauge
// usable on its own, but also intended for further specialisation
class webport : public interface
{

public:

   webport (
      const std::wstring& style,
      const parameters& page_parameters
   );

   sigslot::signal<const std::wstring&> send_content;
   sigslot::signal<> request_content_refresh;

   void
   display () override;

   void
   receive_user_changes (const gauge::parameters& parameters);

protected:

   parameters m_parameters;

   virtual std::wstring
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
      genesis (); //todo: too complicated for no reason

   public:

      const static std::wstring&
      style ();

      const static std::wstring&
      content ();

   };

};

}
