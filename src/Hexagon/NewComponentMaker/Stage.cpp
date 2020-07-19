

#include <Hexagon/NewComponentMaker/Stage.hpp>
#include <sstream>
#include <Blast/ShellCommandExecutorWithCallback.hpp>
#include <Blast/StringSplitter.hpp>
#include <sstream>
#include <Blast/ShellCommandExecutorWithCallback.hpp>
#include <Blast/StringSplitter.hpp>


namespace Hexagon
{
namespace NewComponentMaker
{


ALLEGRO_EVENT Stage::a_default_empty_event = {};


Stage::Stage(std::string current_project_directory, std::string component_name)
   : StageInterface(StageInterface::NEW_COMPONENT_MAKER)
   , current_project_directory(current_project_directory)
   , component_name(component_name)
   , shell_command_has_executed(false)
   , last_executed_shell_response("")
   , path_to_executable("~/Repos/blast/bin/programs/component_generator")
{
}


Stage::~Stage()
{
}


std::string Stage::get_current_project_directory()
{
   return current_project_directory;
}


ALLEGRO_EVENT &Stage::get_a_default_empty_event_ref()
{
   return a_default_empty_event;
}


void Stage::render()
{
return;

}

void Stage::process_local_event(std::string event_name, ActionData action_data)
{
return;
}

void Stage::process_event(ALLEGRO_EVENT& event)
{
return;

}

std::string Stage::get_shell_response()
{
if (shell_command_has_executed) return last_executed_shell_response;
Blast::ShellCommandExecutorWithCallback executor(
      build_shell_command(),
      Blast::ShellCommandExecutorWithCallback::simple_silent_callback
   );
last_executed_shell_response = executor.execute();
return last_executed_shell_response;

}

std::vector<std::string> Stage::get_shell_response_lines()
{
return Blast::StringSplitter(get_shell_response(), '\n').split();

}

std::string Stage::build_shell_command()
{
std::stringstream commit_everything_shell_command;
commit_everything_shell_command << "("
                                << "cd " << current_project_directory
                                << " && "
                                << path_to_executable << " " << component_name
                                << ")";

return commit_everything_shell_command.str();

}
} // namespace NewComponentMaker
} // namespace Hexagon


