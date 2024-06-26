

#include <Hexagon/CodeRangeExtractor.hpp>

#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>


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
      error_message << "[Hexagon::CodeRangeExtractor::extract]: error: guard \"lines\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::CodeRangeExtractor::extract]: error: guard \"lines\" not met");
   }
   if (!(code_range))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::CodeRangeExtractor::extract]: error: guard \"code_range\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::CodeRangeExtractor::extract]: error: guard \"code_range\" not met");
   }
   CodePoint start = code_range->infer_cursor_start();
   CodePoint end = code_range->infer_cursor_end();

   int start_x = start.get_x();
   int end_x = end.get_x();
   int start_y = std::min(std::max(0, start.get_y()), (int)lines->size());
   int end_y = std::min(std::max(0, (end.get_y()+1)), (int)lines->size());

   std::vector<std::string> result_full_lines(lines->begin() + start_y, lines->begin() + end_y);
   std::vector<std::string> result = result_full_lines;

   if (result.size() == 1)
   {
      result[0] = result[0].substr(0, end_x).substr(start_x);
   }

   return result;
}

std::vector<std::string> CodeRangeExtractor::extract_full_lines()
{
   if (!(lines))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::CodeRangeExtractor::extract_full_lines]: error: guard \"lines\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::CodeRangeExtractor::extract_full_lines]: error: guard \"lines\" not met");
   }
   if (!(code_range))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::CodeRangeExtractor::extract_full_lines]: error: guard \"code_range\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::CodeRangeExtractor::extract_full_lines]: error: guard \"code_range\" not met");
   }
   CodePoint start = code_range->infer_cursor_start();
   CodePoint end = code_range->infer_cursor_end();

   int start_x = start.get_x();
   int end_x = end.get_x();
   int start_y = std::min(std::max(0, start.get_y()), (int)lines->size());
   int end_y = std::min(std::max(0, (end.get_y()+1)), (int)lines->size());

   std::vector<std::string> result_full_lines(lines->begin() + start_y, lines->begin() + end_y);

   return result_full_lines;
}


} // namespace Hexagon


