

#include <Hexagon/ProjectNavigator.hpp>
#include <allegro_flare/placement3d.h>
#include <Hexagon/Elements/ListMenu.hpp>
#include <stdexcept>
#include <sstream>
#include <allegro5/allegro.h>
#include <sstream>


namespace Hexagon
{


ALLEGRO_EVENT ProjectNavigator::a_default_empty_event = {};


ProjectNavigator::ProjectNavigator(AllegroFlare::FontBin* font_bin, Hexagon::System::Config* config)
   : StageInterface(StageInterface::PROJECT_NAVIGATOR)
   , font_bin(font_bin)
   , config(config)
   , main_menu({})
   , surface_width(1920)
   , surface_height(1080)
{
}


ProjectNavigator::~ProjectNavigator()
{
}


ALLEGRO_EVENT &ProjectNavigator::get_a_default_empty_event_ref()
{
   return a_default_empty_event;
}


void ProjectNavigator::initialize()
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
   return;
}

void ProjectNavigator::render()
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
   draw_menu();
   return;
}

bool ProjectNavigator::main_menu_cursor_move_up()
{
   return main_menu.move_cursor_up();
}

bool ProjectNavigator::main_menu_cursor_move_down()
{
   return main_menu.move_cursor_down();
}

std::string ProjectNavigator::main_menu_get_current_list_item_identifier()
{
   return main_menu.get_current_list_item_identifier();
}

void ProjectNavigator::draw_menu()
{
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "ProjectNavigator" << "::" << "draw_menu" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   //placement3d place(surface_width/2, surface_height/2, 0);
   //place.start_transform();
   main_menu.render();
   //place.restore_transform();
   return;
}

std::string ProjectNavigator::build_allegro_version_string()
{
   uint32_t version = al_get_allegro_version();
   int major = version >> 24;
   int minor = (version >> 16) & 255;
   int revision = (version >> 8) & 255;
   int release = version & 255;

   std::stringstream result;
   result << "Allegro v" << major << "-" << minor << "-" << revision << " r" << release;
   return result.str();
}

void ProjectNavigator::process_local_event(std::string event_name, ActionData action_data)
{
   //Hexagon::AdvancedCodeEditor::EventController event_controller(this, build_local_events_dictionary());
   //event_controller.process_local_event(event_name, action_data);
   return;
}

void ProjectNavigator::process_event(ALLEGRO_EVENT& event)
{
   switch(event.type)
       {
       case ALLEGRO_EVENT_KEY_CHAR:
          {
             switch (event.keyboard.keycode)
             {
             case ALLEGRO_KEY_M:
                // disable shader
                //draw_motion_effect = false;

                // open dialog box
                break;
             case ALLEGRO_KEY_J:
                main_menu_cursor_move_down();
                break;
             case ALLEGRO_KEY_K:
                main_menu_cursor_move_up();
                break;
             case ALLEGRO_KEY_ENTER:
                //append_project_path_to_config_file_and_reload_injected_config();
                //abort_program = true;
                break;
             case ALLEGRO_KEY_ESCAPE:
                //abort_program = true;
                break;
             }
          }
          break;
   }
   //KeyboardCommandMapper keyboard_command_mapping;
   //if (is_in_insert_mode()) keyboard_command_mapping = build_keyboard_command_mapping_for_insert_mode();
   //else if (is_in_edit_mode()) keyboard_command_mapping = build_keyboard_command_mapping_for_edit_mode();

   //Hexagon::AdvancedCodeEditor::EventController event_controller(
   //      this,
   //      build_local_events_dictionary(),
   //      keyboard_command_mapping
   //   );
   //event_controller.process_event(event);
   return;
}
} // namespace Hexagon


