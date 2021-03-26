#include "dialog.h"
#include "ui_dialog.h"

dialog::dialog (QWidget* parent) :
   QDialog(parent),
   ui(new Ui::main_dialog)
{
   ui->setupUi(this);
}

dialog::~dialog ()
{
   delete ui;
}

QGridLayout*
dialog::grid ()
{
   return ui->grid;
}
