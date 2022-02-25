

#include <ApplicationController.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <Hexagon/TitleScreen.hpp>
#include <Hexagon/System/System.hpp>
#include <Hexagon/System/Renderer.hpp>
#include <iostream>
#include <sstream>
#include <allegro_flare/useful_php.h>
#include <Hexagon/shared_globals.hpp>
#include <stdexcept>
#include <sstream>




ApplicationController::ApplicationController(Hexagon::System::Config hexagon_config)
   : hexagon_config(hexagon_config)
   , display(nullptr)
   , event_queue(nullptr)
   , primary_timer(nullptr)
   , system(nullptr)
   , user_event_source()
   , shutdown_program(false)
{
}


ApplicationController::~ApplicationController()
{
}


void ApplicationController::initialize()
{
   // initialize allegro
   if (!al_init()) std::cerr << "al_init() failed" << std::endl;
   if (!al_init_font_addon()) std::cerr << "al_init_font_addon() failed" << std::endl;
   if (!al_init_ttf_addon()) std::cerr << "al_init_ttf_addon() failed" << std::endl;
   if (!al_init_primitives_addon()) std::cerr << "al_init_primitives_addon() failed" << std::endl;
   if (!al_init_image_addon()) std::cerr << "al_init_image_addon() failed" << std::endl;
   if (!al_install_keyboard()) std::cerr << "al_install_keyboard() failed" << std::endl;
   if (!al_install_mouse()) std::cerr << "al_install_mouse() failed" << std::endl;

   // initialize the config
   hexagon_config.initialize();

   // create the display
   create_display();

   // create the event queue, regester the event sources (keyboard, mouse, etc...)
   create_event_queue_and_register_event_sources();

   // check that the files that act as temp storage strings are present
   verify_presence_of_temp_files_and_assign_to_global_constants();

   // startup the system
   system = new Hexagon::System::System(display, hexagon_config);
   system->initialize();
}

void ApplicationController::shutdown()
{
   al_destroy_event_queue(event_queue);
   al_destroy_display(display);
   //delete system;
   //al_uninstall_system();
}

void ApplicationController::create_event_queue_and_register_event_sources()
{
   event_queue = al_create_event_queue();
   al_register_event_source(event_queue, al_get_keyboard_event_source());
   al_register_event_source(event_queue, al_get_mouse_event_source());
   al_register_event_source(event_queue, al_get_display_event_source(display));

   primary_timer = al_create_timer(1.0/60.0);
   al_register_event_source(event_queue, al_get_timer_event_source(primary_timer));
   al_start_timer(primary_timer);

   al_init_user_event_source(&user_event_source);
   al_register_event_source(event_queue, &user_event_source);
   return;
}

void ApplicationController::create_display()
{
   // display options
   al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
   al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
   al_set_new_display_option(ALLEGRO_DEPTH_SIZE, 32, ALLEGRO_SUGGEST);

   // display flags
   al_set_new_display_flags(ALLEGRO_RESIZABLE);
   al_set_new_display_flags(ALLEGRO_NOFRAME);
   al_set_new_display_flags(ALLEGRO_NOFRAME | ALLEGRO_OPENGL | ALLEGRO_PROGRAMMABLE_PIPELINE);
   al_set_new_display_flags(ALLEGRO_OPENGL | ALLEGRO_PROGRAMMABLE_PIPELINE);
   if (hexagon_config.is_fullscreen())
   {
      al_set_new_display_flags(al_get_new_display_flags() | ALLEGRO_FULLSCREEN_WINDOW);
   }

   // new bitmap flags
   al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);
   //al_set_new_display_flags(ALLEGRO_OPENGL | ALLEGRO_PROGRAMMABLE_PIPELINE);

   display = al_create_display(
      hexagon_config.get_initial_display_width(),
      hexagon_config.get_initial_display_height());
   if (!display) std::cerr << "al_create_display() failed" << std::endl;

   al_set_window_title(display, "[ProjectName] - Hexagon");

   //int display_width = al_get_display_width(display);
   //int display_height = al_get_display_height(display);

   // TODO: This new feature is currently disabled, mostly because it should be handled by the camera.
   // However, there are also other components (like the Hud) which need to setup a projection as well,
   // they need to be accounted for.

   //setup_orthographic_projection();

   return;
}

void ApplicationController::setup_orthographic_projection()
{
   // set the orthographic display projection
   // the display coordinate values used throughout the program will map to these values from here on
   // (unless the projection is modified)

   ALLEGRO_DISPLAY *al_display = display;
   float left = 0;
   float top = 0;
   float right = 1920;
   float bottom = 1080;
   ALLEGRO_BITMAP *display_bitmap = al_get_backbuffer(al_display);
   ALLEGRO_TRANSFORM trans;
   al_identity_transform(&trans);
   al_orthographic_transform(
         &trans,
         left,
         top,
         -1.0,
         right,
         bottom,
         1.0
      );

   ALLEGRO_STATE previous_target_bitmap_state;
   al_store_state(&previous_target_bitmap_state, ALLEGRO_STATE_TARGET_BITMAP);

   al_set_target_bitmap(display_bitmap);
   al_use_projection_transform(&trans);

   al_restore_state(&previous_target_bitmap_state);
   return;
}

