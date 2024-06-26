

#include <Hexagon/AdvancedCodeEditor/Renderer.hpp>

#include <AllegroFlare/Color.hpp>
#include <AllegroFlare/Timer.hpp>
#include <Hexagon/AdvancedCodeEditor/SymbolUnderCursorMatcher.hpp>
#include <Hexagon/AdvancedCodeEditor/WindowRenderer.hpp>
#include <Hexagon/CodeMessagePointsOverlay.hpp>
#include <Hexagon/CodeSelectionBoxRenderer.hpp>
#include <Hexagon/WordRangesFinder.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace Hexagon
{
namespace AdvancedCodeEditor
{


Renderer::Renderer(Hexagon::Elements::TextMesh* text_mesh, ALLEGRO_BITMAP* surface_render, Hexagon::AdvancedCodeEditor::Cursor* cursor, std::vector<Hexagon::AdvancedCodeEditor::Selection>* selections, Hexagon::AdvancedCodeEditor::Selection* search_regex_selections, std::vector<CodeRange>* visual_selections, std::vector<CodeRange>* full_line_visual_selections, std::vector<CodeMessagePoint>* code_message_points, std::vector<std::string>* lines, float width, float height, bool cursor_is_bar, float text_mesh_y_offset, int first_row_offset, bool show_line_numbers, ALLEGRO_FONT* font, bool content_is_modified, bool represents_symlink, bool cursor_is_in_valid_range, bool show_backfill)
   : text_mesh(text_mesh)
   , surface_render(surface_render)
   , cursor(cursor)
   , selections(selections)
   , search_regex_selections(search_regex_selections)
   , visual_selections(visual_selections)
   , full_line_visual_selections(full_line_visual_selections)
   , code_message_points(code_message_points)
   , lines(lines)
   , width(width)
   , height(height)
   , cursor_is_bar(cursor_is_bar)
   , text_mesh_y_offset(text_mesh_y_offset)
   , first_row_offset(first_row_offset)
   , show_line_numbers(show_line_numbers)
   , font(font)
   , content_is_modified(content_is_modified)
   , represents_symlink(represents_symlink)
   , cursor_is_in_valid_range(cursor_is_in_valid_range)
   , line_numbers_color(ALLEGRO_COLOR{1.0, 1.0, 1.0, 1.0})
   , show_backfill(show_backfill)
   , null_space_color(ALLEGRO_COLOR{0.0, 0.0, 0.0, 0.3})
   , backfill_color(ALLEGRO_COLOR{0.06, 0.06, 0.06, 0.06})
{
}


Renderer::~Renderer()
{
}


void Renderer::set_show_line_numbers(bool show_line_numbers)
{
   this->show_line_numbers = show_line_numbers;
}


void Renderer::set_font(ALLEGRO_FONT* font)
{
   this->font = font;
}


void Renderer::set_content_is_modified(bool content_is_modified)
{
   this->content_is_modified = content_is_modified;
}


void Renderer::set_represents_symlink(bool represents_symlink)
{
   this->represents_symlink = represents_symlink;
}


void Renderer::set_cursor_is_in_valid_range(bool cursor_is_in_valid_range)
{
   this->cursor_is_in_valid_range = cursor_is_in_valid_range;
}


void Renderer::set_line_numbers_color(ALLEGRO_COLOR line_numbers_color)
{
   this->line_numbers_color = line_numbers_color;
}


void Renderer::set_show_backfill(bool show_backfill)
{
   this->show_backfill = show_backfill;
}


void Renderer::set_null_space_color(ALLEGRO_COLOR null_space_color)
{
   this->null_space_color = null_space_color;
}


void Renderer::set_backfill_color(ALLEGRO_COLOR backfill_color)
{
   this->backfill_color = backfill_color;
}


ALLEGRO_COLOR Renderer::get_line_numbers_color() const
{
   return line_numbers_color;
}


ALLEGRO_COLOR Renderer::get_null_space_color() const
{
   return null_space_color;
}


ALLEGRO_COLOR Renderer::get_backfill_color() const
{
   return backfill_color;
}


void Renderer::render()
{
   if (!(text_mesh))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::AdvancedCodeEditor::Renderer::render]: error: guard \"text_mesh\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::AdvancedCodeEditor::Renderer::render]: error: guard \"text_mesh\" not met");
   }
   //AllegroFlare::Timer timer;

   //timer.reset(); timer.start();
   // draw the window
   //Hexagon::AdvancedCodeEditor::WindowRenderer window_renderer(width, height);
   //window_renderer.render();
   //timer.pause(); std::cout << " window render: " << timer.get_elapsed_time_microseconds() << std::endl;


   //bool show_backfill = true;
   if (show_backfill) render_backfill();

   // draw the surface render
   //timer.reset(); timer.start();
   //if (surface_render)
   //{
      //al_draw_tinted_bitmap(surface_render, ALLEGRO_COLOR{0.0, 0.2, 0.2, 0.2}, 0, text_mesh_y_offset, 0);
   //}
   text_mesh->render();
   //timer.pause(); std::cout << " surface_render render time: "
   //                         << timer.get_elapsed_time_microseconds() << std::endl;

   bool show_cursor_column_highlight = true;
   if (show_line_numbers)
   {
      render_line_numbers();
      // TODO: Sort this out
      if (show_cursor_column_highlight)
      {
         render_cursor_column_highlight();
      }
   }
   if (selections) draw_selections();
   if (search_regex_selections) draw_search_regex_selections();
   if (visual_selections) draw_visual_selections();
   if (full_line_visual_selections) draw_full_line_visual_selections();
   if (code_message_points) draw_code_message_points();
   //if (lines && cursor) render_word_highlight_under_cursor();
   if (lines && cursor) render_extended_symbol_highlight_under_cursor();
   if (lines && cursor) render_word_highlight_under_cursor();
   if (represents_symlink) draw_represents_symlink_frames();
   render_cursor();

   return;
}

