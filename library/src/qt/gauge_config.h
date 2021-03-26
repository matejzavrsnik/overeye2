#ifndef GAUGE_CONFIG_H
#define GAUGE_CONFIG_H

#include "../gauge/information.h"
#include <sigslot/signal.hpp>
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

    void populate(std::shared_ptr<gauges::information> info);
   sigslot::signal<const gauges::information&> new_settings;

private slots:

   void handleClosePress();
   void handleApplyPress();

private:

    Ui::gauge_config *ui;
    std::shared_ptr<gauges::information> m_info;

};

#endif // GAUGE_CONFIG_H
