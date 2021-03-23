#ifndef GAUGE_CONFIG_H
#define GAUGE_CONFIG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class gauge_config; }
QT_END_NAMESPACE

class gauge_config : public QDialog
{
    Q_OBJECT

public:
    explicit gauge_config(QWidget *parent = nullptr);
    ~gauge_config() override;

private:
    Ui::gauge_config *ui;
};

#endif // GAUGE_CONFIG_H
