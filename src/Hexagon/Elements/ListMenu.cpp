

#include <Hexagon/Elements/ListMenu.hpp>
#include <allegro5/allegro_primitives.h>
#include <algorithm>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace Elements
{


ListMenu::ListMenu(AllegroFlare::FontBin* font_bin, std::string title, std::vector<std::tuple<std::string, std::string>> list_items, ALLEGRO_COLOR color)
   : font_bin(font_bin)
   , title(title)
   , list_items(list_items)
   , color(color)
   , cursor(0)
   , wrap_cursor_when_moving_cursor_outside_bounds(false)
{
}


ListMenu::~ListMenu()
{
}


void ListMenu::set_wrap_cursor_when_moving_cursor_outside_bounds(bool wrap_cursor_when_moving_cursor_outside_bounds)
{
   this->wrap_cursor_when_moving_cursor_outside_bounds = wrap_cursor_when_moving_cursor_outside_bounds;
}


bool ListMenu::get_wrap_cursor_when_moving_cursor_outside_bounds()
{
   return wrap_cursor_when_moving_cursor_outside_bounds;
}


bool ListMenu::move_cursor_up()
{
cursor--;
if (get_wrap_cursor_when_moving_cursor_outside_bounds())
{
   true;
}
else
{
   if (cursor < 0) cursor = 0;
}
return true;

}

bool ListMenu::move_cursor_down()
{
cursor++;
if (get_wrap_cursor_when_moving_cursor_outside_bounds())
{
   true;
}
else
{
   if (cursor >= list_items.size()) cursor = std::max(0, (int)(list_items.size()) - 1);
}
return true;

}

std::string ListMenu::get_current_list_item_identifier()
{
if (cursor < 0 || cursor >= list_items.size()) return "";
return std::get<1>(list_items[cursor]);

}

void ListMenu::render()
{
ALLEGRO_FONT *font = obtain_list_item_font();
//ALLEGRO_COLOR color = ALLEGRO_COLOR{1, 0, 0, 1};
ALLEGRO_COLOR off_color = ALLEGRO_COLOR{0, 0, 0, 1};
ALLEGRO_COLOR backfill_color = ALLEGRO_COLOR{0, 0, 0, 0.2};
float width = 400;
//float height = 300;
int line_height = al_get_font_line_height(font) * 1.2;
int line_num = 0;
float height = line_height * (list_items.size() + 1);
float padding_hack = 10.0f;

// draw backfill
al_draw_filled_rectangle(-padding_hack, -padding_hack, width+padding_hack, height+padding_hack, backfill_color);

// draw frame
al_draw_rectangle(-padding_hack, -padding_hack, width+padding_hack, height+padding_hack, color, 2.0);

// draw title
bool draw_title = true;
if (draw_title)
{
   std::string text_to_render = title;
   std::transform(text_to_render.begin(), text_to_render.end(), text_to_render.begin(), ::toupper);
   al_draw_text(
      font,
      color,
      0,
      0 + line_num * line_height,
      0,
      text_to_render.c_str()
   );
   line_num++;
}

// draw text
int local_list_line_num = 0;
for (auto &list_item : list_items)
{
   bool cursor_on_this_list_item = (cursor == local_list_line_num);

   if (cursor_on_this_list_item)
   {
      // draw selection box
      al_draw_filled_rectangle(0, line_num * line_height, width, line_num * line_height + line_height, color);

      // draw the cursor arrow
      draw_cursor_pointer_arrow(width + padding_hack, line_num * line_height + line_height * 0.5);
   }

   std::string text_to_render = std::get<0>(list_item).c_str();
   std::transform(text_to_render.begin(), text_to_render.end(), text_to_render.begin(), ::toupper);
   text_to_render = std::string("   - ") + text_to_render;

   al_draw_text(
      font,
      cursor_on_this_list_item ? off_color : color,
      0,
      0 + line_num * line_height,
      0,
      text_to_render.c_str()
   );
   local_list_line_num++;
   line_num++;
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
return font_bin->auto_get("Exan-Regular.ttf -23");

}

void ListMenu::draw_cursor_pointer_arrow(float cpx, float cpy)
{
// draw the box and pointer
const float SQRT_3 = 1.73205f;

//float cpx = 1000;  // cursor pointer x
//float cpy = 900;  // cursor pointer y
float s = 30;
std::vector<float> points = { cpx, cpy };
float change[2] = { 0, 0 };

change[0] = 1;
change[1] = -SQRT_3;
points.push_back(points[points.size()-2] + change[0] * s);
points.push_back(points[points.size()-2] + change[1] * s);

change[0] = 0.275;
change[1] = 0;
points.push_back(points[points.size()-2] + change[0] * s);
points.push_back(points[points.size()-2] + change[1] * s);

change[0] = 0;
change[1] = SQRT_3*2;
points.push_back(points[points.size()-2] + change[0] * s);
points.push_back(points[points.size()-2] + change[1] * s);

change[0] = -0.275;
change[1] = 0;
points.push_back(points[points.size()-2] + change[0] * s);
points.push_back(points[points.size()-2] + change[1] * s);

change[0] = -1;
change[1] = -SQRT_3;
points.push_back(points[points.size()-2] + change[0] * s);
points.push_back(points[points.size()-2] + change[1] * s);

ALLEGRO_COLOR color = ALLEGRO_COLOR{1, 0, 0, 1};
al_draw_ribbon(&points[0], sizeof(float) * 2, color, 2.0, (points.size()/2));
return;

}
} // namespace Elements
} // namespace Hexagon


