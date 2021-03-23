#include "gauge_config.h"
#include "ui_gauge_config.h"

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
