#pragma once

#include <sigslot/signal.hpp>
#include <QWidget>
#include <QEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class webport; }
QT_END_NAMESPACE

namespace gauge { class user_setting; }

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
      const std::vector<gauge::user_setting>& user_settings,
      QWidget* parent = nullptr
   );

   ~webport () override;

   sigslot::signal<const gauge::user_setting&> send_user_setting;
   sigslot::signal<> request_content;

   void
   receive_content (const std::wstring& html);

   void
   receive_content_refresh_request ();

   void
   setObjectName (const std::string& object_name);

private slots:

   void
   handleConfigPress ();

private:

   Ui::webport* ui;
   const std::vector<gauge::user_setting>& m_user_settings;

   bool
   event (QEvent* event) override;

};

}
