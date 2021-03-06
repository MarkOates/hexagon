


#include <Hexagon/CodeSelectionBoxRenderer.hpp>

#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>



CodeSelectionBoxRenderer::CodeSelectionBoxRenderer(
      const std::vector<std::string> &lines,
      CodeRange &code_range,
      int first_line_number,
      int cell_width,
      int cell_height
   )
   : lines(lines)
   , code_range(code_range)
   , first_line_number(first_line_number)
   , cell_width(cell_width)
   , cell_height(cell_height)
{}



bool CodeSelectionBoxRenderer::verify_line_in_range(int line_num)
{
   if (line_num >= lines.size()) return false;
   if (line_num < 0) return false;
   return true;
}



int CodeSelectionBoxRenderer::get_line_length(int line_num)
{
   if (!verify_line_in_range(line_num)) return 0;
   return lines[line_num].length();
}



void CodeSelectionBoxRenderer::render()
{
   int num_lines = code_range.infer_num_lines();
   CodePoint start = code_range.infer_cursor_start();
   CodePoint end = code_range.infer_cursor_end();

   ALLEGRO_COLOR selection_color = al_color_name("orange");
   selection_color.r *= 0.4;
   selection_color.g *= 0.4;
   selection_color.b *= 0.4;
   selection_color.a *= 0.4;

   if (num_lines == 0) return;
   if (num_lines == 1)
   {
      // draw beginning-to-end on single line
      //CodePoint start = code_range.infer_cursor_start();
      //CodePoint end = code_range.infer_cursor_end();

      int this_actual_line_y = start.get_y();
      int this_line_y = (this_actual_line_y - first_line_number);

      al_draw_filled_rectangle(
         start.get_x() * cell_width,
         this_line_y * cell_height,
         start.get_x() * cell_width,
         (this_line_y + 1) * cell_height,
         selection_color
      );
   }
   if (num_lines >= 2)
   {
      // draw first line
      //CodePoint start = code_range.infer_cursor_start();
      //CodePoint end = code_range.infer_cursor_end();

      int this_actual_line_y = start.get_y();
      int this_line_y = this_actual_line_y - first_line_number;

      al_draw_filled_rectangle(
         start.get_x() * cell_width,
         this_line_y * cell_height,
         get_line_length(this_actual_line_y) * cell_width,
         (this_line_y + 1) * cell_height,
         selection_color
      );

      if (num_lines > 2)
      {
         // draw intermediate lines
         //CodePoint start = code_range.infer_cursor_start();
         //CodePoint end = code_range.infer_cursor_end();

         for (int i = (start.get_y()+1); i < end.get_y(); i++)
         {
            this_line_y = (i - first_line_number);
            al_draw_filled_rectangle(0, this_line_y * cell_height, get_line_length(i) * cell_width, (this_line_y + 1) * cell_height, selection_color);
         }
      }

      // draw last line

      //CodePoint start = code_range.infer_cursor_start();
      //CodePoint end = code_range.infer_cursor_end();

      this_actual_line_y = end.get_y();
      this_line_y = (this_actual_line_y - first_line_number);
      al_draw_filled_rectangle(0, (this_line_y * cell_height), end.get_x() * cell_width, (this_line_y+1) * cell_height, selection_color);
   }
}



