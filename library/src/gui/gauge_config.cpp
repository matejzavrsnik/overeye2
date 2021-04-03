#include "gauge_config.h"
#include "ui_gauge_config.h"
#include <QMessageBox>

gui::gauge_config::gauge_config (
   std::shared_ptr<gauge::visual_settings> settings,
   QWidget* parent
) :
   QDialog(parent),
   ui(new Ui::gauge_config),
   m_settings(settings)
{
   ui->setupUi(this);

   connect(ui->close, &QPushButton::released, this, &gauge_config::handleClosePress);
   connect(ui->apply, &QPushButton::released, this, &gauge_config::handleApplyPress);

   populate_grid();
}

gui::gauge_config::~gauge_config ()
{
   delete ui;
}

void
gui::gauge_config::populate_grid ()
{
   // populate the form
   ui->config_table->setColumnCount(2);
   ui->config_table->horizontalHeader()->setStretchLastSection(true);
   ui->config_table->alternatingRowColors();
   ui->config_table->verticalHeader()->hide();
   ui->config_table->horizontalHeader()->hide();
   int row = 0;
   for (const auto& setting : m_settings->user_setting_get_all())
   {
      ui->config_table->insertRow(row);
      auto item_name = std::make_unique<QTableWidgetItem>(QString::fromStdWString(m_settings->user_setting_get_name(setting.tag).value()));
      item_name->setFlags(item_name->flags() ^ Qt::ItemIsEditable);
      auto item_value = std::make_unique<QTableWidgetItem>(QString::fromStdWString(setting.value));
      item_value->setData(Qt::UserRole, QString::fromStdWString(setting.tag));
      ui->config_table->setItem(row, 0, item_name.release());
      ui->config_table->setItem(row, 1, item_value.release());
      ++row;
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
   bool anything_changed = false;

   for (int row = 0; row < ui->config_table->rowCount(); ++row)
   {
      const auto& valueItem = ui->config_table->item(row, 1);
      const std::wstring& tag = valueItem->data(Qt::UserRole).toString().toStdWString();
      const std::wstring& value = valueItem->data(Qt::DisplayRole).toString().toStdWString();
      m_settings->user_setting_set({tag, value});
      anything_changed = true; // todo: better if it was done from settings class centraly
   }

   if(anything_changed)
      signal_settings_changed();

}
