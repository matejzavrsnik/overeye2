#include "../include/library/overeye.h"

#include "gui/screen.h"
#include "gauge/factory.h"
#include "logic/load_save_settings.h"
#include "logic/manager.h"

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
      auto set = logic::load_settings();

      std::unique_ptr<gui::screen> screen = std::make_unique<gui::screen>();
      screen->setWindowState(Qt::WindowFullScreen);
      screen->setStyleSheet(QString::fromStdString(set.dialog_stylesheet));

      gauge::manager gauge_manager(std::move(screen));

      for (auto& gc: set.gauge_configurations)
      {
         auto g = gauge::gauge_factory(gc, set.gauge_stylesheet);
         gauge_manager.add(std::move(g));
      }

      gauge_manager.show();

      auto exit_code = QApplication::exec();
      logic::save_settings(set);

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
