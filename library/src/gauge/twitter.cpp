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

twitter::twitter (std::shared_ptr<parameters> parameters) :
   webport(parameters)
{
   m_parameters->set(webport::tags::content(), twitter_embedded_html());

   m_parameters->make_internal(webport::tags::content()); // taking over {content} tag from user
   m_parameters->make_user_facing(twitter::tags::handle(), "Handle");
}

const std::string&
twitter::tags::handle ()
{
   static const std::string tag{"{handle}"};
   return tag;
}

}

