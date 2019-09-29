#pragma once



#include <Hexagon/CodeRange.hpp>
#include <vector>
#include <string>



class CodeRangeRenderer
{
private:
   const std::vector<std::string> &lines;
   CodeRange &code_range;
   int first_line_number;
   int cell_width;
   int cell_height;

public:
   CodeRangeRenderer(const std::vector<std::string> &lines, CodeRange &code_range, int first_line_number, int cell_width, int cell_height);

   bool verify_line_in_range(int line_num);
   int get_line_length(int line_num);
   void render();
};



