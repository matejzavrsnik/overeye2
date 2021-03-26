#pragma once

#include <abstract/unique.h>
#include <sigslot/signal.hpp>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class webport; }
QT_END_NAMESPACE

namespace gauges { class parameters; }

// custom gui widget for base
// goal is to contain gui as much as possible inside this class and not leak it out too much
// added functionality should be just to access gui stuff, not for project needs
class webport : public QWidget
{
Q_OBJECT

public:

   explicit webport (
      const gauges::parameters& parameters,
      QWidget* parent = nullptr
   );

   ~webport () override;

   void
   setHtml (std::wstring_view html);

   void
   setObjectName (const std::string& object_name);

   sigslot::signal<const gauges::parameters&> new_settings;

private slots:

   void
   handleConfigPress ();

private:

   Ui::webport* ui;
   const gauges::parameters& m_parameters;

};
