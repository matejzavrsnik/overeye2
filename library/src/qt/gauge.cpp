#include "gauge.h"
#include "ui_gauge.h"
#include "gauge_config.h"

#include <tools/converters.h>

gauge::gauge (
   const gauges::parameters& parameters,
   QWidget* parent
) :
   QWidget(parent),
   m_parameters(parameters),
   ui(new Ui::gauge)
{
   ui->setupUi(this);
   ui->display->setContextMenuPolicy(Qt::ContextMenuPolicy::NoContextMenu);

   connect(ui->configure, &QPushButton::released, this, &gauge::handleConfigPress);

}

void
gauge::setHtml (std::wstring_view html)
{
   ui->display->setHtml(mzlib::convert<QString>(html));
}

void
gauge::setObjectName (const std::string& object_name)
{
   ui->display->setObjectName(QString::fromStdString(object_name));
}

void
gauge::handleConfigPress ()
{
   gauge_config config(m_parameters, this->parentWidget());

   // implicitely converts to sigslot::scoped_connection which will clean when out of scope
   sigslot::scoped_connection sc = config.new_settings.connect(&gauge::new_settings, this);

   config.exec();
}

gauge::~gauge ()
{
   delete ui;
}
