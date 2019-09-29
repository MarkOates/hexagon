


#include <Hexagon/StageRenderer.hpp>

#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <Hexagon/Stage.hpp>
#include <Hexagon/CodeRangeRenderer.hpp>
#include <sstream>
#include <string>
#include <vector>



void StageRenderer::draw_selections(int cell_width, int cell_height)
{
   for (auto &selection : stage->selections)
   {
      //std::cout << " drawing selection " << selection << std::endl;
      CodeRangeRenderer(stage->get_lines_ref(), selection, stage->first_line_number, cell_width, cell_height).render();
   }
}



void StageRenderer::render_code_lines()
{
}



void StageRenderer::render_raw()
{
   if (!stage) throw std::runtime_error("[StageRenderer] stage cannot be a nullptr");

   placement3d &place = stage->get_place();
   float padding = cell_width;
   float half_padding = padding * 0.5;



   // draw the background and frame (basically the chrome)
   ALLEGRO_COLOR background_overlay_color = al_color_name("steelblue");
   float opacity = 0.2; //0.7;
   background_overlay_color.r *= opacity;
   background_overlay_color.g *= opacity;
   background_overlay_color.b *= opacity;
   background_overlay_color.a *= opacity;
   ALLEGRO_COLOR frame_color = al_color_name("steelblue");
   float roundness = 6.0;
   float line_thickness = 3.0;

   al_draw_filled_rounded_rectangle(0, 0,
                            place.size.x, place.size.y,
                            roundness, roundness,
                            background_overlay_color);
   al_draw_rounded_rectangle(half_padding, half_padding,
                             place.size.x - half_padding, place.size.y - half_padding,
                             roundness, roundness,
                             frame_color, line_thickness);



   // render the code lines, cursor, and acutal code markings and information

   placement3d code_lines_placement;
   code_lines_placement.size = place.size - vec3d(padding*2, padding*2, 0);  
   code_lines_placement.position = vec3d(padding, padding, 0);


   render_code_lines();



   // render cursor
   int &first_line_number = stage->first_line_number;
   float _cursor_y = stage->cursor_y - stage->first_line_number;
   int cursor_x = stage->cursor_x;
   float _cell_width = cell_width;
   float _cell_height = cell_height;
   Stage::mode_t mode = stage->mode;
   ALLEGRO_COLOR cursor_color = al_color_name("chartreuse");
   float cursor_outset = 2.0;

   switch(mode)
   {
   case Stage::EDIT:
      al_draw_rounded_rectangle(cursor_x*_cell_width - cursor_outset, _cursor_y*cell_height - cursor_outset,
                                cursor_x*_cell_width + _cell_width + cursor_outset, _cursor_y*cell_height + cell_height,
                                2.0, 2.0, cursor_color, 3.0);
      break;
   case Stage::INSERT:
      al_draw_line(cursor_x*_cell_width, _cursor_y*cell_height,
                   cursor_x*_cell_width, _cursor_y*cell_height + cell_height,
                   cursor_color, 3);
      break;
   }



   // draw code range selection hilight box(es);
   draw_selections(_cell_width, cell_height);



   // render code lines
   int line_height = al_get_font_line_height(font);
   const int line_count_render_limit = 120;
   int lines_rendered_count = 0;
   int line_length_character_limit = place.size.x / cell_width;
   std::vector<int> &git_modified_line_numbers = stage->git_modified_line_numbers;
   std::vector<CodeMessagePointsOverlay> &code_message_points_overlays = stage->code_message_points_overlays;

   for (int line_number = first_line_number; line_number < (int)stage->lines.size(); line_number++)
   {
      bool line_exists_in_git_modified_line_numbers = std::find(git_modified_line_numbers.begin(), git_modified_line_numbers.end(), (line_number+1)) != git_modified_line_numbers.end();
      if (line_exists_in_git_modified_line_numbers)
      {
         ALLEGRO_COLOR color = al_color_name("orange");
         color.r *= 0.13;
         color.g *= 0.13;
         color.b *= 0.13;
         color.a *= 0.13;
         al_draw_filled_rectangle(0, line_height * (line_number - first_line_number), al_get_display_width(display)*2, line_height * (line_number - first_line_number + 1), color);
      }

      // draw the actual line of code right here:
      int max_line_char_length = line_length_character_limit;
      if (line_number >= 0)
      {
         std::string line = stage->lines[line_number];
         std::string truncated_line = line.substr(0, max_line_char_length);
         bool has_line_been_truncated = false;
         if (truncated_line.size() != line.size()) has_line_been_truncated = true;

         // draw the actual line (truncated, possibly) here:
         al_draw_text(font, al_color_name("white"), 0, (line_number-first_line_number)*cell_height, ALLEGRO_ALIGN_LEFT, truncated_line.c_str());

         // draw an "indication" marker for a line too long
         if (has_line_been_truncated)
         {
            float last_char_position_x = max_line_char_length * cell_width;
            al_draw_text(font, al_color_name("red"), last_char_position_x,
                         (line_number-first_line_number)*cell_height, ALLEGRO_ALIGN_RIGHT,
                         "- --=xxXX#");
         }
      }

      // draw the line numbers (currently_disabled)
      bool draw_line_numbers = false;
      if (draw_line_numbers)
      {
         std::stringstream ss;
         ss << (line_number+1);
         ALLEGRO_COLOR text_color = al_color_name("darkolivegreen");
         if (line_exists_in_git_modified_line_numbers) text_color = al_color_name("orange");
         al_draw_text(font, text_color, -20, (line_number-first_line_number)*cell_height, ALLEGRO_ALIGN_RIGHT, ss.str().c_str());
      }

      lines_rendered_count++;
      if (lines_rendered_count >= line_count_render_limit) break;
   }

   for (auto &code_message_points_overlay : code_message_points_overlays)
   {
      code_message_points_overlay.render(font, first_line_number, al_get_font_line_height(font), cursor_x, _cursor_y);
   }
   //for (auto &code_message_point : code_message_points)
   //{
      //CodeMessagePointRenderer code_message_point_renderer(code_message_point, font, first_line_number, al_get_font_line_height(font));
      //code_message_point_renderer.render();
   //}
}



StageRenderer::StageRenderer(Stage *stage, ALLEGRO_FONT *font, ALLEGRO_DISPLAY *display, int cell_width, int cell_height)
   : stage(stage)
   , font(font)
   , display(display)
   , render_cache()
   , cell_width(cell_width)
   , cell_height(cell_height)
{}



StageRenderer::~StageRenderer() {}



void StageRenderer::render()
{
   placement3d &place = stage->get_place();

   render_cache.setup_surface(place.size.x, place.size.y);
   render_raw();
   render_cache.finish_surface();

   place.start_transform();
   render_cache.draw(0, 0);
   place.restore_transform();
}



