

#include <Hexagon/ComponentNavigator/List.hpp>
#include <vector>
#include <string>
#include <Blast/ShellCommandExecutorWithCallback.hpp>
#include <NcursesArt/ProjectComponentBasenameExtractor.hpp>
#include <Blast/StringSplitter.hpp>


namespace Hexagon
{
namespace ComponentNavigator
{


List::List()
   : project_root_directory("")
{
}


List::~List()
{
}


std::vector<std::string> List::components()
{
std::vector<std::string> result = {};

std::string find_command = "find quintessence -type f -name \"*.q.yml\"";
Blast::ShellCommandExecutorWithCallback executor(find_command);
std::string executor_response = executor.execute();

Blast::StringSplitter splitter(executor_response, '\n');
std::vector<std::string> quintessence_filenames = splitter.split();

for (auto &item : quintessence_filenames)
{
  NcursesArt::ProjectComponentBasenameExtractor extractor(item);
  result.push_back(extractor.identify_component_basename());
}

return result;

}
} // namespace ComponentNavigator
} // namespace Hexagon


