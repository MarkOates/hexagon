

#include <Hexagon/AdvancedComponentNavigator/Stage.hpp>
#include <Hexagon/AdvancedComponentNavigator/ComponentSearcher.hpp>
#include <allegro_flare/color.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <Hexagon/FileSystemNode.hpp>
#include <Hexagon/Shapes/Hexagon/Renderer.hpp>
#include <Hexagon/Shapes/Hexagon/Stroke.hpp>
#include <iostream>
#include <iostream>
#include <iostream>
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
   , search_string("")
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


void Stage::set_search_string(std::string search_string)
{
   this->search_string = search_string;
}


void Stage::set_mode(std::string mode)
{
   this->mode = mode;
}


int Stage::get_cursor_position()
{
   return cursor_position;
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


std::string Stage::get_search_string()
{
   return search_string;
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
Hexagon::AdvancedComponentNavigator::ComponentSearcher searcher(get_project_root(), search_string);
nodes = searcher.components_sorted_by_most_recent();

}

void Stage::render(bool is_focused, ALLEGRO_DISPLAY* display, ALLEGRO_FONT* font, int cell_width, int cell_height)
{
if (!font) throw std::runtime_error("font missing");

placement3d &place = get_place();
place.start_transform();

float line_stroke_thickness = 2.5;

float roundness = 0.0; //6.0;
float padding_x = cell_width;
float padding_y = cell_width;
//std::cout << " size: " << place.size.x << ", " << place.size.y << std::endl;
float not_quite_black_value = 0.0;
ALLEGRO_COLOR frame_color = al_color_html("39c3c5");
ALLEGRO_COLOR not_quite_black;
not_quite_black.r = not_quite_black_value;
not_quite_black.g = not_quite_black_value;
not_quite_black.b = not_quite_black_value;
not_quite_black.a = 0.8;
al_draw_filled_rounded_rectangle(
  0 - padding_x*2,
  0 - padding_y*2,
  place.size.x + padding_x*2,
  place.size.y + padding_y*2,
  roundness,
  roundness,
  not_quite_black
);
al_draw_rounded_rectangle(- padding_x, - padding_y,
   place.size.x+padding_x, place.size.y+padding_y,
   roundness, roundness, frame_color, line_stroke_thickness);

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
std::string current_selection_label_or_empty_string = get_current_selection_label_or_empty_string();
float selector_rectangle_width = al_get_text_width(font, current_selection_label_or_empty_string.c_str());
float selector_rectangle_roundness = 0; //4;
if (current_selection_is_valid())
{
  al_draw_filled_rounded_rectangle(
    0,
    selector_y,
    selector_rectangle_width,
    selector_y+line_height,
    selector_rectangle_roundness,
    selector_rectangle_roundness,
    get_selector_color()
  );
}
else
{
   al_draw_rounded_rectangle(0, selector_y, selector_rectangle_width, selector_y+line_height, 4, 4, get_selector_color(), 3.0);
}

std::string node_root_val = get_project_root();
al_draw_text(font, node_root_font_color,
  pos_x, -line_height * 1.5, 0, get_project_root().c_str());

bool list_clipping_occurred_above = false;
bool list_clipping_occurred_below = false;

for (auto &node : nodes)
{
  std::string line_content = node.get_name();
  //FileSystemNode current_line_node(line_content);
  //bool is_directory = current_line_node.infer_is_directory();
  //ALLEGRO_COLOR col = is_directory ? node_folder_color : font_color;
  ALLEGRO_COLOR col = al_color_name("skyblue");

  if (node.has_quintessence())
  {
    //line_content += " *";
  }
  else if (node.has_only_source_and_header())
  {
     col = color::mix(col, al_color_name("green"), 0.1);
  }
  else if (!node.exists())
  {
     col = al_color_name("red");
  }
  else
  {
     col = al_color_name("gray");
  }

  //if (!node.has_test()) line_content += " (missing test)";

  float final_y = pos_y + cursor_y;
  // clip the region of text displayed in the list
  if (final_y < 0)
  {
     list_clipping_occurred_above = true;
  }
  else if ((final_y + line_height) > place.size.y)
  {
     list_clipping_occurred_below = true;
  }
  else
  {
     al_draw_text(font, col, pos_x, pos_y + cursor_y, 0, line_content.c_str());
  }
  cursor_y += line_height;
}

float list_extension_indicator_radius = 30;
if (list_clipping_occurred_above)
{
   Hexagon::Shapes::Hexagon::Renderer(
       place.size.x - list_extension_indicator_radius,
       list_extension_indicator_radius,
       list_extension_indicator_radius,
       {
         { 9, 3, frame_color, line_stroke_thickness },
       }
     ).render();
}
if (list_clipping_occurred_below)
{
   Hexagon::Shapes::Hexagon::Renderer(
       place.size.x - list_extension_indicator_radius,
       place.size.y - list_extension_indicator_radius,
       list_extension_indicator_radius,
       {
         { 3, 9, frame_color, line_stroke_thickness },
       }
     ).render();
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
   else if (event_name == "set_mode_to_navigating_list")
   {
     executed = true;
     set_mode_to_navigating_list();
   }
   else if (event_name == "set_mode_to_typing_in_search_bar")
   {
     executed = true;
     set_mode_to_typing_in_search_bar();
   }
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


