

#include <Hexagon/AdvancedComponentNavigator/Stage.hpp>
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
   , cursor_position(0)
   , cursor_position_static(true)
   , selector_color(al_color_name("slategray"))
   , project_root(project_root)
   , nodes({})
   , search_text("")
   , mode("navigating_list")
{
}


Stage::~Stage()
{
}


void Stage::set_cursor_position_static(bool cursor_position_static)
{
   this->cursor_position_static = cursor_position_static;
}


void Stage::set_selector_color(ALLEGRO_COLOR selector_color)
{
   this->selector_color = selector_color;
}


void Stage::set_project_root(std::string project_root)
{
   this->project_root = project_root;
}


void Stage::set_nodes(std::vector<Blast::Project::Component> nodes)
{
   this->nodes = nodes;
}


void Stage::set_search_text(std::string search_text)
{
   this->search_text = search_text;
}


void Stage::set_mode(std::string mode)
{
   this->mode = mode;
}


int Stage::get_cursor_position()
{
   return cursor_position;
}


bool Stage::get_cursor_position_static()
{
   return cursor_position_static;
}


ALLEGRO_COLOR Stage::get_selector_color()
{
   return selector_color;
}


std::string Stage::get_project_root()
{
   return project_root;
}


std::vector<Blast::Project::Component> Stage::get_nodes()
{
   return nodes;
}


std::string Stage::get_search_text()
{
   return search_text;
}


std::string Stage::get_mode()
{
   return mode;
}


ALLEGRO_EVENT &Stage::get_a_default_empty_event_ref()
{
   return a_default_empty_event;
}


void Stage::move_cursor_up()
{
cursor_position -= 1;

}

void Stage::move_cursor_down()
{
cursor_position += 1;

}

void Stage::move_cursor_to_top()
{
cursor_position = 0;

}

bool Stage::current_selection_is_valid()
{
if (cursor_position < 0 || cursor_position >= nodes.size()) return false;
return true;

}

void Stage::set_mode_to_navigating_list()
{
this->mode = "navigating_list";

}

void Stage::set_mode_to_typing_in_search_bar()
{
this->mode = "typing_in_search_bar";

}

std::string Stage::get_current_selection_label_or_empty_string()
{
if (!current_selection_is_valid()) return "";
return nodes[get_cursor_position()].get_name();

}

void Stage::refresh_list()
{
Hexagon::AdvancedComponentNavigator::ComponentSearcher searcher(get_project_root(), search_text);
nodes = searcher.components_sorted_by_most_recent();

}

void Stage::render(bool is_focused, ALLEGRO_DISPLAY* display, ALLEGRO_FONT* font, int cell_width, int cell_height)
{
Hexagon::AdvancedComponentNavigator::Renderer renderer(this, is_focused, font, cell_width, cell_height);
renderer.render();
return;

}

void Stage::process_local_event(std::string event_name, ActionData action_data)
{
Hexagon::AdvancedComponentNavigator::EventController event_controller(this);
event_controller.process_local_event(event_name, action_data);
return;

}

bool Stage::save_file()
{
return true;

}

void Stage::process_event(ALLEGRO_EVENT& event)
{
KeyboardCommandMapper keyboard_command_mapper;
                                           // al_keycodee, shift, ctrl, alt, command, { command_identifier }
static const std::string MOVE_CURSOR_TO_TOP = "move_cursor_to_top";
static const std::string MOVE_CURSOR_UP = "move_cursor_up";
static const std::string MOVE_CURSOR_DOWN = "move_cursor_down";

                                   // al_keycodee,         shift, ctrl, alt, command, { command_identifier }
keyboard_command_mapper.set_mapping(ALLEGRO_KEY_J,         false, false, false, false, { MOVE_CURSOR_DOWN });
keyboard_command_mapper.set_mapping(ALLEGRO_KEY_K,         false, false, false, false, { MOVE_CURSOR_UP });

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
   std::vector<std::string> mapped_events = keyboard_command_mapper.get_mapping(event.keyboard.keycode, shift, ctrl_or_command, alt);
   if (!mapped_events.empty()) event_caught = true;
   for (auto &mapped_event : mapped_events) process_local_event(mapped_event);
   break;
}
return;

}
} // namespace AdvancedComponentNavigator
} // namespace Hexagon


