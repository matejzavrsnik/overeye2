//
// Created by matej on 22/03/2021.
//

#include "gauge_manager.h"

#include <QGridLayout>

namespace library
{

   gauge_manager::gauge_manager (QGridLayout* grid) :
      m_grid(grid)
   {
   };

   void
   gauge_manager::add (
      std::unique_ptr <gauge> gauge,
      int row,
      int col,
      int row_span = 1,
      int col_span = 1
   )
   {
      m_grid->addWidget(gauge.get(), row, col, row_span, col_span);
      m_gauges.push_back(std::move(gauge));
   };

}