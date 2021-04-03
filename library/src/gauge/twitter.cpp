#include "twitter.h"

namespace
{

const std::wstring&
html ()
{
   static const std::wstring html = LR"(
   <a class="twitter-timeline"
      href="https://twitter.com/{twitter_handle}"
      data-width="400"
      data-height="1200"
      data-chrome="nofooter noborders transparent noscrollbar"
      data-theme="dark">
   Tweets by TwitterDev
   </a>
   <script async
           src="https://platform.twitter.com/widgets.js"
           charset="utf-8">
   </script>
   )";
   return html;
}

}

namespace gauge
{

twitter::twitter (
   const std::wstring& style,
   std::shared_ptr<interface_gauge_settings> user_settings
) :
   webport(style, user_settings)
{
   // setup parameters expected for this gauge
   m_parameters->set_or_add_internal_setting(webport::tags::content(), html()); // taking over {content} tag from user
   m_parameters->set_or_add_user_setting(twitter::tags::handle(), L"", L"Handle");
}

const std::wstring&
twitter::tags::handle ()
{
   static const std::wstring tag{L"{twitter_handle}"};
   return tag;
}

}

