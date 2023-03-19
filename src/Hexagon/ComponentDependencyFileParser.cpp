

#include <Hexagon/ComponentDependencyFileParser.hpp>

#include <Blast/StringSplitter.hpp>
#include <algorithm>
#include <allegro_flare/useful_php.h>


namespace Hexagon
{


ComponentDependencyFileParser::ComponentDependencyFileParser(std::string dependency_filename)
   : dependency_filename(dependency_filename)
{
}


ComponentDependencyFileParser::~ComponentDependencyFileParser()
{
}


std::set<std::string> ComponentDependencyFileParser::generate_dependencies()
{
   // 1) TODO: validate file exists

   // 2) get the contents from the file
   std::string file_contents = php::file_get_contents(dependency_filename);

   // 3) remove excess characters
   std::string chars = "\n\\"; // remove newline and slash character
   for (char c : chars)
   {
     file_contents.erase(std::remove(file_contents.begin(), file_contents.end(), c), file_contents.end());
   }

   // 4) split tokens
   std::vector<std::string> tokens = Blast::StringSplitter(file_contents, ' ').split();

   // 4.2) remove empty tokens
   tokens.erase(
       std::remove_if(tokens.begin(), tokens.end(),
           [](std::string const& s) { return s.empty(); }),
       tokens.end());

   // 5) remove the first and second token, which are the "NameOfSubject.o:" and "src/Foo/NameOfSubject.cpp" listings
   if (!tokens.empty()) tokens.erase(tokens.begin());
   if (!tokens.empty()) tokens.erase(tokens.begin());

   // 6) convert the vector to a set
   std::set<std::string> result;
   for (auto &token : tokens) result.insert(token);

   return result;
}


} // namespace Hexagon


