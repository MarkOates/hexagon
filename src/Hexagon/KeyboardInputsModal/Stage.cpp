#include <Hexagon/KeyboardInputsModal/Stage.hpp>

#include <allegro5/allegro_primitives.h>
#include <allegro_flare/color.h>


namespace KeyboardInputsModal
{


Stage::Stage(AllegroFlare::KeyboardCommandMapper *keyboard_command_mapper)
   : StageInterface(KEYBOARD_INPUTS_MODAL)
   , keyboard_command_mapper(keyboard_command_mapper)
{}


Stage::~Stage()
{
}


void Stage::render()
{
   //if (!display) throw std::runtime_error("[Stage] error: display cannot be a nullptr.");
   //if (!font) throw std::runtime_error("[Stage] error: font cannot be a nullptr.");

   placement3d &place = get_place();

   float border_thickness = 5.0;
   place.size = vec3d(500.0, 400.0, 0.0);
   place.align = vec3d(0.5, 0.5, 0.0);
   place.rotation = vec3d(place.rotation.x, place.rotation.y, place.rotation.z);

   place.start_transform();
   al_draw_filled_rectangle(0, 0, place.size.x, place.size.y, color::black);
   al_draw_rounded_rectangle(0 - border_thickness, 0 - border_thickness, place.size.x + border_thickness, place.size.y + border_thickness, 8.0, 8.0, color::dimgray, border_thickness);
   place.restore_transform();
}


void Stage::process_local_event(std::string event_name, ActionData action_data)
{
}


void Stage::process_event(ALLEGRO_EVENT &event)
{
}


} // namespace KeyboardInputsModal



