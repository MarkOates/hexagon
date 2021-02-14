#pragma once


#include <allegro5/allegro_color.h>


namespace Hexagon
{
   namespace Elements
   {
      class Window
      {
      private:
         float width;
         float height;
         float box_opacity;
         float cell_padding;
         ALLEGRO_COLOR box_fill_color;
         ALLEGRO_COLOR header_bar_color;
         ALLEGRO_COLOR bottom_line_color;
         ALLEGRO_COLOR outer_line_color;
         ALLEGRO_COLOR header_baseline_color;
         ALLEGRO_COLOR top_left_little_bar_color;
         ALLEGRO_COLOR corner_squares_color;
         float header_bar_height;
         float header_baseline_thickness;
         float header_bar_opacity;
         float header_baseline_opacity;
         float top_left_little_bar_width;
         float outer_line_thickness;
         float outer_line_opacity;
         float bottom_line_thickness;
         float bottom_line_opacity;
         bool corner_squares_resize_from_center;
         float corner_squares_width;
         float corner_squares_height;
         float corner_squares_opacity;
         bool corner_squares_are_circles;
         int number_of_rows;
         int number_of_columns;
         float distance_of_rows;
         float distance_of_columns;

      public:
         Window(float width=0.0f, float height=0.0f, float box_opacity=0.0f, float cell_padding=0.0f, ALLEGRO_COLOR box_fill_color={0.0f, 0.0f, 0.0f, 0.0f});
         ~Window();

         void set_width(float width);
         void set_height(float height);
         void set_box_opacity(float box_opacity);
         void set_cell_padding(float cell_padding);
         void set_box_fill_color(ALLEGRO_COLOR box_fill_color);
         void set_header_bar_color(ALLEGRO_COLOR header_bar_color);
         void set_bottom_line_color(ALLEGRO_COLOR bottom_line_color);
         void set_outer_line_color(ALLEGRO_COLOR outer_line_color);
         void set_header_baseline_color(ALLEGRO_COLOR header_baseline_color);
         void set_top_left_little_bar_color(ALLEGRO_COLOR top_left_little_bar_color);
         void set_corner_squares_color(ALLEGRO_COLOR corner_squares_color);
         void set_header_bar_height(float header_bar_height);
         void set_header_baseline_thickness(float header_baseline_thickness);
         void set_header_bar_opacity(float header_bar_opacity);
         void set_header_baseline_opacity(float header_baseline_opacity);
         void set_top_left_little_bar_width(float top_left_little_bar_width);
         void set_outer_line_thickness(float outer_line_thickness);
         void set_outer_line_opacity(float outer_line_opacity);
         void set_bottom_line_thickness(float bottom_line_thickness);
         void set_bottom_line_opacity(float bottom_line_opacity);
         void set_corner_squares_resize_from_center(bool corner_squares_resize_from_center);
         void set_corner_squares_width(float corner_squares_width);
         void set_corner_squares_height(float corner_squares_height);
         void set_corner_squares_opacity(float corner_squares_opacity);
         void set_corner_squares_are_circles(bool corner_squares_are_circles);
         void set_number_of_rows(int number_of_rows);
         void set_number_of_columns(int number_of_columns);
         void set_distance_of_rows(float distance_of_rows);
         void set_distance_of_columns(float distance_of_columns);
         float get_width();
         float get_height();
         float get_box_opacity();
         float get_cell_padding();
         ALLEGRO_COLOR get_box_fill_color();
         ALLEGRO_COLOR get_header_bar_color();
         ALLEGRO_COLOR get_bottom_line_color();
         ALLEGRO_COLOR get_outer_line_color();
         ALLEGRO_COLOR get_header_baseline_color();
         ALLEGRO_COLOR get_top_left_little_bar_color();
         ALLEGRO_COLOR get_corner_squares_color();
         float get_header_bar_height();
         float get_header_baseline_thickness();
         float get_header_bar_opacity();
         float get_header_baseline_opacity();
         float get_top_left_little_bar_width();
         float get_outer_line_thickness();
         float get_outer_line_opacity();
         float get_bottom_line_thickness();
         float get_bottom_line_opacity();
         bool get_corner_squares_resize_from_center();
         float get_corner_squares_width();
         float get_corner_squares_height();
         float get_corner_squares_opacity();
         bool get_corner_squares_are_circles();
         int get_number_of_rows();
         int get_number_of_columns();
         float get_distance_of_rows();
         float get_distance_of_columns();
         void draw();
         void draw_top_left_little_bar();
         void draw_header_baseline();
         void draw_bottom_line();
         void draw_header_bar();
         void draw_corner_circles();
         void draw_corner_squares();
      };
   }
}



