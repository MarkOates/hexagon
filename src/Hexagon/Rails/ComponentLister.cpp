

#include <Hexagon/Rails/ComponentLister.hpp>
#include <sstream>
#include <Blast/ShellCommandExecutorWithCallback.hpp>
#include <Blast/StringSplitter.hpp>


namespace Hexagon
{
namespace Rails
{


ComponentLister::ComponentLister(std::string project_root_directory)
   : project_root_directory(project_root_directory)
{
}


ComponentLister::~ComponentLister()
{
}


std::vector<std::string> ComponentLister::model_filenames()
{
std::string fragment_folder_name = "app/models";
std::string fragment_extension = ".rb";

std::stringstream find_command;
find_command << "cd "
             << project_root_directory
             << " && find "
             << fragment_folder_name
             << " -type f -name \"*"
             << fragment_extension
             << "\""
             << " -o"
             << " -type l -name \"*"
             << fragment_extension
             << "\"";

Blast::ShellCommandExecutorWithCallback shell_command_executor(
   find_command.str(),
   Blast::ShellCommandExecutorWithCallback::simple_silent_callback
);

std::string executor_response = shell_command_executor.execute();
Blast::StringSplitter splitter(executor_response, '\n');
std::vector<std::string> model_filenames = splitter.split();

return model_filenames;

}
} // namespace Rails
} // namespace Hexagon


