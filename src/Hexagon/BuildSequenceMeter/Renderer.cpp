

#include <Hexagon/BuildSequenceMeter/Renderer.hpp>
#include <allegro5/allegro_color.h>
#include <Blast/FileExistenceChecker.hpp>
#include <allegro_flare/useful_php.h>
#include <allegro_flare/placement2d.h>
#include <AllegroFlare/Color.hpp>
#include <Hexagon/Elements/ColorKit.hpp>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <stdexcept>
#include <sstream>
#include <algorithm>
#include <map>
#include <string>
#include <allegro5/allegro_color.h>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace BuildSequenceMeter
{


Renderer::Renderer(AllegroFlare::FontBin* font_bin, std::string status, std::vector<std::tuple<std::string, std::string, std::string, std::string>> stages, float meter_width, float meter_height, ALLEGRO_COLOR backfill_color, ALLEGRO_COLOR base_text_color)
   : font_bin(font_bin)
   , status(status)
   , stages(stages)
   , meter_width(meter_width)
   , meter_height(meter_height)
   , backfill_color(backfill_color)
   , base_text_color(base_text_color)
   , draw_frame(false)
{
}


Renderer::~Renderer()
{
}


void Renderer::set_backfill_color(ALLEGRO_COLOR backfill_color)
{
   this->backfill_color = backfill_color;
}


void Renderer::set_base_text_color(ALLEGRO_COLOR base_text_color)
{
   this->base_text_color = base_text_color;
}


void Renderer::set_draw_frame(bool draw_frame)
{
   this->draw_frame = draw_frame;
}


ALLEGRO_COLOR Renderer::get_backfill_color() const
{
   return backfill_color;
}


ALLEGRO_COLOR Renderer::get_base_text_color() const
{
   return base_text_color;
}


bool Renderer::get_draw_frame() const
{
   return draw_frame;
}


void Renderer::render()
{
   ALLEGRO_COLOR color = ALLEGRO_COLOR{0.2, 0.2, 0.2, 0.2};
   ALLEGRO_FONT *font = obtain_font();

   // draw_frame
   if (get_draw_frame())
   {
      al_draw_rectangle(0, 0, meter_width, meter_height, ALLEGRO_COLOR{0.1, 0.1, 0.1, 0.1}, 2.0);
   }

   if (stages.empty()) return;

   int num_stages = stages.size();
   float box_height = meter_height / (num_stages * 2 - 1);
   float box_width = meter_width;
   float box_spacing = box_height;

   float cursor_y = meter_height - box_height;
   for (auto &stage : stages)
   {
      std::string PATH_TO_BUILD_DUMPS = "/Users/markoates/Repos/hexagon/bin/programs/data/builds/dumps/";
      std::string stage_result_dump_filename = std::get<3>(stage); // currently not used, but hopefully soon :)
      std::string stage_status = std::get<2>(stage);
      std::string stage_label = std::get<1>(stage);
      std::string sequence_dump_full_path = PATH_TO_BUILD_DUMPS + stage_result_dump_filename;
      bool expecting_stage_to_have_file = !stage_result_dump_filename.empty();
      bool stage_dump_path_exists = expecting_stage_to_have_file
                                  && Blast::FileExistenceChecker(sequence_dump_full_path).exists();

      if (expecting_stage_to_have_file)
      {
         ALLEGRO_COLOR stage_box_color = build_color_from_status(stage_status);
         if (stage_dump_path_exists)
         {
            al_draw_filled_rectangle(0-6, cursor_y, 0-3, cursor_y+box_height, stage_box_color);
         }
         else
         {
            al_draw_rectangle(0-6, cursor_y, 0-3, cursor_y+box_height, stage_box_color, 1.0);
         }
      }

      if (stage_dump_path_exists)
      {
         Hexagon::Elements::ColorKit color_kit;
         //ALLEGRO_COLOR dump_text_color = al_color_html("ffa500");
         //ALLEGRO_COLOR stage_box_color = build_color_from_status(stage_status);
         //al_draw_filled_rectangle(0-6, cursor_y, 0-3, cursor_y+box_height, stage_box_color);

         if (is_status_to_draw_label(stage_status))
         {
            ALLEGRO_FONT *dump_font = obtain_dump_font();
            float font_line_height = al_get_font_line_height(dump_font);
            //ALLEGRO_COLOR dump_text_color = al_color_html("ffa500");
            ALLEGRO_COLOR bg_trans_color = AllegroFlare::Color(backfill_color, 0.3).to_al(); //ALLEGRO_COLOR{0.0, 0.0, 0.0, 0.3};
            ALLEGRO_COLOR dump_text_color = color_kit.terminal_warm_orange();
               //al_color_html("ffa500");

            placement2d dump_place;
            dump_place.scale = vec2d(0.8, 0.8);
            dump_place.position = vec2d(-10, 0);
            dump_place.align = vec2d(1.0, 0.0);
            dump_place.size = vec2d(1000, 900);

            dump_place.start_transform();
            
            //ALLEGRO_COLOR bg_trans_color = AllegroFlare::Color(backfill_color, 0.3); //ALLEGRO_COLOR{0.0, 0.0, 0.0, 0.3};
            al_draw_filled_rectangle(0, 0, dump_place.size.x, dump_place.size.y, bg_trans_color);

            std::string stage_text_dump = php::file_get_contents(sequence_dump_full_path);
            al_draw_multiline_text(dump_font, dump_text_color, 0, 0, dump_place.size.x, font_line_height, ALLEGRO_ALIGN_LEFT,
               stage_text_dump.c_str()
            );

            dump_place.restore_transform();
         }
      }

      //ALLEGRO_COLOR box_color = build_color_from_status(stage_status);
      draw_status_box(0, cursor_y, box_width, cursor_y+box_height, stage_status, stage_label);

      cursor_y -= (box_height + box_spacing);
   }

   return;
}

void Renderer::draw_status_box(float x, float y, float w, float h, std::string status, std::string label)
{
   if (!(al_is_system_installed()))
      {
         std::stringstream error_message;
         error_message << "Renderer" << "::" << "draw_status_box" << ": error: " << "guard \"al_is_system_installed()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_primitives_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "Renderer" << "::" << "draw_status_box" << ": error: " << "guard \"al_is_primitives_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_ttf_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "Renderer" << "::" << "draw_status_box" << ": error: " << "guard \"al_is_ttf_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "Renderer" << "::" << "draw_status_box" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   // statuses:
   //   incomplete: nothing has run yet
   //   running: current step is being executed and will show results once processed
   //   failed: current step failed
   //   succeeded: current step succeeded

   ALLEGRO_COLOR color = build_color_from_status(status);
   if (is_status_to_draw_label(status))
   {
      ALLEGRO_FONT *font = obtain_font();
      if (!font)
      {
         // TODO
      }
      else
      {
         float actual_height = h - y;
         al_draw_text(
            obtain_font(),
            color,
            x + w * 0.5,
            y + actual_height * 0.5 - al_get_font_line_height(font)*0.5 - 1,
            ALLEGRO_ALIGN_CENTER,
            label.c_str()
         );
      }
   }
   al_draw_rectangle(x, y, w, h, color, 1.0);
   //al_draw_rectangle(x, y, w, h, ALLEGRO_COLOR{0.1, 0.1, 0.1, 0.1}, 1.0);

   return;
}

bool Renderer::is_status_to_draw_label(std::string status)
{
   std::vector<std::string> states_that_will_render_label = {
      "running",
      "failed",
      "succeeded",
      "finished",
   };
   std::vector<std::string>::iterator find_iterator;
   find_iterator = std::find(states_that_will_render_label.begin(), states_that_will_render_label.end(), status);
   bool was_found = (find_iterator != states_that_will_render_label.end());
   return was_found;
}

ALLEGRO_COLOR Renderer::build_color_from_status(std::string status)
{
   ALLEGRO_COLOR result;

   std::map<std::string, ALLEGRO_COLOR> status_colors = {
      { "finished", al_color_html("116568") },
      { "running", al_color_html("eae049") },
      { "not_started", ALLEGRO_COLOR{0.2, 0.2, 0.2, 0.2} },
      { "passed", al_color_html("82e499") },
      { "failed", al_color_html("b22222") },
   };

   std::map<std::string, ALLEGRO_COLOR>::iterator it = status_colors.find(status);
   if (it == status_colors.end()) return al_color_html("333333");

   return it->second;
}

ALLEGRO_FONT* Renderer::obtain_dump_font()
{
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "Renderer" << "::" << "obtain_dump_font" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   float scale = 1.45;
   int font_size = -10 * scale;
   std::stringstream ident;
   ident << "Purista Medium.otf " << (int)(font_size * scale);
   return font_bin->auto_get(ident.str());
}

ALLEGRO_FONT* Renderer::obtain_font()
{
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "Renderer" << "::" << "obtain_font" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   return font_bin->auto_get("Purista Medium.otf -20");
}
} // namespace BuildSequenceMeter
} // namespace Hexagon


