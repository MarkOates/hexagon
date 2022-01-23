

#include <Hexagon/ObjectivesLog/ObjectiveRenderer.hpp>
#include <allegro5/allegro_primitives.h>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace ObjectivesLog
{


ObjectiveRenderer::ObjectiveRenderer(AllegroFlare::FontBin* font_bin, Hexagon::ObjectivesLog::Objective* objective, float width, float height)
   : font_bin(font_bin)
   , objective(objective)
   , width(width)
   , height(height)
   , is_activated(false)
{
}


ObjectiveRenderer::~ObjectiveRenderer()
{
}


void ObjectiveRenderer::set_is_activated(bool is_activated)
{
   this->is_activated = is_activated;
}


bool ObjectiveRenderer::get_is_activated()
{
   return is_activated;
}


void ObjectiveRenderer::render()
{
   if (!(al_is_system_installed()))
      {
         std::stringstream error_message;
         error_message << "ObjectiveRenderer" << "::" << "render" << ": error: " << "guard \"al_is_system_installed()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_font_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "ObjectiveRenderer" << "::" << "render" << ": error: " << "guard \"al_is_font_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_primitives_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "ObjectiveRenderer" << "::" << "render" << ": error: " << "guard \"al_is_primitives_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(objective))
      {
         std::stringstream error_message;
         error_message << "ObjectiveRenderer" << "::" << "render" << ": error: " << "guard \"objective\" not met";
         throw std::runtime_error(error_message.str());
      }
   ALLEGRO_COLOR background_color = ALLEGRO_COLOR{0.0, 0.0, 0.0, 0.9};
   ALLEGRO_COLOR frame_color = ALLEGRO_COLOR{1.0, 1.0, 1.0, 1.0};
   float frame_thickness = 2.0;
   float frame_padding = frame_thickness * 2.5;
   float text_padding_x = 20;
   ALLEGRO_FONT *primary_text_font = obtain_primary_text_font();
   float font_line_height = al_get_font_line_height(primary_text_font);

   // draw backfill and frame
   al_draw_filled_rectangle(0, 0, width, height, background_color);
   al_draw_rectangle(
      0+frame_padding,
      0+frame_padding,
      width-frame_padding,
      height-frame_padding,
      frame_color,
      frame_thickness
   );
   //al_draw_text(text_padding_x
   return;
}

ALLEGRO_FONT* ObjectiveRenderer::obtain_primary_text_font()
{
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "ObjectiveRenderer" << "::" << "obtain_primary_text_font" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   return font_bin->auto_get("Purista Medium.otf -32");
}
} // namespace ObjectivesLog
} // namespace Hexagon