void ApplicationController::emit_user_event(ALLEGRO_EVENT user_event)
{
   al_emit_user_event(&user_event_source, &user_event, NULL);
   return;
}

void ApplicationController::run_program()
{
   initialize();
   //system->run_title_screen();
   run_event_loop();
   shutdown();
}

void ApplicationController::run_event_loop()
{
   if (!(system))
      {
         std::stringstream error_message;
         error_message << "ApplicationController" << "::" << "run_event_loop" << ": error: " << "guard \"system\" not met";
         throw std::runtime_error(error_message.str());
      }
   bool mouse_event_occurred_and_requires_screen_refresh = false;
   static int mouse_event_skip = 0;

   while(!shutdown_program)
   {
      ALLEGRO_EVENT this_event;
      al_wait_for_event(event_queue, &this_event);
      global::profiler.clear();

      system->process_event(&this_event);

      bool refresh = true;

      switch(this_event.type)
      {
      case ALLEGRO_EVENT_DISPLAY_CLOSE:
         shutdown_program = true;
         break;
      case ALLEGRO_EVENT_DISPLAY_RESIZE:
         al_acknowledge_resize(display);
         system->acknowledge_display_resize(display);
         //note that each rezie will cause the display to reload, and will be a bit laggy
         //refresh = false;
         break;
      case ALLEGRO_EVENT_DISPLAY_SWITCH_OUT:
         system->acknowledge_display_switch_out(display);
         break;
      case ALLEGRO_EVENT_DISPLAY_SWITCH_IN:
         system->acknowledge_display_switch_in(display);
         break;
      case ALLEGRO_EVENT_TIMER:
         system->get_motion_ref().update(al_get_time());
         //refresh = true;
         static int previous_num_active_animations = 0;
         if (previous_num_active_animations == 0 && system->get_motion_ref().get_num_active_animations() == 0)
            refresh = false;
         previous_num_active_animations = system->get_motion_ref().get_num_active_animations();
         if (mouse_event_occurred_and_requires_screen_refresh) refresh = true;
         break;
      case ALLEGRO_EVENT_MOUSE_AXES:
      case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
      case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
         refresh = false;
         mouse_event_skip++;
         if (mouse_event_skip >= 10)
         {
            mouse_event_skip = 0;
            mouse_event_occurred_and_requires_screen_refresh = true;
         }
         break;
      }

      if (refresh)
      {
         ALLEGRO_COLOR backfill_color = hexagon_config.get_backfill_color();
         al_clear_to_color(backfill_color);

         Hexagon::System::Renderer renderer(system, display, &backfill_color);
         renderer.render();

         al_flip_display();

         bool drop_backed_up_primary_timer_events = true;
         if (drop_backed_up_primary_timer_events)
         {
            ALLEGRO_EVENT next_event;
            while (al_peek_next_event(event_queue, &next_event)
                 && next_event.type == ALLEGRO_EVENT_TIMER
                 && next_event.timer.source == primary_timer)
              al_drop_next_event(event_queue);
         }

         mouse_event_occurred_and_requires_screen_refresh = false;
      }
   }
   return;
}

void ApplicationController::verify_presence_of_temp_files_and_assign_to_global_constants()
{
   std::string regex_temp_filename = hexagon_config.get_regex_temp_filename();
   if (!php::file_exists(regex_temp_filename))
   {
      std::stringstream error_message;
      error_message << "Error: there is no \"" << regex_temp_filename << "\" located in the directory tree.  "
                    << "It has to be present for hexagon to work.";
      throw std::runtime_error(error_message.str());
   }

   std::string clipboard_temp_filename = hexagon_config.get_clipboard_temp_filename();
   if (!php::file_exists(clipboard_temp_filename))
   {
      std::stringstream error_message;
      error_message << "Error: there is no \"" << clipboard_temp_filename << "\" located in the directory tree. "
                    << "It has to be present for hexagon to work.";
      throw std::runtime_error(error_message.str());
   }

   std::string file_navigator_selection_filename = hexagon_config.get_file_navigator_selection_filename();
   if (!php::file_exists(file_navigator_selection_filename))
   {
      std::stringstream error_message;
      error_message << "Error: there is no \"" << file_navigator_selection_filename
                    << "\" located in the directory tree.  It has to be present for hexagon to work.";
      throw std::runtime_error(error_message.str());
   }

   std::string make_command_filename = hexagon_config.get_make_command_filename();
   if (!php::file_exists(make_command_filename))
   {
      std::stringstream error_message;
      error_message << "Error: there is no \"" << make_command_filename
                    << "\" located in the directory tree.  It has to be present for hexagon to work.";
      throw std::runtime_error(error_message.str());
   }

   // assign confirmed values to globals

   REGEX_TEMP_FILENAME = regex_temp_filename;
   CLIPBOARD_TEMP_FILENAME = clipboard_temp_filename;
   FILE_NAVIGATOR_SELECTION_FILENAME = file_navigator_selection_filename;
   MAKE_COMMAND_FILENAME = make_command_filename;

   return;
}


