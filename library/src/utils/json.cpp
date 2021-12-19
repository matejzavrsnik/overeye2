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
   const std::string& json_string)
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


QJsonArray location_to_json_array(const gauge::location& location)
{
   QJsonArray gaugeLocationArray;
   gaugeLocationArray.append(mzlib::convert<QJsonValue>(location.row));
   gaugeLocationArray.append(mzlib::convert<QJsonValue>(location.col));
   gaugeLocationArray.append(mzlib::convert<QJsonValue>(location.row_span));
   gaugeLocationArray.append(mzlib::convert<QJsonValue>(location.col_span));
   return gaugeLocationArray;
}


QJsonObject&
add_settings (
   QJsonObject& gaugeConfig,
   const std::vector<gauge::basic_setting>& settings
)
{
   for(auto& setting : settings) {
      gaugeConfig[mzlib::convert<QString>(setting.tag)] = mzlib::convert<QJsonValue>(setting.value);
   }
   return gaugeConfig;
}

QJsonArray configurations_to_json_array(const std::vector<gauge::configuration>& configurations)
{
   QJsonArray gaugeConfigsArray;
   for (auto& config : configurations)
   {
      QJsonObject gaugeConfig;
      gaugeConfig["type"] = mzlib::convert<QJsonValue>(from_type(config.type));
      gaugeConfig["location"] = location_to_json_array(config.location);
      gaugeConfig = add_settings(gaugeConfig, config.settings);
      gaugeConfigsArray.append(gaugeConfig);
   }
   return gaugeConfigsArray;
}


std::string
serialise_settings (
   const logic::settings& set)
{
   QJsonObject json;
   // todo: there are json utils for reading, add for writing
   json["dialog_stylesheet"] = mzlib::convert<QJsonValue>(set.dialog_stylesheet);
   json["gauge_stylesheet"] = mzlib::convert<QJsonValue>(set.gauge_stylesheet);

   json["gauge_configurations"] = configurations_to_json_array(set.gauge_configurations);

   QJsonDocument json_document(json);

   std::string serialised = mzlib::convert<std::string>(json_document.toJson());
   return serialised;
}

}
