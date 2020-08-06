

#include <Hexagon/Elements/TextPixelPreviewCreator.hpp>
#include <allegro5/allegro.h>
#include <vector>
#include <string>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace Elements
{


TextPixelPreviewCreator::TextPixelPreviewCreator(std::vector<std::string> text_lines, int width)
   : text_lines(text_lines)
   , width(width)
{
}


TextPixelPreviewCreator::~TextPixelPreviewCreator()
{
}


ALLEGRO_BITMAP* TextPixelPreviewCreator::create()
{
if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "TextPixelPreviewCreator" << "::" << "create" << ": error: " << "guard \"al_is_system_installed()\" not met";
      throw std::runtime_error(error_message.str());
   }
int height = text_lines.size();
ALLEGRO_COLOR foreground_color = al_map_rgba_f(1.0f, 1.0f, 1.0f, 1.0f);
ALLEGRO_COLOR background_color = al_map_rgba_f(0.0f, 0.0f, 0.0f, 1.0f);

ALLEGRO_BITMAP *bitmap = al_create_bitmap(width, height);

ALLEGRO_STATE previous_render_state;
al_store_state(&previous_render_state, ALLEGRO_STATE_TARGET_BITMAP);
al_set_target_bitmap(bitmap);

al_lock_bitmap(bitmap, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_WRITEONLY);

for (int y=0; y<text_lines.size(); y++)
{
   std::string &line = text_lines[y];
   for (int x=0; x<width; x++)
   {
      if (x > line.size() || line[x] == ' ') al_put_pixel(x, y, background_color);
      else al_draw_pixel(x, y, foreground_color);
   }
}

al_unlock_bitmap(bitmap);

al_restore_state(&previous_render_state);

return bitmap;

}
} // namespace Elements
} // namespace Hexagon


