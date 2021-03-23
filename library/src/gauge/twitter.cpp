

#include "twitter.h"
#include <string/replace.h>

namespace gauges
{

// basically a constant html string, but written here to make class more to the point
std::wstring
twitter_embedded_html ()
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
};

   twitter::twitter (
      std::wstring_view style,
      parameters params
   ) :
      general(style, {{L"{content}", twitter_embedded_html()}}),
      m_twitter_parameters(params)
   {
   };

   std::wstring
   twitter::render (std::wstring page_template)
   {
      for(const auto& parameter : m_twitter_parameters)
         mzlib::string_replace(page_template, parameter.first, parameter.second);
      return page_template;
   };


}

