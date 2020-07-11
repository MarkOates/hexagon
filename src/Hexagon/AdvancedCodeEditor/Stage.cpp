

#include <Hexagon/AdvancedCodeEditor/Stage.hpp>
#include <Hexagon/AdvancedCodeEditor/Renderer.hpp>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace AdvancedCodeEditor
{


ALLEGRO_EVENT Stage::a_default_empty_event = {};


Stage::Stage()
   : StageInterface(StageInterface::ADVANCED_CODE_EDITOR)
   , place(0.0f, 0.0f, 0.0f)
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
if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "Stage" << "::" << "render" << ": error: " << "guard \"al_is_system_installed()\" not met";
      throw std::runtime_error(error_message.str());
   }
Hexagon::AdvancedCodeEditor::Renderer renderer(this);

place.start_transform();
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
} // namespace AdvancedCodeEditor
} // namespace Hexagon


