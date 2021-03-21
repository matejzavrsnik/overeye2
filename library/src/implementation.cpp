#include "../include/library/header.h"

#include "dialog.h"
#include "gauge.h"

#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QToolBar>
#include <QMenuBar>
#include <QWebEngineView>

#include "internal.h"

namespace library
{

double sum(double a, double b)
{
   return internal::sum_implementation(a, b);
}

class gauge_manager
{

private:

   std::vector<std::unique_ptr<gauge>> m_gauges;
   QGridLayout* m_grid;

public:

   gauge_manager(QGridLayout* grid) : m_grid(grid) {};

   void add(std::wstring_view content, int row, int col)
   {
      auto g = std::make_unique<gauge>();
      g->setObjectName(QString::fromStdString("gauge" + std::to_string(g->unique.id())));
      g->set_content(content);
      m_grid->addWidget(g.get(), row, col);
      m_gauges.push_back(std::move(g));
   }

};

int run_main(int argc, char ** argv)
{
   QApplication app (argc, argv);

   dialog dlg;
   //dlg.setWindowState(Qt::WindowFullScreen);
   dlg.setStyleSheet("background-color: rgb(46, 52, 54);");

   auto grid = dlg.grid();

   gauge_manager gm(grid);
   gm.add(L"Hello", 0, 0);
   gm.add(L"<iframe src=\"https://mars.nasa.gov/layout/embed/image/320mosaicvert/?i=N_L000_0621XEDR031POLTSB1330_DRIVEM1\" width=\"320\" height=\"320\" scrolling=\"no\" frameborder=\"0\"></iframe>", 0, 1);
   gm.add(L"<h1>Hello \U0001f34c\U0001f34c\U0001F412<h1>", 1, 1);

   //gauge g;
   //g.setObjectName(QString::fromUtf8("gauge"));
   //g.set_content(L"Hello");
   //grid->addWidget(&g, 0, 0);

   //gauge g1;
   //g1.setObjectName(QString::fromUtf8("gauge2"));
   //g1.set_content(L"<iframe src=\"https://mars.nasa.gov/layout/embed/image/320mosaicvert/?i=N_L000_0621XEDR031POLTSB1330_DRIVEM1\" width=\"320\" height=\"320\" scrolling=\"no\" frameborder=\"0\"></iframe>");
   //grid->addWidget(&g1, 0, 1);

   //gauge g2;
   //g2.setObjectName(QString::fromUtf8("gauge2"));
   //auto banana = L'\U0001f34c';
   //auto monkey = L'U0001F412';
   //g2.set_content(L"<h1>Hello \U0001f34c\U0001f34c\U0001F412<h1>");
   //grid->addWidget(&g2, 1, 1);

   dlg.show();

   return app.exec();
}

}
