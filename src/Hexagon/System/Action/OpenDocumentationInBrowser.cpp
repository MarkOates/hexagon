

#include <Hexagon/System/Action/OpenDocumentationInBrowser.hpp>
#include <Blast/ShellCommandExecutorWithCallback.hpp>
#include <sstream>


namespace Hexagon
{
namespace System
{
namespace Action
{


std::string OpenDocumentationInBrowser::DEPENDENTS_JSON_FILENAME = "/Users/markoates/Repos/Krampus21/documentation/index.htm";


OpenDocumentationInBrowser::OpenDocumentationInBrowser()
   : ::Action("Hexagon::System::Action::OpenDocumentationInBrowser", ActionData())
{
}


OpenDocumentationInBrowser::~OpenDocumentationInBrowser()
{
}


bool OpenDocumentationInBrowser::execute()
{
   std::string shell_command_to_open_browser = build_shell_command_to_open_browser();
   Blast::ShellCommandExecutorWithCallback shell_command_executor(shell_command_to_open_browser);
   shell_command_executor.execute();
   return true;
}

std::string OpenDocumentationInBrowser::build_shell_command_to_open_browser()
{
   std::stringstream result;
   result << "open " << DEPENDENTS_JSON_FILENAME;
   return result.str();
}
} // namespace Action
} // namespace System
} // namespace Hexagon


