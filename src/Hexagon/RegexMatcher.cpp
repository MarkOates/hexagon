#include <Hexagon/RegexMatcher.hpp>


#include <regex>
#include <iostream>
#include <sstream>


RegexMatcher::RegexMatcher(std::string source_string, std::string regex_expression)
   : source_string(source_string)
   , regex_expression(regex_expression)
{}


RegexMatcher::~RegexMatcher() {}


std::vector<std::pair<int, int>> RegexMatcher::get_match_info()
{
   std::vector<std::pair<int, int>> results;

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
         //std::cout << " - string: " << match.str() << std::endl;
         //std::cout << "   position: " << match.position() << std::endl;
         //std::cout << "   length: " << match.str().size() << std::endl;
         results.push_back(std::pair<int, int>(match.position(), match.str().size()));
         next++;
      }
   }
   catch (std::regex_error& e)
   {
      std::stringstream error_message;
      error_message << "There was a syntax error in the regular expression:"
         << std::endl
         << source_string
         << std::endl;
      throw std::runtime_error(error_message.str());
   }

   return results;
}


