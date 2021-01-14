


#include <Hexagon/CodeEditor/Renderer.hpp>

#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <Hexagon/CodeEditor/CodeEditor.hpp>
#include <Hexagon/CodeEditor/CursorRenderer.hpp>
#include <Hexagon/CodeEditor/Renderer/BasicLineRenderer.hpp>
#include <Hexagon/CodeEditor/Renderer/AdvancedLineRenderer.hpp>
#include <Hexagon/Elements/Window.hpp>
#include <Hexagon/CodeSelectionBoxRenderer.hpp>
#include <Hexagon/shared_globals.hpp> // for hexagon_get_backfill_color() && profile_timer functions
#include <AllegroFlare/Color.hpp>
#include <sstream>
#include <string>
#include <vector>



namespace CodeEditor
{



Renderer::Renderer(
   bool draw_line_numbers,
   bool is_focused,
   ::CodeEditor::CodeEditor *code_editor,
   placement3d place,
   ALLEGRO_FONT *font,
   ALLEGRO_DISPLAY *display,
   int cell_width,
   int cell_height,
   ALLEGRO_COLOR base_font_color,
   ALLEGRO_COLOR backfill_color,
   float backfill_opacity
)
   : Hexagon::RendererInterface()
   , draw_line_numbers(draw_line_numbers)
   , draw_extra_spaces_at_end_of_line(true)
   , draw_null_space(true)
   , draw_backfill(true)
   , is_focused(is_focused)
   , code_editor(code_editor)
   , place(place)
   , font(font)
   , display(display)
   , cell_width(cell_width)
   , cell_height(cell_height)
   , base_font_color(base_font_color)
   , backfill_color(backfill_color)
   , backfill_opacity(backfill_opacity)
{}



Renderer::~Renderer() {}



void Renderer::draw_selections(int cell_width, int cell_height)
{
   if (!code_editor) throw std::runtime_error("CodeEditor::Renderer::draw_selections: code_editor is nullptr");

   for (auto &selection : code_editor->selections)
   {
      //std::cout << " drawing selection " << selection << std::endl;
      CodeSelectionBoxRenderer renderer(
         code_editor->get_lines_ref(),
         selection,
         code_editor->get_first_line_number(),
         cell_width,
         cell_height);
      renderer.render();
   }
}



ALLEGRO_COLOR Renderer::build_font_color(ALLEGRO_COLOR frame_color)
{
   ALLEGRO_COLOR epic_green_color = al_color_html("99ddc4");
   ALLEGRO_COLOR font_color = AllegroFlare::color::mix(epic_green_color, frame_color, 0.5);
   bool using_white_font_color = false;
   if (using_white_font_color)
   {
     // white
     font_color = base_font_color;
   }
   else
   {
     // soft green font
     font_color = AllegroFlare::color::mix(font_color, base_font_color, 0.8);
   }

   return font_color;
}



ALLEGRO_COLOR Renderer::build_frame_color()
{
   if (!code_editor) throw std::runtime_error("CodeEditor::Renderer::draw_selections: code_editor is nullptr");

   ALLEGRO_COLOR frame_color;

   //

   float frame_opacity = 0.6;

   ALLEGRO_COLOR normal_frame_color =
      AllegroFlare::color::color(
         AllegroFlare::color::mix(
             al_color_html("99ddc4"), al_color_name("white"),0.5
           ), 0.85
         );

   bool content_is_modified = code_editor->get_content_is_modified();
   ALLEGRO_COLOR content_is_modified_color =
      AllegroFlare::color::mix(normal_frame_color, al_color_name("orange"), 0.5);
   frame_color = content_is_modified ? content_is_modified_color : normal_frame_color;

   frame_color.r *= frame_opacity;
   frame_color.g *= frame_opacity;
   frame_color.b *= frame_opacity;
   frame_color.a *= frame_opacity;

   //

   return frame_color;
}



ALLEGRO_COLOR Renderer::build_backfill_color()
{
   if (!code_editor) throw std::runtime_error("CodeEditor::Renderer::draw_selections: code_editor is nullptr");

   bool content_is_modified = code_editor->get_content_is_modified();
   float blend_strength = content_is_modified ? 0.2f : 0.1f;

   ALLEGRO_COLOR result_color = backfill_color;
   result_color = AllegroFlare::color::mix(result_color, build_frame_color(), blend_strength);
   result_color = AllegroFlare::color::color(result_color, backfill_opacity);
   return result_color;
}



void Renderer::render_code_lines(placement3d &place, ALLEGRO_COLOR frame_color)
{
   if (!code_editor) throw std::runtime_error("CodeEditor::Renderer::draw_selections: code_editor is nullptr");

   // render cursor

   int first_line_number = code_editor->get_first_line_number();
   float _cursor_y = code_editor->get_cursor_y() - code_editor->get_first_line_number();
   int cursor_x = code_editor->get_cursor_x();
   float _cell_width = cell_width;
   float _cell_height = cell_height;
   ::CodeEditor::CodeEditor::mode_t mode = code_editor->get_mode();
   ALLEGRO_COLOR cursor_color = al_color_name("chartreuse");
   bool not_focused = !is_focused;


    // draw code range selection hilight box(es);

   draw_selections(_cell_width, cell_height);



   // render code lines

   std::vector<std::string> const &lines = code_editor->get_lines_ref();
   int line_height = al_get_font_line_height(font);
   int line_count_render_limit = place.size.y / line_height;
   int lines_rendered_count = 0;
   int line_length_character_limit = place.size.x / cell_width;
   std::vector<int> &git_modified_line_numbers = code_editor->git_modified_line_numbers;
   std::vector<CodeMessagePointsOverlay> &code_message_points_overlays = code_editor->code_message_points_overlays;
   ALLEGRO_COLOR epic_green_color = al_color_html("99ddc4");
   ALLEGRO_COLOR font_color = build_font_color(frame_color);
   ALLEGRO_COLOR line_too_long_font_color = AllegroFlare::color::mix(font_color, al_color_name("red"), 0.3);

   for (int line_number = first_line_number; line_number < (int)lines.size(); line_number++)
   {
      bool line_exists_in_git_modified_line_numbers = std::find(
            git_modified_line_numbers.begin(),
            git_modified_line_numbers.end(),
            (line_number+1))
         != git_modified_line_numbers.end();

      if (line_exists_in_git_modified_line_numbers)
      {
         ALLEGRO_COLOR color = al_color_name("orange");
         color.r *= 0.13;
         color.g *= 0.13;
         color.b *= 0.13;
         color.a *= 0.13;
         al_draw_filled_rectangle(0, line_height * (line_number - first_line_number),
            place.size.x, line_height * (line_number - first_line_number + 1),
            color);
      }

      // draw the actual line of code right here:
      int max_line_char_length = line_length_character_limit;
      if (line_number >= 0)
      {
         std::string line = lines[line_number];
         std::string truncated_line = line.substr(0, max_line_char_length);
         bool line_has_been_truncated = truncated_line.length() != line.length();
         bool line_is_too_long = line.length() > (120 + 1);

         ALLEGRO_COLOR line_font_color = line_is_too_long ? line_too_long_font_color : font_color;
         ALLEGRO_COLOR backfill_color = build_backfill_color();

         // draw the actual line (truncated, possibly) here:
         bool use_advanced_line_renderer = false;
         if (use_advanced_line_renderer)
         {
            Hexagon::CodeEditor::Renderer::AdvancedLineRenderer advanced_line_renderer(
               font,
               &line_font_color,
               &backfill_color,
               0,
               (line_number-first_line_number)*cell_height,
               line);
            advanced_line_renderer.render();
         }
         else
         {
            Hexagon::CodeEditor::Renderer::BasicLineRenderer basic_line_renderer(
               font,
               &line_font_color,
               0,
               (line_number-first_line_number)*cell_height,
               truncated_line.c_str());
            basic_line_renderer.render();
         }

         //Hexagon::CodeEditor::Renderer::BasicLineRenderer line_renderer = advanced_line_renderer;

         //line_renderer.render();

         //al_draw_text(font,
                      //font_color,
                      //0,
                      //(line_number-first_line_number)*cell_height,
                      //ALLEGRO_ALIGN_LEFT,
                      //truncated_line.c_str());

         // draw an "indication" marker for a line too long
         if (line_has_been_truncated)
         {
            float last_char_position_x = max_line_char_length * cell_width;
            al_draw_text(font, al_color_name("red"), last_char_position_x,
                         (line_number-first_line_number)*cell_height, ALLEGRO_ALIGN_RIGHT,
                         "- --=xxXX#");
         }

         // draw extra spaces at end of line
         if (draw_extra_spaces_at_end_of_line)
         {
            const char whitespace_char = ' ';
            const std::string &line = lines[line_number];
            if (!line.empty() && (line.back() == whitespace_char))
            {
               int pos_last_non_whitespace_character = line.find_last_not_of(whitespace_char);
               int character_line_height = al_get_font_line_height(font);
               //int character_width = al_get_(font);
               ALLEGRO_COLOR color = al_color_name("firebrick");
               float character_width = cell_width;

               float leftmost_box_position = (pos_last_non_whitespace_character+1) * character_width;
               float rightmost_box_position = line.length() * character_width;

               al_draw_filled_rectangle(
                  leftmost_box_position,
                  line_height * (line_number - first_line_number),
                  rightmost_box_position,
                  line_height * (line_number - first_line_number + 1),
                  color);
            }
         }
      }

      // draw the line numbers
      if (draw_line_numbers)
      {
         ALLEGRO_COLOR default_line_number_green_color = AllegroFlare::color::color(font_color, 0.2);
         float frame_right_x = place.size.x - cell_width * 0.5;
         bool cursor_is_on_this_line = _cursor_y == (line_number - first_line_number);
         std::stringstream ss;
         ss << (line_number+1);
         ALLEGRO_COLOR text_color = default_line_number_green_color;
         std::string string_to_display = ss.str();
         float y = (line_number-first_line_number)*cell_height;

         if (line_exists_in_git_modified_line_numbers) text_color = al_color_name("orange");
         if (cursor_is_on_this_line)
         {
            text_color = AllegroFlare::color::mix(text_color, cursor_color, 0.5);
            ALLEGRO_COLOR hilight_bar_color = AllegroFlare::color::mix(ALLEGRO_COLOR{0, 0, 0, 0}, text_color, 0.25);
            al_draw_filled_rectangle(0, y, frame_right_x, y+cell_height, hilight_bar_color);
            string_to_display = std::string(">") + string_to_display;
         }

         al_draw_text(font,
                      text_color,
                      frame_right_x,
                      y,
                      ALLEGRO_ALIGN_RIGHT,
                      string_to_display.c_str());
      }

      lines_rendered_count++;
      if (lines_rendered_count >= line_count_render_limit) break;
   }

   for (auto &code_message_points_overlay : code_message_points_overlays)
   {
      code_message_points_overlay.render(font, first_line_number, al_get_font_line_height(font), cursor_x, _cursor_y);
   }

   if (draw_null_space)
   {
      bool draw_above_null_space = true;
      bool draw_below_null_space = true;
      ALLEGRO_COLOR epic_green_color = al_color_html("99ddc4");
      ALLEGRO_COLOR null_space_color = AllegroFlare::color::color(epic_green_color, 0.03);

      if (draw_above_null_space)
      {
         if (first_line_number < 0)
         {
            float null_space_x1 = 0;
            float null_space_y1 = 0;
            float null_space_x2 = place.size.x;
            float null_space_y2 = -first_line_number * cell_height;
                         //(line_number-first_line_number)*cell_height,
            //ALLEGRO_COLOR epic_green_color = al_color_html("99ddc4");
            ////ALLEGRO_COLOR null_space_color = AllegroFlare::color::mix(al_color_name("firebrick"), al_color_name("black"), 0.5);;
            //ALLEGRO_COLOR null_space_color = AllegroFlare::color::color(epic_green_color, 0.03);
            al_draw_filled_rectangle(null_space_x1, null_space_y1, null_space_x2, null_space_y2, null_space_color);
         }
      }
      if (draw_below_null_space)
      {
         float null_space_x1 = 0;
         float null_space_y1 = lines_rendered_count * cell_height;
         float null_space_x2 = place.size.x;
         float null_space_y2 = place.size.y;
         //ALLEGRO_COLOR epic_green_color = al_color_html("99ddc4");
         ////ALLEGRO_COLOR null_space_color = AllegroFlare::color::mix(al_color_name("firebrick"), al_color_name("black"), 0.5);;
         //ALLEGRO_COLOR null_space_color = AllegroFlare::color::color(epic_green_color, 0.03);
         al_draw_filled_rectangle(null_space_x1, null_space_y1, null_space_x2, null_space_y2, null_space_color);
      }
   }

   Hexagon::CodeEditor::CursorRenderer cursor_renderer(cursor_color, cursor_x, _cursor_y, _cell_width, cell_height, mode, is_focused);
   cursor_renderer.render();


   //for (auto &code_message_point : code_message_points)
   //{
      //CodeMessagePointRenderer code_message_point_renderer(code_message_point, font, first_line_number, al_get_font_line_height(font));
      //code_message_point_renderer.render();
   //}
}



void Renderer::render_raw()
{
   if (!code_editor) throw std::runtime_error("CodeEditor::Renderer::draw_selections: code_editor is nullptr");

   bool content_is_modified = code_editor->get_content_is_modified();
   float padding = cell_width;
   float half_padding = padding * 0.5;

   ALLEGRO_COLOR epic_green_color = al_color_html("99ddc4");


   // draw the background and frame (basically the chrome)
   //ALLEGRO_COLOR background_overlay_color = al_color_name("black");
   //ALLEGRO_COLOR background_overlay_color = al_color_html("5b5c60");
   ALLEGRO_COLOR background_overlay_color = build_backfill_color(); //hexagon_get_backfill_color();

   //float opacity = 0.7;
   //background_overlay_color.r *= opacity;
   //background_overlay_color.g *= opacity;
   //background_overlay_color.b *= opacity;
   //background_overlay_color.a *= opacity;

   bool draw_outline = false;
   float roundness = 0; // was previously 6.0;
   float line_thickness = 3.0;

   ALLEGRO_COLOR frame_color = build_frame_color();

   if (draw_backfill)
   {
      al_draw_filled_rounded_rectangle(0, 0,
                               place.size.x, place.size.y,
                               roundness, roundness,
                               background_overlay_color);
   }

   if (draw_outline)
   {
      al_draw_rounded_rectangle(half_padding, half_padding,
                                place.size.x - half_padding, place.size.y - half_padding,
                                roundness, roundness,
                                frame_color, line_thickness);
   }

   Hexagon::Elements::Window window(place.size.x, place.size.y);
   window.set_outer_line_color(base_font_color);
   window.set_outer_line_opacity(0.2);
   window.set_outer_line_thickness(1.0);

   window.set_corner_squares_color(base_font_color);
   window.set_corner_squares_opacity(0.1);
   window.set_corner_squares_width(10.0f);
   window.set_corner_squares_height(10.0f);
   window.set_corner_squares_resize_from_center(true);
   window.draw();



   // render the code lines, cursor, and acutal code markings and information

   placement3d code_lines_placement;
   code_lines_placement.size = place.size - vec3d(padding*2, padding*2, 0);
   code_lines_placement.position = vec3d(padding, padding, 0);
   code_lines_placement.align = vec3d(0, 0, 0);


   code_lines_placement.start_transform();
   render_code_lines(code_lines_placement, frame_color);
   code_lines_placement.restore_transform();
   render_cursor_position_info();
}


void Renderer::render_cursor_position_info()
{
   if (!code_editor) throw std::runtime_error("CodeEditor::Renderer::draw_selections: code_editor is nullptr");

   std::stringstream cursor_position_info;
   int line_length_character_limit = place.size.x / cell_width;

   // draw the current cursor percentage in file
   //cursor_position_info << " n%";

   // draw the current cursor position
   cursor_position_info << " x" << code_editor->get_cursor_x() << " y" << (code_editor->get_cursor_y()+1);

   // draw the width dimensions of the frame
   cursor_position_info << " w" << line_length_character_limit;

   // set colors
   ALLEGRO_COLOR epic_green_color = al_color_html("99ddc4");
   ALLEGRO_COLOR color = AllegroFlare::color::color(epic_green_color, 0.4);

   // draw background box fill
   float text_width = al_get_text_width(font, cursor_position_info.str().c_str());
   bool draw_backfill = false;

   if (draw_backfill)
   {
      ALLEGRO_COLOR background_overlay_color = build_backfill_color(); //hexagon_get_backfill_color();
      al_draw_filled_rectangle(place.size.x - text_width,
                               place.size.y - cell_height,
                               place.size.x,
                               place.size.y,
                               background_overlay_color //al_color_html("5b5c60")
                               );
   }


   ALLEGRO_COLOR frame_color;
   {
   float frame_opacity = 0.6;

   ALLEGRO_COLOR normal_frame_color =
      AllegroFlare::color::color(
         AllegroFlare::color::mix(
             al_color_html("99ddc4"), al_color_name("white"),0.5
           ), 0.85
         );
   bool content_is_modified = code_editor->get_content_is_modified();
   ALLEGRO_COLOR content_is_modified_color =
      AllegroFlare::color::mix(normal_frame_color, al_color_name("orange"), 0.5);
   frame_color = content_is_modified ? content_is_modified_color : normal_frame_color;

   frame_color.r *= frame_opacity;
   frame_color.g *= frame_opacity;
   frame_color.b *= frame_opacity;
   frame_color.a *= frame_opacity;
   }

   // draw whole line of status text
   //ALLEGRO_COLOR text_color = color;
   //ALLEGRO_COLOR font_color = build_font_color(frame_color);
   ALLEGRO_COLOR font_color = build_frame_color();
   bool draw_outline = true;

   al_draw_text(font,
                font_color,
                place.size.x - cell_width * 0.5,
                place.size.y - cell_height,
                ALLEGRO_ALIGN_RIGHT,
                cursor_position_info.str().c_str());
}



void Renderer::render()
{
   global::profiler.start("render");
   place.start_transform();
   render_raw();
   place.restore_transform();
   global::profiler.pause("render");
}



} // namespace CodeEditor



