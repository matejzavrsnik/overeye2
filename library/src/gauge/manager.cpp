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
   representation gauge
)
{
   gauge.logical->display();
   m_grid->addWidget(gauge.visual.get(), gauge.location.row, gauge.location.col, gauge.location.row_span, gauge.location.col_span);
   m_gauges.push_back(std::move(gauge));
}

}
