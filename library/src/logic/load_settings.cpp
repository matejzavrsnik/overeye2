#include "load_settings.h"
#include "../utils/json.h"

#include <QStandardPaths>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <extension/qt/json.h>

namespace
{



}

logic::settings
logic::load_settings (
   std::optional<std::wstring> default_json,
   std::optional<std::wstring> settings_filename
   )
{
   if(!default_json && !settings_filename)
      throw mzlib::exception::invalid_values("no settings source");

   std::wstring json_string = settings_filename.has_value()
      ? L"" // todo
      : default_json.value();

   settings set = utils::read_settings(json_string);
   return set;

//   QJsonObject root_object = mzlib::get_json_object(json_string);
//
//   set.dialog_stylesheet = mzlib::read_string(root_object, "dialog_stylesheet");
//   set.gauge_stylesheet = mzlib::read_string(root_object, "gauge_stylesheet");
//
//   QJsonArray gauge_configurations = mzlib::read_array(root_object, "gauge_configurations");
//   for(auto gauge_configuration : gauge_configurations)
//   {
//      const QJsonObject& json_object = gauge_configuration.toObject();
//      gauge::configuration gc = utils::read_gauge_configuration(json_object);
//      set.gauge_configurations.push_back(gc);
//   }


}