void Renderer::render_cursor_column_highlight()
{
   if (!(text_mesh))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::AdvancedCodeEditor::Renderer::render_cursor_column_highlight]: error: guard \"text_mesh\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::AdvancedCodeEditor::Renderer::render_cursor_column_highlight]: error: guard \"text_mesh\" not met");
   }
   if (!(font))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::AdvancedCodeEditor::Renderer::render_cursor_column_highlight]: error: guard \"font\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::AdvancedCodeEditor::Renderer::render_cursor_column_highlight]: error: guard \"font\" not met");
   }
   int cursor_x_pos = cursor->get_x();
   int cursor_y_pos = cursor->get_y();
   //if (cursor_x_pos < 0) return;
   //if (cursor_x_pos >= lines->size()) return;

   int cell_width = text_mesh->get_cell_width();
   int cell_height = text_mesh->get_cell_height();
   float line_numbers_opacity = 0.1;
   ALLEGRO_COLOR font_color = get_line_numbers_color(); //al_color_name("white");
   ALLEGRO_COLOR text_color = AllegroFlare::color::color(font_color, line_numbers_opacity);
   ALLEGRO_COLOR cursor_color = al_color_name("dodgerblue");
   text_color = AllegroFlare::color::mix(text_color, cursor_color, 0.5);
   ALLEGRO_COLOR hilight_bar_color = AllegroFlare::color::mix(ALLEGRO_COLOR{0, 0, 0, 0}, text_color, 0.15);
   int num_rows_to_draw_line_numbers = text_mesh->get_num_rows();

   float x1 = cursor_x_pos * cell_width;
   float x2 = (cursor_x_pos + 1) * cell_width;
   // HERE:
   float y1 = 0; //cursor_y_pos * cell_height;
   float y2 = num_rows_to_draw_line_numbers * cell_height; //cursor_y_pos * (cell_height + 1);

   al_draw_filled_rectangle(x1, y1, x2, y2, hilight_bar_color);

   return;
}

