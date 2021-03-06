

#include <Blast/Daemus/ProgramRunner.hpp>
#include <sstream>
#include <Hexagon/System/Config.hpp>
#include <Hexagon/System/Config.hpp>
#include <Hexagon/System/Config.hpp>
#include <Hexagon/System/Config.hpp>
#include <Blast/ShellCommandExecutorWithCallback.hpp>


namespace Blast
{
namespace Daemus
{


ProgramRunner::ProgramRunner()
{
}


ProgramRunner::~ProgramRunner()
{
}


void ProgramRunner::run()
{
   al_init();
   Hexagon::System::Config hexagon_config;
   hexagon_config.initialize();

   std::string project_directory = hexagon_config.get_default_navigator_directory();

   cd_to_project_directory_and_run_with_rerun(project_directory);
   return;
}

void ProgramRunner::run_in_holding_pattern()
{
   al_init();
   ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();

   // have event source initialized here

   al_destroy_event_queue(event_queue);
   return;
}

void ProgramRunner::run_once(std::string project_directory)
{
   std::string actual_command_to_execute_in_project_directory = "make focus";

   std::stringstream result_command;
   result_command << "cd "
                  << project_directory
                  << " && "
                  << actual_command_to_execute_in_project_directory;

   std::string output = execute_command(result_command.str());
}

void ProgramRunner::cd_to_project_directory_and_run_with_rerun(std::string project_directory)
{
   std::string actual_command_to_execute_in_project_directory = "make focus";

   std::string build_command = "rerun" \
      " " \
      "-c" \
      " " \
      "--background" \
      " " \
      "--ignore \"{**/bin/programs/data/tmp/*,**/documentation/*\"}" \
      " " \
      "-p \"**/*.{rb,js,tsx,coffee,css,scss,sass,erb,html,haml,ru,yml,slim,md,feature,c,h,cpp,hpp,txt,cfg}\"" \
      " " \
      "\"(cd ";

   build_command += project_directory + " && " + actual_command_to_execute_in_project_directory + ")\"";

   std::string build_command_wrapped = "(cd " + project_directory + " && " + build_command + ")";

   std::string output = execute_command(build_command);
   return;
}

void ProgramRunner::run_with_rerun(std::string project_directory)
{
   std::string actual_command_to_execute_in_project_directory = "make focus";

   std::string build_command = "rerun" \
     " " \
     "-c" \
     " " \
     "--background" \
     " " \
     "--ignore \"**/bin/programs/data/tmp/*\"" \
     " " \
     "-p \"**/*.{rb,js,tsx,coffee,css,scss,sass,erb,html,haml,ru,yml,slim,md,feature,c,h,cpp,hpp,txt,cfg}\"" \
     " " \
     "\"(cd ";

   build_command += project_directory + " && " + actual_command_to_execute_in_project_directory + ")\"";
   std::string output = execute_command(build_command);
   return;
}

std::string ProgramRunner::execute_command(std::string command)
{
   Blast::ShellCommandExecutorWithCallback shell_command_executor(
      command,
      Blast::ShellCommandExecutorWithCallback::simple_cout_callback
      //Blast::ShellCommandExecutorWithCallback::simple_silent_callback
   );
   return shell_command_executor.execute();
}
} // namespace Daemus
} // namespace Blast


