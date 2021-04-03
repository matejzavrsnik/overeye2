#pragma once

#include <sigslot/signal.hpp>
#include <QWidget>
#include <QEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class webport; }
QT_END_NAMESPACE

namespace gauge { class visual_settings; }

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
      std::shared_ptr<gauge::visual_settings> settings,
      QWidget* parent = nullptr
   );

   ~webport () override;

   sigslot::signal<> signal_settings_changed;
   sigslot::signal<> request_content;

   void
   receive_content (const std::wstring& html);

   void
   receive_request_refresh ();

   void
   setObjectName (const std::string& object_name);

private slots:

   void
   handleConfigPress ();

private:

   Ui::webport* ui;
   std::shared_ptr<gauge::visual_settings> m_settings;

   bool
   event (QEvent* event) override;

};

}
