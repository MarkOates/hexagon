

#include <Hexagon/UI/LittleMenu.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace Hexagon
{
namespace UI
{


ALLEGRO_EVENT LittleMenu::a_default_empty_event = {};


LittleMenu::LittleMenu(AllegroFlare::FontBin* font_bin, std::string title, std::vector<std::tuple<std::string, std::string>> items)
   : StageInterface(LITTLE_MENU)
   , font_bin(font_bin)
   , title(title)
   , items(items)
   , menu(font_bin, title, items)
   , initialized(false)
{
}


LittleMenu::~LittleMenu()
{
}


bool LittleMenu::get_initialized() const
{
   return initialized;
}


ALLEGRO_EVENT &LittleMenu::get_a_default_empty_event_ref()
{
   return a_default_empty_event;
}


void LittleMenu::initialize()
{
   if (!((!get_initialized())))
   {
      std::stringstream error_message;
      error_message << "LittleMenu" << "::" << "initialize" << ": error: " << "guard \"(!get_initialized())\" not met";
      throw std::runtime_error(error_message.str());
   }
   menu.set_title_upcase(false);
   menu.set_menu_items_upcase(false);
   initialized = true;
   return;
}

void LittleMenu::render()
{
   if (!(get_initialized()))
   {
      std::stringstream error_message;
      error_message << "LittleMenu" << "::" << "render" << ": error: " << "guard \"get_initialized()\" not met";
      throw std::runtime_error(error_message.str());
   }
   placement3d &place = get_place();
   place.start_transform();
   menu.render();
   place.restore_transform();
   return;
}

void LittleMenu::process_event(ALLEGRO_EVENT& event)
{
   if (!(get_initialized()))
   {
      std::stringstream error_message;
      error_message << "LittleMenu" << "::" << "process_event" << ": error: " << "guard \"get_initialized()\" not met";
      throw std::runtime_error(error_message.str());
   }
   switch(event.type)
   {
   case ALLEGRO_EVENT_KEY_CHAR:
     switch(event.keyboard.keycode)
     {
       case ALLEGRO_KEY_J:
         menu.move_cursor_down();
         break;
       case ALLEGRO_KEY_K:
         menu.move_cursor_up();
         break;
       case ALLEGRO_KEY_ENTER:
         emit_submission();
         break;
     }
     break;
   }
   return;
}

void LittleMenu::process_local_event(std::string event_name, ActionData action_data)
{
   if (!(get_initialized()))
   {
      std::stringstream error_message;
      error_message << "LittleMenu" << "::" << "process_local_event" << ": error: " << "guard \"get_initialized()\" not met";
      throw std::runtime_error(error_message.str());
   }
   return;
}

void LittleMenu::emit_submission()
{
   if (!(get_initialized()))
   {
      std::stringstream error_message;
      error_message << "LittleMenu" << "::" << "emit_submission" << ": error: " << "guard \"get_initialized()\" not met";
      throw std::runtime_error(error_message.str());
   }
   std::cout << "Sumitting Modal with selection \"" << menu.get_current_list_item_identifier() << "\"" << std::endl;
}


} // namespace UI
} // namespace Hexagon


