#pragma once


#include <Hexagon/CodeMessagePoint.hpp>
#include <string>
#include <vector>


namespace Hexagon
{
   class CodeMessagePointManager
   {
   private:
      std::vector<CodeMessagePoint> code_message_points;

   public:
      CodeMessagePointManager();
      ~CodeMessagePointManager();


   std::string run();
   };
}



