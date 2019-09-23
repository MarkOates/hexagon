

#include <Hexagon/FileNavigator/Stage.hpp>
#include <Hexagon/OldFileSystemNode.hpp>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <iostream>
#include <iostream>


namespace Hexagon
{
namespace FileNavigator
{


ALLEGRO_EVENT Stage::a_default_empty_event = {};


Stage::Stage()
   : StageInterface({})
   , circle_color(al_color_name("green"))
   , nodes({})
   , cursor_position(0)
{
}


Stage::~Stage()
{
}


void Stage::set_circle_color(ALLEGRO_COLOR circle_color)
{
   this->circle_color = circle_color;
}


void Stage::set_nodes(std::vector<std::string> nodes)
{
   this->nodes = nodes;
}


ALLEGRO_COLOR Stage::get_circle_color()
{
   return circle_color;
}


std::vector<std::string> Stage::get_nodes()
{
   return nodes;
}


int Stage::get_cursor_position()
{
   return cursor_position;
}


ALLEGRO_EVENT &Stage::get_a_default_empty_event_ref()
{
   return a_default_empty_event;
}


void Stage::move_cursor_down()
{
cursor_position += 1;

}

std::string Stage::run()
{
return "Hello World!";
}

void Stage::refresh_nodes()
{
nodes.clear();
std::string node_root = "/Users/markoates/Repos";
//OldFileSystemNode current_node(node_root);
//current_
nodes.push_back("/Users/markoates/Repos");
OldFileSystemNode current_node(node_root);
current_node.create_children();
for (auto &node : current_node.get_children_ref())
{
  nodes.push_back(node->infer_basename());
}

return;

}

void Stage::render(ALLEGRO_DISPLAY* display, ALLEGRO_FONT* font, int cell_width, int cell_height)
{
if (!font) throw std::runtime_error("font missing");

int line = 0;
int line_height = 36;
int pos_x = 0;
int pos_y = 0;
int cursor_y = 0;
ALLEGRO_COLOR font_color = al_color_name("white");
for (auto &node : nodes)
{
  std::string line_content = node;
  al_draw_text(font, font_color, pos_x, pos_y + cursor_y, 0, line_content.c_str());
  cursor_y += line_height;
}

al_draw_filled_circle(0, 0, 20, get_circle_color());
return;

}

void Stage::change_to_yellow()
{
set_circle_color(al_color_name("yellow"));

}

void Stage::process_local_event(std::string event_name, ActionData action_data)
{
std::cout << "LocalEvent::" << event_name << std::endl;

try
{
   bool executed = false;

   if (event_name == "change_to_yellow")
   {
     executed = true;
     change_to_yellow();
   }
   else if (event_name == "refresh_nodes")
   {
     executed = true;
     refresh_nodes();
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

void Stage::process_event(ALLEGRO_EVENT& action_data)
{
return;

}
} // namespace FileNavigator
} // namespace Hexagon


