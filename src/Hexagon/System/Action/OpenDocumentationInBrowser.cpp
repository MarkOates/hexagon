

#include <Hexagon/System/Action/OpenDocumentationInBrowser.hpp>
#include <Blast/ShellCommandExecutorWithCallback.hpp>
#include <sstream>


namespace Hexagon
{
namespace System
{
namespace Action
{


std::string OpenDocumentationInBrowser::DOCUMENTATION_FILENAME = "documentation/index.htm";


OpenDocumentationInBrowser::OpenDocumentationInBrowser(std::string project_path)
   : ::Action("Hexagon::System::Action::OpenDocumentationInBrowser", ActionData())
   , project_path(project_path)
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
   result << "open " << project_path << "/" << DOCUMENTATION_FILENAME;
   return result.str();
}
} // namespace Action
} // namespace System
} // namespace Hexagon


