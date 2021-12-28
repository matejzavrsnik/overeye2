#ifndef OPROJECT_OVEREYE_JSON_H
#define OPROJECT_OVEREYE_JSON_H

#include "../gauge/location.h"
#include "../gauge/configuration.h"
#include "../logic/settings.h"

#include <QJsonObject>

namespace utils
{

// json -> settings

gauge::configuration
read_gauge_configuration (
   const QJsonObject& json_object);

logic::settings
deserialise_settings(
   const std::string& json_string);

// settings -> json


QJsonObject&
add_settings (
   QJsonObject& gaugeConfig,
   const std::vector<gauge::basic_setting>& settings
);

QJsonArray
configurations_to_json_array(
   const std::vector<gauge::configuration>& configurations);

std::string
serialise_settings (
   const logic::settings& set);

}

#endif //OPROJECT_OVEREYE_JSON_H
