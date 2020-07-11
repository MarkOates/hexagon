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
         float corner_squares_resize_from_center;
         float corner_squares_width;
         float corner_squares_height;
         float corner_squares_opacity;
         float corner_squares_are_circles;
         float number_of_rows;
         float number_of_columns;
         float distance_of_rows;
         float distance_of_columns;

      public:
         Window();
         ~Window();


      void draw();
      };
   }
}



