#pragma once


#include <Hexagon/CodeMessagePoint.hpp>
#include <vector>


namespace Hexagon
{
   class CodeMessagePointManager
   {
   private:
      std::vector<CodeMessagePoint> code_message_points;

   protected:


   public:
      CodeMessagePointManager();
      ~CodeMessagePointManager();

      std::vector<CodeMessagePoint> get_code_message_points() const;
      std::vector<CodeMessagePoint> &get_code_message_points_ref();
      void append(CodeMessagePoint code_message_point={});
      void set_code_message_points(std::vector<CodeMessagePoint> code_message_points={});
      void clear();
      void delete_row(int row=0);
      void shift_rows_down_at_and_after(int row=0);
   };
}



