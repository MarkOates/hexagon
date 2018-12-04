


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



void StageRenderer::render_raw()
{
   if (!stage) throw std::runtime_error("[StageRenderer] stage cannot be a nullptr");

   //get_place().start_transform();
   placement3d &place = stage->get_place();

   //place.start_transform();

   ALLEGRO_COLOR background_overlay_color = al_color_name("black");
   float opacity = 0.8;
   background_overlay_color.r *= opacity;
   background_overlay_color.g *= opacity;
   background_overlay_color.b *= opacity;
   background_overlay_color.a *= opacity;

   //al_draw_filled_rectangle(0, 0, al_get_display_width(display), al_get_display_height(display), background_overlay_color);

   //get_place().start_transform();
   al_draw_filled_rectangle(0, 0, place.size.x, place.size.y, background_overlay_color);

   // draw a frame around the stage
   //float padding = 30;
   //float roundness = 20;
   //float thickness = 20.0;
   //al_draw_rounded_rectangle(-padding, -padding, al_get_display_width(display)+padding, al_get_display_height(display)+padding, roundness, roundness, al_color_name("deepskyblue"), thickness);

   // render cursor
   int &first_line_number = stage->first_line_number;
   float _cursor_y = stage->cursor_y - stage->first_line_number;
   int cursor_x = stage->cursor_x;
   float _cell_width = cell_width;
   float _cell_height = cell_height;
   Stage::mode_t mode = stage->mode;

   switch(mode)
   {
   case Stage::EDIT:
      al_draw_filled_rectangle(cursor_x*_cell_width, _cursor_y*cell_height, cursor_x*_cell_width + _cell_width, _cursor_y*cell_height + cell_height, al_color_name("gray"));
      break;
   case Stage::INSERT:
      al_draw_line(cursor_x*_cell_width, _cursor_y*cell_height, cursor_x*_cell_width, _cursor_y*cell_height + cell_height, al_color_name("gray"), 3);
      break;
   }

   draw_selections(_cell_width, cell_height);

   // render lines
   int line_height = al_get_font_line_height(font);
   const int line_count_render_limit = 120;
   int lines_rendered_count = 0;
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

      if (line_number >= 0) al_draw_text(font, al_color_name("white"), 0, (line_number-first_line_number)*cell_height, ALLEGRO_ALIGN_LEFT, stage->lines[line_number].c_str());
      std::stringstream ss;
      ss << (line_number+1);
      ALLEGRO_COLOR text_color = al_color_name("darkolivegreen");
      if (line_exists_in_git_modified_line_numbers) text_color = al_color_name("orange");
      al_draw_text(font, text_color, -20, (line_number-first_line_number)*cell_height, ALLEGRO_ALIGN_RIGHT, ss.str().c_str());

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

   //stage->get_place().restore_transform();

   // render edit mode
   ALLEGRO_COLOR color;

   switch(mode)
   {
   case Stage::EDIT: color = (stage->currently_grabbing_visual_selection ? al_color_name("orange") : al_color_name("red")); break;
   case Stage::INSERT: color = al_color_name("lime"); break;
   default: break;
   }

   al_draw_text(font, color, al_get_display_width(display)/2, al_get_display_height(display)-al_get_font_line_height(font)*2, ALLEGRO_ALIGN_CENTER, stage->get_current_mode_string().c_str());
   al_draw_text(font, al_color_name("gray"), al_get_display_width(display)/2, al_get_display_height(display)-al_get_font_line_height(font)*1, ALLEGRO_ALIGN_CENTER, stage->filename.c_str());
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



