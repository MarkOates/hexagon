

#include <Hexagon/FileNavigator/Stage.hpp>
#include <Hexagon/OldFileSystemNode.hpp>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <iostream>
#include <iostream>
#include <Blast/KeyboardCommandMapper.hpp>


namespace Hexagon
{
namespace FileNavigator
{


ALLEGRO_EVENT Stage::a_default_empty_event = {};


Stage::Stage(std::string node_root)
   : StageInterface(StageInterface::FILE_NAVIGATOR)
   , cursor_position_static(true)
   , selector_color(al_color_name("green"))
   , nodes({})
   , cursor_position(0)
   , node_root(node_root)
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


void Stage::set_nodes(std::vector<std::string> nodes)
{
   this->nodes = nodes;
}


void Stage::set_node_root(std::string node_root)
{
   this->node_root = node_root;
}


ALLEGRO_COLOR Stage::get_selector_color()
{
   return selector_color;
}


std::vector<std::string> Stage::get_nodes()
{
   return nodes;
}


int Stage::get_cursor_position()
{
   return cursor_position;
}


std::string Stage::get_node_root()
{
   return node_root;
}


ALLEGRO_EVENT &Stage::get_a_default_empty_event_ref()
{
   return a_default_empty_event;
}


void Stage::move_cursor_down()
{
cursor_position += 1;

}

bool Stage::current_selection_is_valid()
{
if (cursor_position < 0 || cursor_position >= nodes.size()) return false;
return true;

}

std::string Stage::get_current_selection_or_spaced_empty_string()
{
if (!current_selection_is_valid()) return " ";
return nodes[get_cursor_position()];

}

std::string Stage::get_current_selection()
{
if (!current_selection_is_valid()) throw std::runtime_error("cannot current_selection_is_folder because is invalid");
return nodes[get_cursor_position()];

}

bool Stage::current_selection_is_folder()
{
std::string current_selection = get_current_selection();
OldFileSystemNode current_selection_node(current_selection);
return current_selection_node.infer_is_directory();

}

void Stage::move_cursor_up()
{
cursor_position -= 1;

}

void Stage::move_cursor_to_top()
{
cursor_position = 0;

}

void Stage::set_node_root_to_system_root_directory()
{
set_node_root("/");
}

void Stage::set_node_root_to_repos_directory()
{
set_node_root("/Users/markoates/Repos");
}

void Stage::set_node_root_to_user_directory()
{
set_node_root("/Users/markoates");
}

void Stage::set_node_root_to_current_selection_if_folder()
{
if (current_selection_is_valid() && current_selection_is_folder())
{
  set_node_root(get_current_selection());
}

}

void Stage::refresh_list()
{
nodes.clear();
//nodes.push_back(get_node_root());
OldFileSystemNode current_node(get_node_root());
current_node.create_children();
for (auto &node : current_node.get_children_ref())
{
  nodes.push_back(node->infer_full_name());
}

return;

}

void Stage::render(ALLEGRO_DISPLAY* display, ALLEGRO_FONT* font, int cell_width, int cell_height)
{
if (!font) throw std::runtime_error("font missing");

placement3d &place = get_place();
place.start_transform();

float roundness = 6.0;
float padding_x = cell_width;
float padding_y = cell_width;
//std::cout << " size: " << place.size.x << ", " << place.size.y << std::endl;
al_draw_filled_rounded_rectangle(0 - padding_x*2, 0 - padding_y*2, place.size.x + padding_x*2, place.size.y + padding_y*2, roundness, roundness, al_color_name("black"));
al_draw_rounded_rectangle(- padding_x, - padding_y, place.size.x+padding_x, place.size.y+padding_y, roundness, roundness, al_color_name("green"), 3.0);

//new_render(display, font, cell_width, cell_height);
//return;

int line = 0;
int line_height = cell_height * 1.1;
int pos_x = 0;
int pos_y = 0;
int cursor_y = 0;
if (cursor_position_static)
{
  cursor_y = - line_height * cursor_position;
}
float current_node_root_y_pos = cursor_y - line_height * 1.5;
ALLEGRO_COLOR font_color = al_color_name("white");
ALLEGRO_COLOR node_root_font_color = al_color_name("gray");
ALLEGRO_COLOR node_folder_color = al_color_name("lightgray");

float selector_y = line_height * cursor_position + cursor_y;
std::string current_selection_text_or_empty_string = get_current_selection_or_spaced_empty_string();
float selector_rectangle_width = al_get_text_width(font, current_selection_text_or_empty_string.c_str());
if (current_selection_is_valid())
{
  al_draw_filled_rounded_rectangle(0, selector_y, selector_rectangle_width, selector_y+line_height, 4, 4, get_selector_color());
}
else
{
  al_draw_rounded_rectangle(0, selector_y, selector_rectangle_width, selector_y+line_height, 4, 4, get_selector_color(), 3.0);
}

std::string node_root_val = get_node_root();
al_draw_text(font, node_root_font_color, pos_x, current_node_root_y_pos, 0, get_node_root().c_str());

for (auto &node : nodes)
{
  std::string line_content = node;
  OldFileSystemNode current_line_node(line_content);
  bool is_directory = current_line_node.infer_is_directory();
  ALLEGRO_COLOR col = is_directory ? node_folder_color : font_color;
  col = is_directory ? al_color_name("lime") : al_color_name("palegreen");
  
  al_draw_text(font, col, pos_x, pos_y + cursor_y, 0, line_content.c_str());
  cursor_y += line_height;
}

place.restore_transform();

return;

}

void Stage::process_local_event(std::string event_name, ActionData action_data)
{
std::cout << "LocalEvent::" << event_name << std::endl;

try
{
   bool executed = false;

   if (event_name == "refresh_list")
   {
     executed = true;
     refresh_list();
   }
   else if (event_name == "set_node_root_to_system_root_directory")
   {
     executed = true;
     set_node_root_to_system_root_directory();
   }
   else if (event_name == "toggle_cursor_position_to_remain_static")
   {
     executed = true;
     set_node_root_to_repos_directory();
   }
   else if (event_name == "set_node_root_to_repos_directory")
   {
     executed = true;
     set_node_root_to_repos_directory();
   }
   else if (event_name == "set_node_root_to_user_directory")
   {
     executed = true;
     set_node_root_to_user_directory();
   }
   else if (event_name == "move_cursor_to_top")
   {
     executed = true;
     move_cursor_to_top();
   }
   else if (event_name == "move_cursor_up")
   {
     executed = true;
     move_cursor_up();
   }
   else if (event_name == "move_cursor_down")
   {
     executed = true;
     move_cursor_down();
   }
   else if (event_name == "set_node_root_to_current_selection_if_folder")
   {
     executed = true;
     set_node_root_to_current_selection_if_folder();
   }
   //else if (event_name == ROTATE_STAGE_LEFT) { executed = true; rotate_stage_left(); }

   if (!executed) std::cerr << "???? cannot execute \"" << event_name << "\".  It does not exist." << std::endl;
}
catch (const std::exception &exception)
{
   std::cerr << ">BOOM< cannot execute \"" << event_name << "\".  The following exception occurred: " << exception.what() << std::endl;
}

}

bool Stage::save_file()
{
return true;

}

void Stage::process_event(ALLEGRO_EVENT& event)
{
KeyboardCommandMapper keyboard_command_mapper;
                                           // al_keycodee, shift, ctrl, alt, command, { command_identifier }
static const std::string SET_NODE_ROOT_TO_SYSTEM_ROOT_DIRECTORY = "set_node_root_to_system_root_directory";
static const std::string SET_NODE_ROOT_TO_REPOS_DIRECTORY = "set_node_root_to_repos_directory";
static const std::string SET_NODE_ROOT_TO_USER_DIRECTORY = "set_node_root_to_user_directory";
static const std::string REFRESH_LIST = "refresh_list";
static const std::string MOVE_CURSOR_TO_TOP = "move_cursor_to_top";
static const std::string MOVE_CURSOR_UP = "move_cursor_up";
static const std::string MOVE_CURSOR_DOWN = "move_cursor_down";
static const std::string SET_NODE_ROOT_TO_CURRENT_SELECTION_IF_FOLDER = "set_node_root_to_current_selection_if_folder";

                                   // al_keycodee,         shift, ctrl, alt, command, { command_identifier }
keyboard_command_mapper.set_mapping(ALLEGRO_KEY_FULLSTOP,  false, false, false, false, { SET_NODE_ROOT_TO_REPOS_DIRECTORY, REFRESH_LIST, MOVE_CURSOR_TO_TOP });
keyboard_command_mapper.set_mapping(ALLEGRO_KEY_J,         false, false, false, false, { MOVE_CURSOR_DOWN });
keyboard_command_mapper.set_mapping(ALLEGRO_KEY_K,         false, false, false, false, { MOVE_CURSOR_UP });
keyboard_command_mapper.set_mapping(ALLEGRO_KEY_ENTER,     false, false, false, false, { SET_NODE_ROOT_TO_CURRENT_SELECTION_IF_FOLDER, REFRESH_LIST, MOVE_CURSOR_TO_TOP });

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
} // namespace FileNavigator
} // namespace Hexagon


