//
// Created by matej on 26/12/2020.
//

// You may need to build the project (run Qt uic code generator) to get "ui_dialog.h" resolved

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

QGridLayout* dialog::grid()
{
   return ui->gridLayout;
}