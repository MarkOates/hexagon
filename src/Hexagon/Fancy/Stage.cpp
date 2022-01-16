

#include <Hexagon/Fancy/Stage.hpp>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>


namespace Hexagon
{
namespace Fancy
{


ALLEGRO_EVENT Stage::a_default_empty_event = {};


Stage::Stage()
   : StageInterface(StageInterface::FANCY)
{
}


Stage::~Stage()
{
}


ALLEGRO_EVENT &Stage::get_a_default_empty_event_ref()
{
   return a_default_empty_event;
}


std::string Stage::run()
{
   return "Hello World!";
}

void Stage::render()
{
   float width = 1920 / 5 * 4;
   float height = 1080 / 8 * 6;
   float o = 1.2;
   ALLEGRO_COLOR fill_color = ALLEGRO_COLOR{1.0f*o, 1.0f*o, 0.0f*o, 1.0f*o};
   placement3d place = get_place();

   place.start_transform();
   al_draw_filled_rectangle(0, 0, width, height, fill_color);
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
} // namespace Fancy
} // namespace Hexagon


