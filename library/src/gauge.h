#ifndef OPROJECT_OVEREYE_GAUGE_H
#define OPROJECT_OVEREYE_GAUGE_H

#include <QWidget>
#include <abstract/unique.h>

QT_BEGIN_NAMESPACE
namespace Ui { class gauge; }
QT_END_NAMESPACE

class gauge : public QWidget
{
   Q_OBJECT

public:

   explicit gauge (QWidget* parent = nullptr);

   ~gauge () override;

protected:

   mzlib::unique unique;

   void set_content(std::wstring_view content);

private:

   Ui::gauge* ui;

};

#endif //OPROJECT_OVEREYE_GAUGE_H
