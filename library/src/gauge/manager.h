//
// Created by matej on 22/03/2021.
//

#ifndef OPROJECT_OVEREYE_MANAGER_H
#define OPROJECT_OVEREYE_MANAGER_H

#include <vector>
#include <memory>

class QGridLayout;

namespace gauges
{

class gauge;

class manager
{

private:

   std::vector <std::unique_ptr<gauge>> m_gauges;
   QGridLayout* m_grid;

public:

   manager (QGridLayout* grid);

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

#endif //OPROJECT_OVEREYE_MANAGER_H
