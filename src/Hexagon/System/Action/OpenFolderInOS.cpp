

#include <Hexagon/System/Action/OpenFolderInOS.hpp>

#include <Blast/ShellCommandExecutorWithCallback.hpp>
#include <filesystem>
#include <sstream>


namespace Hexagon
{
namespace System
{
namespace Action
{


OpenFolderInOS::OpenFolderInOS(std::string folder, std::string project_path)
   : ::Action("Hexagon::System::Action::OpenFolderInOS", ActionData())
   , folder(folder)
   , project_path(project_path)
{
}


OpenFolderInOS::~OpenFolderInOS()
{
}


bool OpenFolderInOS::execute()
{
   std::string shell_command_to_open_browser = build_shell_command_to_open_folder_in_os();
   Blast::ShellCommandExecutorWithCallback shell_command_executor(shell_command_to_open_browser);
   shell_command_executor.execute();
   return true;
}

std::string OpenFolderInOS::build_shell_command_to_open_folder_in_os()
{
   // CRITICAL: Validate is folder
   // TODO: 
   std::string proposed_folder = project_path + "/" + folder;
   if (!std::filesystem::is_directory(proposed_folder))
   {
      throw std::runtime_error(
            "Hexagon::System::Action::OpenFolderInOS::build_shell_command_to_open_folder_in_os: error: \"" + 
            proposed_folder + "\" is not a directory."
         );
   }
   std::stringstream result;
   result << "open " << proposed_folder;
   return result.str();
}


} // namespace Action
} // namespace System
} // namespace Hexagon