void Renderer::render_backfill()
{
   //ALLEGRO_COLOR backfill_base_color = 
   //AllegroFlare::color::color(al_color_name("white"), 0.06);
   al_draw_filled_rectangle(0, 0, width, height, backfill_color);

   if (content_is_modified)
   {
      ALLEGRO_COLOR content_is_modified_background_color = ALLEGRO_COLOR{0.05, 0.025, 0.0, 0.05};
      al_draw_filled_rectangle(0, 0, width, height, content_is_modified_background_color);
   }

   draw_null_space_above_and_below();
   return;
}

void Renderer::draw_represents_symlink_frames()
{
   float place_size_x = width;
   float place_size_y = height;
   float inner_padding = place_size_x * 0.333;
   float inset = 6;
   float thickness = 2;
   ALLEGRO_COLOR frame_color = al_color_name("dodgerblue");
   frame_color = AllegroFlare::color::mix(frame_color, al_color_name("white"), 0.5);
      // top line
   al_draw_line(
      inner_padding,
      inset,
      place_size_x-inner_padding,
      inset,
      frame_color,
      thickness
   );
   // bottom line
   al_draw_line(
      inner_padding,
      place_size_y-inset,
      place_size_x-inner_padding,
      place_size_y-inset,
      frame_color,
      thickness
   );
   return;
}

bool Renderer::draw_null_space_above_and_below()
{
   if (!(text_mesh))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::AdvancedCodeEditor::Renderer::draw_null_space_above_and_below]: error: guard \"text_mesh\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::AdvancedCodeEditor::Renderer::draw_null_space_above_and_below]: error: guard \"text_mesh\" not met");
   }
   if (!(lines))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::AdvancedCodeEditor::Renderer::draw_null_space_above_and_below]: error: guard \"lines\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::AdvancedCodeEditor::Renderer::draw_null_space_above_and_below]: error: guard \"lines\" not met");
   }
   float cell_height = text_mesh->get_cell_height();
   float line_num = 0;
   float top_line_y = cell_height * (line_num - first_row_offset) + text_mesh_y_offset;
   ALLEGRO_COLOR line_color = ALLEGRO_COLOR{0.1, 0.1, 0.1, 0.1};
   //ALLEGRO_COLOR null_space_color = ALLEGRO_COLOR{0.0, 0.0, 0.0, 0.3};

   if (top_line_y < 0 || top_line_y > height)
   {
      // don't draw
   }
   else
   {
      al_draw_line(0, top_line_y, width, top_line_y, line_color, 2.0);
      al_draw_filled_rectangle(0, 0, width, top_line_y, null_space_color);
   }
   line_num = lines->size();
   float bottom_line_y = cell_height * (line_num - first_row_offset) + text_mesh_y_offset;
   if (bottom_line_y < 0 || bottom_line_y > height)
   {
      // don't draw
   }
   else
   {
      al_draw_line(0, bottom_line_y, width, bottom_line_y, line_color, 2.0);
      al_draw_filled_rectangle(0, bottom_line_y, width, height, null_space_color);
   }
   return true;
}

