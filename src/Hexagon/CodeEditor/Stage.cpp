

#include <Hexagon/CodeEditor/Stage.hpp>



namespace Hexagon
{
namespace CodeEditor
{


ALLEGRO_EVENT Stage::a_default_empty_event = {};


Stage::Stage(std::string expected_filename)
   : StageInterface(StageInterface::CODE_EDITOR)
   , expected_filename(expected_filename)
   , text("MISSING FILE")
{
}


Stage::~Stage()
{
}


std::string Stage::get_expected_filename()
{
   return expected_filename;
}


ALLEGRO_EVENT &Stage::get_a_default_empty_event_ref()
{
   return a_default_empty_event;
}


void Stage::render(bool is_focused, ALLEGRO_DISPLAY* display, ALLEGRO_FONT* font, int cell_width, int cell_height)
{
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
} // namespace CodeEditor
} // namespace Hexagon


