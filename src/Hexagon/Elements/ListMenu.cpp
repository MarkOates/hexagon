

#include <Hexagon/Elements/ListMenu.hpp>
#include <allegro5/allegro_primitives.h>
#include <algorithm>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace Elements
{


ListMenu::ListMenu(AllegroFlare::FontBin* font_bin, std::vector<std::tuple<std::string, std::string>> list_items)
   : font_bin(font_bin)
   , list_items(list_items)
   , cursor(0)
{
}


ListMenu::~ListMenu()
{
}


bool ListMenu::move_cursor_up()
{
cursor--;
return true;

}

bool ListMenu::move_cursor_down()
{
cursor++;
return true;

}

void ListMenu::render()
{
ALLEGRO_FONT *font = obtain_list_item_font();
ALLEGRO_COLOR color = ALLEGRO_COLOR{1, 0, 0, 1};
ALLEGRO_COLOR off_color = ALLEGRO_COLOR{0, 0, 0, 1};
float width = 600;
//float height = 300;
int line_height = al_get_font_line_height(font) * 1.2;

// draw the box and pointer
std::vector<float> points = { 100, 100,  300, 900,  1000, 500 };
al_draw_ribbon(&points[0], sizeof(float) * 2, color, 2.0, 3);

// draw background
//al_draw_rectangle(0, 0, width, height);

// draw text
int y = 0;
for (auto &list_item : list_items)
{
   bool cursor_on_this_list_item = cursor == y;

   if (cursor_on_this_list_item)
   {
      // draw selection box
      al_draw_filled_rectangle(0, y * line_height, width, y * line_height + line_height, color);
   }

   std::string text_to_render = std::get<0>(list_item).c_str();
   std::transform(text_to_render.begin(), text_to_render.end(), text_to_render.begin(), ::toupper);

   al_draw_text(
      font,
      cursor_on_this_list_item ? off_color : color,
      0,
      0 + y * line_height,
      0,
      text_to_render.c_str()
   );
   y++;
}

return;

}

ALLEGRO_FONT* ListMenu::obtain_list_item_font()
{
if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "ListMenu" << "::" << "obtain_list_item_font" << ": error: " << "guard \"font_bin\" not met";
      throw std::runtime_error(error_message.str());
   }
return font_bin->auto_get("Exan-Regular.ttf -46");

}
} // namespace Elements
} // namespace Hexagon


