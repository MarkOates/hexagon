

#include <Hexagon/Elements/ListMenu.hpp>

#include <algorithm>
#include <allegro5/allegro_primitives.h>
#include <allegro_flare/placement3d.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace Hexagon
{
namespace Elements
{


ListMenu::ListMenu(AllegroFlare::FontBin* font_bin, std::string title, std::vector<std::tuple<std::string, std::string>> list_items, ALLEGRO_COLOR color, ALLEGRO_COLOR backfill_color, float backfill_opacity)
   : font_bin(font_bin)
   , title(title)
   , list_items(list_items)
   , color(color)
   , backfill_color(backfill_color)
   , backfill_opacity(backfill_opacity)
   , cursor(0)
   , cursor_max_scroll_distance(600.0f)
   , wrap_cursor_when_moving_cursor_outside_bounds(true)
   , title_upcase(true)
   , menu_items_upcase(false)
   , width(600)
   , active(true)
   , padding(14.0f)
{
}


ListMenu::~ListMenu()
{
}


void ListMenu::set_color(ALLEGRO_COLOR color)
{
   this->color = color;
}


void ListMenu::set_backfill_color(ALLEGRO_COLOR backfill_color)
{
   this->backfill_color = backfill_color;
}


void ListMenu::set_backfill_opacity(float backfill_opacity)
{
   this->backfill_opacity = backfill_opacity;
}


void ListMenu::set_wrap_cursor_when_moving_cursor_outside_bounds(bool wrap_cursor_when_moving_cursor_outside_bounds)
{
   this->wrap_cursor_when_moving_cursor_outside_bounds = wrap_cursor_when_moving_cursor_outside_bounds;
}


void ListMenu::set_title_upcase(bool title_upcase)
{
   this->title_upcase = title_upcase;
}


void ListMenu::set_menu_items_upcase(bool menu_items_upcase)
{
   this->menu_items_upcase = menu_items_upcase;
}


void ListMenu::set_width(int width)
{
   this->width = width;
}


void ListMenu::set_active(bool active)
{
   this->active = active;
}


std::vector<std::tuple<std::string, std::string>> ListMenu::get_list_items() const
{
   return list_items;
}


ALLEGRO_COLOR ListMenu::get_color() const
{
   return color;
}


ALLEGRO_COLOR ListMenu::get_backfill_color() const
{
   return backfill_color;
}


float ListMenu::get_backfill_opacity() const
{
   return backfill_opacity;
}


bool ListMenu::get_wrap_cursor_when_moving_cursor_outside_bounds() const
{
   return wrap_cursor_when_moving_cursor_outside_bounds;
}


bool ListMenu::get_title_upcase() const
{
   return title_upcase;
}


bool ListMenu::get_menu_items_upcase() const
{
   return menu_items_upcase;
}


int ListMenu::get_width() const
{
   return width;
}


bool ListMenu::get_active() const
{
   return active;
}


float ListMenu::get_padding() const
{
   return padding;
}


void ListMenu::set_list_items(std::vector<std::tuple<std::string, std::string>> list_items)
{
   this->list_items = list_items;
   cursor = 0;
   return;
}

bool ListMenu::move_cursor_up()
{
   if (list_items.empty()) return true;

   cursor--;
   if (get_wrap_cursor_when_moving_cursor_outside_bounds())
   {
      while (cursor < 0) cursor += list_items.size();
   }
   else
   {
      if (cursor < 0) cursor = 0;
   }
   return true;
}

bool ListMenu::move_cursor_down()
{
   if (list_items.empty()) return true;

   cursor++;
   if (get_wrap_cursor_when_moving_cursor_outside_bounds())
   {
      while (cursor >= list_items.size()) cursor -= list_items.size();
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

float ListMenu::calc_normalized_cursor_position()
{
   if (list_items.size() <= 1) return 0.0f;
   return (float)cursor / (float)(list_items.size() - 1);
}

void ListMenu::render()
{
   ALLEGRO_FONT *font = obtain_list_item_font();
   ALLEGRO_FONT *title_font = obtain_title_font();
   //ALLEGRO_COLOR color = ALLEGRO_COLOR{1, 0, 0, 1};
   ALLEGRO_COLOR off_color = ALLEGRO_COLOR{0, 0, 0, 1};
   ALLEGRO_COLOR opacified_backfill_color = build_opacified_backfill_color();
   ALLEGRO_COLOR inactive_but_selected_color = build_inactive_color(); //al_color_html("4e2f1a");
   float width = get_width();
   //float height = 300;
   int line_height = al_get_font_line_height(font) * 1.2;
   int line_num = 0;
   float height = line_height * (list_items.size() + 1);
   int title_font_line_height = al_get_font_line_height(title_font) * 1.2;
   float padding_hack = 10.0f;
   ALLEGRO_COLOR frame_color = get_active() ? color : inactive_but_selected_color;

   // draw backfill
   //al_draw_filled_rectangle(-padding_hack, -padding_hack, width+padding_hack, height+padding_hack, backfill_color);

   float place_size_x = width;
   float place_size_y = height;


   // Calculate the offset for the menu when the scroll space exceeds the maximum
   float normalized_scroll_position = calc_normalized_cursor_position();
   float frame_offset_y = (height <= cursor_max_scroll_distance)
                        ? 0.0f
                        : -(normalized_scroll_position * height) // NOTE this part of the calculation it not 100% correct
                                                                 // and is missing some offset due to padding or smth
                              + normalized_scroll_position * cursor_max_scroll_distance;


   placement3d offset_placement(0, frame_offset_y, 0);
   offset_placement.start_transform();

   // draw frame
   //if (get_active())
   {
      float outer_roundness = 16;
      float inner_roundness = 6;
      //float padding = 6;
      float padding = get_padding();
      al_draw_filled_rounded_rectangle(
         0-padding*2,
         0-padding*2,
         place_size_x+padding*2,
         place_size_y+padding*2,
         outer_roundness,
         outer_roundness,
         opacified_backfill_color);
      al_draw_rounded_rectangle(
         0-padding,
         0-padding,
         place_size_x+padding,
         place_size_y+padding,
         inner_roundness,
         inner_roundness,
         frame_color,
         5.0);

      //al_draw_rectangle(-padding_hack, -padding_hack, width+padding_hack, height+padding_hack, color, 2.0);
      //al_draw_rectangle(
      //   -padding_hack,
      //   -padding_hack,
      //   width+padding_hack,
      //   height+padding_hack,
      //   color,
      //   2.0);
   }

   line_num++;

   // draw text
   int local_list_line_num = 0;
   for (auto &list_item : list_items)
   {
      bool cursor_on_this_list_item = (cursor == local_list_line_num);

      if (cursor_on_this_list_item)
      {
         // draw selection box
         //if (get_active())
         {
            al_draw_filled_rectangle(
               0,
               line_num * line_height,
               width,
               line_num * line_height + line_height,
               get_active() ? color : inactive_but_selected_color
            );
         }
         //if (!get_active())
         if (false)
         {
            ALLEGRO_COLOR inactive_hilighted_list_item_border_color = al_color_html("b45c05");
            al_draw_rectangle(
               0,
               line_num * line_height,
               width,
               line_num * line_height + line_height,
               inactive_hilighted_list_item_border_color,
               2.0
            );
         }

         // draw the cursor arrow
         if (get_active())
         {
            float padding = get_padding();
            //draw_cursor_pointer_arrow(width + padding_hack, line_num * line_height + line_height * 0.5);
            draw_cursor_pointer_arrow(
                  width + padding,
                  line_num * line_height + line_height * 0.5
               );
         }
      }

      std::string text_to_render = std::get<0>(list_item).c_str();
      if (get_menu_items_upcase())
      {
        std::transform(text_to_render.begin(), text_to_render.end(), text_to_render.begin(), ::toupper);
      }
      bool show_bullets = false;
      if (show_bullets) text_to_render = std::string("   - ") + text_to_render;

      al_draw_text(
         font,
         (cursor_on_this_list_item && get_active()) ? off_color : color,
         0,
         0 + line_num * line_height,
         0,
         text_to_render.c_str()
      );
      local_list_line_num++;
      line_num++;
   }

   offset_placement.restore_transform();


   // draw title
   line_num = 0;
   bool draw_title = true;
   if (draw_title)
   {
      std::string text_to_render = title;
      if (get_title_upcase())
      {
         std::transform(text_to_render.begin(), text_to_render.end(), text_to_render.begin(), ::toupper);
      }
      al_draw_text(
         title_font,
         color,
         0,
         0 + line_num * title_font_line_height,
         0,
         text_to_render.c_str()
      );
      line_num++;
   }

   return;
}

ALLEGRO_FONT* ListMenu::obtain_list_item_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::Elements::ListMenu::obtain_list_item_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::Elements::ListMenu::obtain_list_item_font]: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get("Jura-Medium.ttf -26");
   //return font_bin->auto_get("Exan-Regular.ttf -23");
   //return font_bin->auto_get("Helvetica.ttf -23");
}

ALLEGRO_FONT* ListMenu::obtain_title_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::Elements::ListMenu::obtain_title_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::Elements::ListMenu::obtain_title_font]: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get("EurostileExtendedBlack-aka-ExtendedBold.ttf -26");
   //return font_bin->auto_get("Exan-Regular.ttf -23");
   //return font_bin->auto_get("Exan-Regular.ttf -23");
   //return font_bin->auto_get("Exan-Regular.ttf -23");
   //return font_bin->auto_get("Helvetica.ttf -23");
}

ALLEGRO_COLOR ListMenu::build_inactive_color()
{
   return ALLEGRO_COLOR{color.r * 0.38f, color.g * 0.38f, color.b * 0.4f, color.a * 0.4f};
}

ALLEGRO_COLOR ListMenu::build_opacified_backfill_color()
{
   return ALLEGRO_COLOR{
         backfill_color.r * backfill_opacity,
         backfill_color.g * backfill_opacity,
         backfill_color.b * backfill_opacity,
         backfill_color.a * backfill_opacity
      };
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

   ALLEGRO_COLOR color = this->color; //ALLEGRO_COLOR{1, 0, 0, 1};
   al_draw_ribbon(&points[0], sizeof(float) * 2, color, 2.0, (points.size()/2));
   return;
}


} // namespace Elements
} // namespace Hexagon


