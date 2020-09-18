#pragma once


#include <Hexagon/StageInterface.hpp>
#include <string>
#include <vector>


namespace Hexagon
{
   class StageCollectionHelper
   {
   private:
      std::vector<StageInterface *>* stages;

   public:
      StageCollectionHelper();
      ~StageCollectionHelper();


   std::string run();
   };
}



