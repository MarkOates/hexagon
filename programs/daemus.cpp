#include <allegro5/allegro.h> // for compatibility with union/Makefile
#include <Hexagon/Daemus/ProgramRunner.hpp>

int main(int argc, char **argv)
{
   std::vector<std::string> args;
   for (int i=1; i<argc; i++) args.push_back(argv[i]);

   Hexagon::Daemus::ProgramRunner daemus;

   if (args.size() == 1 && args[0] == "run_once")
   {
      daemus.run_once();
   }
   else
   {
      Hexagon::Daemus::ProgramRunner::WatchMode watch_mode = Hexagon::Daemus::ProgramRunner::WatchMode::UNDEFINED;

      if (args.size() == 0)
      {
         watch_mode = Hexagon::Daemus::ProgramRunner::WatchMode::WATCH_FOR_CHANGES_IN_TREE;
         daemus.set_watch_mode(watch_mode);
         daemus.run();
      }
      else
      {
         watch_mode = Hexagon::Daemus::ProgramRunner::WatchMode::WATCH_FOR_CHANGE_IN_BUILDFILE;
         daemus.set_watch_mode(watch_mode);
         daemus.run();
         //daemus.run(false);
      }
   }
 
   //if (args.size() == 0) daemus.run();
   //else if (args[0] == "run_once") daemus.run_once();
   //else daemus.run(false);

   return 0;
}

