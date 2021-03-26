#ifndef GAUGE_CONFIG_H
#define GAUGE_CONFIG_H

#include "../gauge/configuration.h"
#include <sigslot/signal.hpp>
#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class gauge_config; }
QT_END_NAMESPACE



class gauge_config : public QDialog
{
    Q_OBJECT

public:
    explicit gauge_config(const gauges::cparameters& parameters, QWidget *parent = nullptr);
    ~gauge_config() override;


   sigslot::signal<const gauges::cparameters&> new_settings;

private slots:

   void handleClosePress();
   void handleApplyPress();

private:

   Ui::gauge_config *ui;
   void populate_grid(const gauges::cparameters& parameters);

};

#endif // GAUGE_CONFIG_H
