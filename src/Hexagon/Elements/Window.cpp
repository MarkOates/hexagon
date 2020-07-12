

#include <Hexagon/Elements/Window.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>
#include <allegro_flare/color.h>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace Elements
{


Window::Window(float width, float height, float box_opacity, float cell_padding, ALLEGRO_COLOR box_fill_color)
   : width(width)
   , height(height)
   , box_opacity(box_opacity)
   , cell_padding(cell_padding)
   , box_fill_color(box_fill_color)
   , header_bar_color({0.0f, 0.0f, 0.0f, 0.0f})
   , bottom_line_color({0.0f, 0.0f, 0.0f, 0.0f})
   , outer_line_color({0.0f, 0.0f, 0.0f, 0.0f})
   , header_baseline_color({0.0f, 0.0f, 0.0f, 0.0f})
   , top_left_little_bar_color({0.0f, 0.0f, 0.0f, 0.0f})
   , corner_squares_color({0.0f, 0.0f, 0.0f, 0.0f})
   , header_bar_height(0.0f)
   , header_baseline_thickness(0.0f)
   , header_bar_opacity(0.0f)
   , header_baseline_opacity(0.0f)
   , top_left_little_bar_width(0.0f)
   , outer_line_thickness(0.0f)
   , outer_line_opacity(0.0f)
   , bottom_line_thickness(0.0f)
   , bottom_line_opacity(0.0f)
   , corner_squares_resize_from_center(false)
   , corner_squares_width(0.0f)
   , corner_squares_height(0.0f)
   , corner_squares_opacity(0.0f)
   , corner_squares_are_circles(false)
   , number_of_rows(1)
   , number_of_columns(1)
   , distance_of_rows(0.0f)
   , distance_of_columns(0.0f)
{
}


Window::~Window()
{
}


void Window::set_width(float width)
{
   this->width = width;
}


void Window::set_height(float height)
{
   this->height = height;
}


void Window::set_box_opacity(float box_opacity)
{
   this->box_opacity = box_opacity;
}


void Window::set_cell_padding(float cell_padding)
{
   this->cell_padding = cell_padding;
}


void Window::set_box_fill_color(ALLEGRO_COLOR box_fill_color)
{
   this->box_fill_color = box_fill_color;
}


void Window::set_header_bar_color(ALLEGRO_COLOR header_bar_color)
{
   this->header_bar_color = header_bar_color;
}


void Window::set_bottom_line_color(ALLEGRO_COLOR bottom_line_color)
{
   this->bottom_line_color = bottom_line_color;
}


void Window::set_outer_line_color(ALLEGRO_COLOR outer_line_color)
{
   this->outer_line_color = outer_line_color;
}


void Window::set_header_baseline_color(ALLEGRO_COLOR header_baseline_color)
{
   this->header_baseline_color = header_baseline_color;
}


void Window::set_top_left_little_bar_color(ALLEGRO_COLOR top_left_little_bar_color)
{
   this->top_left_little_bar_color = top_left_little_bar_color;
}


void Window::set_corner_squares_color(ALLEGRO_COLOR corner_squares_color)
{
   this->corner_squares_color = corner_squares_color;
}


void Window::set_header_bar_height(float header_bar_height)
{
   this->header_bar_height = header_bar_height;
}


void Window::set_header_baseline_thickness(float header_baseline_thickness)
{
   this->header_baseline_thickness = header_baseline_thickness;
}


void Window::set_header_bar_opacity(float header_bar_opacity)
{
   this->header_bar_opacity = header_bar_opacity;
}


void Window::set_header_baseline_opacity(float header_baseline_opacity)
{
   this->header_baseline_opacity = header_baseline_opacity;
}


void Window::set_top_left_little_bar_width(float top_left_little_bar_width)
{
   this->top_left_little_bar_width = top_left_little_bar_width;
}


void Window::set_outer_line_thickness(float outer_line_thickness)
{
   this->outer_line_thickness = outer_line_thickness;
}


void Window::set_outer_line_opacity(float outer_line_opacity)
{
   this->outer_line_opacity = outer_line_opacity;
}


void Window::set_bottom_line_thickness(float bottom_line_thickness)
{
   this->bottom_line_thickness = bottom_line_thickness;
}


void Window::set_bottom_line_opacity(float bottom_line_opacity)
{
   this->bottom_line_opacity = bottom_line_opacity;
}


void Window::set_corner_squares_resize_from_center(bool corner_squares_resize_from_center)
{
   this->corner_squares_resize_from_center = corner_squares_resize_from_center;
}


void Window::set_corner_squares_width(float corner_squares_width)
{
   this->corner_squares_width = corner_squares_width;
}


void Window::set_corner_squares_height(float corner_squares_height)
{
   this->corner_squares_height = corner_squares_height;
}


void Window::set_corner_squares_opacity(float corner_squares_opacity)
{
   this->corner_squares_opacity = corner_squares_opacity;
}


void Window::set_corner_squares_are_circles(bool corner_squares_are_circles)
{
   this->corner_squares_are_circles = corner_squares_are_circles;
}


void Window::set_number_of_rows(int number_of_rows)
{
   this->number_of_rows = number_of_rows;
}


void Window::set_number_of_columns(int number_of_columns)
{
   this->number_of_columns = number_of_columns;
}


void Window::set_distance_of_rows(float distance_of_rows)
{
   this->distance_of_rows = distance_of_rows;
}


void Window::set_distance_of_columns(float distance_of_columns)
{
   this->distance_of_columns = distance_of_columns;
}


void Window::draw()
{
if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "Window" << "::" << "draw" << ": error: " << "guard \"al_is_system_installed()\" not met";
      throw std::runtime_error(error_message.str());
   }
if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "Window" << "::" << "draw" << ": error: " << "guard \"al_is_primitives_addon_initialized()\" not met";
      throw std::runtime_error(error_message.str());
   }
