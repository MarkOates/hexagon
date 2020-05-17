

#include <Hexagon/AdvancedComponentNavigator/Stage.hpp>
#include <AllegroFlare/KeyboardCommandMapper.hpp>
#include <Hexagon/AdvancedComponentNavigator/Renderer.hpp>
#include <Hexagon/AdvancedComponentNavigator/EventController.hpp>
#include <AllegroFlare/KeyboardCommandMapper.hpp>


namespace Hexagon
{
namespace AdvancedComponentNavigator
{


ALLEGRO_EVENT Stage::a_default_empty_event = {};


Stage::Stage(std::string project_root)
   : StageInterface(StageInterface::COMPONENT_NAVIGATOR)
   , project_root(project_root)
   , component(project_root)
{
}


Stage::~Stage()
{
}


void Stage::set_project_root(std::string project_root)
{
   this->project_root = project_root;
}


std::string Stage::get_project_root()
{
   return project_root;
}


Hexagon::AdvancedComponentNavigator::AdvancedComponentNavigator &Stage::get_component_ref()
{
   return component;
}


ALLEGRO_EVENT &Stage::get_a_default_empty_event_ref()
{
   return a_default_empty_event;
}


KeyboardCommandMapper Stage::build_keyboard_command_mapping()
{
constexpr auto NO_MODIFIER = KeyboardCommandMapper::NO_MODIFIER;
constexpr auto SHIFT = KeyboardCommandMapper::SHIFT;
constexpr auto CTRL = KeyboardCommandMapper::CTRL;
constexpr auto ALT = KeyboardCommandMapper::ALT;
constexpr auto COMMAND = KeyboardCommandMapper::COMMAND;
constexpr auto OPTION = KeyboardCommandMapper::OPTION;

KeyboardCommandMapper mapping;

static const std::string MOVE_CURSOR_TO_TOP = "move_cursor_to_top";
static const std::string MOVE_CURSOR_UP = "move_cursor_up";
static const std::string MOVE_CURSOR_DOWN = "move_cursor_down";

mapping.set_mapping(ALLEGRO_KEY_J, NO_MODIFIER, { MOVE_CURSOR_DOWN });
mapping.set_mapping(ALLEGRO_KEY_K, NO_MODIFIER, { MOVE_CURSOR_UP });

return mapping;

}

std::map<std::string, std::function<void(AdvancedComponentNavigator&)>> Stage::build_local_events_dictionary()
{
std::map<std::string, std::function<void(AdvancedComponentNavigator&)>> local_events = {
   { "refresh_list", &AdvancedComponentNavigator::refresh_list },
   { "move_cursor_to_top", &AdvancedComponentNavigator::move_cursor_to_top },
   { "move_cursor_up", &AdvancedComponentNavigator::move_cursor_up },
   { "move_cursor_down", &AdvancedComponentNavigator::move_cursor_down },
   { "set_mode_to_navigating_list", &AdvancedComponentNavigator::set_mode_to_navigating_list },
   { "set_mode_to_typing_in_search_bar", &AdvancedComponentNavigator::set_mode_to_typing_in_search_bar },
};
return local_events;

}

void Stage::render(bool is_focused, ALLEGRO_DISPLAY* display, ALLEGRO_FONT* font, int cell_width, int cell_height)
{
Hexagon::AdvancedComponentNavigator::Renderer renderer(this, is_focused, font, cell_width, cell_height);
renderer.render();
return;

}

void Stage::process_local_event(std::string event_name, ActionData action_data)
{
using Hexagon::AdvancedComponentNavigator::AdvancedComponentNavigator;
std::map<std::string, std::function<void(AdvancedComponentNavigator&)>> local_events =
   build_local_events_dictionary();
Hexagon::AdvancedComponentNavigator::EventController event_controller(&component, local_events);
event_controller.process_local_event(event_name, action_data);
return;

}

void Stage::process_char_event(int keycode, int unichar, bool is_repeat)
{
if (keycode == ALLEGRO_KEY_BACKSPACE) {}
else if (keycode == ALLEGRO_KEY_TAB) {}
else if (keycode == ALLEGRO_KEY_ENTER) {}
else if (keycode == ALLEGRO_KEY_ESCAPE) {}
else if (keycode == ALLEGRO_KEY_DELETE) {}
else
{
   //search_text += unichar; // <-- for example
}
return;

}

void Stage::process_event(ALLEGRO_EVENT& event)
{
KeyboardCommandMapper keyboard_command_mapper = build_keyboard_command_mapping();

bool event_caught = false;

switch(event.type)
{
case ALLEGRO_EVENT_KEY_UP:
   break;
case ALLEGRO_EVENT_KEY_DOWN:
   break;
case ALLEGRO_EVENT_KEY_CHAR:
   bool shift = event.keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT;
   bool alt = event.keyboard.modifiers & ALLEGRO_KEYMOD_ALT;
   bool ctrl = event.keyboard.modifiers & ALLEGRO_KEYMOD_CTRL;
   bool command = event.keyboard.modifiers & ALLEGRO_KEYMOD_COMMAND;
   bool ctrl_or_command = ctrl || command;

   std::vector<std::string> mapped_events =
      keyboard_command_mapper.get_mapping(event.keyboard.keycode, shift, ctrl_or_command, alt);
   if (!mapped_events.empty()) event_caught = true;
   for (auto &mapped_event : mapped_events) process_local_event(mapped_event);
   if (!event_caught) process_char_event(event.keyboard.keycode, event.keyboard.unichar, event.keyboard.repeat);
   break;
}
return;

}

bool Stage::save_file()
{
return true;

}
} // namespace AdvancedComponentNavigator
} // namespace Hexagon


