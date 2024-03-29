#pragma once


#include <Hexagon/System/System.hpp>
#include <allegro5/allegro.h>


class ApplicationController
{
private:
   Hexagon::System::Config hexagon_config;
   ALLEGRO_DISPLAY* display;
   ALLEGRO_EVENT_QUEUE* event_queue;
   ALLEGRO_TIMER* primary_timer;
   ALLEGRO_TIMER* regular_refresh_timer;
   Hexagon::System::System* system;
   ALLEGRO_EVENT_SOURCE user_event_source;
   bool shutdown_program;

protected:


public:
   ApplicationController(Hexagon::System::Config hexagon_config={"/Users/markoates/Repos/hexagon/bin/programs/data/config/hexagon.boot.cfg"});
   ~ApplicationController();

   void initialize();
   void shutdown();
   void create_event_queue_and_register_event_sources();
   void create_display();
   void setup_orthographic_projection();
   void emit_user_event(ALLEGRO_EVENT user_event={});
   void run_program();
   void run_event_loop();
   void verify_presence_of_temp_files_and_assign_to_global_constants();
};



