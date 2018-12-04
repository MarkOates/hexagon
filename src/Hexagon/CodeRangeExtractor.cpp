


#include <Hexagon/CodeRangeExtractor.hpp>

#include <iostream>



CodeRangeExtractor::CodeRangeExtractor(const std::vector<std::string> &lines, CodeRange &code_range)
   : lines(lines)
   , code_range(code_range)
{}



CodeRangeExtractor::~CodeRangeExtractor()
{}



std::vector<std::string> CodeRangeExtractor::extract()
{
   CodePoint start = code_range.infer_cursor_start();
   CodePoint end = code_range.infer_cursor_end();

   int start_y = std::min(std::max(0, start.get_y()), (int)lines.size());
   int end_y = std::min(std::max(0, (end.get_y()+1)), (int)lines.size());

   std::cout << "CodeRangeExtractor: attempting extraction at (" << start_y << ", " << end_y << ")" << std::endl;

   std::vector<std::string> result(lines.begin() + start_y, lines.begin() + end_y);

   return result;
}




