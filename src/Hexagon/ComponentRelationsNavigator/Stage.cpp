

#include <Hexagon/ComponentRelationsNavigator/Stage.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <iostream>


namespace Hexagon
{
namespace ComponentRelationsNavigator
{


ALLEGRO_EVENT Stage::a_default_empty_event = {};


Stage::Stage(AllegroFlare::FontBin* font_bin, std::vector<std::tuple<std::string, std::string>> dependents_menu_items, std::vector<std::tuple<std::string, std::string>> relatives_menu_items, std::vector<std::tuple<std::string, std::string>> dependencies_menu_items)
   : StageInterface(StageInterface::COMPONENT_RELATIONS_NAVIGATOR)
   , font_bin(font_bin)
   , dependents_menu_items(dependents_menu_items)
   , relatives_menu_items(relatives_menu_items)
   , dependencies_menu_items(dependencies_menu_items)
   , dependents_menu(font_bin, "Dependents", dependents_menu_items)
   , relatives_menu(font_bin, "Relatives", relatives_menu_items)
   , dependencies_menu(font_bin, "Dependencies", dependencies_menu_items)
   , dependents_menu_place(-700, 0, 0)
   , relatives_menu_place(0, 0, 0)
   , dependencies_menu_place(700, 0, 0)
   , initialized(false)
   , currently_active_menu(nullptr)
   , default_color({0.973, 0.592, 0.078, 1.0})
{
}


Stage::~Stage()
{
}


bool Stage::get_initialized()
{
   return initialized;
}


Hexagon::Elements::ListMenu* Stage::get_currently_active_menu()
{
   return currently_active_menu;
}


ALLEGRO_COLOR Stage::get_default_color()
{
   return default_color;
}


ALLEGRO_EVENT &Stage::get_a_default_empty_event_ref()
{
   return a_default_empty_event;
}


void Stage::initialize()
{
   if (!((!get_initialized())))
      {
         std::stringstream error_message;
         error_message << "Stage" << "::" << "initialize" << ": error: " << "guard \"(!get_initialized())\" not met";
         throw std::runtime_error(error_message.str());
      }
   dependents_menu.set_color(default_color);
   relatives_menu.set_color(default_color);
   dependencies_menu.set_color(default_color);

   dependents_menu_place.size.x = 600; //dependents_menu.get_width();
   relatives_menu_place.size.x = 600; //relatives_menu.get_width();
   dependencies_menu_place.size.x = 600; //dependencies_menu.get_width();

   dependents_menu_place.align.x = 0.5;
   relatives_menu_place.align.x = 0.5;
   dependencies_menu_place.align.x = 0.5;

   set_currently_active_menu(&relatives_menu);
   initialized = true;
   return;
}

void Stage::set_currently_active_menu(Hexagon::Elements::ListMenu* menu)
{
   if (!(menu))
      {
         std::stringstream error_message;
         error_message << "Stage" << "::" << "set_currently_active_menu" << ": error: " << "guard \"menu\" not met";
         throw std::runtime_error(error_message.str());
      }
   dependents_menu.set_active(false);
   relatives_menu.set_active(false);
   dependencies_menu.set_active(false);

   this->currently_active_menu = menu;
   if (currently_active_menu) currently_active_menu->set_active(true);

   return;
}

bool Stage::is_currently_active_menu(Hexagon::Elements::ListMenu* currently_active_menu)
{
   return (get_currently_active_menu() == currently_active_menu);
}

void Stage::render()
{
   if (!(get_initialized()))
      {
         std::stringstream error_message;
         error_message << "Stage" << "::" << "render" << ": error: " << "guard \"get_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   placement3d &place = get_place();
   place.start_transform();
      dependents_menu_place.start_transform();
         dependents_menu.render();
      dependents_menu_place.restore_transform();
      relatives_menu_place.start_transform();
         relatives_menu.render();
      relatives_menu_place.restore_transform();
      dependencies_menu_place.start_transform();
         dependencies_menu.render();
      dependencies_menu_place.restore_transform();
   place.restore_transform();
   return;
}

void Stage::move_cursor_up()
{
   if (is_currently_active_menu(&dependents_menu))
   {
      dependents_menu.move_cursor_up();
   }
   else if (is_currently_active_menu(&relatives_menu))
   {
      relatives_menu.move_cursor_up();
   }
   else if (is_currently_active_menu(&dependencies_menu))
   {
      dependencies_menu.move_cursor_up();
   }
   return;
}

void Stage::move_cursor_down()
{
   if (is_currently_active_menu(&dependents_menu))
   {
      dependents_menu.move_cursor_down();
   }
   else if (is_currently_active_menu(&relatives_menu))
   {
      relatives_menu.move_cursor_down();
   }
   else if (is_currently_active_menu(&dependencies_menu))
   {
      dependencies_menu.move_cursor_down();
   }
   return;
}

void Stage::move_cursor_left()
{
   if (!(get_initialized()))
      {
         std::stringstream error_message;
         error_message << "Stage" << "::" << "move_cursor_left" << ": error: " << "guard \"get_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (is_currently_active_menu(&dependents_menu))
   {
      set_currently_active_menu(&dependencies_menu);
   }
   else if (is_currently_active_menu(&relatives_menu))
   {
      set_currently_active_menu(&dependents_menu);
   }
   else if (is_currently_active_menu(&dependencies_menu))
   {
      set_currently_active_menu(&relatives_menu);
   }
   else
   {
      // throw an error
   }
   return;
}

void Stage::move_cursor_right()
{
   if (!(get_initialized()))
      {
         std::stringstream error_message;
         error_message << "Stage" << "::" << "move_cursor_right" << ": error: " << "guard \"get_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (is_currently_active_menu(&dependents_menu))
   {
      set_currently_active_menu(&relatives_menu);
   }
   else if (is_currently_active_menu(&relatives_menu))
   {
      set_currently_active_menu(&dependencies_menu);
   }
   else if (is_currently_active_menu(&dependencies_menu))
   {
      set_currently_active_menu(&dependents_menu);
   }
   else
   {
      // throw an error
   }
   return;
}

void Stage::process_event(ALLEGRO_EVENT& event)
{
   if (!(get_initialized()))
      {
         std::stringstream error_message;
         error_message << "Stage" << "::" << "process_event" << ": error: " << "guard \"get_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   switch(event.type)
   {
   case ALLEGRO_EVENT_KEY_CHAR:
     switch(event.keyboard.keycode)
     {
       case ALLEGRO_KEY_K:
         move_cursor_up();
         break;
       case ALLEGRO_KEY_J:
         move_cursor_down();
         break;
       case ALLEGRO_KEY_H:
         move_cursor_left();
         break;
       case ALLEGRO_KEY_L:
         move_cursor_right();
         break;
       case ALLEGRO_KEY_ENTER:
         emit_submission();
         break;
     }
     break;
   }
   return;
}

void Stage::set_upcase(bool upcase)
{
   dependents_menu.set_upcase(upcase);
   relatives_menu.set_upcase(upcase);
   dependencies_menu.set_upcase(upcase);
   return;
}

void Stage::process_local_event(std::string event_name, ActionData action_data)
{
   if (!(get_initialized()))
      {
         std::stringstream error_message;
         error_message << "Stage" << "::" << "process_local_event" << ": error: " << "guard \"get_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   return;
}

void Stage::emit_submission()
{
   std::cout << "DUMMY_MESSAGE: Sumitting ComponentRelationsNavigator/Stage with current selections (\""
             << dependents_menu.get_current_list_item_identifier() << ", "
             << relatives_menu.get_current_list_item_identifier() << ", "
             << dependencies_menu.get_current_list_item_identifier() << ")"
             << "\"" << std::endl;
}
} // namespace ComponentRelationsNavigator
} // namespace Hexagon


