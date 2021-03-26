#include "manager.h"
#include "representation.h"
#include <QGridLayout>

namespace gauges
{

manager::manager (QGridLayout* grid) :
   m_grid(grid)
{
}

void
manager::add (
   representation gauge,
   int row,
   int col,
   int row_span = 1,
   int col_span = 1
)
{
   gauge.logical->display();
   m_grid->addWidget(gauge.visual.get(), row, col, row_span, col_span);
   m_gauges.push_back(std::move(gauge));
}

}
