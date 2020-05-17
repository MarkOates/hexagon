

#include <Hexagon/AdvancedComponentNavigator/Renderer.hpp>
#include <stdexcept>
#include <sstream>
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


Renderer::Renderer(Hexagon::AdvancedComponentNavigator::Stage* stage, bool is_focused, ALLEGRO_FONT* font, int cell_width, int cell_height)
   : stage(stage)
   , is_focused(is_focused)
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
placement3d &place = stage->get_place();
place.start_transform();
render_raw();
place.restore_transform();
return;

}

void Renderer::render_raw()
{
if (!(stage))
   {
      std::stringstream error_message;
      error_message << "Renderer" << "::" << "render_raw" << ": error: " << "guard \"stage\" not met";
      throw std::runtime_error(error_message.str());
   }
if (!(font))
   {
      std::stringstream error_message;
      error_message << "Renderer" << "::" << "render_raw" << ": error: " << "guard \"font\" not met";
      throw std::runtime_error(error_message.str());
   }
Hexagon::AdvancedComponentNavigator::Stage &stage = *this->stage;
Hexagon::AdvancedComponentNavigator::AdvancedComponentNavigator &component = stage.get_component_ref();
placement3d &place = stage.get_place();

float line_stroke_thickness = 2.5;

// draw backfill and outline

float roundness = 0.0; //6.0;
float padding_x = cell_width;
float padding_y = cell_width;
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


// draw cursor box for focused line

int line = 0;
int line_height = cell_height * 1.1;
int pos_x = 0;
int pos_y = 0;
int cursor_y = 0;
if (stage.get_component_ref().get_cursor_position_static())
{
  cursor_y = - line_height * stage.get_component_ref().get_cursor_position();
}
float current_node_root_y_pos = cursor_y - line_height * 1.5;
ALLEGRO_COLOR font_color = al_color_name("white");
ALLEGRO_COLOR node_folder_color = al_color_name("lightgray");
ALLEGRO_COLOR selector_color = al_color_name("slategray");

float selector_y = line_height * stage.get_component_ref().get_cursor_position() + cursor_y;
std::string current_selection_label_or_empty_string = component.get_current_selection_label_or_empty_string();
float selector_rectangle_width = al_get_text_width(font, current_selection_label_or_empty_string.c_str());
float selector_rectangle_roundness = 0; //4;
if (component.current_selection_is_valid())
{
  al_draw_filled_rounded_rectangle(
    0,
    selector_y,
    selector_rectangle_width,
    selector_y+line_height,
    selector_rectangle_roundness,
    selector_rectangle_roundness,
    selector_color
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
                             selector_color,
                             3.0);
}


// draw the project root (window title)

ALLEGRO_COLOR node_root_font_color = frame_color;
std::string node_root_val = stage.get_project_root();
float title_text_width = al_get_text_width(font, node_root_val.c_str());
float title_text_height = al_get_font_line_height(font);
float title_y = (title_text_height * -1.3) * 2;
al_draw_filled_rectangle(0, title_y, title_text_width, title_y+title_text_height, not_quite_black);
al_draw_text(font, node_root_font_color, 0, title_y, 0, stage.get_project_root().c_str());


// draw the search_text

ALLEGRO_COLOR search_text_font_color = al_color_name("yellow");
std::string search_text_val = stage.get_component_ref().get_search_text();
float search_text_width = al_get_text_width(font, search_text_val.c_str());
float search_text_height = al_get_font_line_height(font);
float search_text_y = search_text_height * -1.3;
al_draw_filled_rectangle(0, search_text_y, search_text_width, search_text_y+search_text_height, not_quite_black);
al_draw_text(font, search_text_font_color, 0, search_text_y, 0, search_text_val.c_str());


// draw list elements

bool list_clipping_occurred_above = false;
bool list_clipping_occurred_below = false;

for (auto &node : stage.get_component_ref().get_nodes())
{
  std::string line_content = node.get_name();
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
     al_draw_text(font, col, 0, pos_y + cursor_y, 0, line_content.c_str());
  }
  cursor_y += line_height;
}


// draw list clipping hint arrows

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

return;

}
} // namespace AdvancedComponentNavigator
} // namespace Hexagon


