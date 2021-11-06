#include "load_settings.h"

#include "../gauge/webport.h"
#include "../gauge/clock.h"
#include "../gauge/twitter.h"

#include <lang/exceptions.h>

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

gauge::location
read_gauge_location(const QJsonObject& json_object)
{
   QJsonArray json_loc_arr = mzlib::read_array(json_object, "location");
   std::vector<int> loc_numbers = mzlib::read_as_numbers<int>(json_loc_arr);

   if (loc_numbers.size() != 4)
      throw mzlib::exception::parse_error("location needs 4 and only 4 numbers");

   // order matters
   gauge::location loc {
      .row = loc_numbers[0],
      .col = loc_numbers[1],
      .row_span = loc_numbers[2],
      .col_span = loc_numbers[3],
   };

   return loc;
}

gauge::configuration
read_gauge_configuration(const QJsonObject& json_object)
{
   bool has_type = false, has_location = false; // required for all

   gauge::configuration new_gauge;
   for(const QString& key : json_object.keys())
   {
      if (key == "type")
      {
         new_gauge.type = gauge::to_type(mzlib::read_string(json_object, "type"));
         has_type = true;
      }
      else if (key == "location")
      {
         new_gauge.location = read_gauge_location(json_object);
         has_location = true;
      }
      else
         new_gauge.settings.push_back(
            gauge::basic_setting {
               .tag = key.toStdWString(),
               .value = mzlib::read_string(json_object, key)
            }
         );
   }

   if(!has_type || !has_location)
      throw mzlib::exception::parse_error("gauge definition lacks type or location");

   return new_gauge;
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
      gauge::configuration gc = read_gauge_configuration(json_object);
      set.gauge_configurations.push_back(gc);
   }

   return set;
}

