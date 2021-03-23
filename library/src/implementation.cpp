#include "../include/library/header.h"

#include "internal.h"
#include "qt/dialog.h"
#include "gauge/manager.h"
#include "gauge/types.h"
#include "gauge/factory.h"
#include "settings.h"

#include <tools/converters.h>

#include <QApplication>

namespace library
{

double sum(double a, double b)
{
   return internal::sum_implementation(a, b);
}


int run_main(int argc, char ** argv)
{
   QApplication app (argc, argv);

   settings set;
   set.dialog_stylesheet = L"background-color: rgb(46, 52, 54)";
   set.gauge_stylesheet = L"body { color: yellow; background-color: rgb(50, 56, 58) }";
   set.gauge_configurations = {
      {gauges::type::generic, 0, 0, 1, 1, {{L"{content}", L"Hello"}}},
      {gauges::type::generic, 0, 1, 1, 1, {{L"{content}", L"<iframe src=\"https://mars.nasa.gov/layout/embed/image/320mosaicvert/?i=N_L000_0621XEDR031POLTSB1330_DRIVEM1\" width=\"320\" height=\"320\" scrolling=\"no\" frameborder=\"0\"></iframe>"}}},
      {gauges::type::twitter, 0, 2, 2, 1, {{L"{twitter_handle}", L"NASAPersevere"}}},
      {gauges::type::generic, 1, 1, 1, 1, {{L"{content}", L"<h1>Hello \U0001f34c\U0001f34c\U0001F412<h1>"}}},
   };

   dialog dlg;
   dlg.setWindowState(Qt::WindowFullScreen);
   dlg.setStyleSheet(mzlib::convert<QString>(set.dialog_stylesheet));

   gauges::manager gm(dlg.grid());

   for(auto& gc : set.gauge_configurations)
   {
      auto g = gauges::gauge_factory(gc, set);
      if(g)
      {
         g->display();
         gm.add(std::move(g), gc.row, gc.col, gc.row_span, gc.col_span);

      }
   }

   dlg.show();

   return app.exec();
}

}
