

#include <Hexagon/MultiplexMenu/Stage.hpp>
#include <Hexagon/MultiplexMenu/Renderer.hpp>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace MultiplexMenu
{


ALLEGRO_EVENT Stage::a_default_empty_event = {};


Stage::Stage(AllegroFlare::FontBin* font_bin, StageInterface* stage, std::vector<std::tuple<std::string, std::string, std::string, std::string>> items)
   : StageInterface(StageInterface::MULTIPLEX_MENU)
   , font_bin(font_bin)
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

   Hexagon::MultiplexMenu::Renderer renderer(font_bin);
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
   switch(event.type)
   {
   case ALLEGRO_EVENT_KEY_DOWN:
      break;
   case ALLEGRO_EVENT_KEY_UP:
      break;
   case ALLEGRO_EVENT_KEY_CHAR:
      bool shift = event.keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT;
      bool ctrl = event.keyboard.modifiers & ALLEGRO_KEYMOD_CTRL;
      bool command = event.keyboard.modifiers & ALLEGRO_KEYMOD_COMMAND;
      bool alt = event.keyboard.modifiers & ALLEGRO_KEYMOD_ALT;

      // TODO
      // right now, pressing the A key will send "delete_word_under_cursor" to the stage
      if (event.keyboard.keycode == ALLEGRO_KEY_A) send_message_to_stage("delete_word_under_cursor");

      break;
   }
   return;
}
} // namespace MultiplexMenu
} // namespace Hexagon


