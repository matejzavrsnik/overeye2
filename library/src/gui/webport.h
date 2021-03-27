#pragma once

#include <abstract/unique.h>
#include <sigslot/signal.hpp>
#include <QWidget>
#include <QEvent>

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

   void
   setHtml (const std::wstring& html);

   void
   setObjectName (const std::string& object_name);

   sigslot::signal<const gauge::parameters&> new_settings;

   sigslot::signal<> request_new_content;


private slots:

   void
   handleConfigPress ();

private:

   Ui::webport* ui;
   const gauge::parameters& m_parameters;

   // https://stackoverflow.com/questions/40916479/thread-safety-of-calling-qobjects-method-from-another-non-qt-thread

   bool event(QEvent* event) override
   {
      if (event->type() == QEvent::User+1)
      {
         int i = request_new_content.slot_count();
         request_new_content();
         return true;
      }

      // Make sure the rest of events are handled
      return QWidget::event(event);
   }


};

}
