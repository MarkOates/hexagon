

#include <Hexagon/ProjectComponentNavigator/Renderer.hpp>

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
namespace ProjectComponentNavigator
{


Renderer::Renderer(Hexagon::ProjectComponentNavigator::Stage* stage, ALLEGRO_FONT* font, int cell_width, int cell_height, ALLEGRO_COLOR* base_backfill_color, float backfill_opacity, ALLEGRO_COLOR* base_text_color)
   : stage(stage)
   , font(font)
   , cell_width(cell_width)
   , cell_height(cell_height)
   , base_backfill_color(base_backfill_color)
   , backfill_opacity(backfill_opacity)
   , base_text_color(base_text_color)
   , line_stroke_thickness(2.5f)
{
}


Renderer::~Renderer()
{
}


ALLEGRO_COLOR* Renderer::get_base_backfill_color() const
{
   return base_backfill_color;
}


ALLEGRO_COLOR* Renderer::get_base_text_color() const
{
   return base_text_color;
}


ALLEGRO_COLOR Renderer::build_backfill_color()
{
   if (!(base_backfill_color))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::ProjectComponentNavigator::Renderer::build_backfill_color]: error: guard \"base_backfill_color\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::ProjectComponentNavigator::Renderer::build_backfill_color]: error: guard \"base_backfill_color\" not met");
   }
   ALLEGRO_COLOR result_backfill_color = color::color(*base_backfill_color, 0.8);
   return result_backfill_color;
}

ALLEGRO_COLOR Renderer::build_text_color()
{
   if (!(base_text_color))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::ProjectComponentNavigator::Renderer::build_text_color]: error: guard \"base_text_color\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::ProjectComponentNavigator::Renderer::build_text_color]: error: guard \"base_text_color\" not met");
   }
   ALLEGRO_COLOR result_text_color = color::color(*base_text_color, 0.8);
   return result_text_color;
}

ALLEGRO_COLOR Renderer::build_frame_color()
{
   if (!(base_text_color))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::ProjectComponentNavigator::Renderer::build_frame_color]: error: guard \"base_text_color\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::ProjectComponentNavigator::Renderer::build_frame_color]: error: guard \"base_text_color\" not met");
   }
   return al_color_html("39c3c5");
   //ALLEGRO_COLOR result_frame_color = color::color(*base_text_color, 0.8);
   //return result_frame_color;
}

float Renderer::build_line_height()
{
   return cell_height * 1.1;
}

void Renderer::draw_search_text_box()
{
   // draw the search_text
   Hexagon::ProjectComponentNavigator::Stage &stage = *this->stage;
   Hexagon::ProjectComponentNavigator::ProjectComponentNavigator &component = stage.get_component_ref();

   ALLEGRO_COLOR backfill_color = build_backfill_color();
   bool focus_is_search_bar = component.is_mode_typing_in_search_bar();

   ALLEGRO_COLOR search_text_font_color = focus_is_search_bar ? al_color_name("chartreuse") : build_frame_color();
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

void Renderer::render()
{
   if (!(stage))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::ProjectComponentNavigator::Renderer::render]: error: guard \"stage\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::ProjectComponentNavigator::Renderer::render]: error: guard \"stage\" not met");
   }
   if (!(font))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::ProjectComponentNavigator::Renderer::render]: error: guard \"font\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::ProjectComponentNavigator::Renderer::render]: error: guard \"font\" not met");
   }
   placement3d &place = stage->get_place();
   place.start_transform();
   render_raw();
   place.restore_transform();
   return;
}

void Renderer::render_window_raw()
{
   Hexagon::ProjectComponentNavigator::Stage &stage = *this->stage;
   placement3d &place = stage.get_place();

   // draw backfill and outline

   float roundness = 0.0; //6.0;
   float padding_x = cell_width;
   float padding_y = cell_width;
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
      roundness, roundness, build_frame_color(), line_stroke_thickness);

   return;
}

void Renderer::render_cursor_box_raw()
{
   Hexagon::ProjectComponentNavigator::Stage &stage = *this->stage;
   Hexagon::ProjectComponentNavigator::ProjectComponentNavigator &component = stage.get_component_ref();


   // draw cursor box for focused line

   int line = 0;
   int line_height = build_line_height();
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
   return;
}

