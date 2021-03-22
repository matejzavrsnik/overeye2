#include "../include/library/header.h"

#include "dialog.h"
#include "gauge.h"

#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QToolBar>
#include <QMenuBar>
#include <QWebEngineView>

#include <tools/converters.h>
#include <string/replace.h>

#include "internal.h"

namespace library
{

double sum(double a, double b)
{
   return internal::sum_implementation(a, b);
}

const std::wstring_view g_style_placeholder = L"{style}";
const std::wstring_view g_content_placeholder = L"{content}";

class gauge_web : public gauge
{

private:

   std::wstring_view m_style;
   const std::wstring m_page_template;

public:

   gauge_web(std::wstring_view style, std::wstring_view content) :
      m_style(style),
      m_page_template(
         std::wstring(L"<!DOCTYPE html><html><head><meta charset=\"utf-8\"><style>")
         + std::wstring(g_style_placeholder)
         + std::wstring(L"</style></head><body>")
         + std::wstring(g_content_placeholder)
         + std::wstring(L"</body></html>")
      )
   {
      setObjectName(QString::fromStdString("gauge" + std::to_string(unique.id())));
      std::wstring page = m_page_template;
      mzlib::string_replace(page, g_style_placeholder, m_style);
      mzlib::string_replace(page, g_content_placeholder, content);
      set_content(page);
   }
};

class gauge_manager
{

private:

   std::vector<std::unique_ptr<gauge>> m_gauges;
   QGridLayout* m_grid;

public:

   gauge_manager(QGridLayout* grid) :
      m_grid(grid)
   {
   };

   void add(std::unique_ptr<gauge> gauge, int row, int col, int row_span = 1, int col_span = 1)
   {
      m_grid->addWidget(gauge.get(), row, col, row_span, col_span);
      m_gauges.push_back(std::move(gauge));
   }

};

struct gauge_configuration
{
   int row;
   int col;
   int row_span;
   int col_span;
   std::wstring_view content;
};

struct settings
{
   std::wstring_view dialog_stylesheet;
   std::wstring_view gauge_stylesheet;
   std::vector<gauge_configuration> gauge_configurations;
};


int run_main(int argc, char ** argv)
{
   QApplication app (argc, argv);

   settings set;
   set.dialog_stylesheet = L"background-color: rgb(46, 52, 54)";
   set.gauge_stylesheet = L"body { color: yellow; background-color: rgb(50, 56, 58) }";
   set.gauge_configurations = {
      {0, 0, 1, 1, L"Hello"},
      {0, 1, 1, 1, L"<iframe src=\"https://mars.nasa.gov/layout/embed/image/320mosaicvert/?i=N_L000_0621XEDR031POLTSB1330_DRIVEM1\" width=\"320\" height=\"320\" scrolling=\"no\" frameborder=\"0\"></iframe>"},
      {0, 2, 2, 1, L"<a class=\"twitter-timeline\" href=\"https://twitter.com/NASAPersevere\" data-width=\"400\" data-height=\"1200\" data-chrome=\"nofooter noborders transparent noscrollbar\" data-theme=\"dark\">Tweets by TwitterDev</a> <script async src=\"https://platform.twitter.com/widgets.js\" charset=\"utf-8\"></script> "},
      {1, 1, 1, 1, L"<h1>Hello \U0001f34c\U0001f34c\U0001F412<h1>"},
   };

   dialog dlg;
   dlg.setWindowState(Qt::WindowFullScreen);
   dlg.setStyleSheet(mzlib::convert<QString>(set.dialog_stylesheet));

   gauge_manager gm(dlg.grid());

   for(auto& gc : set.gauge_configurations)
   {
      auto g = std::make_unique<gauge_web>(set.gauge_stylesheet, gc.content);
      gm.add(std::move(g), gc.row, gc.col, gc.row_span, gc.col_span);
   }

   dlg.show();

   return app.exec();
}

}
