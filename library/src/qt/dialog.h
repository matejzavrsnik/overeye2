//
// Created by matej on 26/12/2020.
//

#ifndef OPROJECT_OVEREYE_DIALOG_H
#define OPROJECT_OVEREYE_DIALOG_H

#include <QDialog>
#include <QGridLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class main_dialog; }
QT_END_NAMESPACE

class dialog : public QDialog
{
   Q_OBJECT

public:
   explicit dialog (QWidget* parent = nullptr);

   QGridLayout* grid();

   ~dialog () override;

private:

   Ui::main_dialog* ui;
};

#endif //OPROJECT_OVEREYE_DIALOG_H
