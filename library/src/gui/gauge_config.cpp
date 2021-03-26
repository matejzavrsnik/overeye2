#include "gauge_config.h"
#include "ui_gauge_config.h"
#include <QMessageBox>

gui::gauge_config::gauge_config (
   const gauge::parameters& parameters,
   QWidget* parent
) :
   QDialog(parent),
   ui(new Ui::gauge_config)
{
   ui->setupUi(this);

   connect(ui->close, &QPushButton::released, this, &gauge_config::handleClosePress);
   connect(ui->apply, &QPushButton::released, this, &gauge_config::handleApplyPress);

   populate_grid(parameters);
}

gui::gauge_config::~gauge_config ()
{
   delete ui;
}

void
gui::gauge_config::populate_grid (const gauge::parameters& parameters)
{
   // populate the form
   ui->config_table->setColumnCount(2);
   ui->config_table->horizontalHeader()->setStretchLastSection(true);
   ui->config_table->alternatingRowColors();
   ui->config_table->verticalHeader()->hide();
   ui->config_table->horizontalHeader()->hide();
   int row = 0;
   for (const auto& parameter : parameters)
   {
      //todo: ideally it would never even get settings that aren't user settings
      if (parameter.is_user_setting())
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
gui::gauge_config::handleClosePress ()
{
   //todo: undo the applied
   this->close();
}

void
gui::gauge_config::handleApplyPress ()
{
   gauge::parameters new_parameters;
   for (int row = 0; row < ui->config_table->rowCount(); ++row)
   {
      const auto& valueItem = ui->config_table->item(row, 1);
      const std::wstring& tag = valueItem->data(Qt::UserRole).toString().toStdWString();
      const std::wstring& value = valueItem->data(Qt::DisplayRole).toString().toStdWString();
      new_parameters.set(tag, value);
   }
   new_settings(new_parameters);
}
