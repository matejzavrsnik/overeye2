#include "../include/library/header.h"

#include "gui/screen.h"
#include "gauge/manager.h"
#include "gauge/types.h"
#include "gauge/factory.h"
#include "gauge/representation.h"
#include "gauge/webport.h"
#include "gauge/twitter.h"
#include "settings.h"

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
      //todo: don't like the fact that it needs to be set from outside of webport which parameters are user setting and
      // which are not. That should be known to webport, from outside only values for tags should come, not definitions
      {
         gauge::type::webport, 0, 0, 1, 1, {
                                               {gauge::webport::tags::content(), L"Hello",                                                                                                                                                                                    true, L"Content"}
                                            }
      },
      {
         gauge::type::webport, 0, 1, 1, 1, {
                                               {gauge::webport::tags::content(), L"<iframe src=\"https://mars.nasa.gov/layout/embed/image/320mosaicvert/?i=N_L000_0621XEDR031POLTSB1330_DRIVEM1\" width=\"320\" height=\"320\" scrolling=\"no\" frameborder=\"0\"></iframe>", true, L"Content"}
                                            }
      },
      {
         gauge::type::twitter, 0, 2, 2, 1, {
                                               {gauge::twitter::tags::handle(),  L"NASAPersevere",                                                                                                                                                                            true, L"Twitter handle"}
                                            }
      },
      {
         gauge::type::webport, 1, 1, 1, 1, {
                                               {gauge::webport::tags::content(), L"<h1>Hello \U0001f34c\U0001f34c\U0001F412<h1>",                                                                                                                                             true, L"Content"}
                                            }
      },
   };

   //todo: rename screen to screen
   gui::screen screen;
   //dlg.setWindowState(Qt::WindowFullScreen);
   screen.setStyleSheet(QString::fromStdWString(set.dialog_stylesheet));

   gauge::manager gm(screen.grid());

   for (
      auto& gc : set.gauge_configurations
      )
   {
      if (auto g = gauge::gauge_factory(gc, set))
         gm.add(std::move(g.value()));
   }

   screen.show();

   return QApplication::exec();
}

}
