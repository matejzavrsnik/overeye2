#pragma once

#include <abstract/unique.h>
#include <sigslot/signal.hpp>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class gauge; }
QT_END_NAMESPACE

namespace gauges { class parameters; }

// custom qt widget for base
// goal is to contain qt as much as possible inside this class and not leak it out too much
// added functionality should be just to access qt stuff, not for project needs
class gauge : public QWidget
{
Q_OBJECT

public:

   explicit gauge (
      const gauges::parameters& parameters,
      QWidget* parent = nullptr
   );

   ~gauge () override;

   void
   setHtml (std::wstring_view html);

   void
   setObjectName (const std::string& object_name);

   sigslot::signal<const gauges::parameters&> new_settings;

private slots:

   void
   handleConfigPress ();

private:

   Ui::gauge* ui;
   const gauges::parameters& m_parameters;

};
