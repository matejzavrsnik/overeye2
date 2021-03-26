#pragma once

#include <memory>

class QWidget;

namespace gauges
{

class gauge;

struct representation
{
   mzlib::unique unique;
   std::unique_ptr <gauges::gauge> logical;
   std::unique_ptr <QWidget> visual;
};

}