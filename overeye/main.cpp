#include <iostream>

#include <library/header.h>

#include "application.h"

int main(int argc, char ** argv)
{
   // example of running imgui GUI
   std::cout << library::run_main(argc, argv) << std::endl;

   // example of running library function
   std::cout << library::sum(1.0, 2.0) << std::endl;

   // example of running application function
   std::cout << application::mul(2, 3) << std::endl;

   return 0;
}
