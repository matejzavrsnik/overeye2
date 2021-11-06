#ifndef OPROJECT_OVEREYE_JSON_H
#define OPROJECT_OVEREYE_JSON_H

#include "../gauge/location.h"
#include "../gauge/configuration.h"

#include <QJsonObject>


namespace utils
{

gauge::location
read_gauge_location (
   const QJsonObject& json_object);

gauge::configuration
read_gauge_configuration (
   const QJsonObject& json_object);

}

#endif //OPROJECT_OVEREYE_JSON_H
