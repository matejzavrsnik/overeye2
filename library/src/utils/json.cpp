#include "json.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <extension/qt/json.h>

namespace utils
{

gauge::configuration
read_gauge_configuration (const QJsonObject& json_object)
{
   bool has_type = false;

   gauge::configuration new_gauge;
   for (const QString& key: json_object.keys())
   {
      if (key == "type")
      {
         new_gauge.type = gauge::to_type(mzlib::read_string(json_object, key));
         has_type = true;
      }
      else
         new_gauge.settings[key.toStdString()] = mzlib::read_string(json_object, key);
   }

   if (!has_type)
      throw mzlib::exception::parse_error("gauge definition doesn't specify type");

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


QJsonObject&
add_settings (
   QJsonObject& gaugeConfig,
   const std::map<std::string, std::string>& settings
)
{
   for(auto& [tag, value] : settings) {
      gaugeConfig[mzlib::convert<QString>(tag)] = mzlib::convert<QJsonValue>(value);
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

   json["dialog_stylesheet"] = mzlib::convert<QJsonValue>(set.dialog_stylesheet);
   json["gauge_stylesheet"] = mzlib::convert<QJsonValue>(set.gauge_stylesheet);
   json["gauge_configurations"] = configurations_to_json_array(set.gauge_configurations);

   QJsonDocument json_document(json);

   std::string serialised = mzlib::convert<std::string>(json_document.toJson());
   return serialised;
}

}
