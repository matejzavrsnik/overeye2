#include "../include/library/overeye.h"

#include "gui/screen.h"
#include "gauge/factory.h"
#include "logic/load_save_settings.h"
#include "logic/manager.h"
#include "logic/settings.h"

#include <lang/exceptions.h>

#include <QApplication>
#include <QMessageBox>
#include <iostream>

namespace
{

}

namespace library
{

int
run_main (
   int argc,
   char** argv
)
{
   // can't have this inside the try, because then I can't display error message box in catch
   QApplication app(argc, argv);
   app.setApplicationName("overeye");
   app.setApplicationVersion("2.0");

   try
   {
      auto settings = logic::load_settings();
      gauge::manager gauge_manager(settings);
      gauge_manager.show();

      auto exit_code = QApplication::exec();

      settings = gauge_manager.collect_settings();
      logic::save_settings(settings);

      return exit_code;
   }
   catch(mzlib::exception::parse_error& parse_error)
   {
      QMessageBox::critical(
         nullptr,
         QString::fromWCharArray(L"Unable to start"),
         QString::fromWCharArray(L"JSON error: ") + parse_error.what());
   }

   return -1;
}

}
