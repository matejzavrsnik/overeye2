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

}
