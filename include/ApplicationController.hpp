#pragma once


#include <Hexagon/System/System.hpp>


class ApplicationController
{
private:
   Hexagon::System::Config config;

public:
   ApplicationController(Hexagon::System::Config config={"/Users/markoates/Repos/hexagon/bin/programs/data/config/hexagon.boot.cfg"});
   ~ApplicationController();


void run_program();
void verify_presence_of_temp_files_and_assign_to_global_constants();
void draw_hexagon_logo_and_wait_for_keypress(int display_width=1, int display_height=1);
};



