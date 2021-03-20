//
// Created by matej on 20/03/2021.
//

// You may need to build the project (run Qt uic code generator) to get "ui_gauge.h" resolved

#include "gauge.h"
#include "ui_gauge.h"

gauge::gauge (QWidget* parent) :
   QWidget(parent),
   ui(new Ui::gauge)
{
   ui->setupUi(this);
   ui->webEngineView->setHtml("Hello");
   ui->webEngineView->setContextMenuPolicy(Qt::ContextMenuPolicy::NoContextMenu);
}

gauge::~gauge ()
{
   delete ui;
}
