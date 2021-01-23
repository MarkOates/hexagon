

#include <Hexagon/UI/LittleMenu.hpp>



namespace Hexagon
{
namespace UI
{


ALLEGRO_EVENT LittleMenu::a_default_empty_event = {};


LittleMenu::LittleMenu()
   : StageInterface(LITTLE_MENU)
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


