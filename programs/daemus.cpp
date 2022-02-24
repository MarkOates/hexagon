#include <allegro5/allegro.h> // for compatibility with union/Makefile
#include <Hexagon/Daemus/ProgramRunner.hpp>

int main(int argc, char **argv)
{
   std::vector<std::string> args;
   for (int i=1; i<argc; i++) args.push_back(argv[i]);

   Hexagon::Daemus::ProgramRunner daemus;

   if (args.size() == 0) daemus.run();
   else if (args[0] == "run_once") daemus.run_once();
   else daemus.run(false);

   return 0;
}

