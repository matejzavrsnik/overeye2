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
      std::wstring style,
      const parameters& page_parameters
   ) :
      general(style, {{general::tags::content(), html()}})
   {
      for(const auto& page_parameter : page_parameters)
         set_parameter(page_parameter.tag, page_parameter.replacement);
   };

   const std::wstring& twitter::tags::handle()
   {
      static const std::wstring tag{L"{twitter_handle}"};
      return tag;
   }

}

