#pragma once




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
         float box_fill_color;
         float header_color;
         float bottom_line_color;
         float outer_line_color;
         float header_baseline_color;
         float top_left_little_bar_color;
         float corner_square_colour;
         float header_height;
         float header_baseline_thickness;
         float header_bar_opacity;
         float header_baseline_opacity;
         float top_left_little_bar_width;
         float outer_line_thickness;
         float outer_box_line_opacity;
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
         Window();
         ~Window();

         void set_width(float width);
         void set_height(float height);
         void set_box_opacity(float box_opacity);
         void set_cell_padding(float cell_padding);
         void set_box_fill_color(float box_fill_color);
         void set_header_color(float header_color);
         void set_bottom_line_color(float bottom_line_color);
         void set_outer_line_color(float outer_line_color);
         void set_header_baseline_color(float header_baseline_color);
         void set_top_left_little_bar_color(float top_left_little_bar_color);
         void set_corner_square_colour(float corner_square_colour);
         void set_header_height(float header_height);
         void set_header_baseline_thickness(float header_baseline_thickness);
         void set_header_bar_opacity(float header_bar_opacity);
         void set_header_baseline_opacity(float header_baseline_opacity);
         void set_top_left_little_bar_width(float top_left_little_bar_width);
         void set_outer_line_thickness(float outer_line_thickness);
         void set_outer_box_line_opacity(float outer_box_line_opacity);
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

      void draw();
      };
   }
}



