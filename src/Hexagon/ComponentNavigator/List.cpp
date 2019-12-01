

#include <Hexagon/ComponentNavigator/List.hpp>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>
#include <iostream>
#include <Blast/ShellCommandExecutorWithCallback.hpp>
#include <NcursesArt/ProjectComponentBasenameExtractor.hpp>
#include <Blast/StringSplitter.hpp>


namespace Hexagon
{
namespace ComponentNavigator
{


List::List(std::string project_root_directory)
   : project_root_directory(project_root_directory)
{
}


List::~List()
{
}


std::vector<std::string> List::components()
{
std::vector<std::string> result = {};

std::stringstream warning_message;
warning_message << "WARNING: This function does NOT vaildate the passed project_root_directory "
                << "and injects it directly into a shell command.  This needs to be fixed."
                << std::endl;
//std::cerr << warning_message;

std::stringstream find_command;
find_command << "cd " << project_root_directory << " && find quintessence -type f -name \"*.q.yml\"";
Blast::ShellCommandExecutorWithCallback executor(find_command.str(), Blast::ShellCommandExecutorWithCallback::simple_silent_callback);
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