bool Renderer::render_line_numbers()
{
   if (!(text_mesh))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::AdvancedCodeEditor::Renderer::render_line_numbers]: error: guard \"text_mesh\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::AdvancedCodeEditor::Renderer::render_line_numbers]: error: guard \"text_mesh\" not met");
   }
   if (!(font))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::AdvancedCodeEditor::Renderer::render_line_numbers]: error: guard \"font\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::AdvancedCodeEditor::Renderer::render_line_numbers]: error: guard \"font\" not met");
   }
   int cell_width = text_mesh->get_cell_width();
   ALLEGRO_COLOR font_color = get_line_numbers_color(); //al_color_name("white");
   float line_numbers_opacity = 0.1;
   ALLEGRO_COLOR cursor_color = al_color_name("dodgerblue");
   int first_line_number = first_row_offset;
   int _cursor_y = cursor->get_y();
   float cell_height = text_mesh->get_cell_height();
   bool line_exists_in_git_modified_line_numbers = false;
   int num_rows_to_draw_line_numbers = text_mesh->get_num_rows();

   for (int i=0; i<num_rows_to_draw_line_numbers; i++)
   {
      int line_number = first_line_number + i;
      if (line_number < 0) continue;

      //ALLEGRO_COLOR default_line_number_green_color = AllegroFlare::color::color(font_color, 0.2);
      float frame_right_x = width - cell_width * 0.5;
      bool cursor_is_on_this_line = (_cursor_y == line_number);
      std::stringstream ss;
      ss << (line_number+1);
      ALLEGRO_COLOR text_color = AllegroFlare::color::color(font_color, line_numbers_opacity);
      std::string string_to_display = ss.str();
      float y = i * cell_height;
      float that_y = y;

      if (line_exists_in_git_modified_line_numbers) text_color = al_color_name("orange");
      if (cursor_is_on_this_line)
      {
         float this_y = y;
         text_color = AllegroFlare::color::mix(text_color, cursor_color, 0.5);
         ALLEGRO_COLOR hilight_bar_color = AllegroFlare::color::mix(ALLEGRO_COLOR{0, 0, 0, 0}, text_color, 0.15);
         al_draw_filled_rectangle(0, this_y, frame_right_x, this_y+cell_height, hilight_bar_color);
         string_to_display = std::string(">") + string_to_display;
      }

      al_draw_text(font,
                   text_color,
                   frame_right_x,
                   that_y,
                   ALLEGRO_ALIGN_RIGHT,
                   string_to_display.c_str());
   }
   return true;
}

void Renderer::render_extended_symbol_highlight_under_cursor()
{
   if (!(text_mesh))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::AdvancedCodeEditor::Renderer::render_extended_symbol_highlight_under_cursor]: error: guard \"text_mesh\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::AdvancedCodeEditor::Renderer::render_extended_symbol_highlight_under_cursor]: error: guard \"text_mesh\" not met");
   }
   if (!(cursor))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::AdvancedCodeEditor::Renderer::render_extended_symbol_highlight_under_cursor]: error: guard \"cursor\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::AdvancedCodeEditor::Renderer::render_extended_symbol_highlight_under_cursor]: error: guard \"cursor\" not met");
   }
   if (!(lines))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::AdvancedCodeEditor::Renderer::render_extended_symbol_highlight_under_cursor]: error: guard \"lines\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::AdvancedCodeEditor::Renderer::render_extended_symbol_highlight_under_cursor]: error: guard \"lines\" not met");
   }
   int cursor_x_pos = cursor->get_x();
   int cursor_y_pos = cursor->get_y();
   if (cursor_y_pos < 0) return;
   if (cursor_y_pos >= lines->size()) return;

   std::string line_under_cursor = lines->at(cursor_y_pos);

   //Hexagon::WordRangesFinder word_ranges_finder(line_under_cursor, cursor_x_pos);
   Hexagon::AdvancedCodeEditor::SymbolUnderCursorMatcher symbol_under_cursor_matcher;

   //std::pair<int, int> found_range = word_ranges_finder.find_ranges();
   //if (!word_ranges_finder.is_valid(found_range)) return;

   std::pair<int, int> found_range = symbol_under_cursor_matcher.find_symbol_range(line_under_cursor, cursor_x_pos);
   if (!symbol_under_cursor_matcher.is_valid_match(found_range)) return;

   // render it
   float cell_width = text_mesh->get_cell_width();
   float cell_height = text_mesh->get_cell_height();
   float x = found_range.first * cell_width;
   float y = (cursor_y_pos - first_row_offset) * cell_height;
   float height = cell_height;
   float width = (found_range.second - found_range.first) * cell_width;
   ALLEGRO_COLOR highlight_color = ALLEGRO_COLOR{0.0, 0.3, 0.3, 0.3};
   float line_thickness = 3.0;
   //al_draw_filled_rectangle(x, y+height-line_thickness*1.5, x+width, y+height, highlight_color);
   al_draw_line(x, y+height, x+width, y+height, highlight_color, line_thickness);
     
   return;
}

