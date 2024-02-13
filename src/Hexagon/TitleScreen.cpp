

#include <Hexagon/TitleScreen.hpp>

#include <AllegroFlare/Profiler.hpp>
#include <Hexagon/Elements/DataTable.hpp>
#include <Hexagon/Elements/ListMenu.hpp>
#include <Hexagon/Logo.hpp>
#include <Hexagon/Shaders/TiledHexagonMotionEffect.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro_flare/placement3d.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace Hexagon
{


TitleScreen::TitleScreen(AllegroFlare::FontBin* font_bin, Hexagon::System::Config* config)
   : font_bin(font_bin)
   , config(config)
   , main_menu({})
   , surface_width(1920)
   , surface_height(1080)
   , initialized(false)
{
}


TitleScreen::~TitleScreen()
{
}


bool TitleScreen::get_initialized() const
{
   return initialized;
}


void TitleScreen::initialize()
{
   main_menu = Hexagon::Elements::ListMenu(font_bin, "Projects", {
      { "Hexagon", "/Users/markoates/Repos/hexagon/" },
      { "Blast", "/Users/markoates/Repos/blast/" },
      { "LabyrinthOfLore", "/Users/markoates/Repos/LabyrinthOfLore/" },
      { "LightracerMax", "/Users/markoates/Repos/lightracer-max/" },
      { "NcursesArt", "/Users/markoates/Repos/ncurses_art/" },
      { "Solitare", "/Users/markoates/Repos/Solitare/" },
      { "AllegroFlare", "/Users/markoates/Repos/allegro_flare/" },
      { "Wicked", "/Users/markoates/Repos/Wicked/" },
      { "Krampus21 (Fade to White)", "/Users/markoates/Repos/Krampus21/" },
      { "Peri", "/Users/markoates/Repos/Peri/" },
      { "Solitare", "/Users/markoates/Repos/Solitare/" },
      { "Epidemic", "/Users/markoates/Repos/Epidemic/" },
      { "Ontario Driver's Quiz", "/Users/markoates/Repos/OntarioDriversQuiz/" },
      //{ "tins2021", "/Users/markoates/Repos/tins2021/" },
   });
   initialized = true;
   return;
}

bool TitleScreen::main_menu_cursor_move_up()
{
   return main_menu.move_cursor_up();
}

bool TitleScreen::main_menu_cursor_move_down()
{
   return main_menu.move_cursor_down();
}

std::string TitleScreen::main_menu_get_current_list_item_identifier()
{
   return main_menu.get_current_list_item_identifier();
}

void TitleScreen::draw_hexagon_logo_and_wait_for_keypress()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[TitleScreen::draw_hexagon_logo_and_wait_for_keypress]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TitleScreen::draw_hexagon_logo_and_wait_for_keypress: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[TitleScreen::draw_hexagon_logo_and_wait_for_keypress]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TitleScreen::draw_hexagon_logo_and_wait_for_keypress: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[TitleScreen::draw_hexagon_logo_and_wait_for_keypress]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TitleScreen::draw_hexagon_logo_and_wait_for_keypress: error: guard \"font_bin\" not met");
   }
   if (!(al_get_target_bitmap()))
   {
      std::stringstream error_message;
      error_message << "[TitleScreen::draw_hexagon_logo_and_wait_for_keypress]: error: guard \"al_get_target_bitmap()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TitleScreen::draw_hexagon_logo_and_wait_for_keypress: error: guard \"al_get_target_bitmap()\" not met");
   }
   if (!(get_initialized()))
   {
      std::stringstream error_message;
      error_message << "[TitleScreen::draw_hexagon_logo_and_wait_for_keypress]: error: guard \"get_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TitleScreen::draw_hexagon_logo_and_wait_for_keypress: error: guard \"get_initialized()\" not met");
   }
   AllegroFlare::Profiler profiler;

   float logo_radius = 64;
   int display_width = al_get_bitmap_width(al_get_target_bitmap());
   int display_height = al_get_bitmap_height(al_get_target_bitmap());
   ALLEGRO_COLOR hexagon_red = al_color_html("#bc2d48");
   Hexagon::Shaders::TiledHexagonMotionEffect shader;
   shader.initialize();

   std::string logo_font_identifier = "Expansiva_bold.otf 23";
   ALLEGRO_FONT *expansiva_font = font_bin->auto_get(logo_font_identifier);

   std::string detail_text_font_identifier = "Exan-Regular.ttf 16";
   //"Purista Medium.otf 16";
   ALLEGRO_FONT *purista_font = font_bin->auto_get(detail_text_font_identifier);

   al_install_keyboard();

   ALLEGRO_EVENT_QUEUE *primary_event_queue;
   primary_event_queue = al_create_event_queue();
   al_register_event_source(primary_event_queue, al_get_keyboard_event_source());

   ALLEGRO_TIMER *primary_timer = al_create_timer(1.0/60);
   al_register_event_source(primary_event_queue, al_get_timer_event_source(primary_timer));
   al_start_timer(primary_timer);

   ALLEGRO_BITMAP *dummy_bitmap = al_create_bitmap(surface_width, surface_height);


   ALLEGRO_STATE previous_render_state; 
   al_store_state(&previous_render_state, ALLEGRO_STATE_TARGET_BITMAP);

   al_set_target_bitmap(dummy_bitmap);
   ALLEGRO_TRANSFORM dummy_bitmap_transform;
   al_identity_transform(&dummy_bitmap_transform);
   //float x_scale = (float)surface_width / display_width;
   //float y_scale = (float)surface_height / display_height;
   //al_scale_transform(&dummy_bitmap_transform, x_scale, y_scale);
   //al_use_projection_transform(&dummy_bitmap_transform);
   //al_set_target_bitmap(al_get_backbuffer(al_get_current_display()));

   al_restore_state(&previous_render_state);


   // wait for keypress
   bool abort_program = false;
   bool draw_motion_effect = true;
   while (!abort_program)
   {
      ALLEGRO_EVENT event;
      al_wait_for_event(primary_event_queue, &event);

      switch(event.type)
      {
      case ALLEGRO_EVENT_KEY_CHAR:
         {
            switch (event.keyboard.keycode)
            {
            case ALLEGRO_KEY_M:
               // disable shader
               draw_motion_effect = false;

               // open dialog box
               break;
            case ALLEGRO_KEY_J:
               main_menu_cursor_move_down();
               break;
            case ALLEGRO_KEY_K:
               main_menu_cursor_move_up();
               break;
            case ALLEGRO_KEY_ENTER:
               append_project_path_to_config_file_and_reload_injected_config();
               abort_program = true;
               break;
            case ALLEGRO_KEY_ESCAPE:
               abort_program = true;
               break;
            }
         }
         break;
      case ALLEGRO_EVENT_TIMER:
         {
            profiler.emit("primary_timer logic started");

            ALLEGRO_STATE previous_render_state; 
            al_store_state(&previous_render_state, ALLEGRO_STATE_TARGET_BITMAP);
            al_set_target_bitmap(dummy_bitmap);

            al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 1});

            bool draw_motion_effect = false;
            if (draw_motion_effect)
            {
               shader.activate();
               shader.set_texture_width(al_get_bitmap_width(dummy_bitmap));
               shader.set_texture_height(al_get_bitmap_height(dummy_bitmap));
               shader.set_time(al_get_time());

               al_draw_bitmap(dummy_bitmap, 0, 0, 0);

               shader.deactivate();
            }

            Hexagon::Logo logo(
              display_width/2,
              display_height/2,
              logo_radius,
              expansiva_font,
              hexagon_red,
              2.25);
            logo.render();

            std::string allegro_version_string = build_allegro_version_string();
            al_draw_text(purista_font, hexagon_red,
               display_width/2, display_height/2 + logo_radius * 2.0, ALLEGRO_ALIGN_CENTER,
               allegro_version_string.c_str());

            draw_menu();

            //render_profiler_graph(&profiler, purista_font);

            //al_set_target_bitmap(al_get_backbuffer(al_get_current_display()));
            al_restore_state(&previous_render_state);

            al_draw_bitmap(dummy_bitmap, 0, 0, 0);

            profiler.emit("primary_timer logic ended");
            profiler.emit("al_flip_display logic started");
            al_flip_display();
            profiler.emit("al_flip_display logic ended");

            bool drop_backed_up_primary_timer_events = true;
            if (drop_backed_up_primary_timer_events)
            {
               ALLEGRO_EVENT next_event;
               while (al_peek_next_event(primary_event_queue, &next_event)
                    && next_event.type == ALLEGRO_EVENT_TIMER
                    && next_event.timer.source == primary_timer)
                 al_drop_next_event(primary_event_queue);
            }
         }
         break;
      default:
         break;
      }
   }

   al_destroy_bitmap(dummy_bitmap);
   al_stop_timer(primary_timer);
   al_destroy_event_queue(primary_event_queue);
   al_destroy_timer(primary_timer);

   return;
}

