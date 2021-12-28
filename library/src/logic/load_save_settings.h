#pragma once

#include "settings.h"

#include <lang/binary_options.h>
#include <lang/exceptions.h>
#include <filesystem/filesystem_proxy.h>
#include <QDir>
#include <QStandardPaths>
#include <tools/converters.h>
#include <iostream>

class filesystem_extended : public mzlib::filesystem_proxy
{
public:

   std::filesystem::path
   get_system_app_config_location() const override
   {
      auto appConfigLocation = QDir{QStandardPaths::writableLocation(QStandardPaths::StandardLocation::AppConfigLocation)};
      return mzlib::convert<std::filesystem::path>(appConfigLocation.path());
   }

};

namespace logic
{

const std::string&
default_settings_content ();

settings
load_settings (
   const mzlib::filesystem_proxy& fs = filesystem_extended{});

void
save_settings (
   const settings& set,
   const mzlib::filesystem_proxy& fs = filesystem_extended{});

}

