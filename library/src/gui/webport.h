#pragma once

#include <abstract/unique.h>
#include <sigslot/signal.hpp>
#include <QWidget>
#include <QEvent>
#include <QCoreApplication>

QT_BEGIN_NAMESPACE
namespace Ui { class webport; }
QT_END_NAMESPACE

namespace gauge { class parameters; }

namespace gui
{

// custom gui widget for webport gauge
// goal is to contain gui as much as possible inside this class and not leak it out too much
// added functionality should be just to access gui stuff, not for project needs
class webport : public QWidget
{
Q_OBJECT

public:

   explicit webport (
      const gauge::parameters& parameters,
      QWidget* parent = nullptr
   );

   ~webport () override;

   sigslot::signal<const gauge::parameters&> send_user_changes;
   sigslot::signal<> request_content;

   void
   receive_content (const std::wstring& html);

   void
   receive_content_refresh_request ()
   {
      // Logical part of gauge wishes to be refreshed and the signal may be coming from another thread.
      // QWidget doesn't behave well with concurrent access. This function may be invoked from that other
      // thread, so all I'll do here is leave a nice QEvent here for the QWidget in the original thread
      // to pick up. It can then request content from it's own thread and not die on me.
      auto event = std::make_unique<QEvent>(static_cast<QEvent::Type>(QEvent::User + 1));
      QCoreApplication::postEvent(this, event.release());
   }

   void
   setObjectName (const std::string& object_name);

private slots:

   void
   handleConfigPress ();

private:

   Ui::webport* ui;
   const gauge::parameters& m_parameters;

   bool event(QEvent* event) override
   {
      if (event->type() == QEvent::User+1)
      {
         // For explanation see: receive_content_refresh_request method
         request_content();
         return true;
      }

      return QWidget::event(event);
   }




};

}
