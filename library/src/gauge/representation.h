#pragma once

#include "location.h"
#include <abstract/unique.h>
#include <memory>

class QWidget;

namespace gauge
{

class interface;

class representation
{
public:
   representation(representation&) = delete;
   representation(const representation&) = delete;
   representation(representation&&) = default;
   representation() = default;

   mzlib::unique unique;
   std::unique_ptr<gauge::interface> logical;
   std::unique_ptr<QWidget> visual;
   gauge::location location;
   std::shared_ptr<gauge::parameters> parameters = std::make_shared<gauge::parameters>();
};

}