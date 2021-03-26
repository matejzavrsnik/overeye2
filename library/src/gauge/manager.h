#pragma once

#include <vector>
#include <memory>

class QGridLayout;

namespace gauges
{

class gauge;

class manager
{

private:

   std::vector<std::unique_ptr<gauge>> m_gauges;
   QGridLayout* m_grid;

public:

   explicit manager (QGridLayout* grid);

   void
   add (
      std::unique_ptr<gauge> gauge,
      int row,
      int col,
      int row_span,
      int col_span
   );

};

}
