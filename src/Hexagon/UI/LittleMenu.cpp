

#include <Hexagon/UI/LittleMenu.hpp>



namespace Hexagon
{
namespace UI
{


ALLEGRO_EVENT LittleMenu::a_default_empty_event = {};


LittleMenu::LittleMenu(AllegroFlare::FontBin* font_bin)
   : StageInterface(LITTLE_MENU)
   , font_bin(font_bin)
   , menu({})
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
return;

}

void LittleMenu::process_local_event(std::string event_name, ActionData action_data)
{
return;

}
} // namespace UI
} // namespace Hexagon