void TitleScreen::draw_menu()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[TitleScreen::draw_menu]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TitleScreen::draw_menu: error: guard \"font_bin\" not met");
   }
   placement3d place(surface_width/2, surface_height/2, 0);
   place.start_transform();
   main_menu.render();
   place.restore_transform();
   return;
}

void TitleScreen::render_profiler_graph(AllegroFlare::Profiler* profiler, ALLEGRO_FONT* font)
{
   if (!(profiler))
   {
      std::stringstream error_message;
      error_message << "[TitleScreen::render_profiler_graph]: error: guard \"profiler\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TitleScreen::render_profiler_graph: error: guard \"profiler\" not met");
   }
   if (!(font))
   {
      std::stringstream error_message;
      error_message << "[TitleScreen::render_profiler_graph]: error: guard \"font\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TitleScreen::render_profiler_graph: error: guard \"font\" not met");
   }
   std::list<std::string> event_bucket_names = profiler->get_event_bucket_names();
   int line_height = 20;
   ALLEGRO_COLOR hexagon_red = al_color_html("#bc2d48");
   std::vector<std::vector<std::string>> data2d = {};
   for (auto &event_bucket_name : event_bucket_names)
   {
      int past_two_events_duration =
         profiler->get_event_bucket_duration_between_last_two_samples(event_bucket_name);
      std::string event_bucket_num_samples = std::to_string(past_two_events_duration);
      event_bucket_num_samples = std::to_string(profiler->get_event_bucket_num_samples(event_bucket_name));

      data2d.push_back(
         {
            event_bucket_name,
            event_bucket_num_samples,
            std::to_string(past_two_events_duration),
         }
      );
   }
   Hexagon::Elements::DataTable data_table(font, 300, line_height, data2d);
   data_table.render();
   return;
}

std::string TitleScreen::build_allegro_version_string()
{
   uint32_t version = al_get_allegro_version();
   int major = version >> 24;
   int minor = (version >> 16) & 255;
   int revision = (version >> 8) & 255;
   int release = version & 255;

   std::stringstream result;
   result << "Allegro v" << major << "." << minor << "." << revision << " r" << release;
   return result.str();
}

void TitleScreen::append_project_path_to_config_file_and_reload_injected_config()
{
   if (!(config))
   {
      std::stringstream error_message;
      error_message << "[TitleScreen::append_project_path_to_config_file_and_reload_injected_config]: error: guard \"config\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TitleScreen::append_project_path_to_config_file_and_reload_injected_config: error: guard \"config\" not met");
   }
   std::string config_filename = config->get_config_filename();
   std::string current_menu_selection_path_text = main_menu_get_current_list_item_identifier();

   std::ofstream outfile;
   outfile.open(config_filename, std::ios_base::app); // append instead of overwrite
   outfile << std::endl << "default_navigator_directory = " << current_menu_selection_path_text;
   outfile.close();

   config->reload();

   return;
}


} // namespace Hexagon


