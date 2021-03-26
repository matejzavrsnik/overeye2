#pragma once

#include <vector>
#include <memory>

class QGridLayout;

namespace gauges
{

class base;

class manager
{

private:

   std::vector<std::unique_ptr<base>> m_gauges;
   QGridLayout* m_grid;

public:

   explicit manager (QGridLayout* grid);

   void
   add (
      std::unique_ptr<base> gauge,
      int row,
      int col,
      int row_span,
      int col_span
   );

};

}
