//
// Created by matej on 22/03/2021.
//

#pragma once

#include "../qt/gauge.h"

namespace gauges
{

// base class for all gauges
// goal is to maintain as little references to qt as possible
class base
{
public:

   explicit base (QWidget* parent = nullptr);

   virtual void
   display () = 0;

   ::gauge*
   qt();

protected:

   mzlib::unique unique;

   void
   set_html (std::wstring_view html);

private:


   std::unique_ptr<::gauge> m_qt_gauge;

};

}

