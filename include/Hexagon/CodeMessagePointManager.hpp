#pragma once


#include <Hexagon/CodeMessagePoint.hpp>
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


   void add();
   void clear();
   void delete_row();
   void insert_row();
   };
}



