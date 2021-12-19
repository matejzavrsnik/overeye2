#include "load_save_settings.h"
#include "../utils/json.h"

#include <QStandardPaths>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDir>

#include <tools/converters.h>
#include <iostream>


   //std::filesystem::path
   //default_settings_file (const filesystem_interface& fsi)
   //{
   //   auto appConfigLocation = fsi.get_system_app_config_location();
   //   appConfigLocation /= L"settings.json";
   //   return appConfigLocation;
   //   //auto appConfigLocation = QDir{QStandardPaths::writableLocation(QStandardPaths::StandardLocation::AppConfigLocation)};
   //   //return QFile{appConfigLocation.filePath("settings.json")};
//
   //}







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

settings
load_settings (
   const mzlib::filesystem_proxy& fs
)
{
   auto app_config_location = fs.get_system_app_config_location();

   auto app_config_file = app_config_location / std::filesystem::path{L"settings.json"};
   std::string json_string;
   if (fs.exists(app_config_file) && fs.is_regular_file(app_config_file))
   {
      json_string = fs.read_file(app_config_file);
   }

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

   auto app_config_location = fs.get_system_app_config_location();
   if (!fs.exists(app_config_location))
   {
      fs.create_directories(app_config_location);
   }

   auto app_config_file = app_config_location / std::filesystem::path{L"settings.json"};
   fs.save_file(app_config_file, serialised);
}
