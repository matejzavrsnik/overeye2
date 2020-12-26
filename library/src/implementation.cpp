#include "../include/library/header.h"

#include "dialog.h"

#include <tools/time_operations.h>

#include <QApplication>
#include <QPushButton>

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
   dlg.show();
   return app.exec();
}

}
