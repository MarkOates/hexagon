

#include <Hexagon/AdvancedComponentNavigator/Stage.hpp>
#include <AllegroFlare/KeyboardCommandMapper.hpp>
#include <Hexagon/AdvancedComponentNavigator/ComponentSearcher.hpp>
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
   , X_cursor_position(0)
   , X_cursor_position_static(true)
   , X_nodes({})
   , X_search_text("")
   , X_mode("navigating_list")
{
}


Stage::~Stage()
{
}


void Stage::set_project_root(std::string project_root)
{
   this->project_root = project_root;
}


void Stage::set_X_cursor_position_static(bool X_cursor_position_static)
{
   this->X_cursor_position_static = X_cursor_position_static;
}


void Stage::set_X_nodes(std::vector<Blast::Project::Component> X_nodes)
{
   this->X_nodes = X_nodes;
}


void Stage::set_X_search_text(std::string X_search_text)
{
   this->X_search_text = X_search_text;
}


void Stage::set_X_mode(std::string X_mode)
{
   this->X_mode = X_mode;
}


std::string Stage::get_project_root()
{
   return project_root;
}


int Stage::get_X_cursor_position()
{
   return X_cursor_position;
}


bool Stage::get_X_cursor_position_static()
{
   return X_cursor_position_static;
}


std::vector<Blast::Project::Component> Stage::get_X_nodes()
{
   return X_nodes;
}


std::string Stage::get_X_search_text()
{
   return X_search_text;
}


std::string Stage::get_X_mode()
{
   return X_mode;
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

void Stage::move_cursor_up()
{
component.move_cursor_up();
//cursor_position -= 1;

}

void Stage::move_cursor_down()
{
component.move_cursor_down();
//cursor_position += 1;

}

void Stage::move_cursor_to_top()
{
component.move_cursor_to_top();
//cursor_position = 0;

}

bool Stage::current_selection_is_valid()
{
return component.current_selection_is_valid();
//if (cursor_position < 0 || cursor_position >= nodes.size()) return false;
//return true;

}

void Stage::set_mode_to_navigating_list()
{
return component.set_mode_to_navigating_list();
//this->mode = "navigating_list";

}

void Stage::set_mode_to_typing_in_search_bar()
{
return component.set_mode_to_typing_in_search_bar();
//this->mode = "typing_in_search_bar";

}

std::string Stage::get_current_selection_label_or_empty_string()
{
return component.get_current_selection_label_or_empty_string();
//if (!current_selection_is_valid()) return "";
//return nodes[component.get_cursor_position()].get_name();

}

void Stage::refresh_list()
{
return component.refresh_list();
//Hexagon::AdvancedComponentNavigator::ComponentSearcher searcher(get_project_root(), search_text);
//nodes = searcher.components_sorted_by_most_recent();

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


