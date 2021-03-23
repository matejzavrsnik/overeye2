#ifndef OPROJECT_OVEREYE_GAUGE_H
#define OPROJECT_OVEREYE_GAUGE_H

#include "../gauge/information.h"
#include <abstract/unique.h>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class gauge; }
QT_END_NAMESPACE



// custom qt widget for base
// goal is to contain qt as much as possible inside this class and not leak it out too much
// added functionality should be just to access qt stuff, not for project needs
class gauge : public QWidget
{
   Q_OBJECT

public:

   explicit gauge (QWidget* parent = nullptr);

   ~gauge () override;

   void setHtml(std::wstring_view html);
   void setObjectName(std::string object_name);

   std::shared_ptr<gauges::information> m_info;

private slots:

   void handleConfigPress();

private:

   Ui::gauge* ui;

};

#endif //OPROJECT_OVEREYE_GAUGE_H
