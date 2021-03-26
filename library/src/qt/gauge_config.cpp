
#include "gauge_config.h"
#include "ui_gauge_config.h"
#include <string/trim.h>
#include <QMessageBox>


gauge_config::gauge_config(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gauge_config)
{
   ui->setupUi(this);

   connect(ui->close, &QPushButton::released, this, &gauge_config::handleClosePress);
   connect(ui->apply, &QPushButton::released, this, &gauge_config::handleApplyPress);
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
   ui->config_table->horizontalHeader()->setStretchLastSection(true);
   ui->config_table->alternatingRowColors();
   ui->config_table->verticalHeader()->hide();
   ui->config_table->horizontalHeader()->hide();
   int row = 0;
   for(const auto& parameter : m_info->parameters)
   {
      //todo: ideally it would never even get settings that aren't user settings
      if(parameter.is_user_setting())
      {
         ui->config_table->insertRow(row);
         auto item_tag = std::make_unique<QTableWidgetItem>(QString::fromStdWString(parameter.get_name()));
         item_tag->setFlags(item_tag->flags() ^ Qt::ItemIsEditable);
         auto item_value = std::make_unique<QTableWidgetItem>(QString::fromStdWString(parameter.get_value()));
         item_value->setData(Qt::UserRole, QString::fromStdWString(parameter.get_tag()));
         ui->config_table->setItem(row, 0, item_tag.release());
         ui->config_table->setItem(row, 1, item_value.release());
         ++row;
      }
   }
   ui->config_table->resizeColumnToContents(0);

}

void
gauge_config::handleClosePress ()
{
   //todo: undo the applied
   this->close();
}

void
gauge_config::handleApplyPress ()
{
   for (int row = 0; row < ui->config_table->rowCount(); ++row)
   {
      const auto& valueItem = ui->config_table->item(row, 1);
      const std::wstring& tag = valueItem->data(Qt::UserRole).toString().toStdWString();
      const std::wstring& value = valueItem->data(Qt::DisplayRole).toString().toStdWString();
      m_info->parameters.set(tag, value);
      int i=0;
   }
   new_settings(*m_info);
}
