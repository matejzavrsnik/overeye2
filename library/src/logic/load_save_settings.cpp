#include "load_save_settings.h"
#include "../utils/json.h"
#include "../utils/load_save_settings.h"

#include <tools/converters.h>

namespace logic
{

const std::string&
default_settings_content ()
{
   static const std::string json = R"(
{
   "dialog_stylesheet" : "background-color: rgb(46, 52, 54) ",
   "gauge_stylesheet" : "body { color: rgb(179, 179, 0); background-color: rgb(50, 56, 58) } ",
   "gauge_configurations" :
   [  {  "type" : "clock",
         "x" : 30,
         "y" : 0,
         "width" : 400,
         "height" : 400,
         "{format}" : "ddd MMMM d yyyy hh:mm:ss",
         "{timezone}" : "America/Tijuana"
      },
      {  "type" : "webport",
         "x" : 430,
         "y" : 0,
         "width" : 400,
         "height" : 400,
         "{content}" : "<iframe src=\"https://mars.nasa.gov/layout/embed/image/320mosaicvert/?i=N_L000_0621XEDR031POLTSB1330_DRIVEM1\" width=\"320\" height=\"320\" scrolling=\"no\" frameborder=\"0\"></iframe>"
      },
      {  "type" : "twitter",
         "x" : 830,
         "y" : 0,
         "width" : 400,
         "height" : 800,
         "{handle}" : "NASAPersevere"
      },
      {  "type" : "webport",
         "x" : 430,
         "y" : 400,
         "width" : 400,
         "height" : 400,
         "{content}" : "<h1>Hello 🍌🐒<h1>"
      }
   ]
})";

   return json;
}

settings
load_settings (
   const mzlib::filesystem_proxy& fs
)
{
   std::string json_string = mzlib::load_settings(fs, "settings.json");

   if (json_string.empty())
      json_string = default_settings_content();

   settings set = utils::deserialise_settings(json_string);

   return set;
}

}

void
logic::save_settings (
   const logic::settings& set,
   const mzlib::filesystem_proxy& fs)
{
   std::string serialised = utils::serialise_settings(set);
   mzlib::save_settings(fs, "settings.json", serialised);
}
