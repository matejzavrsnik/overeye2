//
// Created by matej on 22/03/2021.
//

#include "manager.h"
#include "base.h"
#include <QGridLayout>

namespace gauges
{

   manager::manager (QGridLayout* grid) :
      m_grid(grid)
   {
   };

   void
   manager::add (
      std::unique_ptr <base> gauge,
      int row,
      int col,
      int row_span = 1,
      int col_span = 1
   )
   {
      m_grid->addWidget(gauge->qt(), row, col, row_span, col_span);
      m_gauges.push_back(std::move(gauge));
   };

}