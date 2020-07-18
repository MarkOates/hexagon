

#include <Hexagon/PacketRenderer.hpp>
#include <allegro5/allegro_primitives.h>
#include <stdexcept>
#include <sstream>
#include <Hexagon/Elements/Window.hpp>
#include <vector>
#include <tuple>
#include <string>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>


namespace Hexagon
{


PacketRenderer::PacketRenderer(Hexagon::Packet* packet, ALLEGRO_FONT* font, float width, float height)
   : packet(packet)
   , font(font)
   , width(width)
   , height(height)
{
}


PacketRenderer::~PacketRenderer()
{
}


void PacketRenderer::render()
{
if (!(packet))
   {
      std::stringstream error_message;
      error_message << "PacketRenderer" << "::" << "render" << ": error: " << "guard \"packet\" not met";
      throw std::runtime_error(error_message.str());
   }
if (!(font))
   {
      std::stringstream error_message;
      error_message << "PacketRenderer" << "::" << "render" << ": error: " << "guard \"font\" not met";
      throw std::runtime_error(error_message.str());
   }
if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "PacketRenderer" << "::" << "render" << ": error: " << "guard \"al_is_primitives_addon_initialized()\" not met";
      throw std::runtime_error(error_message.str());
   }
render_window();
render_text();
return;

}

void PacketRenderer::render_window()
{
Hexagon::Elements::Window window(width, height);

window.set_box_fill_color(ALLEGRO_COLOR{0.5f, 0.5f, 0.5f, 1.0f});
window.set_box_opacity(0.1);
window.set_cell_padding(10);

window.set_outer_line_color(ALLEGRO_COLOR{1.0f, 1.0f, 1.0f, 1.0f});
window.set_outer_line_opacity(0.2);
window.set_outer_line_thickness(2.0);

window.set_header_bar_height(height);
window.set_top_left_little_bar_color(ALLEGRO_COLOR{0.26, 0.26, 0.26, 1.0});
window.set_top_left_little_bar_width(6.0f);

window.draw();
return;

}

void PacketRenderer::render_text()
{
ALLEGRO_COLOR text_color = ALLEGRO_COLOR{0.5, 0.5, 0.5, 0.5};

std::vector<std::tuple<std::string, std::string>> table = {
   { "SEARCHES", std::to_string(packet->get_searches_count()) },
   { "SAVES",    std::to_string(packet->get_saves_count()) },
   { "SCORE",    std::to_string(packet->calculate_score()) },
};

int line_number = 0;
float row1_x = 22;
float row2_x = 115;
float first_row_y = 20;
int line_height = al_get_font_line_height(font) * 1.2;
for (auto &row : table)
{
   std::string row_label = std::get<0>(row);
   std::string row_value = std::get<1>(row);
   float row_y = first_row_y + line_height * line_number;

   // draw label
   al_draw_text(font, text_color, row1_x, row_y, ALLEGRO_ALIGN_LEFT, row_label.c_str());

   // draw data
   al_draw_text(font, text_color, row2_x, row_y, ALLEGRO_ALIGN_RIGHT, row_value.c_str());

   line_number++;
}

return;

}
} // namespace Hexagon


