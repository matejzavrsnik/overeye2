//
// Created by matej on 20/03/2021.
//

// You may need to build the project (run Qt uic code generator) to get "ui_gauge.h" resolved

#include "gauge.h"
#include "ui_gauge.h"
#include "gauge_config.h"

#include <tools/converters.h>

gauge::gauge (QWidget* parent) :
   QWidget(parent),
   ui(new Ui::gauge)
{
   ui->setupUi(this);
   ui->display->setContextMenuPolicy(Qt::ContextMenuPolicy::NoContextMenu);

   connect(ui->configure, &QPushButton::released, this, &gauge::handleConfigPress);
}

void gauge::setHtml(std::wstring_view html)
{
   ui->display->setHtml(mzlib::convert<QString>(html));
}

void gauge::setObjectName(std::string object_name)
{
   ui->display->setObjectName(QString::fromStdString(object_name));
}

void
gauge::handleConfigPress ()
{
   gauge_config config(this->parentWidget());
   config.populate(m_info);
   config.exec();
   new_settings(*m_info);
}

gauge::~gauge ()
{
   delete ui;
}



