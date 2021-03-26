#include "screen.h"
#include "ui_screen.h"

screen::screen (QWidget* parent) :
   QDialog(parent),
   ui(new Ui::main_dialog)
{
   ui->setupUi(this);
}

screen::~screen ()
{
   delete ui;
}

QGridLayout*
screen::grid ()
{
   return ui->grid;
}
