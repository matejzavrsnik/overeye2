#pragma once

#include "../gauge/parameters.h"
#include "../gauge/i_gauge_parameters.h"
#include <sigslot/signal.hpp>
#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class gauge_config; }
QT_END_NAMESPACE

namespace gui
{

class gauge_config : public QDialog
{
Q_OBJECT

public:
   explicit gauge_config (
      std::shared_ptr<gauge::i_gauge_parameters> settings,
      QWidget* parent = nullptr
   );

   ~gauge_config () override;

   sigslot::signal<> signal_settings_changed;

private slots:

   void
   handleClosePress ();

   void
   handleApplyPress ();

private:

   Ui::gauge_config* ui;
   std::shared_ptr<gauge::i_gauge_parameters> m_settings;

   void
   populate_grid ();

};

}
