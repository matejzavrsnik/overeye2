#include "../include/library/overeye.h"

#include "gui/screen.h"
#include "gauge/factory.h"
#include "logic/load_settings.h"
#include "logic/manager.h"

#include <lang/exceptions.h>

#include <QApplication>
#include <QMessageBox>

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

   try
   {
      app.setApplicationName("overeye");
      app.setApplicationVersion("2.0");

      auto set = logic::load_settings();

      gui::screen screen;
      //screen.setWindowState(Qt::WindowFullScreen);
      screen.setStyleSheet(QString::fromStdWString(set.dialog_stylesheet));

      gauge::manager gm(screen.grid());

      for (auto& gc: set.gauge_configurations)
      {
         auto g = gauge::gauge_factory(gc, set.gauge_stylesheet);
         gm.add(std::move(g));
      }

      screen.show();

      // weird things happen if QApplication::exec() isn't inside try-block
      return QApplication::exec();
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
