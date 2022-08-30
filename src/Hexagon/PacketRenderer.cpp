

#include <Hexagon/PacketRenderer.hpp>
#include <allegro5/allegro_primitives.h>
#include <allegro_flare/placement2d.h>
#include <stdexcept>
#include <sstream>
#include <Hexagon/Elements/Window.hpp>
#include <vector>
#include <tuple>
#include <string>
#include <string>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>


namespace Hexagon
{


PacketRenderer::PacketRenderer(AllegroFlare::FontBin* font_bin, Hexagon::Packet* packet, ALLEGRO_FONT* font, float width, float height, ALLEGRO_COLOR text_color)
   : font_bin(font_bin)
   , packet(packet)
   , font(font)
   , width(width)
   , height(height)
   , text_color(text_color)
{
}


PacketRenderer::~PacketRenderer()
{
}


void PacketRenderer::set_text_color(ALLEGRO_COLOR text_color)
{
   this->text_color = text_color;
}


ALLEGRO_COLOR PacketRenderer::get_text_color() const
{
   return text_color;
}


void PacketRenderer::render()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "PacketRenderer" << "::" << "render" << ": error: " << "guard \"font_bin\" not met";
      throw std::runtime_error(error_message.str());
   }
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

   placement2d text_scaler(0, 0, 0, 0);
   float text_scale = 2.0;
   text_scaler.scale.x = text_scaler.scale.y = 1.0 / text_scale;
   text_scaler.start_transform();
   render_text();
   text_scaler.restore_transform();
   return;
}

ALLEGRO_COLOR PacketRenderer::box_fill_color()
{
   return ALLEGRO_COLOR{0.5f, 0.5f, 0.5f, 1.0f};
}

float PacketRenderer::box_fill_opacity()
{
   return 0.1f;
}

ALLEGRO_COLOR PacketRenderer::box_outline_color()
{
   return ALLEGRO_COLOR{1.0f, 1.0f, 1.0f, 1.0f};
}

float PacketRenderer::box_outline_opacity()
{
   return 0.2f;
}

ALLEGRO_COLOR PacketRenderer::color_good()
{
   return ALLEGRO_COLOR{0.066, 0.394, 0.4023, 1.0};
}

ALLEGRO_COLOR PacketRenderer::color_failure()
{
   return ALLEGRO_COLOR{1.0, 0.0, 0.0, 1.0};
}

ALLEGRO_COLOR PacketRenderer::color_approaching_failure()
{
   return ALLEGRO_COLOR{0.957, 0.46, 0.05, 1.0};
}

ALLEGRO_COLOR PacketRenderer::color_warning()
{
   return ALLEGRO_COLOR{1.0, 1.0, 0, 1.0};
}

ALLEGRO_COLOR PacketRenderer::color_neutral()
{
   return ALLEGRO_COLOR{0.26, 0.26, 0.26, 1.0};
}

void PacketRenderer::render_window()
{
   Hexagon::Elements::Window window(width, height);

   window.set_box_fill_color(box_fill_color());
   window.set_box_opacity(box_fill_opacity());
   window.set_cell_padding(10);

   window.set_outer_line_color(box_outline_color());
   window.set_outer_line_opacity(box_outline_opacity());
   window.set_outer_line_thickness(1.0);

   ALLEGRO_COLOR top_left_little_bar_color = generate_top_left_little_bar_color();

   window.set_header_bar_height(height);
   window.set_top_left_little_bar_color(top_left_little_bar_color);
   window.set_top_left_little_bar_width(6.0f);

   window.draw();
   return;
}

void PacketRenderer::render_text()
{
   float text_scale = 2.0;
   //ALLEGRO_COLOR text_color = ALLEGRO_COLOR{0.5, 0.5, 0.5, 0.5};

   std::vector<std::tuple<std::string, std::string>> table = {
      { "SEARCHES", std::to_string(packet->get_searches_count()) },
      { "SAVES",    std::to_string(packet->get_saves_count()) },
      { "SCORE",    std::to_string(packet->calculate_score()) },
   };

   ALLEGRO_FONT *font = obtain_table_text_font();
   int line_number = 0;
   float row1_x = 22 * text_scale;
   float row2_x = 105 * text_scale;
   float first_row_y = 20 * text_scale;
   int line_height = al_get_font_line_height(font) * 1.2;
   for (auto &row : table)
   {
      std::string row_label = std::get<0>(row);
      std::string row_value = std::get<1>(row);
      float row_y = first_row_y + line_height * line_number;

      // draw label
      al_draw_text(font, get_text_color(), row1_x, row_y, ALLEGRO_ALIGN_LEFT, row_label.c_str());

      // draw data
      al_draw_text(font, get_text_color(), row2_x, row_y, ALLEGRO_ALIGN_RIGHT, row_value.c_str());

      line_number++;
   }

   return;
}

ALLEGRO_COLOR PacketRenderer::generate_top_left_little_bar_color()
{
   int packet_score = packet->calculate_score();
   if (packet_score <= 10) return color_good();
   if (packet_score >= 100) return color_failure();
   if (packet_score >= 50) return color_approaching_failure();
   if (packet_score >= 20) return color_warning();
   return color_neutral();
}

ALLEGRO_FONT* PacketRenderer::obtain_table_text_font()
{
   return font_bin->auto_get("Purista Medium.otf -28");
}
} // namespace Hexagon


