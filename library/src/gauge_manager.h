//
// Created by matej on 22/03/2021.
//

#ifndef OPROJECT_OVEREYE_GAUGE_MANAGER_H
#define OPROJECT_OVEREYE_GAUGE_MANAGER_H

#include "gauge.h"

#include <vector>
#include <memory>

class QGridLayout;

namespace library
{



class gauge_manager
{

private:

   std::vector <std::unique_ptr<gauge>> m_gauges;
   QGridLayout* m_grid;

public:

   gauge_manager (QGridLayout* grid);

   void
   add (
      std::unique_ptr <gauge> gauge,
      int row,
      int col,
      int row_span,
      int col_span
   );

};

}

#endif //OPROJECT_OVEREYE_GAUGE_MANAGER_H
