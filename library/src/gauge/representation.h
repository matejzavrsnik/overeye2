#pragma once

#include <memory>

class QWidget;

namespace gauges
{

class gauge;

struct representation
{
   std::unique_ptr <gauges::gauge> logical;
   std::unique_ptr <QWidget> visual;
};

}