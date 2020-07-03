#pragma once


#include <Hexagon/System/System.hpp>
#include <allegro5/allegro.h>
#include <allegro_flare/motion.h>


class ApplicationController
{
private:
   Hexagon::System::Config config;
   ALLEGRO_DISPLAY* display;
   ALLEGRO_EVENT_QUEUE* event_queue;
   ALLEGRO_TIMER* primary_timer;
   Motion motion;

public:
   ApplicationController(Hexagon::System::Config config={"/Users/markoates/Repos/hexagon/bin/programs/data/config/hexagon.boot.cfg"});
   ~ApplicationController();


void initialize_allegro_config_display_event_queue_and_timer();
void run_program();
void verify_presence_of_temp_files_and_assign_to_global_constants();
void draw_hexagon_logo_and_wait_for_keypress(int display_width=1, int display_height=1);
};



