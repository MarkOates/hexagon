

#include <Hexagon/Git/CommitStagedWithMessage.hpp>
#include <sstream>
#include <Blast/ShellCommandExecutorWithCallback.hpp>


namespace Hexagon
{
namespace Git
{


CommitStagedWithMessage::CommitStagedWithMessage(std::string current_project_directory, std::string message)
   : current_project_directory(current_project_directory)
   , message(message)
{
}


CommitStagedWithMessage::~CommitStagedWithMessage()
{
}


std::string CommitStagedWithMessage::build_sanitized_commit_message()
{
std::string sanitized_commit_message = std::string("* ") + message;
std::replace(sanitized_commit_message.begin(), sanitized_commit_message.end(), '\\', '#');
std::replace(sanitized_commit_message.begin(), sanitized_commit_message.end(), '"', '#');
std::replace(sanitized_commit_message.begin(), sanitized_commit_message.end(), '\r', '#');
std::replace(sanitized_commit_message.begin(), sanitized_commit_message.end(), '\n', '#');
return sanitized_commit_message;

}

bool CommitStagedWithMessage::commit()
{
std::stringstream commit_everything_shell_command;

std::string sanitized_commit_message = build_sanitized_commit_message();
commit_everything_shell_command << "(cd "
                                << current_project_directory
                                << " && git commit -m "
                                << "\"" << sanitized_commit_message << "\""
                                << ")";
Blast::ShellCommandExecutorWithCallback executor(commit_everything_shell_command.str());
executor.execute();
return true;

}
} // namespace Git
} // namespace Hexagon


