


#include <Hexagon/GitLinesModifiedExtractor.hpp>

#include <Blast/ShellCommandExecutor.hpp>
#include <Blast/StringSplitter.hpp>
#include <sstream>



GitLinesModifiedExtractor::GitLinesModifiedExtractor(std::string filename)
   : filename(filename)
   , lines_modified()
   , executed(false)
{}



GitLinesModifiedExtractor::~GitLinesModifiedExtractor()
{}



void GitLinesModifiedExtractor::execute()
{
   if (executed) return;

   std::stringstream git_changed_lines_shell_command;
   git_changed_lines_shell_command << "git blame " << filename << " | grep -n '^0\\{8\\} ' | cut -f1 -d:";
   Blast::ShellCommandExecutor shell_command_executor(git_changed_lines_shell_command.str());
   std::string output = shell_command_executor.execute();
   std::vector<std::string> line_numbers_str = Blast::StringSplitter(output, '\n').split();
   lines_modified.clear();
   lines_modified.resize(line_numbers_str.size());
   for (auto &line_number_str : line_numbers_str)
      lines_modified.push_back(atoi(line_number_str.c_str()));
   executed = true;
}



std::vector<int> GitLinesModifiedExtractor::get_lines_modified()
{
   return lines_modified;
}



