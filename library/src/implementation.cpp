#include "../include/library/header.h"

#include "qt/dialog.h"
#include "gauge/manager.h"
#include "gauge/types.h"
#include "gauge/factory.h"
#include "settings.h"
#include "gauge/general.h"
#include "gauge/twitter.h"

#include <QApplication>

namespace library
{

int
run_main (
   int argc,
   char** argv
)
{
   QApplication app(argc, argv);

   settings set;
   set.dialog_stylesheet = L"background-color: rgb(46, 52, 54)";
   set.gauge_stylesheet = L"body { color: yellow; background-color: rgb(50, 56, 58) }";
   set.gauge_configurations = {
      //todo: don't like the fact that it needs to be set from outside of gauge which parameters are user setting and
      // which are not. That should be known to gauge, from outside only values for tags should come, not definitions
      {
         gauges::type::general, 0, 0, 1, 1, {
                                               {gauges::general::tags::content(), L"Hello", true,                                                                                                                                                                                    L"Content"}
                                            }
      },
      {
         gauges::type::general, 0, 1, 1, 1, {
                                               {gauges::general::tags::content(), L"<iframe src=\"https://mars.nasa.gov/layout/embed/image/320mosaicvert/?i=N_L000_0621XEDR031POLTSB1330_DRIVEM1\" width=\"320\" height=\"320\" scrolling=\"no\" frameborder=\"0\"></iframe>", true, L"Content"}
                                            }
      },
      {
         gauges::type::twitter, 0, 2, 2, 1, {
                                               {gauges::twitter::tags::handle(),  L"NASAPersevere", true,                                                                                                                                                                            L"Twitter handle"}
                                            }
      },
      {
         gauges::type::general, 1, 1, 1, 1, {
                                               {gauges::general::tags::content(), L"<h1>Hello \U0001f34c\U0001f34c\U0001F412<h1>", true,                                                                                                                                             L"Content"}
                                            }
      },
   };

   //todo: rename dialog to screen
   dialog dlg;
   //dlg.setWindowState(Qt::WindowFullScreen);
   dlg.setStyleSheet(QString::fromStdWString(set.dialog_stylesheet));

   gauges::manager gm(dlg.grid());

   for (
      auto& gc : set.gauge_configurations
      )
   {
      auto g = gauges::gauge_factory(gc, set);
      if (g)
      {
         g->display();
         gm.add(std::move(g), gc.row, gc.col, gc.row_span, gc.col_span);

      }
   }

   dlg.show();

   return QApplication::exec();
}

}
