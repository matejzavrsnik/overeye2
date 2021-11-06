#include "load_settings.h"
#include "../utils/json.h"

#include <QStandardPaths>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <extension/qt/json.h>

namespace
{

const std::wstring&
default_settings_content ()
{
   static const std::wstring json = LR"(
{
   "dialog_stylesheet" : "background-color: rgb(46, 52, 54) ",
   "gauge_stylesheet" : "body { color: rgb(179, 179, 0); background-color: rgb(50, 56, 58) } ",
   "gauge_configurations" :
   [  {  "type" : "clock",
         "location" : [0, 0, 1, 1],
         "{format}" : "ddd MMMM d yyyy hh:mm:ss",
         "{timezone}" : "America/Tijuana"
      },
      {  "type" : "webport",
         "location" : [0, 1, 1, 1],
         "{content}" : "<iframe src=\"https://mars.nasa.gov/layout/embed/image/320mosaicvert/?i=N_L000_0621XEDR031POLTSB1330_DRIVEM1\" width=\"320\" height=\"320\" scrolling=\"no\" frameborder=\"0\"></iframe>"
      },
      {  "type" : "twitter",
         "location" : [0, 2, 2, 1],
         "{handle}" : "NASAPersevere"
      },
      {  "type" : "webport",
         "location" : [1, 1, 1, 1],
         "{content}" : "<h1>Hello 🍌🐒<h1>"
      }
   ]
})";

   return json;
}

}

logic::settings
logic::load_settings ()
{
   settings set;

   // Todo: load from file, if none, then load default config
   auto json_string = default_settings_content();

   QJsonObject root_object = mzlib::get_json_object(json_string);

   set.dialog_stylesheet = mzlib::read_string(root_object, "dialog_stylesheet");
   set.gauge_stylesheet = mzlib::read_string(root_object, "gauge_stylesheet");

   QJsonArray gauge_configurations = mzlib::read_array(root_object, "gauge_configurations");
   for(auto gauge_configuration : gauge_configurations)
   {
      const QJsonObject& json_object = gauge_configuration.toObject();
      gauge::configuration gc = utils::read_gauge_configuration(json_object);
      set.gauge_configurations.push_back(gc);
   }

   return set;
}

