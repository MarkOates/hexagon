#include <Hexagon/RegexMatcher.hpp>


#include <regex>
#include <iostream>


RegexMatcher::RegexMatcher(std::string source_string, std::string regex_expression)
   : source_string(source_string)
   , regex_expression(regex_expression)
{}


RegexMatcher::~RegexMatcher() {}


std::vector<int> RegexMatcher::get_match_positions()
{
   std::vector<int> results;

   std::string subject(source_string);
   try
   {
      //std::regex re("\\w+"); // find words
      std::regex re(regex_expression);
      std::sregex_iterator next(subject.begin(), subject.end(), re);
      std::sregex_iterator end;
      while (next != end)
      {
         std::smatch match = *next;
         std::cout << " - string: " << match.str() << std::endl;
         std::cout << "   position: " << match.position() << std::endl;
         std::cout << "   length: " << match.str().size() << std::endl;
         results.push_back(match.position());
         next++;
      }
   }
   catch (std::regex_error& e)
   {
      throw std::runtime_error("There was a syntax error in the regular expression");
   }

   return results;
}


