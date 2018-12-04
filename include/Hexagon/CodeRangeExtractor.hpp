#pragma once



#include <Hexagon/CodeRange.hpp>
#include <string>
#include <vector>



class CodeRangeExtractor
{
private:
   const std::vector<std::string> &lines;
   CodeRange &code_range;

public:
   CodeRangeExtractor(const std::vector<std::string> &lines, CodeRange &code_range);
   ~CodeRangeExtractor();

   std::vector<std::string> extract();
};




