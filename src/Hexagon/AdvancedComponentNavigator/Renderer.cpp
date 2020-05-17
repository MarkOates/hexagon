

#include <Hexagon/AdvancedComponentNavigator/Renderer.hpp>
#include <allegro_flare/placement3d.h>
#include <allegro_flare/color.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <Hexagon/FileSystemNode.hpp>
#include <Hexagon/Shapes/Hexagon/Renderer.hpp>
#include <Hexagon/Shapes/Hexagon/Stroke.hpp>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace AdvancedComponentNavigator
{


Renderer::Renderer(Hexagon::AdvancedComponentNavigator::Stage* stage, bool is_focused, ALLEGRO_DISPLAY* display, ALLEGRO_FONT* font, int cell_width, int cell_height)
   : stage(stage)
   , is_focused(is_focused)
   , display(display)
   , font(font)
   , cell_width(cell_width)
   , cell_height(cell_height)
{
}


Renderer::~Renderer()
{
}


void Renderer::render()
{
if (!(stage))
   {
      std::stringstream error_message;
      error_message << "Renderer" << "::" << "render" << ": error: " << "guard \"stage\" not met";
      throw std::runtime_error(error_message.str());
   }
if (!(font))
   {
      std::stringstream error_message;
      error_message << "Renderer" << "::" << "render" << ": error: " << "guard \"font\" not met";
      throw std::runtime_error(error_message.str());
   }
if (!font) throw std::runtime_error("font missing");
Hexagon::AdvancedComponentNavigator::Stage &stage = *this->stage;

placement3d &place = stage.get_place();
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
if (stage.get_cursor_position_static())
{
  cursor_y = - line_height * stage.get_cursor_position();
}
float current_node_root_y_pos = cursor_y - line_height * 1.5;
ALLEGRO_COLOR font_color = al_color_name("white");
ALLEGRO_COLOR node_root_font_color = al_color_name("gray");
ALLEGRO_COLOR node_folder_color = al_color_name("lightgray");

float selector_y = line_height * stage.get_cursor_position() + cursor_y;
std::string current_selection_label_or_empty_string = stage.get_current_selection_label_or_empty_string();
float selector_rectangle_width = al_get_text_width(font, current_selection_label_or_empty_string.c_str());
float selector_rectangle_roundness = 0; //4;
if (stage.current_selection_is_valid())
{
  al_draw_filled_rounded_rectangle(
    0,
    selector_y,
    selector_rectangle_width,
    selector_y+line_height,
    selector_rectangle_roundness,
    selector_rectangle_roundness,
    stage.get_selector_color()
  );
}
else
{
   al_draw_rounded_rectangle(0,
                             selector_y,
                             selector_rectangle_width,
                             selector_y+line_height,
                             4,
                             4,
                             stage.get_selector_color(),
                             3.0);
}

std::string node_root_val = stage.get_project_root();
al_draw_text(font, node_root_font_color,
  pos_x, -line_height * 1.5, 0, stage.get_project_root().c_str());

bool list_clipping_occurred_above = false;
bool list_clipping_occurred_below = false;

for (auto &node : stage.get_nodes())
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
} // namespace AdvancedComponentNavigator
} // namespace Hexagon


