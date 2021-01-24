

#include <Hexagon/UI/LittleMenu.hpp>
#include <iostream>


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
{
}


LittleMenu::~LittleMenu()
{
}


ALLEGRO_EVENT &LittleMenu::get_a_default_empty_event_ref()
{
   return a_default_empty_event;
}


void LittleMenu::render()
{
placement3d &place = get_place();
place.start_transform();
menu.render();
place.restore_transform();
return;

}

void LittleMenu::process_event(ALLEGRO_EVENT& event)
{
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
return;

}

void LittleMenu::emit_submission()
{
std::cout << "Sumitting Modal with selection \"" << menu.get_current_list_item_identifier() << "\"" << std::endl;

}
} // namespace UI
} // namespace Hexagon


