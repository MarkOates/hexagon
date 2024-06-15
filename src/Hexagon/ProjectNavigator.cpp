

#include <Hexagon/ProjectNavigator.hpp>

#include <Hexagon/Elements/ListMenu.hpp>
#include <allegro5/allegro_primitives.h>
#include <allegro_flare/placement3d.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace Hexagon
{


ALLEGRO_EVENT ProjectNavigator::a_default_empty_event = {};


ProjectNavigator::ProjectNavigator(AllegroFlare::FontBin* font_bin, Hexagon::System::Config* config, std::vector<std::tuple<std::string, std::string>> menu_items)
   : StageInterface(StageInterface::PROJECT_NAVIGATOR)
   , font_bin(font_bin)
   , config(config)
   , menu_items(menu_items)
   , main_menu({})
   , surface_width(1920)
   , surface_height(1080)
   , initialized(false)
{
}


ProjectNavigator::~ProjectNavigator()
{
}


std::vector<std::tuple<std::string, std::string>> ProjectNavigator::get_menu_items() const
{
   return menu_items;
}


ALLEGRO_EVENT &ProjectNavigator::get_a_default_empty_event_ref()
{
   return a_default_empty_event;
}


void ProjectNavigator::set_menu_items(std::vector<std::tuple<std::string, std::string>> menu_items)
{
   this->menu_items = menu_items;
   main_menu.set_list_items(menu_items);
   return;
}

bool ProjectNavigator::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::ProjectNavigator::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::ProjectNavigator::initialize]: error: guard \"(!initialized)\" not met");
   }
   main_menu = Hexagon::Elements::ListMenu(font_bin, "Projects", menu_items);
   main_menu.set_color(ALLEGRO_COLOR{0.8f, 0.85f, 0.86f, 0.86f});
   initialized = true;
   return true;
}

void ProjectNavigator::render()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::ProjectNavigator::render]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::ProjectNavigator::render]: error: guard \"initialized\" not met");
   }
   draw_frame();
   draw_menu();
   return;
}

void ProjectNavigator::draw_frame()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::ProjectNavigator::draw_frame]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::ProjectNavigator::draw_frame]: error: guard \"initialized\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::ProjectNavigator::draw_frame]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::ProjectNavigator::draw_frame]: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   float inset = 20;
   float thickness = 4;
   float roundness = 19;
   ALLEGRO_COLOR color = ALLEGRO_COLOR{0.8f, 0.85f, 0.86f, 0.86f};
   al_draw_rounded_rectangle(
      0+inset,
      0+inset,
      surface_width-inset,
      surface_height-inset,
      roundness,
      roundness,
      color,
      thickness
   );
   return;
}

bool ProjectNavigator::main_menu_cursor_move_up()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::ProjectNavigator::main_menu_cursor_move_up]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::ProjectNavigator::main_menu_cursor_move_up]: error: guard \"initialized\" not met");
   }
   return main_menu.move_cursor_up();
}

bool ProjectNavigator::main_menu_cursor_move_down()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::ProjectNavigator::main_menu_cursor_move_down]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::ProjectNavigator::main_menu_cursor_move_down]: error: guard \"initialized\" not met");
   }
   return main_menu.move_cursor_down();
}

std::string ProjectNavigator::main_menu_get_current_list_item_identifier()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::ProjectNavigator::main_menu_get_current_list_item_identifier]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::ProjectNavigator::main_menu_get_current_list_item_identifier]: error: guard \"initialized\" not met");
   }
   return main_menu.get_current_list_item_identifier();
}

void ProjectNavigator::draw_menu()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::ProjectNavigator::draw_menu]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::ProjectNavigator::draw_menu]: error: guard \"initialized\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::ProjectNavigator::draw_menu]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::ProjectNavigator::draw_menu]: error: guard \"font_bin\" not met");
   }
   placement3d place(surface_width/2, surface_height/2, 0);
   place.scale = vec3d(0.6, 0.6, 0.6);
   place.size = vec3d{ (float)main_menu.get_width(), 400.0f, 0.0f };
   place.start_transform();
   main_menu.render();
   place.restore_transform();
   return;
}

void ProjectNavigator::process_local_event(std::string event_name, ActionData action_data)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::ProjectNavigator::process_local_event]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::ProjectNavigator::process_local_event]: error: guard \"initialized\" not met");
   }
   //Hexagon::AdvancedCodeEditor::EventController event_controller(this, build_local_events_dictionary());
   //event_controller.process_local_event(event_name, action_data);
   return;
}

void ProjectNavigator::process_event(ALLEGRO_EVENT& event)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::ProjectNavigator::process_event]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::ProjectNavigator::process_event]: error: guard \"initialized\" not met");
   }
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

std::vector<std::tuple<std::string, std::string>> ProjectNavigator::build_placeholder_menu_items()
{
   return {
      { "AllegroFlare", "/Users/markoates/Repos/allegro_flare/" },
      { "Hexagon", "/Users/markoates/Repos/hexagon/" },
      { "Blast", "/Users/markoates/Repos/blast/" },
   };
}


} // namespace Hexagon


