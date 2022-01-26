

#include <Hexagon/MultiplexMenu/Stage.hpp>
#include <Hexagon/MultiplexMenu/Renderer.hpp>


namespace Hexagon
{
namespace MultiplexMenu
{


ALLEGRO_EVENT Stage::a_default_empty_event = {};


Stage::Stage()
   : StageInterface(StageInterface::MULTIPLEX_MENU)
{
}


Stage::~Stage()
{
}


ALLEGRO_EVENT &Stage::get_a_default_empty_event_ref()
{
   return a_default_empty_event;
}


void Stage::render()
{
   placement3d &place = get_place();
   place.start_transform();

   Hexagon::MultiplexMenu::Renderer renderer;
   renderer.render();

   place.restore_transform();
   return;
}

void Stage::process_local_event(std::string event_name, ActionData action_data)
{
   return;
}

void Stage::process_event(ALLEGRO_EVENT& event)
{
   return;
}
} // namespace MultiplexMenu
} // namespace Hexagon


