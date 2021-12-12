#include "load_settings.h"
#include "../utils/json.h"

#include <QStandardPaths>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDir>
#include <extension/qt/json.h>
#include <tools/converters.h>
#include <iostream>

namespace
{
   QFile
   default_settings_file ()
   {
      auto appConfigLocation = QDir{QStandardPaths::writableLocation(QStandardPaths::StandardLocation::AppConfigLocation)};
      return QFile{appConfigLocation.filePath("settings.json")};
   }

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
   QFile settingsFile = default_settings_file();
   std::wstring json_string =
      settingsFile.exists() && settingsFile.open(QIODevice::ReadOnly)
      ? mzlib::convert<std::wstring>(settingsFile.readAll())
      : default_settings_content ();

   settings set = utils::deserialise_settings(json_string);

   return set;
}



void
logic::save_settings (
   const logic::settings& set )
{
   std::wstring serialised = utils::serialise_settings(set);

   QFile settingsFile = default_settings_file();
   settingsFile.open(QIODevice::WriteOnly);
   settingsFile.write(mzlib::convert<QByteArray>(serialised));
}


