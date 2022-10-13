

#include <Hexagon/DarkModeDetector.hpp>

#include <Blast/ShellCommandExecutorWithCallback.hpp>
#include <Blast/String/Trimmer.hpp>


namespace Hexagon
{


DarkModeDetector::DarkModeDetector()
{
}


DarkModeDetector::~DarkModeDetector()
{
}


bool DarkModeDetector::is_dark()
{
   std::string command_result = get_trimmed_command_result();
   return command_result == DARK_MODE_RESPONSE_STRING;
}

bool DarkModeDetector::is_light()
{
   std::string command_result = get_trimmed_command_result();
   return command_result != DARK_MODE_RESPONSE_STRING;
}

std::string DarkModeDetector::get_trimmed_command_result()
{
   std::string shell_command = "defaults read -g AppleInterfaceStyle";
   std::string command_result = Blast::ShellCommandExecutorWithCallback(shell_command).execute();
   return Blast::String::Trimmer(command_result).trim();
}


} // namespace Hexagon


