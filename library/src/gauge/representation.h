#pragma once

#include "location.h"
#include <memory>

class QWidget;

namespace gauge
{

class interface;

struct representation
{
   mzlib::unique unique;
   std::unique_ptr <gauge::interface> logical;
   std::unique_ptr <QWidget> visual;
   gauge::location location;
};

}