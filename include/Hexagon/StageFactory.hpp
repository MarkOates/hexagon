#pragma once


#include <Hexagon/StageInterface.hpp>


namespace Hexagon
{
   class StageFactory
   {
   private:

   public:
      StageFactory();
      ~StageFactory();


   StageInterface* create();
   };
}



