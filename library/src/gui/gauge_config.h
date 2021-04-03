#pragma once

#include "../gauge/parameters.h"
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
      const std::vector<gauge::user_setting>& user_settings,
      QWidget* parent = nullptr
   );

   ~gauge_config () override;

   sigslot::signal<const gauge::user_setting&> new_setting;

private slots:

   void
   handleClosePress ();

   void
   handleApplyPress ();

private:

   Ui::gauge_config* ui;

   void
   populate_grid (const std::vector<gauge::user_setting>& user_settings);

};

}
