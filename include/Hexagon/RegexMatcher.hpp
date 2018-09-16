#pragma once


#include <string>
#include <vector>


class RegexMatcher
{
private:
   std::string source_string;
   std::string regex_expression;

public:
   RegexMatcher(std::string source_string, std::string regex_expression);
   ~RegexMatcher();

   std::vector<std::pair<int, int>> get_match_info();
};


