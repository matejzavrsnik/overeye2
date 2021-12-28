#pragma once

#include <QDialog>
#include <QGridLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class main_dialog; }
QT_END_NAMESPACE

namespace gui
{

class screen : public QDialog
{
Q_OBJECT

public:
   explicit screen (QWidget* parent = nullptr);

   ~screen () override;

private:

   Ui::main_dialog* ui;
};

}
