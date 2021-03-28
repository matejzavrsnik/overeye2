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
   ui->display->setHtml(QString::fromStdWString(html));
}

void
gui::webport::receive_content_refresh_request ()
{
   // Logical part of gauge wishes to be refreshed and the signal may be coming from another thread.
   // QWidget doesn't behave well with concurrent access. This function may be invoked from that other
   // thread, so all I'll do here is leave a nice QEvent here for the QWidget in the original thread
   // to pick up. It can then request content from it's own thread and not die on me.
   auto event = std::make_unique<QEvent>(static_cast<QEvent::Type>(QEvent::User + 1));
   QCoreApplication::postEvent(this, event.release());
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

bool
gui::webport::event (QEvent* event)
{
   if (event->type() == QEvent::User + 1)
   {
      // For explanation see: receive_content_refresh_request method
      request_content();
      return true;
   }

   return QWidget::event(event);
}

gui::webport::~webport ()
{
   delete ui;
}
