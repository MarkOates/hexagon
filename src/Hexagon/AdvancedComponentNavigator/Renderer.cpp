

#include <Hexagon/AdvancedComponentNavigator/Renderer.hpp>

#include <Hexagon/FileSystemNode.hpp>
#include <Hexagon/Shapes/Hexagon/Renderer.hpp>
#include <Hexagon/Shapes/Hexagon/Stroke.hpp>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <allegro_flare/color.h>
#include <allegro_flare/placement3d.h>
#include <cmath>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace Hexagon
{
namespace AdvancedComponentNavigator
{


Renderer::Renderer(Hexagon::AdvancedComponentNavigator::Stage* stage, AllegroFlare::FontBin* font_bin, bool is_focused, ALLEGRO_FONT* font, int cell_width, int cell_height, ALLEGRO_COLOR base_backfill_color, float backfill_opacity, ALLEGRO_COLOR base_text_color, std::vector<std::string> input_hints_tokens)
   : stage(stage)
   , font_bin(font_bin)
   , is_focused(is_focused)
   , font(font)
   , cell_width(cell_width)
   , cell_height(cell_height)
   , base_backfill_color(base_backfill_color)
   , backfill_opacity(backfill_opacity)
   , base_text_color(base_text_color)
   , input_hints_tokens(input_hints_tokens)
   , frame_color_bluegreen(al_color_html("5cb7e2"))
{
}


Renderer::~Renderer()
{
}


void Renderer::set_input_hints_tokens(std::vector<std::string> input_hints_tokens)
{
   this->input_hints_tokens = input_hints_tokens;
}


ALLEGRO_COLOR Renderer::get_base_backfill_color() const
{
   return base_backfill_color;
}


ALLEGRO_COLOR Renderer::get_base_text_color() const
{
   return base_text_color;
}


std::vector<std::string> Renderer::get_input_hints_tokens() const
{
   return input_hints_tokens;
}


void Renderer::note()
{
   // frame_color_bluegree used to be 'al_color_html("39c3c5")'
   return;
}

ALLEGRO_COLOR Renderer::build_backfill_color()
{
   ALLEGRO_COLOR result_backfill_color = color::color(base_backfill_color, 0.8);
   return result_backfill_color;
}

void Renderer::draw_search_text_box()
{
   // draw the search_text
   Hexagon::AdvancedComponentNavigator::Stage &stage = *this->stage;
   Hexagon::AdvancedComponentNavigator::AdvancedComponentNavigator &component = stage.get_component_ref();

   ALLEGRO_COLOR backfill_color = build_backfill_color();
   bool focus_is_search_bar = component.is_mode_typing_in_search_bar();

   ALLEGRO_COLOR search_text_font_color = focus_is_search_bar ? al_color_name("chartreuse") : frame_color_bluegreen;
   std::string search_text_val = component.get_search_text();
   float search_text_width = al_get_text_width(font, search_text_val.c_str());
   float search_text_height = al_get_font_line_height(font);
   float search_text_y = search_text_height * -1.3;
   // background
   al_draw_filled_rectangle(0, search_text_y, search_text_width, search_text_y+search_text_height, backfill_color);

   // draw rectangle if typing
   if (focus_is_search_bar)
   {
      ALLEGRO_COLOR col = search_text_font_color;
      ALLEGRO_COLOR halo_color = search_text_font_color;
      float padding = 4.0f;
      float roundness = 3.0f;
      al_draw_rounded_rectangle(
            0-padding,
            search_text_y-padding,
            search_text_width+padding,
            search_text_y+search_text_height+padding,
            roundness, roundness,
            col, 3.0);

      {
         // halo
         float cursor_thickness = 3.0f;
         int max_outset = 18 + 7 * std::sin(al_get_time() * 3); // is actually animated, but only visible
                                                             // when every frame is rendering
         for (int outset=1; outset<max_outset; outset++)
         {
           float color_opacity = (1.0 - (float)outset / max_outset) * 0.25;
           ALLEGRO_COLOR col = color::color(halo_color, color_opacity);
           al_draw_rounded_rectangle(
             0-padding - outset,
             search_text_y-padding - outset,
             search_text_width+padding + outset,
             search_text_y+search_text_height+padding + outset,
             2.0, 2.0, col, cursor_thickness);
         }
      }
   }

   al_draw_text(font, search_text_font_color, 0, search_text_y, 0, search_text_val.c_str());
   return;
}

void Renderer::draw_input_hints()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::AdvancedComponentNavigator::Renderer::draw_input_hints]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::AdvancedComponentNavigator::Renderer::draw_input_hints]: error: guard \"font_bin\" not met");
   }
   if (input_hints_tokens.empty()) return;

   Hexagon::AdvancedComponentNavigator::Stage &stage = *this->stage;
   placement3d &place = stage.get_place();
   std::string text_to_draw = input_hints_tokens[0];
   ALLEGRO_COLOR color = base_text_color;
   al_draw_text(font, color, place.size.x * 0.5, place.size.y+30, ALLEGRO_ALIGN_CENTER, text_to_draw.c_str());
   std::string help_text = "Note that multiple search filters are applied when search has text separated by spaces.";
   al_draw_text(font, color, place.size.x * 0.5, place.size.y+60, ALLEGRO_ALIGN_CENTER, help_text.c_str());
   return;
}