void Renderer::render_word_highlight_under_cursor()
{
   if (!(text_mesh))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::AdvancedCodeEditor::Renderer::render_word_highlight_under_cursor]: error: guard \"text_mesh\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::AdvancedCodeEditor::Renderer::render_word_highlight_under_cursor]: error: guard \"text_mesh\" not met");
   }
   if (!(cursor))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::AdvancedCodeEditor::Renderer::render_word_highlight_under_cursor]: error: guard \"cursor\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::AdvancedCodeEditor::Renderer::render_word_highlight_under_cursor]: error: guard \"cursor\" not met");
   }
   if (!(lines))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::AdvancedCodeEditor::Renderer::render_word_highlight_under_cursor]: error: guard \"lines\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::AdvancedCodeEditor::Renderer::render_word_highlight_under_cursor]: error: guard \"lines\" not met");
   }
   int cursor_x_pos = cursor->get_x();
   int cursor_y_pos = cursor->get_y();
   if (cursor_y_pos < 0) return;
   if (cursor_y_pos >= lines->size()) return;

   std::string line_under_cursor = lines->at(cursor_y_pos);

   Hexagon::WordRangesFinder word_ranges_finder(line_under_cursor, cursor_x_pos);
   std::pair<int, int> found_range = word_ranges_finder.find_ranges();
   if (!word_ranges_finder.is_valid(found_range)) return;

   // render it
   float cell_width = text_mesh->get_cell_width();
   float cell_height = text_mesh->get_cell_height();
   float x = found_range.first * cell_width;
   float y = (cursor_y_pos - first_row_offset) * cell_height;
   float height = cell_height;
   float width = found_range.second * cell_width;
   ALLEGRO_COLOR highlight_color = ALLEGRO_COLOR{0.0, 0.2, 0.0, 0.2};
   al_draw_filled_rectangle(x, y, x+width, y+height, highlight_color);
   //al_draw_line(x, y+height, x+width, y+height, highlight_color, 2.0);
     
   return;
}

void Renderer::render_cursor()
{
   if (!(text_mesh))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::AdvancedCodeEditor::Renderer::render_cursor]: error: guard \"text_mesh\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::AdvancedCodeEditor::Renderer::render_cursor]: error: guard \"text_mesh\" not met");
   }
   if (!(cursor))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::AdvancedCodeEditor::Renderer::render_cursor]: error: guard \"cursor\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::AdvancedCodeEditor::Renderer::render_cursor]: error: guard \"cursor\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::AdvancedCodeEditor::Renderer::render_cursor]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::AdvancedCodeEditor::Renderer::render_cursor]: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   float cursor_x = cursor->get_x() * text_mesh->get_cell_width();
   float cursor_y = (cursor->get_y() - first_row_offset) * text_mesh->get_cell_height() + text_mesh_y_offset;
   // TODO
   ALLEGRO_COLOR cursor_color = ALLEGRO_COLOR{0.0f, 1.0f, 0.2f, 1.0f};
   ALLEGRO_COLOR h_cursor_color = ALLEGRO_COLOR{0.0f, 0.5f, 0.1f, 0.5f};

   if (!cursor_is_in_valid_range)
   {
      cursor_color = ALLEGRO_COLOR{1.0f, 0.55f, 0.1f, 1.0f};
      h_cursor_color = AllegroFlare::color::color(cursor_color, 0.5);
   }

   if (cursor_is_bar)
   {
      // draw the cursor
      al_draw_line(
         cursor_x,
         cursor_y,
         cursor_x,
         cursor_y+cursor->get_height(),
         cursor_color,
         2.0f
         );
   }
   else
   {
      // draw the cursor
      al_draw_rectangle(
         cursor_x,
         cursor_y,
         cursor_x+cursor->get_width(),
         cursor_y+cursor->get_height(),
         cursor_color,
         2.0f
         );
      // outer highlight
      al_draw_rounded_rectangle(
         cursor_x - 2,
         cursor_y - 2,
         cursor_x + cursor->get_width() + 2,
         cursor_y + cursor->get_height() + 2,
         2.0,
         2.0, 
         h_cursor_color,
         2.0f
         );
   }
   return;
}

