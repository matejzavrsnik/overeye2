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

namespace gauges
{

twitter::twitter (
   const std::wstring& style,
   const parameters& page_parameters
) :
   general(style, {})
{
   // twitter gauge will control the {content} tag, so it's setting it to not be a user setting
   set_parameter(general::tags::content(), html(), false, general::tags::content());
   for (
      const auto& page_parameter : page_parameters
      )
   {
      set_parameter(page_parameter.get_tag(), page_parameter.get_value(), true, page_parameter.get_name());
   }
}

const std::wstring&
twitter::tags::handle ()
{
   static const std::wstring tag{L"{twitter_handle}"};
   return tag;
}

}

