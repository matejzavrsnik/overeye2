#ifndef OPROJECT_OVEREYE_GAUGE_H
#define OPROJECT_OVEREYE_GAUGE_H

#include <abstract/unique.h>
#include <sigslot/signal.hpp>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class gauge; }
QT_END_NAMESPACE

namespace gauges { class cparameters; }

// custom qt widget for base
// goal is to contain qt as much as possible inside this class and not leak it out too much
// added functionality should be just to access qt stuff, not for project needs
class gauge : public QWidget
{
   Q_OBJECT

public:

   explicit gauge (const gauges::cparameters& parameters, QWidget* parent = nullptr);

   ~gauge () override;

   void setHtml(std::wstring_view html);
   void setObjectName(std::string object_name);

   sigslot::signal<const gauges::cparameters&> new_settings;

private slots:

   void handleConfigPress();

private:

   Ui::gauge* ui;
   const gauges::cparameters& m_parameters;

};

#endif //OPROJECT_OVEREYE_GAUGE_H
