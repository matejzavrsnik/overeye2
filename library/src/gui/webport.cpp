#include "webport.h"
#include "ui_webport.h"
#include "gauge_config.h"

#include <tools/converters.h>

gui::webport::webport (
   const gauge::parameters& parameters,
   QWidget* parent
) :
   QWidget(parent),
   m_parameters(parameters),
   ui(new Ui::webport)
{
   ui->setupUi(this);
   ui->display->setContextMenuPolicy(Qt::ContextMenuPolicy::NoContextMenu);

   connect(ui->configure, &QPushButton::released, this, &webport::handleConfigPress);
}

void
gui::webport::receive_content (const std::wstring& html)
{
   std::wstring html2 = html;
   auto html3 = QString::fromStdWString(html2);
   ui->display->setHtml(html3);
}

void
gui::webport::setObjectName (const std::string& object_name)
{
   ui->display->setObjectName(QString::fromStdString(object_name));
}

void
gui::webport::handleConfigPress ()
{
   gauge_config config(m_parameters, this->parentWidget());

   sigslot::scoped_connection _ = config.new_settings.connect(&webport::send_user_changes, this);

   config.exec();
}

gui::webport::~webport ()
{
   delete ui;
}
