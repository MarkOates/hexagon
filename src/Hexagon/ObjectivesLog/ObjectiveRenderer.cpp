

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
   al_draw_filled_rectangle(0, 0, width, height, background_color);
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


