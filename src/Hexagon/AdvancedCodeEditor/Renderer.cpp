

#include <Hexagon/AdvancedCodeEditor/Renderer.hpp>
#include <iostream>
#include <allegro5/allegro.h>
#include <AllegroFlare/Timer.hpp>
#include <Hexagon/AdvancedCodeEditor/WindowRenderer.hpp>
#include <stdexcept>
#include <sstream>
#include <AllegroFlare/Color.hpp>
#include <allegro5/allegro_color.h>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <Hexagon/CodeSelectionBoxRenderer.hpp>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace AdvancedCodeEditor
{


Renderer::Renderer(Hexagon::Elements::TextMesh* text_mesh, ALLEGRO_BITMAP* surface_render, Hexagon::AdvancedCodeEditor::Cursor* cursor, std::vector<Hexagon::AdvancedCodeEditor::Selection>* selections, std::vector<std::string>* lines, float width, float height, bool cursor_is_bar, float text_mesh_y_offset, int first_row_offset, bool draw_line_numbers, ALLEGRO_FONT* font)
   : text_mesh(text_mesh)
   , surface_render(surface_render)
   , cursor(cursor)
   , selections(selections)
   , lines(lines)
   , width(width)
   , height(height)
   , cursor_is_bar(cursor_is_bar)
   , text_mesh_y_offset(text_mesh_y_offset)
   , first_row_offset(first_row_offset)
   , draw_line_numbers(draw_line_numbers)
   , font(font)
{
}


Renderer::~Renderer()
{
}


void Renderer::set_draw_line_numbers(bool draw_line_numbers)
{
   this->draw_line_numbers = draw_line_numbers;
}


void Renderer::set_font(ALLEGRO_FONT* font)
{
   this->font = font;
}


void Renderer::render()
{
if (!(text_mesh))
   {
      std::stringstream error_message;
      error_message << "Renderer" << "::" << "render" << ": error: " << "guard \"text_mesh\" not met";
      throw std::runtime_error(error_message.str());
   }
AllegroFlare::Timer timer;

timer.reset(); timer.start();
// draw the window
Hexagon::AdvancedCodeEditor::WindowRenderer window_renderer(width, height);
//window_renderer.render();
//timer.pause(); std::cout << " window render: " << timer.get_elapsed_time_microseconds() << std::endl;

// draw the surface render
timer.reset(); timer.start();
//if (surface_render) al_draw_bitmap(surface_render, 0, text_mesh_y_offset, 0);
text_mesh->render();
//timer.pause(); std::cout << " surface_render render time: "
//                         << timer.get_elapsed_time_microseconds() << std::endl;

// draw the cursor
if (draw_line_numbers) render_line_numbers();
draw_selections();
render_cursor();

return;

}

bool Renderer::render_line_numbers()
{
if (!(text_mesh))
   {
      std::stringstream error_message;
      error_message << "Renderer" << "::" << "render_line_numbers" << ": error: " << "guard \"text_mesh\" not met";
      throw std::runtime_error(error_message.str());
   }
if (!(font))
   {
      std::stringstream error_message;
      error_message << "Renderer" << "::" << "render_line_numbers" << ": error: " << "guard \"font\" not met";
      throw std::runtime_error(error_message.str());
   }
int cell_width = text_mesh->get_cell_width();
ALLEGRO_COLOR font_color = al_color_name("white");
ALLEGRO_COLOR cursor_color = AllegroFlare::color::color(al_color_name("yellow"), 0.3);
int first_line_number = first_row_offset;
int _cursor_y = cursor->get_y();
float cell_height = text_mesh->get_cell_height();
bool line_exists_in_git_modified_line_numbers = false;
int num_rows_to_draw_line_numbers = text_mesh->get_num_rows();

for (int i=0; i<num_rows_to_draw_line_numbers; i++)
{
   int line_number = first_line_number + i;
   if (line_number < 0) continue;

   ALLEGRO_COLOR default_line_number_green_color = AllegroFlare::color::color(font_color, 0.2);
   float frame_right_x = width - cell_width * 0.5;
   bool cursor_is_on_this_line = (_cursor_y == line_number);
   std::stringstream ss;
   ss << (line_number+1);
   ALLEGRO_COLOR text_color = default_line_number_green_color;
   std::string string_to_display = ss.str();
   float y = i * cell_height;
   float that_y = y;

   if (line_exists_in_git_modified_line_numbers) text_color = al_color_name("orange");
   if (cursor_is_on_this_line)
   {
      float this_y = y;
      text_color = AllegroFlare::color::mix(text_color, cursor_color, 0.5);
      ALLEGRO_COLOR hilight_bar_color = AllegroFlare::color::mix(ALLEGRO_COLOR{0, 0, 0, 0}, text_color, 0.25);
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

void Renderer::render_cursor()
{
if (!(text_mesh))
   {
      std::stringstream error_message;
      error_message << "Renderer" << "::" << "render_cursor" << ": error: " << "guard \"text_mesh\" not met";
      throw std::runtime_error(error_message.str());
   }
if (!(cursor))
   {
      std::stringstream error_message;
      error_message << "Renderer" << "::" << "render_cursor" << ": error: " << "guard \"cursor\" not met";
      throw std::runtime_error(error_message.str());
   }
if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "Renderer" << "::" << "render_cursor" << ": error: " << "guard \"al_is_primitives_addon_initialized()\" not met";
      throw std::runtime_error(error_message.str());
   }
float cursor_x = cursor->get_x() * text_mesh->get_cell_width();
float cursor_y = (cursor->get_y() - first_row_offset) * text_mesh->get_cell_height() + text_mesh_y_offset;
ALLEGRO_COLOR cursor_color = ALLEGRO_COLOR{0.0f, 1.0f, 1.0f, 1.0f};

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
}
return;

}

void Renderer::draw_selections()
{
if (!(selections))
   {
      std::stringstream error_message;
      error_message << "Renderer" << "::" << "draw_selections" << ": error: " << "guard \"selections\" not met";
      throw std::runtime_error(error_message.str());
   }
if (!(lines))
   {
      std::stringstream error_message;
      error_message << "Renderer" << "::" << "draw_selections" << ": error: " << "guard \"lines\" not met";
      throw std::runtime_error(error_message.str());
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
      CodeSelectionBoxRenderer renderer(
         //code_editor->get_lines_ref(),
         *lines,
         code_range,
         //code_editor->get_first_line_number(),
         first_line_number,
         cell_width,
         cell_height);
      renderer.render();
   }
}

}
} // namespace AdvancedCodeEditor
} // namespace Hexagon


