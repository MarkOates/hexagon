

#include <Blast/StringJoiner.hpp>

#include <sstream>


namespace Blast
{


StringJoiner::StringJoiner(std::vector<std::string> words, std::string delimiter)
   : words(words)
   , delimiter(delimiter)
{}


StringJoiner::~StringJoiner()
{}


std::string StringJoiner::join()
{
   std::stringstream result;
   bool last = false;

   for (unsigned i=0; i<words.size(); i++)
   {
      result << words[i];
      if (i == words.size()-1) last = true;
      if (!last) result << delimiter;
   }

   return result.str();
}


} // namespace Blast


