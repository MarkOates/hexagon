#pragma once


#include <string>


class ApplicationController
{
private:
   std::string regex_temp_filename;

public:
   ApplicationController(std::string regex_temp_filename="");
   ~ApplicationController();


void run_program();
void verify_presence_of_temp_files_and_assign_to_global_constants();
void draw_hexagon_logo_and_wait_for_keypress(int display_width=1, int display_height=1);
};



