#include "../include/library/overeye.h"

#include "gui/screen.h"
#include "gauge/factory.h"
#include "logic/load_settings.h"
#include "logic/manager.h"

#include <lang/exceptions.h>

#include <QApplication>
#include <QMessageBox>
#include <iostream>

namespace
{
const std::wstring&
default_settings_content ()
{
   static const std::wstring json = LR"(
{
   "dialog_stylesheet" : "background-color: rgb(46, 52, 54) ",
   "gauge_stylesheet" : "body { color: rgb(179, 179, 0); background-color: rgb(50, 56, 58) } ",
   "gauge_configurations" :
   [  {  "type" : "clock",
         "location" : [0, 0, 1, 1],
         "{format}" : "ddd MMMM d yyyy hh:mm:ss",
         "{timezone}" : "America/Tijuana"
      },
      {  "type" : "webport",
         "location" : [0, 1, 1, 1],
         "{content}" : "<iframe src=\"https://mars.nasa.gov/layout/embed/image/320mosaicvert/?i=N_L000_0621XEDR031POLTSB1330_DRIVEM1\" width=\"320\" height=\"320\" scrolling=\"no\" frameborder=\"0\"></iframe>"
      },
      {  "type" : "twitter",
         "location" : [0, 2, 2, 1],
         "{handle}" : "NASAPersevere"
      },
      {  "type" : "webport",
         "location" : [1, 1, 1, 1],
         "{content}" : "<h1>Hello 🍌🐒<h1>"
      }
   ]
})";

   return json;
}
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

   try
   {
      app.setApplicationName("overeye");
      app.setApplicationVersion("2.0");

      auto set = logic::load_settings(
         default_settings_content(),
         std::nullopt
         );

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

      logic::save_settings(set);

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
