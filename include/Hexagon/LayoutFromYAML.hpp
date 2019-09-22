#pragma once


#include <Hexagon/StageInterface.hpp>
#include <vector>


namespace Hexagon
{
   class LayoutFromYAML
   {
   private:

   public:
      LayoutFromYAML();
      ~LayoutFromYAML();


   std::vector<StageInterface *> load();
   };
}



