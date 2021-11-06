#pragma once

#include "../gauge/location.h"
#include <abstract/unique.h>
#include <memory>

class QWidget;

namespace gauge
{

class i_gauge;

class representation
{
public:
   representation(representation&) = delete;
   representation(const representation&) = delete;
   representation(representation&&) = default;
   representation() = default;

   mzlib::unique unique;
   std::unique_ptr<gauge::i_gauge> logical;
   std::unique_ptr<QWidget> visual;
   gauge::location location;
   std::shared_ptr<gauge::parameters> parameters = std::make_shared<gauge::parameters>();
};

}