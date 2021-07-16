#include "webport.h"
#include "ui_webport.h"
#include "gauge_config.h"
#include "custom_event_types.h"
#include "../gauge/user_parameters.h"

#include <tools/converters.h>

gui::webport::webport (
   std::shared_ptr<gauge::user_parameters> settings,
   QWidget* parent
) :
   QWidget(parent),
   m_settings(settings),
   ui(new Ui::webport)
{
   ui->setupUi(this);
   ui->display->setContextMenuPolicy(Qt::ContextMenuPolicy::NoContextMenu);

   connect(ui->configure, &QPushButton::released, this, &webport::handleConfigPress);
}

gui::webport::~webport ()
{
   delete ui;
}

void
gui::webport::receive_content (const std::wstring& html)
{
   ui->display->setHtml(QString::fromStdWString(html));
}

void
gui::webport::receive_request_refresh ()
{
   // Logical part of gauge wishes to be refreshed and the signal may be coming from another thread.
   // QWidget doesn't behave well with concurrent access. This function may be invoked from that other
   // thread, so all I'll do here is leave a nice QEvent here for the QWidget in the original thread
   // to pick up. It can then request content from it's own thread and not die on me.
   auto event = std::make_unique<QEvent>(custom_qevent_type::refresh_content);
   // segfaults due to race condition with destructor of qobject; don't yet know how to solve it.
   // immediate idea is to synchronise destructor with this call, but might get better idea later.
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
   gauge_config config(m_settings, this->parentWidget());
   sigslot::scoped_connection _ = config.signal_settings_changed.connect(&webport::signal_settings_changed, this);
   config.exec();
}

bool
gui::webport::event (QEvent* event)
{
   if (event->type() == custom_qevent_type::refresh_content)
   {
      request_content();
      return true;
   }

   return QWidget::event(event);
}

