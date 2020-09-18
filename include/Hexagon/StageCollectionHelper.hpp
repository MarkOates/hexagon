#pragma once


#include <Hexagon/StageInterface.hpp>
#include <vector>


namespace Hexagon
{
   class StageCollectionHelper
   {
   private:
      std::vector<StageInterface *>* stages;

   public:
      StageCollectionHelper(std::vector<StageInterface *>* stages=nullptr);
      ~StageCollectionHelper();


   std::vector<StageInterface *> all();
   int count_code_editor_stages();
   StageInterface* get_frontmost_stage();
   };
}



