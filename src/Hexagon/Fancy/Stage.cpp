

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
   // initialize
   float surface_width = 1920;
   float surface_height = 1080;
   float width = surface_width / 5 * 4;
   float height = surface_height / 8 * 6;
   float o = 0.2f;
   ALLEGRO_COLOR fill_color = ALLEGRO_COLOR{1.0f*o, 1.0f*o, 0.0f*o, 1.0f*o};
   placement3d place = get_place();

   // transform
   place.position.x = surface_width / 2;
   place.position.y = surface_height / 2;
   place.size.x = width;
   place.size.y = height;

   // execute
   place.start_transform();
   al_draw_filled_rectangle(0, 0, width, height, fill_color);
   place.restore_transform();

   // return
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


