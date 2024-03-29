

#include <Hexagon/Powerbar/Renderer.hpp>

#include <AllegroFlare/Color.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <allegro_flare/placement3d.h>
#include <sstream>


namespace Hexagon
{
namespace Powerbar
{


Renderer::Renderer(ALLEGRO_DISPLAY* display, Hexagon::Powerbar::Powerbar* powerbar, ALLEGRO_FONT* font, ALLEGRO_COLOR backfill_color, float width)
   : display(display)
   , powerbar(powerbar)
   , font(font)
   , backfill_color(backfill_color)
   , width(width)
   , draw_state_boxes(true)
{
}


Renderer::~Renderer()
{
}


void Renderer::draw_individual_rectangle(float x1, float y1, float x2, float y2, std::string text)
{
   float h_padding = 8.0f;
   float v_padding = 8.0f;
   ALLEGRO_COLOR border_color = al_map_rgba_f(0.2, 0.2, 0.2, 0.2);
   float border_line_thickness = 1.0f;
   ALLEGRO_COLOR color = al_color_name("gray");
   al_draw_rectangle(x1, y1, x2, y2, border_color, border_line_thickness);

   float font_height = al_get_font_line_height(font);
   float text_x = (int)(x1 + h_padding);
   float text_y = (int)(y1 + (y2 - y1) * 0.5 - font_height * 0.5);
   al_draw_text(font, color, text_x, text_y, ALLEGRO_ALIGN_LEFT, text.c_str());
   return;
}

void Renderer::render()
{
   if (!powerbar)
   {
      std::stringstream error_message;
      error_message << "[Hexagon/Powerbar/Renderer error:] cannot \"" << __FUNCTION__ << "\" with a nullptr powerbar";
      throw std::runtime_error(error_message.str());
   }
   if (!font)
   {
      std::stringstream error_message;
      error_message << "[Hexagon/Powerbar/Renderer error:] cannot \"" << __FUNCTION__ << "\" with a nullptr font";
      throw std::runtime_error(error_message.str());
   }

   float height = 30;
   float x = al_get_display_width(display) * 0.5;
   float y = al_get_display_height(display) - height * 2;
   float width = al_get_display_width(display) * 0.75f;
   float line_thickness = 3.0f;
   //ALLEGRO_COLOR background_color = AllegroFlare::color::color(al_color_name("black"), 0.65f);
   ALLEGRO_COLOR background_color = AllegroFlare::color::color(backfill_color, 0.65f);
      //AllegroFlare::color::color(al_color_html("5b5c60"), 0.65f);
   ALLEGRO_COLOR color = al_color_name("gray");

   std::string left_powerbox_text = "";
   std::string center_powerbox_text = "";
   std::string right_powerbox_text = "";

   left_powerbox_text += powerbar->get_files_are_modified() ? "    MODIFIED_FILES    " : "";
   left_powerbox_text += powerbar->get_files_are_staged() ? "    STAGED_FILES    " : "";
   left_powerbox_text += powerbar->get_files_are_untracked() ? "    UNTRACKED_FILES    " : "";
   //center_powerbox_text = powerbar->get_files_are_committed() ? "COMMITTED" : "PENDING COMMIT";
   //right_powerbox_text = powerbar->get_commits_are_in_sync_with_remote() ? "IN SYNC" : "OUT OF SYNC";

   //std::string left_box_text = powerbar->get_files_are_modified();
   //std::string center_box_text = powerbar->get_files_are_modified();
   //std::string right_box_text = powerbar->get_files_are_modified();

   float rectangle_width = width * 0.3333f;
   float h_width = rectangle_width * 0.5; //width * 0.3333f;
   float h_height = height * 0.5f;

   placement3d place(x, y, 0.0);
   place.size.x = width;
   place.size.y = height;

   place.start_transform();

   if (draw_state_boxes)
   {
      al_draw_filled_rectangle(0, 0, place.size.x, place.size.y, background_color);

      draw_individual_rectangle(rectangle_width*0,
                                0,
                                rectangle_width*1,
                                height,
                                left_powerbox_text.c_str());
      draw_individual_rectangle(rectangle_width*1,
                                0,
                                rectangle_width*2,
                                height,
                                center_powerbox_text.c_str());
      draw_individual_rectangle(rectangle_width*2,
                                0,
                                rectangle_width*3,
                                height,
                                right_powerbox_text.c_str());
   }

   place.restore_transform();

   return;
}


} // namespace Powerbar
} // namespace Hexagon


