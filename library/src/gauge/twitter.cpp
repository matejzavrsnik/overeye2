

#include "twitter.h"
#include <string/replace.h>

namespace gauges
{

// basically a constant html string, but written here to make class more to the point
std::wstring_view
twitter_embedded_html ()
{
   static const std::wstring_view html = LR"(
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
      std::wstring_view twitter_handle
   ) :
      general(style, twitter_embedded_html()),
      m_twitter_handle(twitter_handle)
   {
   };

   std::wstring
   twitter::render (std::wstring page_template)
   {
      mzlib::string_replace(page_template, std::wstring_view(L"{twitter_handle}"), m_twitter_handle);
      return page_template;
   };


}

