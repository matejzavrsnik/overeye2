// to be moved to mzlib
#pragma once

#include <string>
#include <filesystem/filesystem_proxy.h>

namespace mzlib
{

std::string
load_settings(
   const mzlib::filesystem_proxy& fs,
   const std::string_view filename)
{
   auto app_config_location = fs.get_system_app_config_location();
   auto app_config_file = app_config_location / std::filesystem::path{filename};
   std::string settings;
   if (fs.exists(app_config_file) && fs.is_regular_file(app_config_file))
   {
      settings = fs.read_file(app_config_file);
   }
   return settings;
}

void
save_settings(
   const mzlib::filesystem_proxy& fs,
   const std::string_view filename,
   const std::string_view settings)
{
   auto app_config_location = fs.get_system_app_config_location();
   if (!fs.exists(app_config_location))
   {
      fs.create_directories(app_config_location);
   }

   auto app_config_file = app_config_location / std::filesystem::path{filename};
   fs.save_file(app_config_file, settings);
}

}
