#include <allegro5/allegro.h> // for compatibility with union/Makefile
#include <Hexagon/Daemus/ProgramRunner.hpp>

void throw_argument_error()
{
   throw std::runtime_error("hexagon/programs/daemus.cpp: error: A valid argument must be used; \"run_once\", "
                            "\"watch_for_buildfile\", or \"watch_in_project_tree\"?");
}

int main(int argc, char **argv)
{
   std::vector<std::string> args;
   for (int i=1; i<argc; i++) args.push_back(argv[i]);

   Hexagon::Daemus::ProgramRunner daemus;
   Hexagon::Daemus::ProgramRunner::WatchMode watch_mode = Hexagon::Daemus::ProgramRunner::WatchMode::UNDEFINED;

   if (args.empty()) throw_argument_error();

   if (args[0] == "watch_in_project_tree")
   {
      // Run Daemus in a holding pattern, watching the project directory for changes in files. This is useful
      // if you are editing in vim.
      watch_mode = Hexagon::Daemus::ProgramRunner::WatchMode::WATCH_FOR_CHANGES_IN_TREE;
      daemus.set_watch_mode(watch_mode);
      daemus.run();
   }
   else if (args[0] == "run_once")
   {
      daemus.run_once();
   }
   else if (args[0] == "watch_for_buildfile")
   {
      // Run Daemus in a holding pattern, watching for a change in the "daemus_buildfile.txt" (see Hexagon/Daemus/ProgramRunner
      // for exact file location). This is useful if editing in Hexagon
      watch_mode = Hexagon::Daemus::ProgramRunner::WatchMode::WATCH_FOR_CHANGE_IN_BUILDFILE;
      daemus.set_watch_mode(watch_mode);
      daemus.run();
   }
   else
   {
      throw std::runtime_error("hexagon/programs/daemus.cpp: error: A valid argument must be used; \"run_once\", "
                               "\"watch_for_buildfile\", or \"watch_in_project_tree\"?");
   }
 

   return 0;
}

