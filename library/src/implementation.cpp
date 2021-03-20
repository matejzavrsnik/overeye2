#include "../include/library/header.h"

#include "dialog.h"

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

int run_main(int argc, char ** argv)
{
   QApplication app (argc, argv);

   dialog dlg;
   dlg.setWindowState(Qt::WindowFullScreen);
   dlg.setStyleSheet("background-color: rgb(46, 52, 54);");

   auto grid = dlg.grid();

   auto webEngineView = new QWebEngineView();
   webEngineView->setObjectName(QString::fromUtf8("webEngineView"));
   webEngineView->setGeometry(QRect(200, 200, 291, 231));
   webEngineView->setAutoFillBackground(false);
   webEngineView->setHtml("Hello");
   webEngineView->setContextMenuPolicy(Qt::ContextMenuPolicy::NoContextMenu);

   auto webEngineView2 = new QWebEngineView();
   webEngineView2->setObjectName(QString::fromUtf8("webEngineView2"));
   webEngineView2->setGeometry(QRect(200, 200, 291, 231));
   webEngineView2->setAutoFillBackground(false);
   webEngineView2->setHtml("Hello");
   webEngineView2->setContextMenuPolicy(Qt::ContextMenuPolicy::NoContextMenu);

   grid->addWidget(webEngineView, 0, 0);
   grid->addWidget(webEngineView2, 1, 1);

   dlg.show();

   return app.exec();
}

}
