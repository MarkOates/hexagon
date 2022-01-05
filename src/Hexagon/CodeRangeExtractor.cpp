

#include <Hexagon/CodeRangeExtractor.hpp>
#include <iostream>
#include <algorithm>
#include <algorithm>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{


CodeRangeExtractor::CodeRangeExtractor(std::vector<std::string>* lines, CodeRange* code_range)
   : lines(lines)
   , code_range(code_range)
{
}


CodeRangeExtractor::~CodeRangeExtractor()
{
}


std::vector<std::string> CodeRangeExtractor::extract()
{
   if (!(lines))
      {
         std::stringstream error_message;
         error_message << "CodeRangeExtractor" << "::" << "extract" << ": error: " << "guard \"lines\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(code_range))
      {
         std::stringstream error_message;
         error_message << "CodeRangeExtractor" << "::" << "extract" << ": error: " << "guard \"code_range\" not met";
         throw std::runtime_error(error_message.str());
      }
   CodePoint start = code_range->infer_cursor_start();
   CodePoint end = code_range->infer_cursor_end();

   int start_y = std::min(std::max(0, start.get_y()), (int)lines->size());
   int end_y = std::min(std::max(0, (end.get_y()+1)), (int)lines->size());

   std::cout << "CodeRangeExtractor: attempting extraction at (" << start_y << ", " << end_y << ")" << std::endl;

   std::vector<std::string> result(lines->begin() + start_y, lines->begin() + end_y);

   return result;
}
} // namespace Hexagon


