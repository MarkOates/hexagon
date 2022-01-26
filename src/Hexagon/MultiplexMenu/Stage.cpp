

#include <Hexagon/MultiplexMenu/Stage.hpp>
#include <Hexagon/MultiplexMenu/Renderer.hpp>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace MultiplexMenu
{


ALLEGRO_EVENT Stage::a_default_empty_event = {};


Stage::Stage(StageInterface* stage, std::vector<std::tuple<std::string, std::string, std::string, std::string>> items)
   : StageInterface(StageInterface::MULTIPLEX_MENU)
   , stage(stage)
   , items(items)
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

void Stage::send_message_to_stage(std::string message)
{
   if (!(stage))
      {
         std::stringstream error_message;
         error_message << "Stage" << "::" << "send_message_to_stage" << ": error: " << "guard \"stage\" not met";
         throw std::runtime_error(error_message.str());
      }
   stage->process_local_event(message);
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


