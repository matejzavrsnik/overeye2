#include "testing_tools.h"
#include "tools/random.h"

namespace testing_tools
{

std::string
sample_of_valid_settings_content ()
{
   std::string json = R"(
   {
      "dialog_stylesheet" : "background-color: rgb(46, 52, 54) ",
      "gauge_stylesheet" : "body { color: rgb(179, 179, 0); background-color: rgb(50, 56, 58) } ",
      "gauge_configurations" :
      [  {  "type" : "clock",
            "x" : "30",
            "y" : "0",
            "width" : "400",
            "height" : "400",
            "{format}" : "ddd MMMM d yyyy hh:mm:ss",
            "{timezone}" : "America/Tijuana"
         },
         {  "type" : "webport",
            "x" : "430",
            "y" : "0",
            "width" : "400",
            "height" : "400",
            "{content}" : "<iframe src=\"https://mars.nasa.gov/layout/embed/image/320mosaicvert/?i=N_L000_0621XEDR031POLTSB1330_DRIVEM1\" width=\"320\" height=\"320\" scrolling=\"no\" frameborder=\"0\"></iframe>"
         },
         {  "type" : "twitter",
            "x" : "830",
            "y" : "0",
            "width" : "400",
            "height" : "800",
            "{handle}" : "NASAPersevere"
         },
         {  "type" : "webport",
            "x" : "430",
            "y" : "400",
            "width" : "400",
            "height" : "400",
            "{content}" : "<h1>Hello 🍌🐒<h1>"
         }
      ]
   })";

   return json;
}

std::string
get_random_short_string()
{
   std::string short_string;
   while(short_string.length() < 5)
   {
      auto random_char = mzlib::get_random_between('0', '{');
      if (std::isalnum(random_char))
         short_string.push_back(random_char);
   }
   return short_string;
}

}
