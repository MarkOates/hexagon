

#include <Hexagon/CodeEditor/LineRenderBin.hpp>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <Hexagon/CodeEditor/Renderer/AdvancedLineRenderer.hpp>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace CodeEditor
{


LineRenderBin::LineRenderBin(ALLEGRO_FONT* font)
   : AllegroFlare::Bin<std::string, ALLEGRO_BITMAP *>()
   , font(font)
{
}


LineRenderBin::~LineRenderBin()
{
}


ALLEGRO_BITMAP* LineRenderBin::load_data(std::string identifier)
{
   if (!(font))
      {
         std::stringstream error_message;
         error_message << "LineRenderBin" << "::" << "load_data" << ": error: " << "guard \"font\" not met";
         throw std::runtime_error(error_message.str());
      }
   std::string text_to_render = identifier;
   ALLEGRO_BITMAP *render = nullptr;

   {
      int line_height = al_get_font_line_height(font);
      int bitmap_width = al_get_text_width(font, text_to_render.c_str());
      int bitmap_height = line_height;
      render = al_create_bitmap(bitmap_width, bitmap_height);

      {
         ALLEGRO_STATE previous_render_state;
         al_store_state(&previous_render_state, ALLEGRO_STATE_TARGET_BITMAP);
         al_set_target_bitmap(render);
         al_clear_to_color(al_map_rgba_f(0.0f, 0.0f, 0.0f, 0.0f));

         {
            //al_draw_text(font, al_color_name("white"), 0, 0, 0, text_to_render.c_str());
         }
         {
            ALLEGRO_COLOR font_color = al_color_name("white");
            ALLEGRO_COLOR backfill_color = al_color_name("black");
            Hexagon::CodeEditor::Renderer::AdvancedLineRenderer renderer(
               font, &font_color, &backfill_color, 0, 0, text_to_render.c_str()
            );
            renderer.render();
            //al_draw_text(font, al_color_name("white"), 0, 0, 0, text_to_render.c_str());
         }

         al_restore_state(&previous_render_state);
      }
   }

   return render;
}

bool LineRenderBin::validate()
{
   return true;
}

void LineRenderBin::destroy_data(ALLEGRO_BITMAP* resource)
{
   al_destroy_bitmap(resource);
   return;
}
} // namespace CodeEditor
} // namespace Hexagon


