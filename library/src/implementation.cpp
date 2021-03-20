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

   auto webEngineView = new QWebEngineView(&dlg);
   webEngineView->setObjectName(QString::fromUtf8("webEngineView"));
   webEngineView->setGeometry(QRect(200, 200, 291, 231));
   webEngineView->setAutoFillBackground(false);
   webEngineView->setHtml("Hello");
   webEngineView->setContextMenuPolicy(Qt::ContextMenuPolicy::NoContextMenu);

   dlg.show();

   return app.exec();
}

}