void Renderer::render_window_title_raw()
{
   Hexagon::ProjectComponentNavigator::Stage &stage = *this->stage;
   Hexagon::ProjectComponentNavigator::ProjectComponentNavigator &component = stage.get_component_ref();
   ALLEGRO_COLOR backfill_color = build_backfill_color();

   // draw the project root (window title)

   ALLEGRO_COLOR node_root_font_color = build_frame_color();
   std::string node_root_val = component.get_project_root();
   float title_text_width = al_get_text_width(font, node_root_val.c_str());
   float title_text_height = al_get_font_line_height(font);
   float title_y = (title_text_height * -1.3) * 2;
   al_draw_filled_rectangle(0, title_y, title_text_width, title_y+title_text_height, backfill_color);
   al_draw_text(font, node_root_font_color, 0, title_y, 0, node_root_val.c_str());

   return;
}

std::pair<bool, bool> Renderer::render_list_elements_raw()
{
   Hexagon::ProjectComponentNavigator::Stage &stage = *this->stage;
   Hexagon::ProjectComponentNavigator::ProjectComponentNavigator &component = stage.get_component_ref();
   placement3d &place = stage.get_place();

   // draw list elements

   bool list_clipping_occurred_above = false;
   bool list_clipping_occurred_below = false;

   int cursor_y = 0;
   int line_height = build_line_height();
   if (component.get_cursor_position_static())
   {
     cursor_y = - line_height * component.get_cursor_position();
   }

   for (auto &node : component.get_nodes())
   {
     std::string line_content = node.get_concept_name();
     //ALLEGRO_COLOR base_text_color = al_color_name("skyblue");
     ALLEGRO_COLOR global_base_text_color = *get_base_text_color();
     ALLEGRO_COLOR local_base_text_color = color::mix(global_base_text_color, color::cyan, 0.8);
     ALLEGRO_COLOR col; //
      //color::mix(base_text_color, al_color_name("chartreuce"), 0.4);

     bool this_line_is_clipped = false;

     col = color::mix(local_base_text_color, color::aqua, 0.9);

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
   return std::pair<bool, bool>(list_clipping_occurred_above, list_clipping_occurred_below);
}

void Renderer::render_list_clipping_arrows_raw(bool list_clipping_occurred_above, bool list_clipping_occurred_below)
{
   Hexagon::ProjectComponentNavigator::Stage &stage = *this->stage;
   Hexagon::ProjectComponentNavigator::ProjectComponentNavigator &component = stage.get_component_ref();
   placement3d &place = stage.get_place();
   float list_extension_indicator_radius = 30;
   if (list_clipping_occurred_above)
   {
      Hexagon::Shapes::Hexagon::Renderer(
          place.size.x - list_extension_indicator_radius,
          list_extension_indicator_radius,
          list_extension_indicator_radius,
          {
            { 9, 3, build_frame_color(), line_stroke_thickness },
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
            { 3, 9, build_frame_color(), line_stroke_thickness },
          }
        ).render();
   }
   return;
}

void Renderer::render_raw()
{
   if (!(stage))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::ProjectComponentNavigator::Renderer::render_raw]: error: guard \"stage\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::ProjectComponentNavigator::Renderer::render_raw]: error: guard \"stage\" not met");
   }
   if (!(font))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::ProjectComponentNavigator::Renderer::render_raw]: error: guard \"font\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::ProjectComponentNavigator::Renderer::render_raw]: error: guard \"font\" not met");
   }
   if (!(base_text_color))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::ProjectComponentNavigator::Renderer::render_raw]: error: guard \"base_text_color\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::ProjectComponentNavigator::Renderer::render_raw]: error: guard \"base_text_color\" not met");
   }
   render_window_raw();

   render_cursor_box_raw();

   render_window_title_raw();

   std::pair<bool, bool> clipping_result = render_list_elements_raw();


   bool list_clipping_occurred_above = clipping_result.first;
   bool list_clipping_occurred_below = clipping_result.second;


   // draw the search_text

   draw_search_text_box();


   // draw list clipping hint arrows

   render_list_clipping_arrows_raw(list_clipping_occurred_above, list_clipping_occurred_below);
   return;
}


} // namespace ProjectComponentNavigator
} // namespace Hexagon


