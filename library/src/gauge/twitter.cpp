#include "twitter.h"

namespace
{

const std::string&
twitter_embedded_html ()
{
   static const std::string html = R"(
   <style type="text/css">
      body { overflow:hidden; }
   </style>
   <a class="twitter-timeline"
      href="https://twitter.com/{handle}"
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
   const std::string& style,
   std::shared_ptr<parameters> user_settings
) :
   webport(style, user_settings)
{
   // setup settings expected for this gauge
   m_settings->set_or_add_internal_setting(webport::tags::content(), twitter_embedded_html()); // taking over {content} tag from user
   m_settings->set_or_add_user_setting(twitter::tags::handle(), "", "Handle");
}

const std::string&
twitter::tags::handle ()
{
   static const std::string tag{"{handle}"};
   return tag;
}

}

