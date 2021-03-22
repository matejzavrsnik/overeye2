//
// Created by matej on 20/03/2021.
//

// You may need to build the project (run Qt uic code generator) to get "ui_gauge.h" resolved

#include "gauge.h"
#include "ui_gauge.h"
#include <tools/converters.h>

gauge::gauge (QWidget* parent) :
   QWidget(parent),
   ui(new Ui::gauge)
{
   ui->setupUi(this);
   ui->display->setContextMenuPolicy(Qt::ContextMenuPolicy::NoContextMenu);
}

void gauge::set_content(std::wstring_view content)
{
   ui->display->setHtml(mzlib::convert<QString>(content));
}

gauge::~gauge ()
{
   delete ui;
}

