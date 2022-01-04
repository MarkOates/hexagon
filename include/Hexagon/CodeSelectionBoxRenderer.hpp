#pragma once


#include <Hexagon/CodeRange.hpp>
#include <string>
#include <vector>


namespace Hexagon
{
   class CodeSelectionBoxRenderer
   {
   private:
      std::vector<std::string>* lines;
      CodeRange* code_range;
      int first_line_number;
      int cell_width;
      int cell_height;

   public:
      CodeSelectionBoxRenderer(std::vector<std::string>* lines=nullptr, CodeRange* code_range=nullptr, int first_line_number=0, int cell_width=0, int cell_height=0);
      ~CodeSelectionBoxRenderer();

      void render();
      bool verify_line_in_range(int line_num=0);
      int get_line_length(int line_num=0);
   };
}



