#include "screen.h"
#include "ui_screen.h"

gui::screen::screen (QWidget* parent) :
   QDialog(parent),
   ui(new Ui::main_dialog)
{
   ui->setupUi(this);
}

gui::screen::~screen ()
{
   delete ui;
}

QGridLayout*
gui::screen::grid ()
{
   return ui->grid;
}
