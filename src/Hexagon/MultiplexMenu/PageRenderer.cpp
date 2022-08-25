

#include <Hexagon/MultiplexMenu/PageRenderer.hpp>
#include <stdexcept>
#include <sstream>
#include <AllegroFlare/Color.hpp>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_color.h>
#include <Blast/StringJoiner.hpp>
#include <allegro5/allegro.h>
#include <stdexcept>
#include <sstream>
#include <Hexagon/Elements/ColorKit.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace MultiplexMenu
{


PageRenderer::PageRenderer(AllegroFlare::FontBin* font_bin, Hexagon::MultiplexMenu::MultiplexMenuPage* page, bool is_active, int width, int height)
   : font_bin(font_bin)
   , page(page)
   , is_active(is_active)
   , width(width)
   , height(height)
   , padding(14.0f)
{
}


PageRenderer::~PageRenderer()
{
}


float PageRenderer::get_padding() const
{
   return padding;
}


void PageRenderer::render()
{
   if (!(al_is_system_installed()))
      {
         std::stringstream error_message;
         error_message << "PageRenderer" << "::" << "render" << ": error: " << "guard \"al_is_system_installed()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_font_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "PageRenderer" << "::" << "render" << ": error: " << "guard \"al_is_font_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "PageRenderer" << "::" << "render" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   float menu_item_spacing_y = 66;

   render_frame();

   if (!page)
   {
      // render the "invalid" page
      ALLEGRO_FONT *font = obtain_font();
      std::string page_text = "Not a valid page";
      al_draw_text(font, ALLEGRO_COLOR{1, 0, 0, 1}, 0, 0, ALLEGRO_ALIGN_LEFT, page_text.c_str());
      return;
   }

   int i = 0;
   for (auto &menu_item : page->get_items_ref())
   {
      int x = 0;
      int y = menu_item_spacing_y*i;
      Hexagon::KeyboardCommandKey keyboard_command_key = menu_item.get_keyboard_command_key();
      std::string input_text = convert_key_input_to_string(
            keyboard_command_key.get_al_keycode(),
            keyboard_command_key.get_ctrl(),
            keyboard_command_key.get_alt(),
            keyboard_command_key.get_command(),
            keyboard_command_key.get_shift()
         );

      std::string label = menu_item.get_label();
      bool opens_menu = true;
      std::string state = "no_state";

      render_menu_item(x, y, input_text, label, opens_menu, state);

      i++;
   }

   return;
}

void PageRenderer::render_menu_item(float x, float y, std::string input, std::string label, bool opens_menu, std::string state)
{
   ALLEGRO_COLOR backfill_color = ALLEGRO_COLOR{0.0, 0.0, 0.0, 0.8};
   ALLEGRO_COLOR input_backfill_color = ALLEGRO_COLOR{0.25, 0.25, 0.25, 1.0};
   float frame_opacity = 0.4f;
   ALLEGRO_COLOR frame_color = AllegroFlare::color::color(al_color_name("dodgerblue"), frame_opacity);
   float text_opacity = 0.95f;
   ALLEGRO_COLOR text_color = AllegroFlare::color::color(al_color_name("white"), text_opacity);

   ALLEGRO_FONT *font = obtain_font();
   ALLEGRO_FONT *keyboard_key_font = obtain_keyboard_key_font();
   float padding_x = 20;
   float padding_y = 12;
   float input_text_length = al_get_text_width(keyboard_key_font, input.c_str());
   float label_text_length = al_get_text_width(font, label.c_str());
   float roundness = 6.0;
   float height = al_get_font_line_height(font) + padding_y * 2;
   float width = label_text_length + input_text_length + padding_x * 3;
   float frame_thickness = 2.0;

   //if (opens_menu) label = "= " + label;

   // draw the surrounding box
   al_draw_filled_rounded_rectangle(x, y, x+width, y+height, roundness, roundness, backfill_color);

   // draw the input key
   al_draw_filled_rounded_rectangle(
      x+10,
      y+10,
      x+10+padding_x+input_text_length,
      y-10+height,
      roundness,
      roundness,
      input_backfill_color
   );
   al_draw_text(keyboard_key_font, text_color, x+padding_x, y+padding_y+5, ALLEGRO_ALIGN_LEFT, input.c_str());

   // draw the label text
   al_draw_text(font, text_color, x+padding_x + input_text_length + 20, y+padding_y, ALLEGRO_ALIGN_LEFT, label.c_str());

   // draw the border
   if (state == "activated")
   {
      frame_color = ALLEGRO_COLOR{1, 1, 1, 1};
      frame_thickness = 4.0f;
      al_draw_rounded_rectangle(
         x+frame_thickness*2,
         y+frame_thickness*2,
         x+width-frame_thickness*2,
         y+height-frame_thickness*2,
         roundness,
         roundness,
         frame_color,
         frame_thickness
      );
   }

   return;
}

std::string PageRenderer::convert_key_input_to_string(int al_keycode, bool ctrl, bool alt, bool command, bool shift)
{
   if (!(al_is_system_installed()))
      {
         std::stringstream error_message;
         error_message << "PageRenderer" << "::" << "convert_key_input_to_string" << ": error: " << "guard \"al_is_system_installed()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_keyboard_installed()))
      {
         std::stringstream error_message;
         error_message << "PageRenderer" << "::" << "convert_key_input_to_string" << ": error: " << "guard \"al_is_keyboard_installed()\" not met";
         throw std::runtime_error(error_message.str());
      }
   std::vector<std::string> result_tokens;

   if (ctrl) result_tokens.push_back("Ctrl");
   if (alt) result_tokens.push_back("Alt");
   if (shift) result_tokens.push_back("Shift");
   if (command) result_tokens.push_back("Command");
   result_tokens.push_back(al_keycode_to_name(al_keycode));

   Blast::StringJoiner joiner(result_tokens, "+");

   return joiner.join();
}

void PageRenderer::render_frame()
{
   Hexagon::Elements::ColorKit color_kit;
   //bool is_active = true;
   //ALLEGRO_FONT *font = obtain_list_item_font();
   //ALLEGRO_FONT *title_font = obtain_title_font();
   ALLEGRO_COLOR color = color_kit.pure_white_blue();
   //ALLEGRO_COLOR{1, 0, 0, 1};
   //ALLEGRO_COLOR off_color = ALLEGRO_COLOR{0, 0, 0, 1};
   ALLEGRO_COLOR backfill_color = ALLEGRO_COLOR{0, 0, 0, 0.9};
   ALLEGRO_COLOR inactive_but_selected_color = al_color_html("4e2f1a"); //build_inactive_color();
   //float width = get_width();
   //float height = 300;
   //int line_height = al_get_font_line_height(font) * 1.2;
   //int line_num = 0;
   //float height = line_height * (list_items.size() + 1);
   //int title_font_line_height = al_get_font_line_height(title_font) * 1.2;
   float padding_hack = 10.0f;
   ALLEGRO_COLOR frame_color = is_active ? color : inactive_but_selected_color;

   // draw backfill
   //al_draw_filled_rectangle(-padding_hack, -padding_hack, width+padding_hack, height+padding_hack, backfill_color);

   float place_size_x = width;
   float place_size_y = height;

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
         backfill_color);
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
}

ALLEGRO_FONT* PageRenderer::obtain_font()
{
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "PageRenderer" << "::" << "obtain_font" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   return font_bin->auto_get("Purista Medium.otf -38");
}

ALLEGRO_FONT* PageRenderer::obtain_keyboard_key_font()
{
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "PageRenderer" << "::" << "obtain_keyboard_key_font" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   return font_bin->auto_get("consolas.ttf -30");
}
} // namespace MultiplexMenu
} // namespace Hexagon


