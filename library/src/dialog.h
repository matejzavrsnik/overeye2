//
// Created by matej on 26/12/2020.
//

#ifndef OPROJECT_OVEREYE_DIALOG_H
#define OPROJECT_OVEREYE_DIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class dialog; }
QT_END_NAMESPACE

class dialog : public QDialog
{
   Q_OBJECT

public:
   explicit dialog (QWidget* parent = nullptr);

   ~dialog () override;

private:
   Ui::dialog* ui;
};

#endif //OPROJECT_OVEREYE_DIALOG_H
