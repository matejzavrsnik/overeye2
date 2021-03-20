//
// Created by matej on 20/03/2021.
//

#ifndef OPROJECT_OVEREYE_GAUGE_H
#define OPROJECT_OVEREYE_GAUGE_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class gauge; }
QT_END_NAMESPACE

class gauge : public QWidget
{
   Q_OBJECT

public:
   explicit gauge (QWidget* parent = nullptr);

   ~gauge () override;

private:
   Ui::gauge* ui;
};

#endif //OPROJECT_OVEREYE_GAUGE_H