void Renderer::draw_selections()
{
   if (!(selections))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::AdvancedCodeEditor::Renderer::draw_selections]: error: guard \"selections\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::AdvancedCodeEditor::Renderer::draw_selections]: error: guard \"selections\" not met");
   }
   if (!(lines))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::AdvancedCodeEditor::Renderer::draw_selections]: error: guard \"lines\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::AdvancedCodeEditor::Renderer::draw_selections]: error: guard \"lines\" not met");
   }
   int cell_width = text_mesh->get_cell_width();
   int first_line_number = first_row_offset;
   float cell_height = text_mesh->get_cell_height();

   //if (!code_editor) throw std::runtime_error("CodeEditor::Renderer::draw_selections: code_editor is nullptr");

   //for (auto &selection : code_editor->selections)
   for (auto &selection : *selections)
   {
      for (auto &code_range : selection.get_code_ranges())
      {
         //std::cout << " drawing selection " << selection << std::endl;
         Hexagon::CodeSelectionBoxRenderer renderer(
            //code_editor->get_lines_ref(),
            lines,
            &code_range,
            //code_editor->get_first_line_number(),
            first_line_number,
            cell_width,
            cell_height);
         renderer.render();
      }
   }
}

void Renderer::draw_visual_selections()
{
   if (!(visual_selections))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::AdvancedCodeEditor::Renderer::draw_visual_selections]: error: guard \"visual_selections\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::AdvancedCodeEditor::Renderer::draw_visual_selections]: error: guard \"visual_selections\" not met");
   }
   if (!(lines))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::AdvancedCodeEditor::Renderer::draw_visual_selections]: error: guard \"lines\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::AdvancedCodeEditor::Renderer::draw_visual_selections]: error: guard \"lines\" not met");
   }
   int cell_width = text_mesh->get_cell_width();
   int first_line_number = first_row_offset;
   float cell_height = text_mesh->get_cell_height();

   //if (!code_editor) throw std::runtime_error("CodeEditor::Renderer::draw_selections: code_editor is nullptr");

   //for (auto &selection : code_editor->selections)
   //for (auto &visual_selection : *visual_selections)
   if ((*visual_selections).empty()) return;

   for (auto &code_range : (*visual_selections))
   {
      //std::cout << " drawing selection " << selection << std::endl;
      Hexagon::CodeSelectionBoxRenderer renderer(
         //code_editor->get_lines_ref(),
         lines,
         &code_range,
         //code_editor->get_first_line_number(),
         first_line_number,
         cell_width,
         cell_height);
      renderer.render();
   }
   return;
}

void Renderer::draw_full_line_visual_selections()
{
   if (!(full_line_visual_selections))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::AdvancedCodeEditor::Renderer::draw_full_line_visual_selections]: error: guard \"full_line_visual_selections\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::AdvancedCodeEditor::Renderer::draw_full_line_visual_selections]: error: guard \"full_line_visual_selections\" not met");
   }
   if (!(lines))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::AdvancedCodeEditor::Renderer::draw_full_line_visual_selections]: error: guard \"lines\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::AdvancedCodeEditor::Renderer::draw_full_line_visual_selections]: error: guard \"lines\" not met");
   }
   int cell_width = text_mesh->get_cell_width();
   int first_line_number = first_row_offset;
   float cell_height = text_mesh->get_cell_height();

   //if (!code_editor) throw std::runtime_error("CodeEditor::Renderer::draw_selections: code_editor is nullptr");

   //for (auto &selection : code_editor->selections)
   //for (auto &visual_selection : *visual_selections)
   if ((*full_line_visual_selections).empty()) return;
   ALLEGRO_COLOR selection_color = al_color_name("violet");
   selection_color = AllegroFlare::color::color(selection_color, 0.4);

   for (auto &code_range : (*full_line_visual_selections))
   {
      //std::cout << " drawing selection " << selection << std::endl;
      Hexagon::CodeSelectionBoxRenderer renderer(
         //code_editor->get_lines_ref(),
         lines,
         &code_range,
         //code_editor->get_first_line_number(),
         first_line_number,
         cell_width,
         cell_height);
      renderer.set_selection_color(selection_color);
      renderer.render_full_line_selection();
   }
   return;
}

