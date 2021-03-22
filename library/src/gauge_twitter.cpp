

#include "gauge_twitter.h"
#include <string/replace.h>

namespace library
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

   gauge_twitter::gauge_twitter (
      std::wstring_view style,
      std::wstring_view twitter_handle
   ) :
      gauge_web(style, twitter_embedded_html()),
      m_twitter_handle(twitter_handle)
   {
   };

   std::wstring
   gauge_twitter::render (std::wstring page_template)
   {
      mzlib::string_replace(page_template, std::wstring_view(L"{twitter_handle}"), m_twitter_handle);
      return page_template;
   };


}