if (!(al_get_target_bitmap()))
   {
      std::stringstream error_message;
      error_message << "Window" << "::" << "draw" << ": error: " << "guard \"al_get_target_bitmap()\" not met";
      throw std::runtime_error(error_message.str());
   }
ALLEGRO_COLOR final_box_fill_color = color::color(box_fill_color, box_opacity);
al_draw_filled_rectangle(
   0+cell_padding,
   0+cell_padding,
   width-cell_padding,
   height-cell_padding,
   final_box_fill_color
);

ALLEGRO_COLOR final_outer_line_color = color::color(outer_line_color, outer_line_opacity);
al_draw_rectangle(
  0,
  0,
  width,
  height,
  final_outer_line_color,
  outer_line_thickness
);

draw_header_bar();
draw_header_baseline();
draw_top_left_little_bar();
draw_bottom_line();
if (corner_squares_are_circles) draw_corner_circles();
else draw_corner_squares();

return;

}

void Window::draw_top_left_little_bar()
{
al_draw_filled_rectangle(0, 0, top_left_little_bar_width, header_bar_height, top_left_little_bar_color);
return;

}

void Window::draw_header_baseline()
{
ALLEGRO_COLOR final_header_baseline_color = color::color(header_baseline_color, header_baseline_opacity);
al_draw_filled_rectangle(
   0,
   header_bar_height,
   width,
   header_bar_height+header_baseline_thickness,
   final_header_baseline_color
);
return;

}

void Window::draw_bottom_line()
{
ALLEGRO_COLOR final_bottom_line_color = color::color(bottom_line_color, bottom_line_opacity);
float bottom_line_y = height + outer_line_thickness * 0.5f;
al_draw_filled_rectangle(
   -outer_line_thickness * 0.5,
   bottom_line_y,
   width + outer_line_thickness * 0.5,
   bottom_line_y+bottom_line_thickness,
   final_bottom_line_color
);
return;

}

void Window::draw_header_bar()
{
ALLEGRO_COLOR final_header_bar_color = color::color(header_bar_color, header_bar_opacity);
al_draw_filled_rectangle(0, 0, width, header_bar_height, final_header_bar_color);
return;

}

void Window::draw_corner_circles()
{
ALLEGRO_COLOR final_corner_squares_color = color::color(corner_squares_color, corner_squares_opacity);
float x_offset = corner_squares_resize_from_center ? corner_squares_width * 0.5f : 0.0f;
float y_offset = corner_squares_resize_from_center ? corner_squares_height * 0.5f : 0.0f;

// top left
al_draw_filled_circle(0, 0, corner_squares_width * 0.5f, final_corner_squares_color);
// top right
al_draw_filled_circle(width, 0, corner_squares_width * 0.5f, final_corner_squares_color);
// bottom left
al_draw_filled_circle(0, height, corner_squares_width * 0.5f, final_corner_squares_color);
// bottom right
al_draw_filled_circle(width, height, corner_squares_width * 0.5f, final_corner_squares_color);
return;

}

void Window::draw_corner_squares()
{
ALLEGRO_COLOR final_corner_squares_color = color::color(corner_squares_color, corner_squares_opacity);
float x_offset = corner_squares_resize_from_center ? corner_squares_width * 0.5f : 0.0f;
float y_offset = corner_squares_resize_from_center ? corner_squares_height * 0.5f : 0.0f;

// top left
al_draw_filled_rectangle(
   0 - x_offset,
   0 - y_offset,
   corner_squares_width - x_offset,
   corner_squares_height - y_offset,
   final_corner_squares_color
);
// top right
al_draw_filled_rectangle(
   width - corner_squares_width + x_offset,
   0 - y_offset,
   width + x_offset,
   corner_squares_height - y_offset,
   final_corner_squares_color
);
// bottom left
al_draw_filled_rectangle(
   0 - x_offset,
   height - corner_squares_height + y_offset,
   corner_squares_width - x_offset,
   height + y_offset,
   final_corner_squares_color
);
// bottom right
al_draw_filled_rectangle(
   width - corner_squares_width + x_offset,
   height - corner_squares_height + y_offset,
   width + x_offset,
   height + y_offset,
   final_corner_squares_color
);
return;

}
} // namespace Elements
} // namespace Hexagon