void Renderer::render()
{
   if (!(stage))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::AdvancedComponentNavigator::Renderer::render]: error: guard \"stage\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::AdvancedComponentNavigator::Renderer::render]: error: guard \"stage\" not met");
   }
   if (!(font))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::AdvancedComponentNavigator::Renderer::render]: error: guard \"font\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::AdvancedComponentNavigator::Renderer::render]: error: guard \"font\" not met");
   }
   placement3d &place = stage->get_place();
   place.start_transform();
   render_raw();
   place.restore_transform();
   return;
}

void Renderer::render_raw()
{
   if (!(stage))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::AdvancedComponentNavigator::Renderer::render_raw]: error: guard \"stage\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::AdvancedComponentNavigator::Renderer::render_raw]: error: guard \"stage\" not met");
   }
   if (!(font))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::AdvancedComponentNavigator::Renderer::render_raw]: error: guard \"font\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::AdvancedComponentNavigator::Renderer::render_raw]: error: guard \"font\" not met");
   }
   Hexagon::AdvancedComponentNavigator::Stage &stage = *this->stage;
   Hexagon::AdvancedComponentNavigator::AdvancedComponentNavigator &component = stage.get_component_ref();
   placement3d &place = stage.get_place();

   float line_stroke_thickness = 2.5;

   // draw backfill and outline

   float roundness = 0.0; //6.0;
   float padding_x = cell_width;
   float padding_y = cell_width;
   //ALLEGRO_COLOR frame_color_bluegreen = al_color_html("39c3c5");
   ALLEGRO_COLOR backfill_color = build_backfill_color();

   al_draw_filled_rounded_rectangle(
     0 - padding_x*2,
     0 - padding_y*2,
     place.size.x + padding_x*2,
     place.size.y + padding_y*2,
     roundness,
     roundness,
     backfill_color
   );
   al_draw_rounded_rectangle(- padding_x, - padding_y,
      place.size.x+padding_x, place.size.y+padding_y,
      roundness, roundness, frame_color_bluegreen, line_stroke_thickness);


   // draw cursor box for focused line

   int line = 0;
   int line_height = cell_height * 1.1;
   int pos_x = 0;
   int cursor_y = 0;
   if (component.get_cursor_position_static())
   {
     cursor_y = - line_height * component.get_cursor_position();
   }
   float current_node_root_y_pos = cursor_y - line_height * 1.5;
   ALLEGRO_COLOR font_color = al_color_name("white");
   ALLEGRO_COLOR node_folder_color = al_color_name("lightgray");

   bool mode_navigating_list = component.is_mode_navigating_list();
   ALLEGRO_COLOR selector_outline_color =
      mode_navigating_list ? al_color_name("chartreuse") : al_color_name("slategray");
   ALLEGRO_COLOR selector_fill_color =
      mode_navigating_list ? color::transparent : al_color_name("darkslategray");
   ALLEGRO_COLOR halo_color =
      mode_navigating_list ? al_color_name("chartreuse") : al_color_name("slategray");

   float cursor_thickness = 3.0f;

   float selector_y = line_height * component.get_cursor_position() + cursor_y;
   std::string current_selection_label_or_empty_string = component.get_current_selection_label_or_empty_string();
   float selector_rectangle_width = al_get_text_width(font, current_selection_label_or_empty_string.c_str());
   float selector_rectangle_roundness = 0; //4;

   if (component.current_selection_is_valid())
   {
     al_draw_filled_rounded_rectangle(
       0,
       selector_y,
       selector_rectangle_width,
       selector_y+line_height,
       selector_rectangle_roundness,
       selector_rectangle_roundness,
       selector_fill_color
     );
      al_draw_rounded_rectangle(0,
                                selector_y,
                                selector_rectangle_width,
                                selector_y+line_height,
                                4,
                                4,
                                selector_outline_color,
                                2.0);

      if (component.is_mode_navigating_list())
      {
         // halo
         int max_outset = 18 + 7 * std::sin(al_get_time() * 3); // is actually animated, but only visible
                                                             // when every frame is rendering
         for (int outset=1; outset<max_outset; outset++)
         {
           float color_opacity = (1.0 - (float)outset / max_outset) * 0.25;
           ALLEGRO_COLOR col = color::color(halo_color, color_opacity);
           al_draw_rounded_rectangle(
             0 - outset,
             selector_y - outset,
             selector_rectangle_width + outset,
             selector_y + line_height + outset,
             2.0, 2.0, col, cursor_thickness);
         }
      }
   }
   else
   {
      al_draw_rounded_rectangle(0,
                                selector_y,
                                selector_rectangle_width,
                                selector_y+line_height,
                                4,
                                4,
                                selector_outline_color,
                                3.0);
   }


   // draw the project root (window title)

   ALLEGRO_COLOR node_root_font_color = frame_color_bluegreen;
   ALLEGRO_FONT* title_text_font = obtain_title_text_font();
   std::string node_root_val = component.get_project_root();
   float title_text_font_width = al_get_text_width(title_text_font, node_root_val.c_str());
   float title_text_font_height = al_get_font_line_height(title_text_font);
   float title_y = (title_text_font_height * -1.3) * 2;

   al_draw_filled_rectangle(
      0 - padding_x,
      title_y - padding_x,
      place.size.x + padding_x,
      //title_text_font_width,
      title_y + title_text_font_height + padding_y,
      node_root_font_color
      //backfill_color
   );
   al_draw_text(
      title_text_font,
      //node_root_font_color,
      backfill_color,
      0,
      title_y,
      0,
      node_root_val.c_str()
   );


   // draw the search_text

   draw_search_text_box();


   // draw list elements

   bool list_clipping_occurred_above = false;
   bool list_clipping_occurred_below = false;

   for (auto &node : component.get_nodes())
   {
     std::string line_content = node.get_name();
     //ALLEGRO_COLOR base_text_color = al_color_name("skyblue");
     ALLEGRO_COLOR global_base_text_color = get_base_text_color();
     ALLEGRO_COLOR local_base_text_color = color::mix(global_base_text_color, color::cyan, 0.8);
     ALLEGRO_COLOR col; //
      //color::mix(base_text_color, al_color_name("chartreuce"), 0.4);

     bool this_line_is_clipped = false;

     if (node.has_quintessence())
     {
        col = color::mix(local_base_text_color, color::aqua, 0.4);
        //line_content += " *";
     }
     else if (node.has_only_source_and_header())
     {
        col = color::mix(local_base_text_color, color::aqua, 0.4);
        col = color::mix(col, color::green, 0.15);
     }
     else if (!node.exists())
     {
        col = al_color_name("red");
     }
     else
     {
        col = color::mix(local_base_text_color, color::aqua, 0.5);
        //col = color::color(col, 0.4);
     }

     //if (!node.has_test()) line_content += " (missing test)";

     float final_y = cursor_y;
     // clip the region of text displayed in the list
     if (final_y < 0)
     {
        list_clipping_occurred_above = true;
        this_line_is_clipped = true;
     }
     else if ((final_y + line_height) > place.size.y)
     {
        list_clipping_occurred_below = true;
        this_line_is_clipped = true;
     }

     if (!this_line_is_clipped) al_draw_text(font, col, 0, cursor_y, 0, line_content.c_str());

     cursor_y += line_height;
   }


   // draw list clipping hint arrows

   float list_extension_indicator_radius = 30;
   if (list_clipping_occurred_above)
   {
      Hexagon::Shapes::Hexagon::Renderer(
          place.size.x - list_extension_indicator_radius,
          list_extension_indicator_radius,
          list_extension_indicator_radius,
          {
            { 9, 3, frame_color_bluegreen, line_stroke_thickness },
          }
        ).render();
   }
   if (list_clipping_occurred_below)
   {
      Hexagon::Shapes::Hexagon::Renderer(
          place.size.x - list_extension_indicator_radius,
          place.size.y - list_extension_indicator_radius,
          list_extension_indicator_radius,
          {
            { 3, 9, frame_color_bluegreen, line_stroke_thickness },
          }
        ).render();
   }


   // draw the input hints

   draw_input_hints();


   return;
}

ALLEGRO_FONT* Renderer::obtain_title_text_font()
{
   //return font_bin->auto_get("Eurostile.ttf -18");
   return font_bin->auto_get("Purista Medium.otf -22");
}


} // namespace AdvancedComponentNavigator
} // namespace Hexagon


