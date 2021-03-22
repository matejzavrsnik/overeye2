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

// generic web gauge
class gauge_web : public gauge
{

private:

   std::wstring_view m_style;
   std::wstring m_page_template;
   std::wstring m_page_content;
   std::wstring m_last_rendered_page;

public:

   gauge_web(std::wstring_view style, std::wstring_view content) :
      m_style(style),
      m_page_template(
         std::wstring(L"<!DOCTYPE html><html><head><meta charset=\"utf-8\"><style>")
         + std::wstring(g_style_placeholder)
         + std::wstring(L"</style></head><body>")
         + std::wstring(g_content_placeholder)
         + std::wstring(L"</body></html>")),
      m_page_content(content)
   {
      setObjectName(QString::fromStdString("gauge" + std::to_string(unique.id())));
   }

   void display() override
   {
      m_page_template = render_template(m_page_template, m_page_content);
      m_last_rendered_page = render(m_page_template);
      set_content(m_last_rendered_page);
   }

protected:

   // customisation point for additional rendering by derived classes
   virtual std::wstring render(std::wstring page_template)
   {
      return page_template;
   }

private:

   // render basic html to be used with anything
   // can't be done in dtor because we might want to change stylesheet after control is created
   std::wstring render_template(std::wstring page_template, std::wstring_view content)
   {
      mzlib::string_replace(page_template, g_style_placeholder, m_style);
      mzlib::string_replace(page_template, g_content_placeholder, content);
      return page_template;
   }

};


// basically a constant html string, but written here to make class more to the point
std::wstring_view twitter_embedded_html()
{
   static const std::wstring_view html =
LR"(
<a class="twitter-timeline"
   href="https://twitter.com/{twitter_handle}"
   data-width="400"
   data-height="1200"
   data-chrome="nofooter noborders transparent noscrollbar"
   data-theme="dark">
Tweets by TwitterDev
</a>
<script async
        src="https://platform.twitter.com/widgets.js"
        charset="utf-8">
</script>
)";

   return html;
}
//L"NASAPersevere"
class gauge_twitter : public gauge_web
{

private:

   std::wstring_view m_twitter_handle;

public:

   gauge_twitter(std::wstring_view style, std::wstring_view twitter_handle) :
      gauge_web(style,twitter_embedded_html()),
      m_twitter_handle(twitter_handle)
   {
   }

protected:

   // customisation point for additional rendering by derived classes
   virtual std::wstring render(std::wstring page_template) override
   {
      mzlib::string_replace(page_template, std::wstring_view(L"{twitter_handle}"), m_twitter_handle);
      return page_template;
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

enum class gauge_type
{
   generic,
   twitter
};

struct gauge_configuration
{
   gauge_type type;
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

std::unique_ptr<gauge> gauge_factory(const gauge_configuration& gc, const settings& set)
{
   switch(gc.type)
   {
      case gauge_type::generic:
         return std::make_unique<gauge_web>(set.gauge_stylesheet, gc.content);
      case gauge_type::twitter:
         return std::make_unique<gauge_twitter>(set.gauge_stylesheet, gc.content);
   }
   return nullptr; // should never happen (tm)
}

int run_main(int argc, char ** argv)
{
   QApplication app (argc, argv);

   settings set;
   set.dialog_stylesheet = L"background-color: rgb(46, 52, 54)";
   set.gauge_stylesheet = L"body { color: yellow; background-color: rgb(50, 56, 58) }";
   set.gauge_configurations = {
      {gauge_type::generic, 0, 0, 1, 1, L"Hello"},
      {gauge_type::generic, 0, 1, 1, 1, L"<iframe src=\"https://mars.nasa.gov/layout/embed/image/320mosaicvert/?i=N_L000_0621XEDR031POLTSB1330_DRIVEM1\" width=\"320\" height=\"320\" scrolling=\"no\" frameborder=\"0\"></iframe>"},
      //L"<a class=\"twitter-timeline\" href=\"https://twitter.com/NASAPersevere\" data-width=\"400\" data-height=\"1200\" data-chrome=\"nofooter noborders transparent noscrollbar\" data-theme=\"dark\">Tweets by TwitterDev</a> <script async src=\"https://platform.twitter.com/widgets.js\" charset=\"utf-8\"></script> "},
      {gauge_type::twitter, 0, 2, 2, 1, L"NASAPersevere"},
      {gauge_type::generic, 1, 1, 1, 1, L"<h1>Hello \U0001f34c\U0001f34c\U0001F412<h1>"},
   };

   dialog dlg;
   dlg.setWindowState(Qt::WindowFullScreen);
   dlg.setStyleSheet(mzlib::convert<QString>(set.dialog_stylesheet));

   gauge_manager gm(dlg.grid());

   for(auto& gc : set.gauge_configurations)
   {
      auto g = gauge_factory(gc, set);
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
