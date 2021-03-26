#include "manager.h"
#include "gauge.h"
#include <QGridLayout>

namespace gauges
{

manager::manager (QGridLayout* grid) :
   m_grid(grid)
{
}

void
manager::add (
   std::unique_ptr<gauges::gauge> gauge,
   int row,
   int col,
   int row_span = 1,
   int col_span = 1
)
{
   m_grid->addWidget(gauge->graphical_representation(), row, col, row_span, col_span);
   m_gauges.push_back(std::move(gauge));
}

}
