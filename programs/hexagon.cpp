#include <ApplicationController.hpp>
#include <allegro5/allegro.h>

int main(int argc, char **argv)
{
   // TODO: have the config file location be injectable by arg
   std::string config_file_path = "/Users/markoates/Repos/me/hexagon/config/hexagon.boot.cfg";
   ApplicationController app(config_file_path);
   app.run_program();
   return 0;
}
