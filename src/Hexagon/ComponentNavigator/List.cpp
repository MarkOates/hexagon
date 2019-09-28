

#include <Hexagon/ComponentNavigator/List.hpp>
#include <vector>
#include <string>
#include <Blast/ShellCommandExecutorWithCallback.hpp>


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
result = { executor.execute() };
return result;

}
} // namespace ComponentNavigator
} // namespace Hexagon