void Renderer::draw_search_regex_selections()
{
   if (!(search_regex_selections))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::AdvancedCodeEditor::Renderer::draw_search_regex_selections]: error: guard \"search_regex_selections\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::AdvancedCodeEditor::Renderer::draw_search_regex_selections]: error: guard \"search_regex_selections\" not met");
   }
   if (!(lines))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::AdvancedCodeEditor::Renderer::draw_search_regex_selections]: error: guard \"lines\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::AdvancedCodeEditor::Renderer::draw_search_regex_selections]: error: guard \"lines\" not met");
   }
   if (!(text_mesh))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::AdvancedCodeEditor::Renderer::draw_search_regex_selections]: error: guard \"text_mesh\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::AdvancedCodeEditor::Renderer::draw_search_regex_selections]: error: guard \"text_mesh\" not met");
   }
   int cell_width = text_mesh->get_cell_width();
   int first_line_number = first_row_offset;
   float cell_height = text_mesh->get_cell_height();
   ALLEGRO_COLOR selection_color = ALLEGRO_COLOR{0.12*0.4, 0.56*0.4, 1.0*0.4, 1.0*0.4};
   int num_rows = text_mesh->get_num_rows();

   //if (!code_editor) throw std::runtime_error("CodeEditor::Renderer::draw_selections: code_editor is nullptr");

   //for (auto &selection : code_editor->selections)
   //for (auto &selection : *search_regex_selections)
   {
      for (auto &code_range : (*search_regex_selections).get_code_ranges())
      {
         // skip if below range
         CodePoint start = code_range.infer_cursor_start();
         if (start.get_y() >= (first_line_number+num_rows)) continue;

         // TODO: skip if below range
         CodePoint end = code_range.infer_cursor_end();
         if (end.get_y() < first_line_number) continue;

         Hexagon::CodeSelectionBoxRenderer renderer(
            //code_editor->get_lines_ref(),
            lines,
            &code_range,
            //code_editor->get_first_line_number(),
            first_line_number,
            cell_width,
            cell_height,
            selection_color);
         renderer.render();
      }
   }
}

void Renderer::draw_code_message_points()
{
   if (!(code_message_points))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::AdvancedCodeEditor::Renderer::draw_code_message_points]: error: guard \"code_message_points\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::AdvancedCodeEditor::Renderer::draw_code_message_points]: error: guard \"code_message_points\" not met");
   }
   if (!(cursor))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::AdvancedCodeEditor::Renderer::draw_code_message_points]: error: guard \"cursor\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::AdvancedCodeEditor::Renderer::draw_code_message_points]: error: guard \"cursor\" not met");
   }
   if (!(lines))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::AdvancedCodeEditor::Renderer::draw_code_message_points]: error: guard \"lines\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::AdvancedCodeEditor::Renderer::draw_code_message_points]: error: guard \"lines\" not met");
   }
   if (!(font))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::AdvancedCodeEditor::Renderer::draw_code_message_points]: error: guard \"font\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::AdvancedCodeEditor::Renderer::draw_code_message_points]: error: guard \"font\" not met");
   }
   int cell_width = text_mesh->get_cell_width();
   int first_line_number = first_row_offset;
   float cell_height = text_mesh->get_cell_height();
   ALLEGRO_COLOR color = al_color_name("green");

   CodeMessagePointsOverlay code_message_points_overlay(color, *code_message_points);
   code_message_points_overlay.render(font, first_line_number, cell_height, cursor->get_x(), cursor->get_y());

   return;
}


} // namespace AdvancedCodeEditor
} // namespace Hexagon


