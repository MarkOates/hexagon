

#include <Hexagon/Elements/Window.hpp>
#include <allegro5/allegro.h>
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
   , header_color({0.0f, 0.0f, 0.0f, 0.0f})
   , bottom_line_color({0.0f, 0.0f, 0.0f, 0.0f})
   , outer_line_color({0.0f, 0.0f, 0.0f, 0.0f})
   , header_baseline_color({0.0f, 0.0f, 0.0f, 0.0f})
   , top_left_little_bar_color({0.0f, 0.0f, 0.0f, 0.0f})
   , corner_square_colour({0.0f, 0.0f, 0.0f, 0.0f})
   , header_height(0.0f)
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


void Window::set_header_color(ALLEGRO_COLOR header_color)
{
   this->header_color = header_color;
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


void Window::set_corner_square_colour(ALLEGRO_COLOR corner_square_colour)
{
   this->corner_square_colour = corner_square_colour;
}


void Window::set_header_height(float header_height)
{
   this->header_height = header_height;
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
// TODO: also need to check al_is_primitives_addon_initialized()
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

return;

}
} // namespace Elements
} // namespace Hexagon


