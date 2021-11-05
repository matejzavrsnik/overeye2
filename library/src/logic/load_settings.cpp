#include "load_settings.h"

#include "../gauge/webport.h"
#include "../gauge/clock.h"
#include "../gauge/twitter.h"

#include <lang/exceptions.h>

#include <QStandardPaths>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <iostream>

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

// general for qt json

QJsonObject
get_json_object (const std::wstring& json_string)
{
   auto byteArray = QString::fromStdWString(json_string).toUtf8();
   QJsonParseError parseError;
   QJsonDocument json_document = QJsonDocument::fromJson(byteArray, &parseError);
   if(parseError.error != QJsonParseError::NoError)
      throw mzlib::exception::parse_error(parseError.errorString().toStdString());
   QJsonObject root_object = json_document.object();
   return root_object;
}


QJsonValue
read_json_value (
   const QJsonObject& json_object,
   const QString key
)
{
   if (!json_object.contains(key))
      throw mzlib::exception::parse_error(
         std::string("Tried to read ") + key.toStdString() + std::string(" from settings file but it wasn't there.")
      );

   return json_object.value(key);
}

std::wstring
read_string (
   const QJsonObject& json_object,
   const QString key
)
{
   QJsonValue json_value = read_json_value(json_object, key);

   if (!json_value.isString())
      throw mzlib::exception::parse_error(
         std::string("Tried to read ") + key.toStdString() + std::string(" as string, but it isn't a string.")
      );

   std::wstring value = json_value.toString().toStdWString();
   return value;
}

QJsonArray
read_array (
   const QJsonObject& json_object,
   const QString key
)
{
   QJsonValue json_value = read_json_value(json_object, key);

   if (!json_value.isArray())
      throw mzlib::exception::parse_error(
         std::string("Tried to read ") + key.toStdString() + std::string(" as array, but it isn't an array.")
      );

   return json_value.toArray();
}

template<typename Number>
std::vector<Number> read_as_numbers(QJsonArray arr)
{
   std::vector<Number> numbers;
   for(auto number : arr)
      if(!number.isDouble())
         throw mzlib::exception::parse_error("expected only numbers");
      else
      {
         if constexpr(std::is_integral_v<Number>)
            numbers.push_back(number.toInt());
         else
            numbers.push_back(number.toDouble());
      }

   return numbers;
}

// specific for this project

gauge::location
read_gauge_location(const QJsonObject& json_object)
{
   QJsonArray json_loc_arr = read_array(json_object, "location");
   std::vector<int> loc_numbers = read_as_numbers<int>(json_loc_arr);

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
         new_gauge.type = gauge::to_type(read_string(json_object, "type"));
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
               .value = read_string(json_object, key)
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

   QJsonObject root_object = get_json_object(json_string);

   set.dialog_stylesheet = read_string(root_object, "dialog_stylesheet");
   set.gauge_stylesheet = read_string(root_object, "gauge_stylesheet");

   QJsonArray gauge_configurations = read_array(root_object, "gauge_configurations");
   for(auto gauge_configuration : gauge_configurations)
   {
      const QJsonObject& json_object = gauge_configuration.toObject();
      gauge::configuration gc = read_gauge_configuration(json_object);
      set.gauge_configurations.push_back(gc);
   }

   settings set_old;
   set_old.gauge_configurations = {
      {gauge::type::clock,
         gauge::location{0, 0, 1, 1},
         {{gauge::clock::tags::format(), L"ddd MMMM d yyyy hh:mm:ss"},
            {gauge::clock::tags::timezone(), L"America/Tijuana"}}},
      {gauge::type::webport,
         gauge::location{0, 1, 1, 1},
         {{gauge::webport::tags::content(),
            L"<iframe src=\"https://mars.nasa.gov/layout/embed/image/320mosaicvert/?i=N_L000_0621XEDR031POLTSB1330_DRIVEM1\" width=\"320\" height=\"320\" scrolling=\"no\" frameborder=\"0\"></iframe>"}}},
      {gauge::type::twitter,
         gauge::location{0, 2, 2, 1},
         {{gauge::twitter::tags::handle(), L"NASAPersevere"}}},
      {gauge::type::webport,
         gauge::location{1, 1, 1, 1},
         {{gauge::webport::tags::content(), L"<h1>Hello \U0001f34c\U0001f34c\U0001F412<h1>"}}}};

   return set;
}

