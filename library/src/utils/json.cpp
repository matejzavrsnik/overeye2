#include "json.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <extension/qt/json.h>

namespace utils
{

gauge::location
read_gauge_location (const QJsonObject& json_object)
{
   QJsonArray json_loc_arr = mzlib::read_array(json_object, "location");
   std::vector<int> loc_numbers = mzlib::read_as_numbers<int>(json_loc_arr);

   if (loc_numbers.size() != 4)
      throw mzlib::exception::parse_error("location needs 4 and only 4 numbers");

   // order matters
   gauge::location
      loc{.row = loc_numbers[0], .col = loc_numbers[1], .row_span = loc_numbers[2], .col_span = loc_numbers[3],};

   return loc;
}

gauge::configuration
read_gauge_configuration (const QJsonObject& json_object)
{
   bool has_type = false, has_location = false; // required for all

   gauge::configuration new_gauge;
   for (const QString& key: json_object.keys())
   {
      if (key == "type")
      {
         new_gauge.type = gauge::to_type(mzlib::read_string(json_object, "type"));
         has_type = true;
      }
      else if (key == "location")
      {
         new_gauge.location = utils::read_gauge_location(json_object);
         has_location = true;
      }
      else
         new_gauge.settings.push_back(
            gauge::basic_setting{.tag = key.toStdWString(), .value = mzlib::read_string(json_object, key)}
         );
   }

   if (!has_type || !has_location)
      throw mzlib::exception::parse_error("gauge definition lacks type or location");

   return new_gauge;
}

logic::settings
deserialise_settings(
   const std::wstring& json_string)
{
   logic::settings set;

   QJsonObject root_object = mzlib::get_json_object(json_string);

   set.dialog_stylesheet = mzlib::read_string(root_object, "dialog_stylesheet");
   set.gauge_stylesheet = mzlib::read_string(root_object, "gauge_stylesheet");

   QJsonArray gauge_configurations = mzlib::read_array(root_object, "gauge_configurations");
   for (auto gauge_configuration: gauge_configurations)
   {
      const QJsonObject& json_object = gauge_configuration.toObject();
      gauge::configuration gc = utils::read_gauge_configuration(json_object);
      set.gauge_configurations.push_back(gc);
   }

   return set;
}

std::wstring
serialise_settings (
   const logic::settings& set)
{
   QJsonObject json;
   // todo: there are json utils for reading, add for writing
   json["dialog_stylesheet"] = mzlib::convert<QJsonValue>(set.dialog_stylesheet);
   json["gauge_stylesheet"] = mzlib::convert<QJsonValue>(set.gauge_stylesheet);

   QJsonArray gaugeConfigsArray;
   for (auto& gc : set.gauge_configurations)
   {
      QJsonObject gaugeConfig;
      gaugeConfig["type"] = mzlib::convert<QJsonValue>(from_type(gc.type));

      QJsonArray gaugeLocationArray;
      gaugeLocationArray.append(mzlib::convert<QJsonValue>(gc.location.row));
      gaugeLocationArray.append(mzlib::convert<QJsonValue>(gc.location.col));
      gaugeLocationArray.append(mzlib::convert<QJsonValue>(gc.location.row_span));
      gaugeLocationArray.append(mzlib::convert<QJsonValue>(gc.location.col_span));
      gaugeConfig["location"] = gaugeLocationArray;

      for(auto& gc_setting : gc.settings) {
         gaugeConfig[mzlib::convert<QString>(gc_setting.tag)] = mzlib::convert<QJsonValue>(gc_setting.value);
      }
      gaugeConfigsArray.append(gaugeConfig);
   }
   json["gauge_configurations"] = gaugeConfigsArray;

   QJsonDocument json_document(json);

   std::wstring serialised = mzlib::convert<std::wstring>(json_document.toJson());
   return serialised;
}

}
