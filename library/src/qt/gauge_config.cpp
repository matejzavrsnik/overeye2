
#include "gauge_config.h"
#include "ui_gauge_config.h"
#include <string/trim.h>
#include <QMessageBox>


gauge_config::gauge_config(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gauge_config)
{
   ui->setupUi(this);
}

gauge_config::~gauge_config()
{
    delete ui;
}

void gauge_config::populate(std::shared_ptr<gauges::information> info)
{
   m_info = info;
   // populate the form
   ui->config_table->setColumnCount(2);
   int row = 0;
   for(const auto& parameter : m_info->parameters)
   {
      if(parameter.user_setting)
      {
         ui->config_table->insertRow(row);
         auto item_tag = std::make_unique<QTableWidgetItem>(QString::fromStdWString(parameter.tag));
         item_tag->setFlags(item_tag->flags() ^ Qt::ItemIsEditable);
         auto item_value = std::make_unique<QTableWidgetItem>(QString::fromStdWString(parameter.replacement));
         ui->config_table->setItem(row, 0, item_tag.release());
         ui->config_table->setItem(row, 1, item_value.release());
         ++row;
      }
   }

}
